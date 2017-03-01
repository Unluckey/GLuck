//GL means Good Luck!
//Basic object class
#define GRAVITY 1


struct Vector2
{
	float x,y;
};

class GLuckObject
{
public:
	GLuckObject(int iniPosX,int iniPosY);
	~GLuckObject();
	bool setGravity(bool newGravity);
	int posX();
	int posY();
	bool fall();
protected:
	Vector2 speed;
	int x,y;
	bool onGravity;
};
bool GLuckObject::setGravity(bool newGravity){
	bool tG = onGravity;
	onGravity = newGravity;
	return tG;
}
GLuckObject::GLuckObject(int iniPosX = 0,int iniPosY = 0,bool iniGravity = false){
	speed.x = 0;
	speed.y = 0;
	x = iniPosX;
	y = iniPosY;
	onGravity = iniGravity;
}

bool GLuckObject::fall(){
	if(onGravity){
		y -= speed.y;
		speed.y += GRAVITY;
	}
	return onGravity;
}