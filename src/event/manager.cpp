/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Walter Julius Hennecke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "manager.h"

namespace gst {
	namespace event {

		manager::manager() 
			: m_nextId(1) {
		}

		manager::manager(const manager& other) 
			: m_queue(other.m_queue)
			, m_nextId(other.m_nextId)
			, m_listListeners(other.m_listListeners) {
		}

		manager::~manager() {
		}

		manager& manager::operator =(const manager& other) {
			m_nextId = other.m_nextId;
			m_listListeners = other.m_listListeners;
			m_queue = other.m_queue;

			return *this;
		}

		void manager::registerListener(listener* l) {
			for (auto n : m_listListeners) {
				if (n == l) {
					return;
				}
			}

			l->setID(m_nextId);
			m_nextId++;
			m_listListeners.insert(m_listListeners.end(), l);
		}

		void manager::removeListener(listener* l) {
			m_listListeners.remove(l);
		}

		void manager::push(const qevent& ev) {
			m_queue.push(ev);
		}

		void manager::progressEvents() {

			for (auto l : m_listListeners) {
				l->appendQueue(m_queue);
				l->progressEvents();
			}

			m_queue.clear();
		}

		manager& manager::operator <<(const qevent& ev) {
			m_queue.push(ev);

			return *this;
		}

		manager& manager::operator <<(listener* l) {
			if (l == nullptr) {
				return *this;
			}

			m_listListeners.insert(m_listListeners.end(), l);

			return *this;
		}

		manager& manager::operator <<(const queue& q) {
		  auto n = q;

			while (n.empty() == false) {
				m_queue.push(n.pop());
			}

			return *this;
		}

		manager& manager::operator >>(listener* l) {
			if (l == nullptr) {
				return *this;
			}

			m_listListeners.remove(l);

			return *this;
		}

	}
}
