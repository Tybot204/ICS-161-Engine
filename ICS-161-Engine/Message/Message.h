//Message.h

#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"

class Message{

public:
	Message(Camera camera,int message_type);
	Message(Sprite sprite, int message_type);
	Message();
	~Message();
	void move();

private:
	Camera camera;
	Sprite sprite;
	int message_type;p
};
