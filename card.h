#ifndef CARD_H
#define CARD_H

//#include <iostream>

using namespace std;

class card 
{
	public:
	card();
	card(int num, string s);
	card(string r, string s);
	string getRank() const;
	string getSuit() const;
	int getValue() const;
	string description() const;
		
	private:
	string rank;
	string suit;
	int value;
		
};

#endif
