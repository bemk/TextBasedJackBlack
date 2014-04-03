/*
 * Card.cpp
 *
 *  Created on: Mar 31, 2014
 *      Author: eilel
 */
#include "Card.h"

Card::Card(ECardType type, int value){
	this->type = type;
	this->value = value;
}

int Card::getValue(){
	return this->value;
}

void Card::setValue(int value){
	// in line if statement
	// if(type>10) value = 10; else value = type;
	this->value = value > 10 ? 10 : value;
}

ECardType Card::getType(){
	return this->type;
}

void Card::setType(ECardType eCardtype){
	this->type = eCardtype;
}


