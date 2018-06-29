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

#include <deque>

#include "qevent.h"
#include "listener.h"
#include <queue>
#include <algorithm>

namespace gst::event
{
  class manager
  {
  public:
    virtual ~manager() = default;
    manager(const manager& Other) = delete;
    manager(manager&& Other) = delete;
    manager& operator =(const manager& Other) = delete;
    manager& operator =(manager&& Other) = delete;

    static void register_listener(listener* l)
    {
      for (auto n : get_instance().m_ListListeners)
      {
        if (n == l)
        {
          return;
        }
      }

      l->setID(get_instance().m_NextId);
      get_instance().m_NextId++;
      get_instance().m_ListListeners.insert(get_instance().m_ListListeners.end(), l);
    }

    static void remove_listener(listener* l)
    {
      get_instance().m_ListListeners.erase(std::find(get_instance().m_ListListeners.begin(), get_instance().m_ListListeners.end(), l));
    }

    static void push(qevent&& ev)
    {
      get_instance().m_Queue.push(std::forward<qevent>(ev));
    }

    static void push(const qevent& ev)
    {
      get_instance().m_Queue.push(ev);
    }

    static void proccess_events()
    {
      for (auto l : get_instance().m_ListListeners)
      {
        l->appendQueue(get_instance().m_Queue);
        l->progressEvents();
      }

      while (!get_instance().m_Queue.empty())
        get_instance().m_Queue.pop();
    }

  protected:
    std::queue<qevent> m_Queue;
    uint64_t m_NextId;
    std::deque<listener*> m_ListListeners;

    manager() : m_NextId{1} {}

    static manager& get_instance()
    {
      static manager s_Instance;
      return s_Instance;
    }
  };
}
