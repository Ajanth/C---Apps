/*
 * Cell.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: muthu
 */

#include "stdafx.h"
#include "Cell.h"
#include "stdio.h"


Cell::Cell() : pos(0,0) {
	isDynamic = true;
	value = 0;
	isError = false;
}
Cell::~Cell() {

}

void Cell::setValue(int value){
    if((value<10) & (value >= 0))
	 this->value = value;
    else{
    char s[30];
    sprintf(s,"Invalid value : %d",value);
    throw Exception("Invalid value");
    }
}

int Cell::getValue(){
	return value;
}

Cell& Cell::operator =(Cell const& temp){
	this->pos = temp.pos;
	this->isDynamic = temp.isDynamic;
	this->isError = temp.isError;
	setValue(temp.value);
	return *this;
}

bool Cell::operator ==(Cell const& temp){
	if((this->pos == temp.pos) & (this->isDynamic == temp.isDynamic) & (this->value == temp.value) & (this->isError == temp.isError))
		return true;

		return false;
}

/*@self-deprecated : reason:  conceptwise instable;
bool Cell::operator !=(Cell const& temp){
//IMP:(this->pos != temp.pos) position will be always equal!!!
	if( (this->isDynamic != temp.isDynamic) | (this->value != temp.value))
		return true;

		return false;
}
*/

bool Cell::operator !=(Cell const& temp){

	if( *this == temp )
		return false;

		return true;
}
