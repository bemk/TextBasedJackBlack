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
	int endTurn = 0;

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
				break;
			}
		}
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
/*
	void shuffle(int size){
		Card tempCardList[52];
		for (int i = 0; i < size; ++i){
			int x = 0;
		}
	} */
	//TODO: Shuffle list
	//TODO: DrawCard method
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
	//---------------------------------\\
	//For the wiringPi
	wiringPiSetup();
	pinMode (0, OUTPUT);
	//---------------------------------\\
	while(input != 'n'){
		//Debug reasons for the LEDS on the Pi
		digitalWrite(0, HIGH);
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


