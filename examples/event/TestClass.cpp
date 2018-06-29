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

#include "TestClass.h"

#include <iostream>

EVENT_MAPSTART(TestClass)
EVENT_MAPENTRY("Event1", "Event 1", TestClass::ETestClassEvents::TCE_EV1, TestClass::EventHandler1)
EVENT_MAPENTRY_PARM("Event2", "Event 2", TestClass::ETestClassEvents::TCE_EV2, TestClass::EventHandler2, EVENT_PARAMETER("text", "A text"))
EVENT_MAPEND;

EVENT_IMPLEMENT(TestClass, gst::event::listener);


void TestClass::EventHandler1(const gst::event::qevent& /*ev*/)
{
  std::cout << "Listener: " << m_id << " Event 1" << std::endl;
}

void TestClass::EventHandler2(const gst::event::qevent& ev)
{
  std::cout << "Listener: " << m_id << " Event 2: " << ev.param<std::string>("text") << std::endl;
}
