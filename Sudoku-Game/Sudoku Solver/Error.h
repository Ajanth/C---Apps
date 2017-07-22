/*
 * Error.h
 *
 *  Created on: Jan 23, 2012
 *      Author: muthu
 */

#ifndef ERROR_H_
#define ERROR_H_

#include "Pos.h"
#include <string>

using namespace std;

class Pos;

class Error {

	 string errmsg;
	 Pos pos1,pos2;

public:
	 bool isError;

public:

	Error();
	Error(Error const&);
	Error(string,Pos const&,Pos const&);

	Error& operator=(Error const&);
	bool operator==(Error const&);
	bool operator!=(Error const&);

	const Pos *  getPos1();
	const Pos *  getPos2();


	string getErrorMsg();
	string getErrorReport();

	bool isThereError();
	void clearError();

	virtual ~Error();

};

#endif /* ERROR_H_ */
