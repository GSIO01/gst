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

#include <utility>
#include "fsm.h"
#include "fevent.h"
#include "transition.h"

namespace gst::fsm
{
  /**
   * @brief Base class for finite state machines.
   */
  class machine
  {
  public:
    machine() : m_state{} {}

    /**
     * @brief Constructor.
     */
    explicit machine(fsm_state state, transition_table transition_tab)
      : m_transitiontable(std::move(transition_tab)), m_state(state)
    {}

    /**
     * @brief Copy constructor.
     * @param other Object to copy.
     */
    machine(const machine &other) = default;

    /**
     * @brief Destructor.
     */
    virtual ~machine() = default;

    /**
     * @brief Assignment operator.
     * @param other Object to assign.
     * @return This object.
     */
    machine &operator=(const machine &other) = default;

    /**
     * @brief Get the current state of the finite state mashine.
     * @return Current state.
     */
    fsm_state state() const
    {
      return m_state;
    }

    /**
     * @brief Change the state of the fsm.
     * @param state New state.
     */
    void setState(fsm_state state)
    {
      m_state = state;
    }

    /**
     * @brief Replace the transition table of the fsm.
     * @param transition_tab New transition table.
     */
    void setTransitionTable(const transition_table &transition_tab)
    {
      m_transitiontable = transition_tab;
    }

    /**
     * @brief Process an event.
     * @param ev Event to process.
     * @return True on success, false on error.
     */
    bool processEvent(const fevent &ev);

  protected:
    transition_table m_transitiontable;
    fsm_state m_state;
  };
}
