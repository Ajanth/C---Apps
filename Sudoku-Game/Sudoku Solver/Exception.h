/*
 * Exception.h
 *
 *  Created on: Jan 25, 2012
 *      Author: muthu
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
using namespace std;

class Exception {
    string exception;
public:
	Exception();
	Exception(string);
	const string& getException();
	virtual ~Exception();
};

#endif /* EXCEPTION_H_ */
