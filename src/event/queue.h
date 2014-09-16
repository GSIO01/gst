/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Walter Julius Hennecke
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

#ifndef QUEUE_H
#define	QUEUE_H

#include <list>

#include "qevent.h"

namespace gst {
	namespace event {

		class queue {
			public:
			queue();
			queue(const queue& other);
			virtual ~queue();
			queue& operator =(const queue& other);

			bool empty();
			void clear();
			void push(const qevent& ev);
			qevent& pop();
			const std::list<qevent>& getQueue();

			queue& operator <<(const qevent& ev);
			queue& operator >>(qevent& ev);
			private:
			std::list<qevent> m_queue;
			qevent m_event;
		};

	}
}

#endif	/* QUEUE_H */

