/*
 * Error.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: muthu
 */
#include "stdafx.h"
#include "Error.h"



/*
 * #include "string.h"
#include "stdlib.h"
#include "Pos.cpp"
#include "Error.h"
 * */

Error::Error() : pos1(0,0) ,pos2(9,9) {
      errmsg = "No error";
      isError = false;
}

Error :: Error(string errmsg,Pos const& p1,Pos const& p2) : pos1(0,0) ,pos2(9,9) {
    isError = false;
	this->errmsg = errmsg;
	pos1 = p1;
	pos2 = p2;
}

Error :: Error(Error const& temp) : pos1(0,0) ,pos2(9,9){
		*this = temp;
}

Error& Error::operator=(Error const& temp){

		this->errmsg = temp.errmsg;
		pos1 = temp.pos1;
		pos2 = temp.pos2;
	return *this;
}

bool Error::operator==(Error const& temp){

				if( (this->errmsg == temp.errmsg) & (pos1 == temp.pos1) & (pos2 == temp.pos2))
					return true;
				else
					return false;

}

string Error::getErrorReport(){
	if(isError)
		return string( errmsg + " at positions " + pos1.getPosReport() + " and " + pos2.getPosReport());
	else
		return string("No error.");
}

bool Error::operator!=(Error const& temp){
		if( *this == temp )
			return false;
		else
			return true;
}

bool Error::isThereError(){
	return isError;
}

string Error::getErrorMsg(){
	if(isError)
		return errmsg;
	else
		return "No error.";
}

void Error::clearError(){
	isError = false;
	*this =  Error("No error",Pos(0,0),Pos(9,9));
}
const Pos* Error::getPos1(){
	if(isError)
		return &pos1;
	else
		return NULL;
}

const Pos* Error::getPos2(){
	if(isError)
		return &pos2;
	else
		return NULL;
}

Error::~Error() {

}
