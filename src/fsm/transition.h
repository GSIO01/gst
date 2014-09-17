#ifndef _GST_FSM_TRANSITION_H
#define _GST_FSM_TRANSITION_H

#include <functional>
#include <vector>

#include "fevent.h"
#include "fsm.h"

namespace gst {
	namespace fsm {

		typedef struct transition_s transition;
		struct transition_s {
			fsm_state state;
			fevent ev;
			fsm_state new_state;
			std::function<void(const fevent&)> handeler;
		};

		typedef std::vector<transition> transition_table;

	}
}

#endif /* _GST_FSM_TRANSITION_H */