//Message.h

class Message;

struct EventMessage{
	virtual void move(Message& msg) const = 0;

};

struct EventUp :public EventMessage {
	void move(Message& msg) const;
};

struct EventDown :public EventMessage {
	void move(Message& msg) const;
};

struct EventLeft :public EventMessage {
	void move(Message& msg) const;
};

struct EventRight :public EventMessage {
	void move(Message& msg) const;
};

