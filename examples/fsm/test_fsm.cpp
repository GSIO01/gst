#include "test_fsm.h"

#include <functional>
#include <algorithm>
#include <iostream>

test_fsm::test_fsm(gst::fsm::fsm_state st /* = 0 */, const gst::fsm::transition_table& trt /* = gst::fsm::transition_table() */) {
	m_state = st;
	gst::fsm::transition_table tr_t = {
		TRANSITION(	STATE_IDLE,		EV_GO_IDLE, 		STATE_IDLE,		test_fsm::go_idle		),
		TRANSITION(	STATE_IDLE,		EV_BEGIN_PATROL, 	STATE_PATROL,	test_fsm::start_patrol	),
		TRANSITION(	STATE_IDLE,		EV_DIE, 			STATE_DEAD,		test_fsm::die			),
		TRANSITION(	STATE_PATROL,	EV_GO_IDLE, 		STATE_IDLE,		test_fsm::go_idle		),
		TRANSITION(	STATE_PATROL,	EV_BEGIN_PATROL,	STATE_PATROL,	test_fsm::start_patrol	),
		TRANSITION(	STATE_PATROL,	EV_ENEMY_SIGHTED,	STATE_ATTACK,	test_fsm::attack_enemy	),
		TRANSITION(	STATE_PATROL,	EV_DIE, 			STATE_DEAD,		test_fsm::die			),
		TRANSITION(	STATE_ATTACK,	EV_GO_IDLE, 		STATE_IDLE,		test_fsm::go_idle		),
		TRANSITION(	STATE_ATTACK,	EV_ENEMY_SIGHTED, 	STATE_ATTACK,	test_fsm::attack_enemy	),
		TRANSITION(	STATE_ATTACK,	EV_ENEMY_KILLED, 	STATE_PATROL,	test_fsm::start_patrol	),
		TRANSITION(	STATE_ATTACK,	EV_DIE, 			STATE_DEAD,		test_fsm::die			)
	};

	m_transitiontable = tr_t;
}

void test_fsm::start_patrol(const gst::fsm::fevent& ev) {
	std::cout << "start_patrol" << std::endl;
}

void test_fsm::go_idle(const gst::fsm::fevent& ev) {
	std::cout << "go_idle" << std::endl;
}

void test_fsm::attack_enemy(const gst::fsm::fevent& ev) {
	std::cout << "attack_enemy" << std::endl;
}

void test_fsm::die(const gst::fsm::fevent& ev) {
	std::cout << "die" << std::endl;
}

