/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Walter Julius Hennecke
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

#pragma once

#include <string>
#include <vector>

#define EVENT_MAPSTART(CLASSNAME) const CLASSNAME::TEventMapEntry CLASSNAME::s_##CLASSNAME##_eventMap[] = {
#define EVENT_MAPEND }
#define EVENT_MAPENTRY(NAME,DESCRIPTION,EVENTID,HANDLER) { NAME, DESCRIPTION, EVENTID, &HANDLER },
#define EVENT_MAPENTRY_PARM(NAME,DESCRIPTION,EVENTID,HANDLER,PARAMS) { NAME, DESCRIPTION, { PARAMS }, EVENTID, &HANDLER },
#define EVENT_PARAMETER(NAME,DESCRIPTIOM) { NAME, DESCRIPTIOM },

#define EVENT_DECLARE(CLASSNAME, BASECLASS) \
public: \
typedef void(CLASSNAME::*CLASSNAME##_function_ptr)(const gst::event::qevent& ev); \
\
struct TEventMapEntry { \
	std::string m_name; \
	std::string m_description; \
	std::vector<gst::event::parameter> m_parameters; \
	gst::event::qevent::event_id m_eventID; \
	CLASSNAME##_function_ptr m_eventHandler; \
	\
	TEventMapEntry(const std::string& name, const std::string& description, const std::vector<gst::event::parameter>& parameters, gst::event::qevent::event_id eventID, CLASSNAME##_function_ptr eventHandler) \
		: m_name(name) \
		, m_description(description) \
		, m_parameters(parameters) \
		, m_eventID(eventID) \
		, m_eventHandler(eventHandler) { \
	} \
	\
	TEventMapEntry(const std::string& name, const std::string& description, gst::event::qevent::event_id eventID, CLASSNAME##_function_ptr eventHandler) \
		: m_name(name) \
		, m_description(description) \
		, m_eventID(eventID) \
		, m_eventHandler(eventHandler) { \
	} \
}; \
\
virtual bool progressEvents() override; \
virtual void registerEvents() override; \
virtual std::string getEventInfo() override; \
private: \
	static const TEventMapEntry s_##CLASSNAME##_eventMap[]; \
	std::map<gst::event::qevent::event_id, CLASSNAME##_function_ptr> m_##CLASSNAME##_eventMap


#define EVENT_IMPLEMENT(CLASSNAME, BASECLASS) \
bool CLASSNAME::progressEvents() { \
  if(BASECLASS::progressEvents()) \
    return true; \
  \
	if (m_##CLASSNAME##_eventMap.empty()) { \
		return false; \
	} \
	\
	while (m_queue.empty() == false) { \
		gst::event::qevent ev = m_queue.front(); \
    m_queue.pop();\
		\
		if (ev.eventID() == gst::event::global_events::Empty) { \
			continue; \
		} \
		\
		if (ev.targetID() != 0 && ev.targetID() != m_id) { \
			continue; \
		} \
		\
		if (m_##CLASSNAME##_eventMap.find(ev.eventID()) == m_##CLASSNAME##_eventMap.end()) { \
			continue; \
		} \
		\
		auto funcPtr = m_##CLASSNAME##_eventMap[ev.eventID()]; \
		\
		(this->*funcPtr)(ev); \
	} \
  \
  return true; \
} \
\
void CLASSNAME::registerEvents() { \
  BASECLASS::registerEvents(); \
  \
  for(const auto& Entry : s_##CLASSNAME##_eventMap) \
		m_##CLASSNAME##_eventMap[Entry.m_eventID] = Entry.m_eventHandler; \
} \
std::string CLASSNAME::getEventInfo() { \
	std::string eventInfo = BASECLASS::getEventInfo(); \
	\
	for(const auto& entry : s_##CLASSNAME##_eventMap) { \
		eventInfo.append(entry.m_name); \
		eventInfo.append("\n"); \
		eventInfo.append(entry.m_description); \
		eventInfo.append("\nid: "); \
		eventInfo.append(std::to_string(entry.m_eventID)); \
		eventInfo.append("\n"); \
		\
		if(!entry.m_parameters.empty()) { \
			eventInfo.append("parameters: \n"); \
		} \
		\
		for(const auto& paramInfo : entry.m_parameters) { \
			eventInfo.append("\t"); \
			eventInfo.append(paramInfo.name()); \
			eventInfo.append(" - "); \
			eventInfo.append(paramInfo.description()); \
			eventInfo.append("\n"); \
		} \
		eventInfo.append("\n"); \
	} \
	\
	return eventInfo; \
}

namespace gst::event
{
  enum class global_events
  {
    Empty,
    Max
  };

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif

  template<typename T, typename = std::enable_if_t<std::is_convertible<T, std::underlying_type<global_events>::type>::value>>
  bool operator ==(T Rhs, global_events Lhs)
  {
    const std::underlying_type<global_events>::type ConvertedRhs(Rhs);
    return ConvertedRhs == static_cast<std::underlying_type<global_events>::type>(Lhs);
  }

  template<typename T, typename = std::enable_if_t<std::is_convertible<T, std::underlying_type<global_events>::type>::value>>
  bool operator ==(global_events Rhs, T Lhs)
  {
    return Lhs == Rhs;
  }

#ifdef _MSC_VER
#pragma warning(pop)
#endif
}
