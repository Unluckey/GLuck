//GL means Good Luck!
//Basic object class
#pragma once
#define GRAVITY 1
#define PI 3.14159265

#include "windows.h"
#include "GL\glut.h"
#include <math.h>
#include <vector>
using namespace std;


class GLuckVector2
{
public:
	GLuckVector2(float iniX, float iniY);

	void set(float x, float y);
	void setX(float x) {vecX = x; update();};
	void setY(float y) { vecY = y; update();};
	void addX(float x) { vecX += x; update();};
	void addY(float y) { vecY += y; update();};

	float getX() { return vecX; };
	float getY() { return vecY; };
	float getSlope() { return slope; };
	int getQuad() { return (int)quadrant; };
protected:
	void update();
	enum direction{RightUp, LeftUp,LeftDown,RightDown}quadrant;
	float slope;
	float vecX, vecY;
	
};

inline GLuckVector2::GLuckVector2(float iniX = 0, float iniY = 0) {
	vecX = iniX;
	vecY = iniY;
	update();
}

inline void GLuckVector2::update()
{
	if (vecX != 0)
		slope = vecY / vecX;
	else
		slope = 0;

	if (vecX >= 0)
		if (vecY > 0)
			quadrant = (direction)1;
		else
			quadrant = (direction)4;
	else
		if (vecY > 0)
			quadrant = (direction)2;
		else
			quadrant = (direction)3;
}

inline void GLuckVector2::set(float x, float y)
{
	vecX = x;
	vecY = y;
	update();
}


class GLuckPOINT
{
public:
	GLuckPOINT() {};
	GLuckPOINT(GLfloat iniX, GLfloat iniY);
	void set(GLfloat newX, GLfloat newY);
	GLfloat x, y;
};

GLuckPOINT::GLuckPOINT(GLfloat iniX, GLfloat iniY) {
	x = iniX;
	y = iniY;
}
void GLuckPOINT::set(GLfloat newX, GLfloat newY) {
	x = newX;
	y = newY;
}


class GLuckColor
{
public:
	GLuckColor(int r,int g,int b);
	void set(int r, int g, int b);
	int r, g, b;
};

GLuckColor::GLuckColor(int r = 0, int g = 0, int b = 0) {
	this->r = r;
	this->g = g;
	this->b = b;
}
void GLuckColor::set(int r, int g, int b) {
	this->r = r;
	this->g = g;
	this->b = b;
}


//==================================================
//GluckObject
//==================================================
class GLuckObject
{
public:
	GLuckObject(GLfloat iniPosX, GLfloat iniPosY, bool iniGravity);
	~GLuckObject() {};
	bool setGravity(bool newGravity);
	bool changeGravity();
	GLfloat posX() { return x; };
	GLfloat posY() { return y; };
	int ID();

	void setColor(int r, int g, int b);
	void setColor(GLuckColor color);

	virtual bool move();
	virtual void transform(GLfloat posX, GLfloat posY);
	virtual void display() {};
	GLuckVector2 speed;

protected:
	float elastic;
	
	GLuckColor RGB;
	GLfloat x,y;
	bool onGravity;
	int ObjID;
	int mass;
};

GLuckObject::GLuckObject(GLfloat iniPosX = 0, GLfloat iniPosY = 0, bool iniGravity = false) {
	x = iniPosX;
	y = iniPosY;
	onGravity = iniGravity;
	setColor(255,255,255);
	elastic = 0.4;
	mass = 1;
}

bool GLuckObject::setGravity(bool newGravity){
	bool tG = onGravity;
	onGravity = newGravity;
	return tG;
}

inline bool GLuckObject::changeGravity()
{
	onGravity = !onGravity;
	return onGravity;
}

inline int GLuckObject::ID()
{
	return ObjID;
}

inline void GLuckObject::setColor(int r, int g, int b)
{
	RGB.r = r;
	RGB.g = g;
	RGB.b = b;
}

