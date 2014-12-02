#ifndef POINT_HPP
#define POINT_HPP

#include "Color.hpp"

class Point {

private:
	int x;
	int y;
	
public:

	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
	
	int getX(){
		return x;
	}
	int getY(){
		return y;
	}
	
	void setX(int x){
		this->x = x;
	}
	void setOffsetX(int x){
		this->x += x;
	}
	void setY(int y){
		this->y = y;
	}
	void setOffsetY(int y){
		this->y += y;
	}
	

};

#endif
