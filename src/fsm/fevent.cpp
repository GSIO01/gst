#include "fevent.h"

namespace gst {
	namespace fsm {

		fevent::fevent(event_id id, const std::map<std::string, any>& parameters) :
			m_id(id),
			m_parameters(parameters)
		{
		}

		fevent::fevent(const fevent& other) :
			m_id(other.m_id),
			m_parameters(other.m_parameters)
		{
		}

		fevent::~fevent() {
		}

		fevent& fevent::operator =(const fevent& other) {
			m_id = other.m_id;
			m_parameters = other.m_parameters;

			return *this;
		}

		event_id fevent::id() const {
			return m_id;
		}

		void fevent::setParameter(const std::string& name, const any& data) {
			m_parameters.insert(std::make_pair(name, data));
		}
	}
}
