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

#ifndef QEVENT_H
#define	QEVENT_H

#include <map>
#include <string>

#include "../types/any.hpp"
#include "events.h"

namespace gst {
	namespace event {

		class qevent {
			public:
			qevent(event_id evID, unsigned long targetID = 0);
			qevent(const qevent& other);
			virtual ~qevent();
			qevent& operator =(const qevent& other);

			event_id eventID() const;

			unsigned long targetID() const;

			void setParameter(const std::string& name, const any& data);

			template<typename T>
			T parameter(const char* name) const {
				std::string sname(name);

				return gst::any_cast<T>(m_parameters.at(sname));
			}

			template<typename T>
			T parameter(const std::string& name) const {

				return gst::any_cast<T>(m_parameters.at(name));
			}

			private:
			std::map<std::string, any> m_parameters;
			event_id m_eventID;
			unsigned long m_targetID;
		};

	}
}

#endif	/* QEVENT_H */

