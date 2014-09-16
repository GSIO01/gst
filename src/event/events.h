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

#ifndef EVENTS_H
#define	EVENTS_H

/* Required includes */
#include <functional>

#define EVENT_REGISTER(EVENT_ID, EVENT_HANDLER) m_eventMap.insert(std::make_pair(EVENT_ID, std::bind(EVENT_HANDLER, this, std::placeholders::_1)));
#define EVENT_DECLARE(CLASSNAME) private: \
										 std::map<gst::event::event_id, gst::event::function_ptr> m_eventMap; \
                                 public: \
                                          virtual void progressEvents(); \
                                          virtual void registerEvents();
#define EVENT_IMPLEMENT(CLASSNAME) void test_class::progressEvents() { \
										\
										if (m_eventMap.empty()) { \
											return; \
										} \
										\
										while (m_queue.empty() == false) { \
											gst::event::qevent ev = m_queue.pop(); \
											\
											if (ev.eventID() == gst::event::EV_GLOBAL_EMPTY) { \
												continue;  \
											} \
											\
											if (ev.targetID() != 0 && ev.targetID() != m_id) { \
												continue;  \
											}  \
											\
											if (m_eventMap.find(ev.eventID()) == m_eventMap.end()) { \
												continue;  \
											}  \
											\
											m_eventMap[ev.eventID()](ev); \
										} \
									}

namespace gst {
	namespace event {

		typedef enum {
			EV_GLOBAL_EMPTY,
			EV_GLOBAL_MAX
		} global_events;

		typedef unsigned long event_id;

		class qevent;
		typedef std::function<void(const qevent& ev)> function_ptr;
	}
}

#endif	/* EVENTS_H */

