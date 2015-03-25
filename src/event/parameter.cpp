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

#include "parameter.h"

namespace gst {
	namespace event {

		parameter::parameter() {
		}

		parameter::parameter(const any& data)
			: m_data(data) {
		}

		parameter::parameter(const parameter& other)
			: m_data(other.m_data)
			, m_name(other.m_name)
			, m_description(other.m_description) {
		}

		parameter::parameter(const std::string& name, const std::string& description, const any& data /* = any() */)
			: m_data(data)
			, m_name(name)
			, m_description(description) {
		}

		parameter::~parameter() {
		}

		parameter& parameter::operator =(const parameter& other) {
			m_data = other.m_data;
			m_name = other.m_name;
			m_description = other.m_description;

			return *this;
		}

	}
}

