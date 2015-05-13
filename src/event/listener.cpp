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

#include "listener.h"

namespace gst {
	namespace event {

		listener::listener(qevent::target_id id) :
			m_id(id) {
		}

		listener::listener(const listener& other) :
			m_queue(other.m_queue),
			m_id(other.m_id) {
		}

		listener::~listener() {
		}

		listener& listener::operator =(const listener& other) {
			m_queue = other.m_queue;
			m_id = other.m_id;

			return *this;
		}

		const queue& listener::getQueue() const {
			return m_queue;
		}

		void listener::queueEvent(const qevent& ev) {
			m_queue.push(ev);
		}

		qevent::target_id listener::id() const {
			return m_id;
		}

		void listener::setID(qevent::target_id id) {
			m_id = id;
		}

		void listener::appendQueue(const queue& q) {
		  auto t = q;

			while (t.empty() == false) {
				m_queue.push(t.pop());
			}
		}

	}
}
