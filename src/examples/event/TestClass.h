#ifndef _TEST_CLASS_H
#define _TEST_CLASS_H

#include "../../event/events.h"
#include "../../event/qevent.h"
#include "../../event/listener.h"

class TestClass : public gst::event::listener {
	EVENT_DECLARE(TestClass);

public:
	TestClass() { registerEvents(); }
	~TestClass() { }

	enum ETestClassEvents {
		TCE_EV1,
		TCE_EV2
	};

private:
	void EventHandler1(const gst::event::qevent& ev);
	void EventHandler2(const gst::event::qevent& ev);
};

#endif /* _TEST_CLASS_H */
