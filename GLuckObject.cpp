//GL means Good Luck!
//Basic object class
#define GRAVITY 9


struct Vector2
{
	float x,y;
};
class GLuckObject
{
public:
	GLuckObject(int iniPosX,int iniPosY);
	~GLuckObject();
	bool setGravity();
	int posX();
	int posY();
	bool fall();
private:
	Vector2 speed;
	int x,y;
	bool onGravity;
};

GLuckObject::GLuckObject(int iniPosX = 0,int iniPosY = 0,bool iniGravity = false){
	speed.x = 0;
	speed.y = 0;
	x = iniPosX;
	y = iniPosY;
	onGravity = iniGravity;
}

GLuckObject::fall(){
	if(onGravity){
		y -= speed.y;
		speed.y += GRAVITY;
	}
}