#ifndef _GST_TYPES_ANY_H
#define _GST_TYPES_ANY_H

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

#include <typeinfo>
#include <algorithm>

namespace gst {

	class any {
		public:
		any() : content(0) {
		}

		~any() {
			delete content;
		}

		const std::type_info& type_info() const {
			return content ? content->type_info() : typeid(void);
		}

		any(const any& other) : content(other.content ? other.content->clone() : 0) {
		}

		template<typename value_type>
		any(const value_type& value) : content(new holder<value_type>(value)) {
		}

		any& swap(any rhs) {

			std::swap(content, rhs.content);
			return *this;
		}

		any& operator=(const any& rhs) {
			return swap(any(rhs));
		}

		template<typename value_type>
		any& operator=(const value_type& rhs) {
			return swap(any(rhs));
		}

		operator const void* () const {
			return content;
		}

		template<typename value_type>
		bool copy_to(value_type& value) const {
			const value_type* copyable = to_ptr<value_type>();

			if (copyable) {
				value = *copyable;
			}

			return copyable;
		}

		template<typename value_type>
		const value_type* to_ptr() const {
			return type_info() == typeid(value_type) ? &static_cast<holder<value_type> *>(content)->held : nullptr;
		}

		private:
		class placeholder {
			public:
			virtual ~placeholder() {
			}

			virtual const std::type_info& type_info() const = 0;

			virtual placeholder *clone() const = 0;
		};

		template<typename value_type>
		class holder : public placeholder {
			public:
			holder(const value_type& value) : held(value) {
			}

			virtual const std::type_info& type_info() const {
				return typeid(value_type);
			}

			virtual placeholder* clone() const {
				return new holder(held);
			}

			const value_type held;
		};

		placeholder* content;
	};

	template<typename value_type>
	value_type any_cast(const any& operand) {
		const value_type* result = operand.to_ptr<value_type>();

		return result ? *result : throw std::bad_cast();
	}

}

#endif /* _GST_TYPES_ANY_H */
