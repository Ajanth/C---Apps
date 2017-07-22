/*
 * Matrix.cpp
 *
 *  Created on: Jan 23, 2012
 *      Author: muthu
 */
#include "stdafx.h"
#include "Matrix.h"



Matrix::Matrix() : dynIte(*this){

}

Matrix::Matrix(const Matrix& temp) : dynIte(*this) {
	*this = temp;
}


void Matrix::MatrixToArray(int array[9][9]){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			array[i][j] = cell[i][j].getValue();
}


bool Matrix::setMatrix(const int src[9][9]){

	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			cell[i][j].setValue(src[i][j]);

			if(cell[i][j].getValue() != 0)
				cell[i][j].isDynamic = false;
			else
				cell[i][j].isDynamic = true;
			cell[i][j].pos.setPos(i,j);
		}

	if(checkMatrixConsistency() != false)
		return true;
	else
		return  false;

}

bool Matrix::checkMatrixConsistency(){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(cell[i][j].getValue() != 0)
				if( consistencyCheck(cell[i][j].pos) == false)
					return false;


    return true;
}


bool Matrix::consistencyCheck(const Pos& p) {

	int row = p.getx();
	int col = p.gety();

	//Row check....
	for(int i=0;i<9;i++)
		if( i != col )
			if(cell[row][i].getValue() != 0)
				if(cell[row][i].getValue() == cell[row][col].getValue()){
					errmsg = Error(string("Row inconsistency"),p,Pos(row,i));
					errmsg.isError = true;
					return false;
				}

	//Column check....
	for(int i=0;i<9;i++)
		if( i != row )
			if(cell[i][col].getValue() != 0)
				if(cell[i][col].getValue() == cell[row][col].getValue()){
					errmsg = Error(string("Column inconsistency"),p,Pos(i,col));
					errmsg.isError = true;
					return false;
				}

   //Block check....
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++){
			Pos k((row/3)*3+i,(col/3)*3+j);
			if(k != cell[row][col].pos)
				if(getCellAtPos(k).getValue() != 0)
					if(getCellAtPos(k).getValue() == getCellAtPos(p).getValue()){
						errmsg = Error(string("Block inconsistency"),p,k);
						errmsg.isError = true;
						return false;
					}
		}

		errmsg.clearError();
		return true;
}

const Error& Matrix::getError(){
	return errmsg;
}

Cell* Matrix::getCellPtrAtPos(Pos const& p){
	return &cell[p.getx()][p.gety()];
}

Cell& Matrix::getCellAtPos(Pos const& p){
	return cell[p.getx()][p.gety()];
}
Matrix& Matrix::operator=(Matrix const& temp){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			cell[i][j] = temp.cell[i][j];
	dynIte = temp.dynIte;
	errmsg = temp.errmsg;
	return *this;
}

bool Matrix::operator==(Matrix const& temp){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(cell[i][j] != temp.cell[i][j])
			  return false;

	if((dynIte != temp.dynIte) | (errmsg != temp.errmsg))
		return false;

	return true;
}

bool Matrix::operator!=(Matrix const& temp){
	   if(*this == temp)
		   return false;
	   else
		   return true;
}

Matrix::~Matrix() {
}



Matrix::DynamicCellIterator::DynamicCellIterator(Matrix& ref): outerRef(ref),currentCellPtr(NULL){

}

Matrix::DynamicCellIterator& Matrix::DynamicCellIterator::operator=(Matrix::DynamicCellIterator const& temp){
	this->currentCellPtr = temp.currentCellPtr;
	return *this;
}
bool Matrix::DynamicCellIterator::operator==(Matrix::DynamicCellIterator const& temp){
	if((this->currentCellPtr == NULL) ^ (temp.currentCellPtr == NULL))
			return false; // if any one is null.
		else if((this->currentCellPtr == NULL) & (temp.currentCellPtr == NULL))
			return true; // if both are null.
		else
			return *(this->currentCellPtr) == *(temp.currentCellPtr);
}

bool Matrix::DynamicCellIterator::operator!=(Matrix::DynamicCellIterator const& temp){
	if((this->currentCellPtr == NULL) ^ (temp.currentCellPtr == NULL))
		return true; // if any one is null.
	else if((this->currentCellPtr == NULL) & (temp.currentCellPtr == NULL))
		return false; // if both are null.
	else
		return *(this->currentCellPtr) != *(temp.currentCellPtr);
                     //if none is null.
}


/*@Replaced by new func.
bool Matrix::isFirstDynamicPosExist(){
	for(int i=0; i<=8;i++)
		for(int j=0; j<=8;j++)
			if(cell[i][j].isDynamic)
				return true;
	return false;
}
*/
const Pos* Matrix::getFirstDynamicPosPtr(){
	for(int i=0; i<=8;i++)
		for(int j=0; j<=8;j++)
			if(cell[i][j].isDynamic)
				return &cell[i][j].pos;
	return NULL;
}

/*
 * @Replaced by new func
bool Matrix::isLastDynamicPosExist(){
	for(int i=8; i>=0;i--)
			for(int j=8; j>=0;j--)
				if(cell[i][j].isDynamic)
					return true;
	return false;
}
*/

const Pos*  Matrix::getLastDynamicPosPtr(){
	for(int i=8; i>=0;i--)
		for(int j=8; j>=0;j--)
			if(cell[i][j].isDynamic)
				return &cell[i][j].pos;
	return NULL;
}



bool Matrix::DynamicCellIterator::iterateForward(){

	int i = (currentCellPtr->pos).getx() ;
	int j = (currentCellPtr->pos).gety()+1;

	while(i<=8){
		while(j<=8){
			if(outerRef.cell[i][j].isDynamic){
					currentCellPtr = &(outerRef.cell[i][j]);
					return true;// successful iteration.
			}
			j++;
		}
		i++;
		j=0;
	}

	 currentCellPtr = NULL;
	 return false; //non successful iterations.
}

bool Matrix::DynamicCellIterator::iterateBackward(){

	int i = (currentCellPtr->pos).getx() ;
	int j = (currentCellPtr->pos).gety()-1;

	while(i>=0){
		while(j>=0){
			if(outerRef.cell[i][j].isDynamic){
					currentCellPtr = &(outerRef.cell[i][j]);
					return true;// successful iteration.
			}
			j--;
		}
		i--;
		j=8;
	}

	 currentCellPtr = NULL;
	 return false; //non successful iterations.
}
