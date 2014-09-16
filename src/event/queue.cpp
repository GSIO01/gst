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

#include "queue.h"

namespace gst {
	namespace event {

		queue::queue() :
			m_event(EV_GLOBAL_EMPTY) {
		}

		queue::queue(const queue& other) :
			m_queue(other.m_queue),
			m_event(other.m_event) {
		}

		queue::~queue() {
		}

		queue& queue::operator =(const queue& other) {
			m_queue = other.m_queue;

			return *this;
		}

		void queue::push(const qevent& ev) {
			m_queue.insert(m_queue.end(), ev);
		}

		qevent& queue::pop() {
			if (m_queue.empty()) {
				m_event = qevent(EV_GLOBAL_EMPTY);
				return m_event;
			}

			m_event = m_queue.front();
			m_queue.pop_front();
			return m_event;
		}

		const std::list<qevent>& queue::getQueue() {
			return m_queue;
		}

		bool queue::empty() {
			return m_queue.empty();
		}

		void queue::clear() {
			m_queue.clear();
		}

		queue& queue::operator <<(const qevent& ev) {
			m_queue.insert(m_queue.end(), ev);

			return *this;
		}

		queue& queue::operator >>(qevent& ev) {
			ev = m_queue.front();
			m_queue.pop_front();

			return *this;
		}


	}
}

