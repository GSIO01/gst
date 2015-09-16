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

#ifndef _GST_EVENT_PARAMETER_H
#define	_GST_EVENT_PARAMETER_H

#include <string>

#include "../tools/api.h"
#include "../types/any.hpp"

namespace gst {
	namespace event {

		class parameter {
		public:
			parameter();
		  explicit parameter(const any& data);
			parameter(const parameter& other);
			parameter(const std::string& name, const std::string& description, const any& data = any());
			virtual ~parameter();
			parameter& operator =(const parameter& other);
      parameter& operator =(const any& other);

			const any& data() const;
			const std::string& name() const;
			const std::string& description() const;
		private:
			any m_data;
			std::string m_name;
			std::string m_description;
		};

		inline const any& parameter::data() const {
			return m_data;
		}

		inline const std::string& parameter::name() const {
			return m_name;
		}

		inline const std::string& parameter::description() const {
			return m_description;
		}

	}
}

#endif	/* _GST_EVENT_PARAMETER_H */

