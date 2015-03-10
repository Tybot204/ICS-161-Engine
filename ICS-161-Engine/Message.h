//Message.h



class Message{
	Message(Camera*, int);
public:
	virtual void onDown(const EventDown&){

	}
	virtual void onUp(const EventUp&){

	}
	virtual void onLeft(const EventLeft&){

	}
	virtual void onRight(const EvenetRight&){

	}
	virtual void onEvent(const EventMessage& m){
		m.execute(*this);
	}
};