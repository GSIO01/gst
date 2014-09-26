#include <cstdlib>
#include <cstdio>

#include "test_fsm.h"

int main(int argc, char* argv[]) {
	test_fsm fsm;

	fsm.processEvent(gst::fsm::fevent(test_fsm::EV_BEGIN_PATROL));
	fsm.processEvent(gst::fsm::fevent(test_fsm::EV_BEGIN_PATROL));
	fsm.processEvent(gst::fsm::fevent(test_fsm::EV_ENEMY_SIGHTED));
	fsm.processEvent(gst::fsm::fevent(test_fsm::EV_ENEMY_KILLED));
	fsm.processEvent(gst::fsm::fevent(test_fsm::EV_BEGIN_PATROL));
	fsm.processEvent(gst::fsm::fevent(test_fsm::EV_ENEMY_SIGHTED));
	fsm.processEvent(gst::fsm::fevent(test_fsm::EV_DIE));

	getchar();

	return EXIT_SUCCESS;
}
