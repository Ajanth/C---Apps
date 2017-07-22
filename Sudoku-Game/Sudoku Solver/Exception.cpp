/*
 * Exception.cpp
 *
 *  Created on: Jan 25, 2012
 *      Author: muthu
 */
#include "stdafx.h"
#include "Exception.h"


Exception::Exception() {
	 exception.assign("");
}
Exception::Exception(string exception) {
	 this->exception.assign(exception);
}


Exception::~Exception() {

}

const string& Exception::getException(){
	return this->exception;
}

