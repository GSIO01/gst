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
#ifndef _GST_EVENT_LISTENER_H
#define	_GST_EVENT_LISTENER_H

#include "../tools/api.h"
#include "qevent.h"
#include "queue.h"

namespace gst {
	namespace event {

		class GSTAPI listener {
			public:
		  explicit listener(qevent::target_id id = 0);
			listener(const listener& other);
			virtual ~listener();
			listener& operator =(const listener& other);

			void appendQueue(const queue& q);
			void queueEvent(const qevent& ev);
			const queue& getQueue() const;
			virtual void registerEvents() = 0;
			virtual void progressEvents() = 0;
			qevent::target_id id() const;
			void setID(qevent::target_id id);
			protected:
			queue m_queue;
			qevent::target_id m_id;
		};

	}
}

#endif	/* _GST_EVENT_LISTENER_H */

