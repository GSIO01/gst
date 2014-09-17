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

#include "qevent.h"

namespace gst {
	namespace event {

		qevent::qevent(event_id evID, unsigned long targetID) :
			m_eventID(evID),
			m_targetID(targetID) {
		}

		qevent::qevent(const qevent& other) :
			m_eventID(other.m_eventID),
			m_targetID(other.m_targetID),
			m_parameters(other.m_parameters) {
		}

		qevent::~qevent() {
		}

		qevent& qevent::operator =(const qevent& other) {
			m_eventID = other.m_eventID;
			m_targetID = other.m_targetID;
			m_parameters = other.m_parameters;

			return *this;
		}

		void qevent::setParameter(const std::string& name, const any& data) {
			if (name.empty()) {
				return;
			}

			m_parameters[name] = data;
		}

		event_id qevent::eventID() const {
			return m_eventID;
		}

		unsigned long qevent::targetID() const {
			return m_targetID;
		}

	}
}

