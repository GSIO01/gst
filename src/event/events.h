/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Walter Julius Hennecke
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

#ifndef _GST_EVENT_EVENTS_H
#define	_GST_EVENT_EVENTS_H

/* Required includes */
#include <string>
#include <vector>


#define EVENT_MAPSTART(CLASSNAME) const CLASSNAME::TEventMapEntry CLASSNAME::s_eventMap[] = {
#define EVENT_MAPEND }


#define EVENT_DECLARE(CLASSNAME) \
public: \
typedef void(CLASSNAME::*function_ptr)(const gst::event::qevent& ev); \
\
struct TEventMapEntry { \
	std::string m_name; \
	std::string m_description; \
	std::vector<gst::event::parameter> m_parameters; \
	gst::event::qevent::event_id m_eventID; \
	function_ptr m_eventHandler; \
	\
	TEventMapEntry(const std::string& name, const std::string& description, const std::vector<gst::event::parameter>& parameters, gst::event::qevent::event_id eventID, function_ptr eventHandler) \
		: m_name(name) \
		, m_description(description) \
		, m_parameters(parameters) \
		, m_eventID(eventID) \
		, m_eventHandler(eventHandler) { \
	} \
	\
	TEventMapEntry(const std::string& name, const std::string& description, gst::event::qevent::event_id eventID, function_ptr eventHandler) \
		: m_name(name) \
		, m_description(description) \
		, m_eventID(eventID) \
		, m_eventHandler(eventHandler) { \
	} \
}; \
\
virtual void progressEvents(); \
virtual void registerEvents(); \
std::string getEventInfo(); \
private: \
	static const TEventMapEntry s_eventMap[]; \
	std::map<gst::event::qevent::event_id, function_ptr> m_eventMap;


#define EVENT_IMPLEMENT(CLASSNAME) \
void CLASSNAME::progressEvents() { \
	if (m_eventMap.empty()) { \
		return; \
	} \
	\
	while (m_queue.empty() == false) { \
		gst::event::qevent ev = m_queue.pop(); \
		\
		if (ev.eventID() == gst::event::EV_GLOBAL_EMPTY) { \
			continue; \
		} \
		\
		if (ev.targetID() != 0 && ev.targetID() != m_id) { \
			continue; \
		} \
		\
		if (m_eventMap.find(ev.eventID()) == m_eventMap.end()) { \
			continue; \
		} \
		\
		auto funcPtr = m_eventMap[ev.eventID()]; \
		\
		(this->*funcPtr)(ev); \
	} \
} \
\
void CLASSNAME::registerEvents() { \
	for (int i = 0; s_eventMap[i].m_eventHandler != nullptr; i++) { \
		TEventMapEntry entry = s_eventMap[i]; \
		\
		m_eventMap[entry.m_eventID] = entry.m_eventHandler; \
	} \
} \
std::string CLASSNAME::getEventInfo() { \
	std::string eventInfo; \
	\
	for(int i = 0; s_eventMap[i].m_eventHandler != nullptr; i++) { \
		TEventMapEntry entry = s_eventMap[i]; \
		\
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
} \


namespace gst {
	namespace event {

		typedef enum {
			EV_GLOBAL_EMPTY,
			EV_GLOBAL_MAX
		} global_events;

	}
}

#endif	/* _GST_EVENT_EVENTS_H */

