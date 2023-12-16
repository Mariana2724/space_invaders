#pragma once
class Shapes {
public:
	virtual void draw() = 0;
	virtual void movement() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
};