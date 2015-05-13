#include <cstdlib>
#include <cstdio>
#include <cinttypes>
#include <iostream>

#include "../../event/manager.h"
#include "../../event/qevent.h"

#include "TestClass.h"

int32_t main(int32_t argc, char* argv[]) {
	gst::event::manager man;
	TestClass tc, tc2;

	std::cout << tc.getEventInfo() << std::endl;

	man.registerListener(&tc);
	man.registerListener(&tc2);

	gst::event::qevent ev1(TestClass::TCE_EV1, tc.id());
	gst::event::qevent ev2(TestClass::TCE_EV2, tc2.id());
	ev2.setParameter("text", std::string("A test."));
	gst::event::qevent ev3(TestClass::TCE_EV1);

	man.push(ev1);
	man.push(ev2);
	man.push(ev3);

	man.progressEvents();

	getchar();
	return EXIT_SUCCESS;
}