inline void GLuckObject::setColor(GLuckColor color)
{
	RGB = color;
}

bool GLuckObject::move(){
	x += speed.getX();
	y -= speed.getY();
	if (onGravity && (int)y > 0)speed.addY(GRAVITY);

	if (y < 0) {
		y = 0;
		speed.setY((-speed.getY() + 1) * elastic);
		if (speed.getY() > -1)speed.setY(0);
	}
	return onGravity;
}

inline void GLuckObject::transform(GLfloat newX,GLfloat newY)
{
	x = newX;
	y = newY;
}


//==================================================
//GLuckPolygon  GluckObject
//==================================================
class GLuckPolygon :public GLuckObject {
public:
	GLuckPolygon(int iniEdge, GLfloat iniRange, int iniPosX, int iniPosY, bool iniGravity, bool clockWise);

	bool move();
	GLfloat scale(GLfloat changeValue, GLfloat maxScaleSzie);
	virtual void rotate(GLfloat speed);
	virtual void display();
	//added
	GLuckVector2 force;
	bool collDetection(GLuckPolygon other);

protected:
	void update();
	bool clockWise;
	GLfloat rotationAngle;
	vector<GLuckPOINT> vPivot;
	int edge;
	GLfloat range;
};

GLuckPolygon::GLuckPolygon(int iniEdge,GLfloat iniRange, int iniPosX = 0, int iniPosY = 0, bool iniGravity = false, bool clockWise = true)
:GLuckObject(iniPosX,iniPosY,iniGravity){
	edge = iniEdge;
	range = iniRange;
	elastic = 0.4;
	rotationAngle = 0;
	this->clockWise = clockWise;
	float dAng = 2 * PI / edge;

	for (int i = 0; i < edge; i++)
	{
		GLuckPOINT p(x + range*sin(dAng*i + rotationAngle), y + range*cos(dAng*i + rotationAngle));
		vPivot.push_back(p);
	}
}

inline bool GLuckPolygon::collDetection(GLuckPolygon other)
{
	GLfloat distance = pow(this->posX() - other.posX(), 2) + pow(this->posY() - other.posY(),2);
	if (distance > range)
		return false;
	else
	{

		return true;
	}
}

inline GLfloat GLuckPolygon::scale(GLfloat changeValue, GLfloat maxSzie)
{
	range += changeValue;
	if (range <= 0) range = 0;
	if (range > maxSzie)range = maxSzie;
	update();

	return range;
}

inline void GLuckPolygon::rotate(GLfloat speed)
{
	if (!clockWise) {
		rotationAngle += speed;
		rotationAngle = rotationAngle > PI * 2 ? 0 : rotationAngle;
	}
	else {
		rotationAngle -= speed;
		rotationAngle = rotationAngle < -PI * 2 ? 0 : rotationAngle;
	}
}



inline bool GLuckPolygon::move() {
	x += speed.getX();
	y -= speed.getY();
	if (onGravity && (int)y > range)speed.addY(GRAVITY);
	//bounce
	if (y < range) {
		y = range;
		speed.setY((-speed.getY() + 1) * elastic);
		if (speed.getY() > -1)speed.setY(0);
	}
	return onGravity;
}

inline void GLuckPolygon::display()
{
	move();
	update();
	glColor3ub(RGB.r,RGB.g,RGB.b);
	
	glBegin(GL_POLYGON);
	
	for(int i = 0;i<vPivot.size();i++)
		glVertex2f(vPivot.at(i).x, vPivot.at(i).y);
	
	glEnd();
	
}

void GLuckPolygon::update() {
	float dAng = 2 * PI / edge;
	GLfloat minY = vPivot.at(0).y;
	int minYPivot = 0;
	for (int i = 0; i < edge; i++)
		vPivot.at(i).set(x + range*sin(dAng*i + rotationAngle), y + range*cos(dAng*i + rotationAngle));
}
 

//Object Manager vector
vector<GLuckPolygon> vPolygons;