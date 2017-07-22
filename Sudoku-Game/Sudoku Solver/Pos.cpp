/*
 * Pos.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: muthu
 */

#include "stdafx.h"
#include "Pos.h"

Pos::Pos(int x,int y) {
    setPos(x,y);
}

Pos::Pos(Pos const& p){
  Pos(p.x,p.y);
}

void Pos::setPos(Pos const& p){
	setPos(p.x,p.y);
}

void Pos::setPos(int x,int y){
	setx(x);
	sety(y);
}

void Pos::setx(int x){
	if((x < 0) & (x > 9))
		throw  Exception("Invalid Position");
	else
		this->x = x;
}

void Pos::sety(int y){
	if((y < 0) & (y > 9)){
		throw Exception("Invalid Position");
	}
	else
		this->y = y;
}

int Pos::getx() const {
	return x;
}

int Pos::gety() const {
return y;
}

Pos& Pos :: operator=(Pos const& p){
   setPos(p);
   return *this;
}

bool Pos :: operator==(Pos const& p){
   if((x != p.x) | (y != p.y) )
	   return false;
   else
	   return true;
}
bool Pos :: operator!=(Pos const& p){
   if( (x != p.x) | (y != p.y) )
	   return true;
   else
	   return false;
}

string Pos::getPosReport(){
   stringstream s;
   s << "(" << x+1 << "," << y+1 << ")";
   return s.str();
}

Pos::~Pos() {

}
