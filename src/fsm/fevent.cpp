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

#include "fevent.h"

namespace gst {
	namespace fsm {

		fevent::fevent(event_id id, const std::map<std::string, any>& parameters) :
			m_id(id),
			m_parameters(parameters)
		{
		}

		fevent::fevent(const fevent& other) :
			m_id(other.m_id),
			m_parameters(other.m_parameters)
		{
		}

		fevent::~fevent() {
		}

		fevent& fevent::operator =(const fevent& other) {
			m_id = other.m_id;
			m_parameters = other.m_parameters;

			return *this;
		}

		event_id fevent::id() const {
			return m_id;
		}

		void fevent::setParameter(const std::string& name, const any& data) {
			m_parameters.insert(std::make_pair(name, data));
		}
	}
}