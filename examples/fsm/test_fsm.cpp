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

