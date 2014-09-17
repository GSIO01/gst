#ifndef _GST_FSM_MASHINE_H
#define _GST_FSM_MASHINE_H

#include "fsm.h"
#include "fevent.h"
#include "transition.h"

namespace gst {
	namespace fsm {

		class mashine
		{
		public:
		mashine(fsm_state state = 0, const transition_table& transition_tab = transition_table());
		mashine(const mashine& other);
		virtual ~mashine();
		mashine& operator =(const mashine& other);

		fsm_state state() const;
		void setState(fsm_state state);
		void setTransitionTable(const transition_table& transition_tab);
		void processEvent(const fevent& ev);

		private:
		transition_table m_transitiontable;
		fsm_state m_state;
		};

	}
}

#endif /* _GST_FSM_MASHINE_H */
