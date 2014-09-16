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
#ifndef LISTENER_H
#define	LISTENER_H

#include "qevent.h"
#include "queue.h"

namespace gst {
	namespace event {

		class listener {
			public:
			listener(unsigned long id = 0);
			listener(const listener& other);
			virtual ~listener();
			listener& operator =(const listener& other);

			void appendQueue(const queue& q);
			void queueEvent(const qevent& ev);
			const queue& getQueue();
			virtual void registerEvents() = 0;
			virtual void progressEvents() = 0;
			unsigned long id() const;
			void setID(unsigned long id);
			protected:
			queue m_queue;
			unsigned long m_id;
		};

	}
}

#endif	/* LISTENER_H */

