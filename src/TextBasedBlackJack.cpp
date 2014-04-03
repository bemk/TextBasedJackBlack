//============================================================================
// Name        : TextBasedBlackJack.cpp
// Author      : Jelle Braat
// Version     :
// Copyright   : Comfy Corparation
// Description : Black Jack in C++, Comfy-style
//============================================================================
#include "Card.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <wiringPi.h>

using namespace std;


class BlackJack{
private:
	vector<Card> cardsInHand;
	// Ace not included
	vector<Card> cardsInDeck;
	int endTurn;

	void fillCards(){
		int i = 0;
		for (int ind = 20; ind < 24; ++ind){
			for (int j = 2; j < 14; ++j){
				Card card ((ECardType)ind, j);
				cardsInDeck.push_back(card);
				++i;
			}
		}
	}

	void startDraw(){
		srand(time(NULL));
		int draw = rand() % cardsInDeck.size();
		addCardToHand(cardsInDeck[draw]);
		cardsInDeck.erase(cardsInDeck.begin() + draw - 1);
		draw = rand() % cardsInDeck.size();
		addCardToHand(cardsInDeck[draw]);
		cardsInDeck.erase(cardsInDeck.begin() + draw - 1);
	}
	void drawCard(){
		srand(time(NULL));
		int draw = rand() % cardsInDeck.size();
		addCardToHand(cardsInDeck[draw]);
		cardsInDeck.erase(cardsInDeck.begin() + draw - 1);
	}

	void inputCheck(char input){
		switch(input){
		case 'y':
			drawCard();
			break;
		case 'n':
			endTurn = 1;
			break;
		default:
			cout << "try a different command" << endl;
			break;
		}
	}
	void print(){
		cout << "number of cards in hand: " << cardsInHand.size() << endl;
		cout << "total value: " << getTotal() << endl;
	}
	int computerSequence(){
		int total;
		vector<Card> computerCards;
		while (1){
			srand(time(NULL));
			int random = rand() % cardsInDeck.size();
			computerCards.push_back(cardsInDeck[random]);
			cardsInDeck.erase(cardsInDeck.begin() + random -1);
			total = 0;
			for(int i = 0; i < computerCards.size(); ++i){
				total += computerCards[i].getValue();
			}
			if (total > 15)
				break;
		}
		cout << "Computer total: " << total << endl;
		return total;
	}

public:
	int pinNumbers[6];

	BlackJack(){
		endTurn = 0;
		pinNumbers[0] = 15;
		pinNumbers[1] = 16;
		pinNumbers[2] = 1;
		pinNumbers[3] = 4;
		pinNumbers[4] = 5;
		pinNumbers[5] = 6;
	}
	void play(){
		fillCards();
//		printCards();
		startDraw();
		char input;
		while(!endTurn){
			print();
			cout << "Draw card? [y/n]" << endl;
			cin >> input;
			inputCheck(input);
			if (getTotal() > 21){
				print();
				cout << "you are dead" << endl;
				digitalWrite(pinNumbers[5], HIGH);
				return;
			}
			displayLED(getTotal());
		}
		displayLED(getTotal());
		int computerValue = computerSequence();
		if (computerValue > 21){
			cout << "You have won the game" << endl;
			return;
		}
		if (getTotal() > computerValue){
			cout << "you have won the game" << endl;
		}
		else{
			cout << "you have lost the game" << endl;
		}
	}
	void addCardToHand(Card card){
		cardsInHand.push_back(card);
	}
	int getNumberOfCards(){
		return cardsInHand.size();
	}
	int getTotal(){
		int total = 0;
		for (int i = 0; i < cardsInHand.size(); ++i)
			total += cardsInHand[i].getValue();
		return total;
	}
	void displayLED(int value){
		digitalWrite(pinNumbers[0], LOW);
		digitalWrite(pinNumbers[1], LOW);
		digitalWrite(pinNumbers[2], LOW);
		digitalWrite(pinNumbers[3], LOW);
		digitalWrite(pinNumbers[4], LOW);
		digitalWrite(pinNumbers[5], LOW);
		switch (value){
		case 4:
			digitalWrite(pinNumbers[2], HIGH);
			break;
		case 5:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[2], HIGH);
			break;
		case 6:
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[2], HIGH);
			break;
		case 7:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[2], HIGH);
			break;
		case 8:
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 9:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 10:
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 11:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 12:
			digitalWrite(pinNumbers[2], HIGH);
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 13:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[2], HIGH);
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 14:
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[2], HIGH);
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 15:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[2], HIGH);
			digitalWrite(pinNumbers[3], HIGH);
			break;
		case 16:
			digitalWrite(pinNumbers[4], HIGH);
			break;
		case 17:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[4], HIGH);
			break;
		case 18:
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[4], HIGH);
			break;
		case 19:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[1], HIGH);
			digitalWrite(pinNumbers[4], HIGH);
			break;
		case 20:
			digitalWrite(pinNumbers[2], HIGH);
			digitalWrite(pinNumbers[4], HIGH);
			break;
		case 21:
			digitalWrite(pinNumbers[0], HIGH);
			digitalWrite(pinNumbers[2], HIGH);
			digitalWrite(pinNumbers[4], HIGH);
			break;
		default:
			break;
		}
	}


	void printCards(){
		for (int i = 0; i < 48; ++i){
			switch(cardsInDeck[i].getType()){
			case 20:
				cout << cardsInDeck[i].getValue() << " of Diamonds." << endl;
				break;
			case 21:
				cout << cardsInDeck[i].getValue() << " of Clubs." << endl;
				break;
			case 22:
				cout << cardsInDeck[i].getValue() << " of Hearts." << endl;
				break;
			case 23:
				cout << cardsInDeck[i].getValue() << " of Spades." << endl;
				break;
			}
		}
	}
};

int main() {
	cout << "BlackJack" << endl; // prints BlackJack
	cout << "*-------------------*" << endl;
	char input;
	int pinNumbersArr[6] = {15,16,1,4,5,6};
	/*
	//---------------------------------\\
	//For the wiringPi
	wiringPiSetup();
	//setup for the LED pins number 5 is the red LED;
	for (int i = 0; i < 6; ++i){
		pinMode(pinNumbers[i], OUTPUT);
	}
	//pin 2 high pin 4 low
	pinMode(2, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(6, INPUT);
	digitalWrite(2, HIGH);
	digitalWrite(4, LOW);
	digitalWrite(6, LOW);
 	*/
	wiringPiSetup();

	pinMode(pinNumbersArr[0], OUTPUT);
	pinMode(pinNumbersArr[1], OUTPUT);
	pinMode(pinNumbersArr[2], OUTPUT);
	pinMode(pinNumbersArr[3], OUTPUT);
	pinMode(pinNumbersArr[4], OUTPUT);
	pinMode(pinNumbersArr[5], OUTPUT);
	digitalWrite(pinNumbersArr[0], LOW);
	digitalWrite(pinNumbersArr[1], LOW);
	digitalWrite(pinNumbersArr[2], LOW);
	digitalWrite(pinNumbersArr[3], LOW);
	digitalWrite(pinNumbersArr[4], LOW);
	digitalWrite(pinNumbersArr[5], LOW);

	while(input != 'n'){
//		for (int i = 0; i < 6; ++i){
//			digitalWrite(pinNumbers[i], HIGH);
//		}
		//Debug reasons for the LEDS on the Pi
		//delay(500);
		//digitalWrite(0, LOW);
		//delay(500);
		BlackJack blj;
		blj.play();
		cout << "Play again? [y/n]" << endl;
		cin >> input;
	}
	return 0;
}


