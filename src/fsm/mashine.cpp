#include "mashine.h"

namespace gst {
	namespace fsm {

		mashine::mashine(fsm_state state, const transition_table& transition_tab) :
			m_state(state),
			m_transitiontable(transition_tab)
		{
		}

		mashine::mashine(const mashine& other) :
			m_state(other.m_state),
			m_transitiontable(other.m_transitiontable)
		{
		}

		mashine::~mashine() {
		}

		mashine& mashine::operator =(const mashine& other) {
			m_state = other.m_state;
			m_transitiontable = other.m_transitiontable;

			return *this;
		}

		fsm_state mashine::state() const {
			return m_state;
		}

		void mashine::setState(fsm_state state) {
			m_state = state;
		}

		void mashine::setTransitionTable(const transition_table& transition_tab) {
			m_transitiontable = transition_tab;
		}

		void mashine::processEvent(const fevent& ev) {
			// TODO write me
		}

	}
}
