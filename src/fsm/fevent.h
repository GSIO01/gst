#ifndef _GST_GSM_FEVENT_H
#define _GST_GSM_FEVENT_H

#include <map>

#include "../types/any.hpp"

namespace gst {
	namespace fsm {

		typedef unsigned long event_id;

		class fevent
		{
		public:
		fevent(event_id id = 0, const std::map<std::string, any>& parameters = std::map<std::string, any>());
		fevent(const fevent& other);
		virtual ~fevent();
		fevent& operator =(const fevent& other);

		event_id id() const;
		void setParameter(const std::string& name, const any& data);

		template<typename T>
		T parameter(const char* name) const {
			std::string sname(name);

			return gst::any_cast<T>(m_parameters.at(sname));
		}

		template<typename T>
		T parameter(const std::string& name) const {

			return gst::any_cast<T>(m_parameters.at(name));
		}

		private:
		std::map<std::string, any> m_parameters;
		event_id m_id;
		};

	}
}

#endif /* _GST_GSM_FEVENT_H */
