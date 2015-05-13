#include "TestClass.h"

#include <iostream>

EVENT_MAPSTART(TestClass)
EVENT_MAPENTRY("Event1", "Event 1", TestClass::ETestClassEvents::TCE_EV1, TestClass::EventHandler1)
EVENT_MAPENTRY_PARM("Event2", "Event 2", TestClass::ETestClassEvents::TCE_EV2, TestClass::EventHandler2, EVENT_PARAMETER("text", "A text"))
EVENT_MAPEND;

EVENT_IMPLEMENT(TestClass);


void TestClass::EventHandler1(const gst::event::qevent& /*ev*/)
{
  std::cout << "Listener: " << m_id << " Event 1" << std::endl;
}

void TestClass::EventHandler2(const gst::event::qevent& ev)
{
  std::cout << "Listener: " << m_id << " Event 2: " << ev.param<std::string>("text") << std::endl;
}
