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

#ifndef _GST_EVENT_QEVENT_H
#define	_GST_EVENT_QEVENT_H

#include <map>
#include <initializer_list>
#include <cinttypes>

#include "../tools/api.h"
#include "../types/any.hpp"
#include "parameter.h"

namespace gst {
	namespace event {

		class qevent {
		public:
			typedef uint64_t event_id;
			typedef uint64_t target_id;

		  explicit qevent(event_id evID, target_id targetID = 0, const std::initializer_list<std::pair<std::string, parameter> >& parameters = std::initializer_list<std::pair<std::string, parameter> >());
			qevent(const qevent& other);
			virtual ~qevent();
			qevent& operator =(const qevent& other);

			event_id eventID() const;

			target_id targetID() const;

			void setParameter(const std::string& name, const any& data);

			template<typename T>
			T param(const char* name) const {
				std::string sname(name);

        return gst::any_cast<T>(m_parameters.at(sname).data());
			}

			template<typename T>
			T param(const std::string& name) const {

				return gst::any_cast<T>(m_parameters.at(name).data());
			}

			const std::string& name() const;
			const std::string& description() const;

		private:
			std::map<std::string, parameter> m_parameters;
			event_id m_eventID;
			target_id m_targetID;
			std::string m_name;
			std::string m_description;
		};

		inline const std::string& qevent::name() const {
			return m_name;
		}

		inline const std::string& qevent::description() const {
			return m_description;
		}

		inline void qevent::setParameter(const std::string& name, const any& data) {
			if (name.empty()) {
				return;
			}

			m_parameters[name] = data;
		}

		inline qevent::event_id qevent::eventID() const {
			return m_eventID;
		}

		inline qevent::target_id qevent::targetID() const {
			return m_targetID;
		}

	}
}

#endif	/* _GST_EVENT_QEVENT_H */

