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

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "../../event/manager.h"
#include "../../event/qevent.h"

#include "TestClass.h"

int32_t main(int32_t argc, char* argv[])
{
  TestClass tc, tc2;

  std::cout << tc.getEventInfo() << std::endl;

  gst::event::manager::register_listener(&tc);
  gst::event::manager::register_listener(&tc2);

  gst::event::qevent ev1(TestClass::TCE_EV1, tc.id());
  gst::event::qevent ev2(TestClass::TCE_EV2, tc2.id());
  ev2.setParameter("text", std::string("A test."));
  gst::event::qevent ev3(TestClass::TCE_EV1);

  gst::event::manager::push(ev1);
  gst::event::manager::push(ev2);
  gst::event::manager::push(ev3);

  gst::event::manager::proccess_events();

  getchar();
  return EXIT_SUCCESS;
}
