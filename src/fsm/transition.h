/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Walter Julius Hennecke
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

#pragma once

#include <functional>
#include <vector>

#include "fevent.h"
#include "fsm.h"

#define TRANSITION(STATE,EVID,NEWSTATE,HANDLER) {STATE, EVID, NEWSTATE, std::bind(&HANDLER, this, std::placeholders::_1)}

namespace gst::fsm
{
  /**
   * @brief Structure of transition.
   */
  struct transition
  {
    fsm_state state; //!< Current state
    event_id ev; //!< Event id
    fsm_state new_state; //!< New state for event id
    std::function<void(const fevent&)> handler; //!< Handler function to call.
  };

  /**
   * @brief Transition table type.
   */
  typedef std::vector<transition> transition_table;
}
