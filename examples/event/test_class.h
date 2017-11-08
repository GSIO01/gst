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

#ifndef TEST_CLASS_H
#define	TEST_CLASS_H

#include <map>

#include "../src/event/events.h"
#include "../src/event/qevent.h"
#include "../src/event/listener.h"

class test_class : public virtual gst::event::listener {
   EVENT_DECLARE(test_class)
   
public:
   typedef enum {
      EV_TEST1 = gst::event::EV_GLOBAL_MAX
   } events;
   
   test_class();
   test_class(const test_class& other);
   virtual ~test_class();
   test_class& operator =(const test_class& other);
private:
   void test1(const gst::event::qevent& ev);
};

#endif	/* TEST_CLASS_H */

