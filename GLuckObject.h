//GL means Good Luck!
//Basic object class
#pragma once
#define GRAVITY 1
#define PI 3.14159265

#include "windows.h"
#include "GL\glut.h"
#include <math.h>
#include <vector>




struct GLuckPOINT
{
	GLfloat x, y;
};

struct Vector2
{
	float x,y;
};

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
	~GLuckObject();
	bool setGravity(bool newGravity);
	bool changeGravity();
	GLfloat posX();
	GLfloat posY();
	int ID();

	void setColor(int r, int g, int b);
	void setColor(GLuckColor color);
	virtual bool transform();
	virtual void display() {};
	
	GLuckPOINT hitPoint;
protected:
	//static ObjList list;
	//static int NumOfObj;
	float elastic;
	Vector2 speed;
	GLuckColor RGB;
	GLfloat x,y;
	bool onGravity;
	int ObjID;
};

GLuckObject::GLuckObject(GLfloat iniPosX = 0, GLfloat iniPosY = 0, bool iniGravity = false) {
	speed.x = 0;
	speed.y = 0;
	x = iniPosX;
	y = iniPosY;
	hitPoint.x = x;
	hitPoint.y = y;
	onGravity = iniGravity;
	//ObjID = ++NumOfObj;
	setColor(255,255,255);
	elastic = 0.4;
}

inline GLuckObject::~GLuckObject()
{

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

GLfloat GLuckObject::posX() {
	return x;
}

GLfloat GLuckObject::posY() {
	return y;
}

inline int GLuckObject::ID()
{
	return ObjID;
}

bool GLuckObject::transform(){
	
		y -= speed.y;
		if (onGravity) {
			if(y > 0)
				speed.y += GRAVITY;
		if (y < 0) {
			y = 0;
			speed.y = -speed.y * elastic;
			if (speed.y > -1)speed.y = 0;
		}
	}
	return onGravity;
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

//vector!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
////ObjectList
//class ObjList
//{
//public:
//	ObjList();
//	ObjList(GLuckObject * iniObj);
//	void append(GLuckObject* appendObj);
//	GLuckObject* obj;
//	ObjList* next;
//};
//
//inline ObjList::ObjList()
//{
//	obj = nullptr;
//	next = nullptr;
//}
//
//ObjList::ObjList(GLuckObject * iniObj) {
//	obj = iniObj;
//	next = nullptr;
//}
//
//inline void ObjList::append(GLuckObject * appendObj)
//{
//	ObjList* p = this;
//	for (; p->next; p = p->next);
//
//	p->next = new ObjList(appendObj);
//}
//

//==================================================
//Square  GluckObject
//==================================================
class Square :public GLuckObject {
public:
	Square(int iniEdge, GLfloat iniRange, int iniPosX, int iniPosY, bool iniGravity, bool clockWise);
	virtual void display();
	bool transform();
	GLfloat scale(GLfloat changeValue, GLfloat maxScaleSzie);
	virtual void rotate(GLfloat speed);
protected:
	void refresh();
	bool clockWise;
	GLfloat rotationAngle;
	vector<GLuckPOINT> pivot;
	int edge;
	GLfloat range;
};

Square::Square(int iniEdge,GLfloat iniRange, int iniPosX = 0, int iniPosY = 0, bool iniGravity = false, bool clockWise = true)
:GLuckObject(iniPosX,iniPosY,iniGravity){
	edge = iniEdge;
	range = iniRange;
	refresh();
	elastic = 0.4;
	rotationAngle = 0;
	this->clockWise = clockWise;

}

void Square::refresh() {
	pivot[0].x = x + cos(PI / 4.0)*width*cos(3.0*PI / 4.0 + rotationAngle);
	pivot[0].y = y + cos(PI / 4.0)*width*sin(3.0*PI / 4.0 + rotationAngle);

	pivot[1].x = x + cos(PI / 4.0)*width*cos(PI / 4.0 + rotationAngle);
	pivot[1].y = y + cos(PI / 4.0)*width*sin(PI / 4.0 + rotationAngle);

	pivot[2].x = x + cos(PI / 4.0)*width*cos(5.0*PI / 4.0 + rotationAngle);
	pivot[2].y = y + cos(PI / 4.0)*width*sin(5.0*PI / 4.0 + rotationAngle);

	pivot[3].x = x + cos(PI / 4.0)*width*cos(-PI / 4.0 + rotationAngle);
	pivot[3].y = y + cos(PI / 4.0)*width*sin(-PI / 4.0 + rotationAngle);

	hitPoint = pivot[3];

}

inline void Square::display()
{
	transform();
	refresh();
	glColor3ub(RGB.r,RGB.g,RGB.b);
	//glRectf(-0.5f,-0.5f,0.5f,0.5f);
	glBegin(GL_POLYGON);
	glVertex2f(pivot[0].x, pivot[0].y);
	glVertex2f(pivot[1].x, pivot[1].y);
	glVertex2f(pivot[3].x, pivot[3].y);
	glVertex2f(pivot[2].x, pivot[2].y);
	glEnd();
	
}

inline bool Square::transform() {
	y -= speed.y;


	if (onGravity && (int)hitPoint.y > 0)speed.y += GRAVITY;

	//bounce
	if (hitPoint.y < 0) {
		y = (double)range /2.0f;
		refresh();
		speed.y = (-speed.y+1) * elastic;
		if (speed.y > -4)speed.y = 0;
	}

	return onGravity;
}

inline GLfloat Square::scale(GLfloat changeValue,GLfloat maxSzie)
{
	range += changeValue;
	if (range <= 0) range = 0;
	if (range > maxSzie)range = maxSzie;
	refresh();
	
	return range;
}

inline void Square::rotate(GLfloat speed)
{
	if (!clockWise) {
		rotationAngle += speed;
		rotationAngle = rotationAngle > PI*2 ? 0 : rotationAngle;
	}
	else
	{
		rotationAngle -= speed;
		rotationAngle = rotationAngle < -PI*2 ? 0 : rotationAngle;
	}
}

std::vector<Square> vSqares;