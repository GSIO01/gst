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

#include "mashine.h"

namespace gst {
	namespace fsm {

		mashine::mashine(fsm_state state, const transition_table& transition_tab) :
			m_state(state),
			m_transitiontable(transition_tab)
		{
		}

		mashine::mashine(const mashine& other) :
			m_state(other.m_state),
			m_transitiontable(other.m_transitiontable)
		{
		}

		mashine::~mashine() {
		}

		mashine& mashine::operator =(const mashine& other) {
			m_state = other.m_state;
			m_transitiontable = other.m_transitiontable;

			return *this;
		}

		fsm_state mashine::state() const {
			return m_state;
		}

		void mashine::setState(fsm_state state) {
			m_state = state;
		}

		void mashine::setTransitionTable(const transition_table& transition_tab) {
			m_transitiontable = transition_tab;
		}

		bool mashine::processEvent(const fevent& ev) {
			for (const transition& tr : m_transitiontable) {
				if (tr.state == m_state && tr.ev == ev.id()) {
					m_state = tr.new_state;
					tr.handeler(ev);
					return true;
				}
			}

			return false;
		}

	}
}
