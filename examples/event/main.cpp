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


#include <cstdlib>
#include <iostream>

#include "../src/event/events.h"
#include "../src/event/qevent.h"
#include "../src/event/manager.h"

#include "test_class.h"

int main(int argc, char* argv[]) {
   gst::event::manager em;
   test_class* a = new test_class;
   test_class* b = new test_class;
   gst::event::qevent ev1(test_class::EV_TEST1, 1);
   gst::event::qevent ev2(test_class::EV_TEST1, 2);
   gst::event::qevent ev3(test_class::EV_TEST1);
   gst::event::qevent ev4(test_class::EV_TEST1, 42);
   
   a->setID(1);
   b->setID(2);
   
   ev1.setParameter("text", std::string("ev1"));
   ev2.setParameter("text", std::string("ev2"));
   ev3.setParameter("text", std::string("ev3"));
   ev4.setParameter("text", std::string("ev4"));
  
   em.registerListener(a);
   em.registerListener(b);
   
   em.push(ev1);
   em.push(ev2);
   em.push(ev3);
   em.push(ev4);
   em.progressEvents();
   
   em >> a;
   
   em.push(ev1);
   em.push(ev2);
   em.push(ev3);
   em.push(ev4);
   em.progressEvents();
   
   em.registerListener(a);
   
   em.push(ev3);
   em.progressEvents();

   getchar();

   return 0;
}

