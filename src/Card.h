/*
 * Card.h
 *
 *  Created on: Mar 31, 2014
 *      Author: eilel
 */

#ifndef CARD_H_
#define CARD_H_

enum ECardType{
	keDiamonds = 20,
	keClubes,
	keHearts,
	keSpades
};

class Card {
private:
	int value;
	ECardType type;
public:
	Card(ECardType,int);
	int getValue();
	void setValue(int);
	ECardType getType();
	void setType(ECardType);
};

#endif /* CARD_H_ */
