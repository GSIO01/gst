#pragma once

#include <memory>
#include <map>
#include <functional>
#include <cassert>
#include <utility>
#include <mutex>

namespace gst::event2 {
    namespace detail {
        class listenerStorageBase {
        public:
            using handle = size_t;

            virtual ~listenerStorageBase() = default;

            virtual bool remove(handle) = 0;
        };

        template<typename ListenerType>
        class listenerStorage : public listenerStorageBase {
        public:
            using handle = listenerStorageBase::handle;
            using container_type = std::map<handle, ListenerType>;
            using iterator = typename container_type::iterator;
            using const_iterator = typename container_type::const_iterator;

            iterator begin() {
                return m_listeners.begin();
            }

            iterator end() {
                return m_listeners.end();
            }

            const_iterator begin() const {
                return m_listeners.begin();
            }

            const_iterator end() const {
                return m_listeners.end();
            }

            const_iterator cbegin() const {
                return m_listeners.cbegin();
            }

            const_iterator cend() const {
                return m_listeners.cend();
            }

            size_t size() const {
                return m_listeners.size();
            }

            void clear() {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_listeners.clear();
            }

            handle addListener(ListenerType Listener) {
                std::lock_guard<std::mutex> lock(m_mutex);
                auto current = m_next++;
                m_listeners[current] = Listener;
                return current;
            }

            bool remove(handle handle) override {
                std::lock_guard<std::mutex> lock(m_mutex);

                auto it = m_listeners.find(handle);
                if (it == m_listeners.end()) {
                    return false;
                }

                m_listeners.erase(handle);
                return true;
            }

            std::unique_lock<std::mutex> lock() {
                return std::unique_lock<std::mutex>{m_mutex};
            }

            ~listenerStorage() override = default;

        private:
            handle m_next = 0;
            std::map<handle, ListenerType> m_listeners;
            std::mutex m_mutex;
        };
    }

    class connection {
    public:
        using handle = typename detail::listenerStorageBase::handle;

        connection() = default;

        connection(const connection &) = delete;

        connection(connection &&) = default;

        connection &operator=(const connection &) = delete;

        connection &operator=(connection &&) = default;

        connection(std::weak_ptr<detail::listenerStorageBase> listenerStorage, handle handle)
                : m_handle{handle}, m_listenerStorage{std::move(listenerStorage)} {}

        void disconnect() {
            if (auto ptr = m_listenerStorage.lock()) {
                ptr->remove(m_handle);
            }
        }

        virtual ~connection() = default;

    protected:
        handle m_handle{0};
        std::weak_ptr<detail::listenerStorageBase> m_listenerStorage;
    };

    class scopedConnection : public connection {
    public:
        scopedConnection() = default;

        scopedConnection(scopedConnection &&) = default;

        scopedConnection(connection &&other)
                : connection{std::forward<connection>(other)} {}

        scopedConnection &operator=(scopedConnection &&) = default;

        scopedConnection &operator=(connection &&other) {
            connection::operator=(std::forward<connection>(other));
            return *this;
        }

        ~scopedConnection() override {
            disconnect();
        }
    };

    template<typename>
    class event;

    template<typename Ret, typename... Args>
    class event<Ret(Args...)> {
    public:
        event() = default;

        event(const event &) = delete;

        event(event &&) = default;

        event &operator=(const event &) = delete;

        event &operator=(event &&) = default;

        using ListenerType = std::function<Ret(Args...)>;
        using result_type = typename ListenerType::result_type;
        using Handle = typename detail::listenerStorage<ListenerType>::handle;

        void operator()(Args... args) {
            auto lock = m_listenerStorage->lock();

            if (m_emitting) {
                assert(false);
                return;
            }
            m_emitting = true;

            for (const auto &l : *m_listenerStorage) {
                l.second(args...);
            }

            m_emitting = false;
        }

        template<typename L>
        connection operator+=(L &&listener) {
            return connect(std::forward<L>(listener));
        }

        connection connect(ListenerType listener) {
            auto h = m_listenerStorage->addListener(listener);
            return connection{m_listenerStorage, h};
        }

        void disconnect(connection &con) {
            con.disconnect();
        }

        void disconnectAll() {
            m_listenerStorage->clear();
        }

    private:
        std::shared_ptr<detail::listenerStorage<ListenerType> > m_listenerStorage = std::make_shared<detail::listenerStorage<ListenerType>>();
        bool m_emitting = false;
    };
}
