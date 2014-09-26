#ifndef _TEST_FSM_H
#define _TEST_FSM_H

#include <fsm/mashine.h>

class test_fsm : public gst::fsm::mashine {
	public:
	enum states {
		STATE_IDLE,
		STATE_PATROL,
		STATE_ATTACK,
		STATE_DEAD
	};

	enum events {
		EV_BEGIN_PATROL,
		EV_GO_IDLE,
		EV_ENEMY_SIGHTED,
		EV_ENEMY_KILLED,
		EV_DIE
	};

	test_fsm(gst::fsm::fsm_state st = 0, const gst::fsm::transition_table& trt = gst::fsm::transition_table());

	private:
	void start_patrol(const gst::fsm::fevent& ev);
	void go_idle(const gst::fsm::fevent& ev);
	void attack_enemy(const gst::fsm::fevent& ev);
	void die(const gst::fsm::fevent& ev);
};

#endif /* _TEST_FSM_H */

