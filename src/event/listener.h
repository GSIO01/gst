/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Walter Julius Hennecke
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

#include "../tools/api.h"
#include "qevent.h"
#include <queue>

namespace gst::event
{
  class listener
  {
  public:
    explicit listener(qevent::target_id id = 0) : m_id{id} {}

    listener(const listener& Other)
      : m_queue{Other.m_queue}
      , m_id{Other.m_id} {}

    listener(listener&& Other) noexcept
      : m_queue{std::move(Other.m_queue)}
      , m_id{Other.m_id} {}

    virtual ~listener() = default;

    listener& operator=(const listener& Other)
    {
      if (this == &Other)
        return *this;
      m_queue = Other.m_queue;
      m_id = Other.m_id;
      return *this;
    }

    listener& operator=(listener&& Other) noexcept
    {
      if (this == &Other)
        return *this;
      m_queue = std::move(Other.m_queue);
      m_id = Other.m_id;
      return *this;
    }

    void appendQueue(const std::queue<qevent>& q)
    {
      auto t = q;
      while (!t.empty())
      {
        m_queue.push(t.front());
        t.pop();
      }
    }

    void queueEvent(const qevent& ev) { m_queue.push(ev); }
    const std::queue<qevent>& getQueue() const { return m_queue; }

    virtual void registerEvents() {}

    virtual bool progressEvents() { return false; }
    qevent::target_id id() const { return m_id; }
    void setID(qevent::target_id id) { m_id = id; }
  protected:
    std::queue<qevent> m_queue;
    qevent::target_id m_id;
    virtual std::string getEventInfo() { return ""; }
  };
}
