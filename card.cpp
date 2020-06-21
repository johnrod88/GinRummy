#include <iostream>
#include <string>
#include "card.h"

using namespace std;

int faceValue(string x)
{
	if (x == "A")
	{
		return 1;
	}
	else if ((x == "J")||(x == "Q")||(x == "K"))
	{
		return 10;
	}
	else
	{
		return stoi(x);
	}
} 

card::card() 
{
	int value = 0;	
}

card::card(int num, string s) 
{
	rank = to_string(num);
	suit = s;
	value = faceValue(to_string(num));	
}

card::card(string r, string s) 
{
	rank = r;
	suit = s;
	value = faceValue(r);	
}

string card::getRank() const
{
	return rank;
}

string card::getSuit() const
{
	return suit;
}

int card::getValue() const
{
	return value;
}
 
string card::description() const
{
	string x = rank + " <" + suit +">";
	return x;
}
