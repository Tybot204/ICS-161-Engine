#include "Message.h"

class Message{
	void EventUp::execute(Message& msg) {
		msg.onUp(*this);
	};

	void EventDown::execute(Message& msg) {
		msg.onDown(*this);
	};

	void EventLeft::execute(Message& msg) {
		msg.onLeft(*this);
	};

	void EventRight::execute(Message& msg) {
		msg.onRight(*this);
	};

};