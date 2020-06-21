#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include "card.h"
#include "pcMoves.h"
#include "points.h"

#if defined(_WIN32)
#include <cstdlib>
#define OS_WINDOWS
#endif


using namespace std;

//Constants for menu choices
const int PLAY = 1, QUIT = 2,
		  DRAW_DECK = 1, DRAW_DISCARD = 2,
		  SWAP_POS = 1, KNOCK = 2, END_TURN = 3,
		  PLAYER_KNOCK = 1, PC_KNOCK = 2, PC_GIN = 3,
		  PC_DISC_DRAW = 1, PC_DECK_DRAW = 2;

//Function Prototypes
int displayMenu(); // Displays the main menu e.g. Play or quit
void createDeck(vector<card>&); //Creates a new deck of 52 cards, then shuffles it.
void deal(vector<card>&, vector<card>&, vector<card>&, vector<card>&); // deals 10 cards to playerHand, 10 to pcHand, and one to the discard pile.
void clearScreen(); //Clears the console screen.
void showCards(vector<card>&, vector<card>&, vector<card>&, int, int, int, int); //Shows the players hand, # cards left in deck, and discardPile top card.
void drawAndDisc(vector<card>&, vector<card>&, vector<card>&, int, int, int); //function used for player to draw card from deck or discardpile, then discard from hand.
int moveMenu(vector<card>&, vector<card>&, vector<card>&, vector<card>&, vector<int>&, //Menu for player to reposition cards in hand, knock, or end turn
			  vector<int>&, vector<int>&, int&, int, int, int);
void createMelds(vector<card>&, vector<card>&, vector<card>&, vector<int>&, vector<int>&, vector<int>&, int, int, int, int); //Allows player to select melds when knock is chosen.
void whichCard(int); //Used in creatMelds function when building melds. It only cout's current meld card selection. i.e. First card, Second card. etc.
bool validMeld(vector<card>, vector<int>); //Tests whether the meld chosen by the player is valid or not.
bool doneMelds(); // Menu that asks whether the player is finished making melds. 
int playerDw(vector<card>, vector<int>, vector<int>, vector<int>); //Calculates the amount of deadwood in players hand. Used after melds are chosen.
void knockDisplay(vector<card>, vector<card>, int, int, int, int);
int nextRound();

int main()
{
	vector<card> deck;
	vector<card> playerHand;
	vector<card> pcHand;
	vector<card> discardPile;
	vector<int> meld1; //Stores player's 1st meld selection
	vector<int> meld2; //Stores player's 2nd meld selection
	vector<int> meld3; //Stores player's 3rd meld selection. There will never be more than 3 melds.
	int pcDeadWood = 0; //Stores opponents dw.
	int playerDeadWood = 0; //Stores Player's dw.
	int playerScore = 0;
	int pcScore = 0;
	int knock = 0;
	int pcDraw = 0;
	
	int choice; //Variable for menu choice  
			  
	//Intro to user
	cout << "Welcome to Gin Rummy!" << endl << endl;
	choice = displayMenu(); //Displays the main menu at start of program
	
	do
	{
		if (choice == PLAY)
		{
			int gameOver = 0;
			pcDraw = 0;
			createDeck(deck); //Creates a new deck everytime new round is played.
			deal(deck, playerHand, pcHand, discardPile); //Deals the cards.
			while (gameOver == 0) 
			{
				drawAndDisc(deck, playerHand, discardPile, playerScore, pcScore, pcDraw); //Player must draw, then discard at start of every turn.
				knock = moveMenu(deck, playerHand, pcHand, discardPile, meld1, meld2, meld3, playerDeadWood, playerScore, pcScore, pcDraw); //player then has to knock or end turn.
				if(knock == PLAYER_KNOCK)//If player knock was successful
				{
					addPoints(playerScore, pcScore, playerDeadWood, pcDeadWood, knock);
					knockDisplay(playerHand, pcHand, playerDeadWood, pcDeadWood, playerScore, pcScore);
					if(playerDeadWood < pcDeadWood)
					{
						if(playerDeadWood == 0)
						    cout << "\nYOU WENT GIN!!!";
						cout << "\nYou won this round!!!!\n";
					}					
					else
					{
						cout << "\nYou lost this round.\n";
					}
					gameOver = 1;									
				}
				if(gameOver == 0)
				{
					knock = pcMove(deck, pcHand, discardPile, pcDeadWood, pcDraw);//pc turn
					if(knock == PC_KNOCK || knock == PC_GIN)//If pc knocked
					{
						showCards(deck, playerHand, discardPile, playerScore, pcScore, knock, pcDraw);
						createMelds(deck, playerHand, discardPile, meld1, meld2, meld3, playerScore, pcScore, knock, pcDraw);
						playerDeadWood = playerDw(playerHand, meld1, meld2, meld3);
						addPoints(playerScore, pcScore, playerDeadWood, pcDeadWood, knock);
						knockDisplay(playerHand, pcHand, playerDeadWood, pcDeadWood, playerScore, pcScore);
						if(playerDeadWood <= pcDeadWood)
						{
							cout << "\nYou won this round!!!!\n";
						}						
						else
						{
							cout << "\nYou lost this round.\n";
						}
						gameOver = 1;
					}
				}
				if ((deck.size() <= 2) && (gameOver == 0))//if only 2 deck cards left, game ends in draw.
				{
					cout << "The deck has been drawn down to only 2 cards, so this round is a draw!\n";
					gameOver = 1;
				}
			}
			if (playerScore > 100)
			{
				cout << "You have reached 100 points, so you won the game!!!!\n"
					 << "Thanks for playing.\n";
				choice = QUIT;
			}
			if (pcScore > 100)
			{
				cout << "Your opponent has reached 100 points, so you lost the game.\n"
					 << "Better luck next time.\n";
					 choice = QUIT;
					
			}
			if (choice != QUIT)
			{
				choice = nextRound(); 
			}
		}
		
	}while (choice != QUIT);	
	return 0;
}

//This function displays the main menu and returns the user's validated selection.
int displayMenu()
{
	double selection;
	string menu = "1 - Play Gin Rummy\n2 - Quit\n\nEnter your choice: ";
	
	cout << menu;
	cin >> selection;
		
	while ( (cin.fail()) || ((int(selection) != PLAY) && (int(selection) != QUIT))) //Validates input
		{
			cin.clear(); //clears the invalid selection
			cin.ignore(999, '\n'); //ignores anything else left in input buffer.
			
			cout << endl;
			cout << "You have made an invalid entry." << endl
				 << "Please choose one of the following options." << endl;
			cout << menu;
			cin >> selection;
				 
		}
	
	return int(selection); //Returns validated selection
}

void createDeck(vector<card>& newDeck) //Creates a new deck of 52 cards, then shuffles it.
{
	string suits [4] = {"H", "D", "S", "C"};
	string royals [4] = {"A", "J", "Q", "K"};
	newDeck.clear();
	newDeck.shrink_to_fit();
	
	//Creates cards 2 thru 10
	for (int i = 2; i < 11; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newDeck.push_back(card(i, suits[j]));
		}
				
	}
	
	//Creates Aces and Royals
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			newDeck.push_back(card(royals[i], suits[j]));
		}
				
	}
	
	srand(time(0)); //creates a seed for random generator.
	random_shuffle(newDeck.begin(), newDeck.end()); //Shuffles deck.
		
}

void deal(vector<card>& d, vector<card>& player, vector<card>& pc, vector<card>& disc) // deals 10 cards to playerHand, 10 to pcHand, and one to the discard pile.
{
	player.clear();
	player.shrink_to_fit();
	pc.clear();
	pc.shrink_to_fit();
	disc.clear();
	disc.shrink_to_fit();
	for (int k = 0; k < 10; k++)
	{
		player.push_back(d.back());
		d.pop_back();
		pc.push_back(d.back());
		d.pop_back();
	}
	
	disc.push_back(d.back());
	d.pop_back();	
}

void clearScreen()
{
	#ifdef OS_WINDOWS //If running Windows
	system("CLS");
	#else
	cout << "\033[2J" << "\033[H"; //ANSI escape codes to clear screen and move cursor to upper left.
	#endif
}

void showCards(vector<card>& d, vector<card>& player, vector<card>& disc, int playerScore, int pcScore, int knock, int pcDraw) //Shows the players hand, # cards left in deck, and discardPile top card.
{
	clearScreen();
	if ((knock != 0) || (pcDraw != 0))
	{
		if (player.size() == 11)
		    cout << "------------------------------------------------------------------------------------------\n";
		else 
		    cout << "-----------------------------------------------------------------------------------\n";
	}
	
	if (knock == PC_GIN)
	{
		cout << "Your opponent has called Gin!!!\n"
        	 << "Assemble your melds to calculate your deadwood.\n";
	}
	else if (knock == PC_KNOCK)
	{
		cout << "Your opponent has knocked.\n"
        	 << "Assemble your melds to calculate your deadwood.\n";
	}
	else if (pcDraw == PC_DISC_DRAW)
	{
		cout << "Your opponent drew from the discard pile, then discarded a card.\n";
	}
	else if (pcDraw == PC_DECK_DRAW)
	{
		cout << "Your opponent drew from the deck, then discarded a card.\n";
	}
	
	if (player.size() == 11) //if displaying after drawing a card. Playe has 11 cards in hand.
	{
		cout << "------------------------------------------------------------------------------------------\n" 
			 << "    Deck Cards Left                                      Discard Pile Top Card \n"
			 << "          "<<d.size()<<"                                                    ";
		if (disc.size() != 0) //Displays top card on discard pile.
		{
			cout << "|" << disc[disc.size()-1].description() << "|\n\n";
		}
		else //Displays nothing if no cards in discard pile.
		{
			cout << "\n\n";
		}
		
		cout << "                        Your Score      Opponent's Score\n"
			 << "                            " << playerScore << "                  " << pcScore << "\n\n";

		cout << "                               Your Hand \n";
		 
		for(int l = 0; l < player.size(); l++)
		{
			cout << "|" << player[l].description() << "| ";
		}
		cout << endl;
	 
		for (int m = 1; m <= player.size(); m++)
		{
			cout << "   [" << m << "]  "; 
		}
		 cout << "\n------------------------------------------------------------------------------------------\n";
	}
	else // Display if player only has 10 card in hand. 
	{
		cout << "-----------------------------------------------------------------------------------\n" 
			 << "    Deck Cards Left                                      Discard Pile Top Card \n"
			 << "          "<<d.size()<<"                                                    ";
		if (disc.size() != 0)
		{
			cout << "|" << disc[disc.size()-1].description() << "|\n\n";
		}
		else
		{
			cout << "\n\n";
		}
	
		cout << "                        Your Score      Opponent's Score\n"
			 << "                            " << playerScore << "                  " << pcScore << "\n\n";
	
		cout << "                                Your Hand \n";
		 
		for(int l = 0; l < player.size(); l++)
		{
			cout << "|" << player[l].description() << "| ";
		}
		cout << endl;
	 
		for (int m = 1; m <= player.size(); m++)
		{
			cout << "   [" << m << "]  "; 
		}
		 cout << "\n-----------------------------------------------------------------------------------\n";
	}
}

void drawAndDisc(vector<card>& d, vector<card>& myHand, vector<card>& disc, int playerScore, int pcScore, int pcDraw) //function used for player to draw card from deck or discardpile, then discard from hand.
{
	double selection1, selection2;
	showCards(d, myHand, disc, playerScore, pcScore, 0, pcDraw);
	cout << "What would you like to do?\n";
	string  drawMenu =   "1. Draw from the Deck\n";
		 	drawMenu +=  "2. Draw from the Discard Pile\n";
		 	drawMenu +=  "Enter your choice: ";
		 	
	string  discardMenu =  "Which card in your hand would you like to discard?\n";
			discardMenu += "Enter a number 1-11: ";	
	
	cout << drawMenu;	 
	cin >> selection1;
		
	while ( (cin.fail()) || ((int(selection1) != DRAW_DECK) && (int(selection1) != DRAW_DISCARD)))
		{
			cin.clear();
			cin.ignore(999, '\n');
			
			cout << endl;
			cout << "You have made an invalid entry." << endl
				 << "Please choose one of the following options." << endl;
			cout << drawMenu;
			cin >> selection1;
			//cout << endl; 
	 
		}
		
	if (int(selection1) == DRAW_DECK) //If player draws from deck.
	{
		myHand.push_back(d.back()); //Add selected card to hand.
		d.pop_back(); //Delete selected card from deck.
	}
	else //If player draws from discard pile.
	{
		myHand.push_back(disc.back()); //Add selected card to hand.
		disc.pop_back(); //Delete selected card from discard pile.
	}
	
	showCards(d, myHand, disc, playerScore, pcScore, 0, pcDraw); //Shows players hand once a card was drawn. Player has 11 cards now.
	cout << discardMenu; 
	cin >> selection2;
	
	while ( (cin.fail()) || (int(selection2) < 1) || (int(selection2) > 11)) //Validates input for choosing a card to discard.
		{
			cin.clear();
			cin.ignore(999, '\n');
			
			cout << endl;
			cout << "You have made an invalid entry." << endl
				 << "Please choose one of the following options." << endl;
			cout << discardMenu;
			cin >> selection2;
			
		}
	disc.push_back(myHand[selection2 - 1]); //Adds selected card to discard pile.
	myHand.erase(myHand.begin()+(selection2 - 1)); //Deletes selected card from hand.
	//Next 2 lines of code put the drawn card in the same spot as the card the player just discarded
	//so that all other cards keep their previous positions.
	myHand.insert(myHand.begin()+(selection2 - 1), myHand.back());
	myHand.pop_back();
}

int moveMenu(vector<card>& d,vector<card>& myHand, vector<card>& opHand, vector<card>& disc, vector<int>& meldA, vector<int>& meldB, vector<int>& meldC, int& dw, int playerScore, int pcScore, int pcDraw)
{
	double selectionA, selectionB;
	string  moveOptions =   "1. Swap card position\n";
		 	moveOptions +=  "2. Knock\n";
	 		moveOptions +=  "3. End your turn\n";
		 	moveOptions +=  "Enter your choice: ";
		 	
	string  discardMenu =  "Which card in your hand would you like to discard?\n";
			discardMenu += "Enter a number 1-11: ";	
	
	while (selectionA != END_TURN) //Loops as long as player doesn't end turn.
	{
		showCards(d, myHand, disc, playerScore, pcScore, 0, pcDraw);
		cout << "What would you like to do?\n";
			
		cout << moveOptions;	 
		cin >> selectionA;
		
		while ( (cin.fail()) || (int(selectionA) < SWAP_POS) || (int(selectionA) > END_TURN))
		{
			cin.clear();
			cin.ignore(999, '\n');
		
			cout << endl;
			cout << "You have made an invalid entry." << endl
				 << "Please choose one of the following options." << endl;
			cout << moveOptions;
			cin >> selectionA;
		}
		
		if(selectionA == SWAP_POS) //Used to switch card positions in player's hand
		{
			double card1, card2; //Stores card selections
			vector<card>::iterator it = myHand.begin();
			cout << "Select which cards you would like to swap by entering a number 1-10.\n"
				 << "First card: ";
			 
			cin >> card1;
			while ( (cin.fail()) || (int(card1) < 1) || (int(card1) > 10))
			{
				cin.clear();
				cin.ignore(999, '\n');
			
				cout << endl;
				cout << "You have made an invalid entry." << endl
					 << "Please choose a number between 1 and 10." << endl;
				cout << "First card: ";
				cin >> card1;
				//cout << endl; 
	 
			}
		
			cout << "Second card: ";
			cin >> card2;
			while ( (cin.fail()) || (int(card1) < 1) || (int(card1) > 10))
			{
				cin.clear();
				cin.ignore(999, '\n');
			
				cout << endl;
				cout << "You have made an invalid entry." << endl
					 << "Please choose a number between 1 and 10." << endl;
				cout << "Second card: ";
				cin >> card2;
			}
		
			if (int(card1) != int(card2)) //If a player is not trying to swap a card with itself.
			{
				int a = 0, b=0;
				if(int(card1) < int(card2))
				{
					a = int(card1) - 1;
					b = int(card2) - 1;
				}
				else
				{
					a = int(card2) - 1;
					b = int(card1) - 1;
				}
			
				myHand.insert(it + a, myHand[b]);
				myHand.erase(it + (b+1));
				myHand.insert(it + (b+1), myHand[a+1]);
				myHand.erase(it + (a+1));
			}
			//If player tries to swap a card position with it's own position
			//nothing is done.
		}
		
		if(selectionA == KNOCK)
		{
			createMelds(d, myHand, disc, meldA, meldB, meldC, playerScore, pcScore, 0, pcDraw); //Player chooses/builds their melds.
			dw = playerDw(myHand, meldA, meldB, meldC);
			if (dw > 10) //If player's deadwood is more than 10 points.
			{
				cout << "You have too much deadwood, so you can not knock.\n";
				cout << "The value of your dead wood is " << playerDw(myHand, meldA, meldB, meldC) 
					 << ",\nand you must have less than 10.\n\n"
					 << "Press ENTER key to continue...";
					 
				cin.clear();
				cin.ignore(999, '\n');
				cin.ignore(999, '\n');
				//cin.get();
				
			}
			else if (dw == 0) //If player's deadwood is 0.
			{
				//cout << "Gin!!!!\n";
				return PLAYER_KNOCK;
			}	
			else //if player's deadwood is less than 10.
			{
				//cout << "The value of your dead wood is " << playerDw(myHand, meldA, meldB, meldC) << ".\n\n";
				return PLAYER_KNOCK; 
			}
		}
	}
	return 0;
}

void createMelds(vector<card>& deck1, vector<card>& hand, vector<card>& dPile, vector<int>& meldX, vector<int>& meldY, vector<int>& meldZ, int playerScore, int pcScore, int knock, int pcDraw) //Function for player to select meld cards.
{
	int over = 0, finished = 0;
	int melds = 0; //to hold number of melds made by player. 
	int count = 1; //to hold number of cards in meld currently being created.
	meldX.clear(); //Clears any melds made in previous moves.
	meldX.shrink_to_fit(); //shrinks capacity of empty vector to 0.
	meldY.clear(); //Clears any melds made in previous moves.
	meldY.shrink_to_fit(); //shrinks capacity of empty vector to 0.
	meldZ.clear(); //Clears any melds made in previous moves.
	meldZ.shrink_to_fit(); //shrinks capacity of empty vector to 0.
			
	while (over == 0)
	{
	
		double selectionX = 0;
		string first = "Select the cards for your first meld.\n",
			  second = "Select the cards for your second meld.\n",
			   third = "Select the cards for your third meld.\n",
			    done = "Enter 0 if you are done making this meld.\n";
		while (finished == 0)
		{
			if (melds == 0)
			{
				cout << first << done;
			}
			else if (melds == 1)
			{
				if (count == 1)
				{
					showCards(deck1, hand, dPile, playerScore, pcScore, knock, pcDraw);
				}
				
				cout << second << done;
			}
			else
			{
				if (count == 1)
				{
					showCards(deck1, hand, dPile, playerScore, pcScore, knock, pcDraw);
				}
				cout << third << done;
			}
			
			whichCard(count);
									
			cin >> selectionX;
			while ( (cin.fail()) || (int(selectionX) < 0) || (int(selectionX) > 10))
			{
				cin.clear();
				cin.ignore(999, '\n');
			
				cout << endl;
				cout << "You have made an invalid entry." << endl
					 << "Please choose a number between 1 and 10, or 0 to finish this meld." << endl;
				whichCard(count);
				cin >> selectionX;
			}
			bool usedBefore = false;
			if(selectionX != 0)
			{
				do
				{
					usedBefore = false;
					if(melds == 0)
					{
						for(int i = 0; i < meldX.size(); i++)
						{
							if(selectionX == meldX[i])
							usedBefore = true;
						}
					}
					else if(melds == 1)
					{
						for(int i = 0; i < meldX.size(); i++)
						{
							if(selectionX == meldX[i])
							usedBefore = true;
						}
						for(int i = 0; i < meldY.size(); i++)
						{
							if(selectionX == meldY[i])
							usedBefore = true;
						}
					}
					else
					{
						for(int i = 0; i < meldX.size(); i++)
						{
							if(selectionX == meldX[i])
							usedBefore = true;
						}
						for(int i = 0; i < meldY.size(); i++)
						{
							if(selectionX == meldY[i])
							usedBefore = true;
						}
						for(int i = 0; i < meldZ.size(); i++)
						{
							if(selectionX == meldZ[i])
							usedBefore = true;
						}
					}
					
					if(usedBefore)
					{
						cout << "You have already selected this card to be part of a meld.\n"
							 << "Select another card or Enter 0 to finish this meld.\n";
						whichCard(count);
						cin >> selectionX;
						while ( (cin.fail()) || (int(selectionX) < 0) || (int(selectionX) > 10))
						{
							cin.clear();
							cin.ignore(999, '\n');
						
							cout << endl;
							cout << "You have made an invalid entry." << endl
								 << "Please choose a number between 1 and 10, or 0 to finish this meld." << endl;
							whichCard(count);
							cin >> selectionX;
						}
						
					}
					
				}while(usedBefore == true);
			}
			
			if ((int(selectionX) != 0) && (melds == 0)) //If making meld 1.
			{
				meldX.push_back(int(selectionX)); //Adds selected card position (1-10) to 1st meld vector.
				count++;
			}
			else if ((int(selectionX) != 0) && (melds == 1)) //If making meld 2.
			{
				meldY.push_back(int(selectionX)); //Adds selected card position (1-10) to 2nd meld vector.
				count++;
			}
			else if ((int(selectionX) != 0) && (melds == 2)) //If making meld 3.
			{
				meldZ.push_back(int(selectionX)); //Adds selected card position (1-10) to 3rd meld vector.
				count++;
			}
			else
			{
				count = 1; //Resets 'count' variable for next meld.
				if (melds == 0)
				{
					if (!validMeld(hand, meldX)) //If 1st meld not valid.
					{
						cout << "That was not a valid meld.\n";
						meldX.clear(); //Deletes entries of invalid meld.
						meldX.shrink_to_fit();
						if (doneMelds())
						{
							finished = 1;
							over = 1;
						}			
					}
					else
					{
						melds++;
					}
					
				}
				else if (melds == 1)
				{
					if (!validMeld(hand, meldY)) //If 2nd meld not valid.
					{
						cout << "That was not a valid meld.\n";
						meldY.clear(); //Deletes entries of invalid meld.
						meldY.shrink_to_fit();
						if (doneMelds())
						{
							finished = 1;
							over = 1;
						}			
					}
					else
					{
						melds++;
					}
				}
				else if (melds == 2) 
				{
					if (!validMeld(hand, meldZ)) //If 3rd meld not valid.
					{
						cout << "That was not a valid meld.\n";
						meldZ.clear(); //Deletes entries of invalid meld.
						meldZ.shrink_to_fit();
						if (doneMelds())
						{
							finished = 1;
							over = 1;
						}	
					}
					else
					{
						melds++;
					}
				}
				else 
				{
					melds++;
				}
			}
			
			if (melds >= 3)
			{
				finished = 1;
				over = 1;
			}
									
		}

	}	
}

void whichCard(int n)
{
	if (n == 1) 
		cout << "First card: ";
	else if (n == 2) 
		cout << "Second card: ";	
	else if (n == 3) 
		cout << "Third card: ";
	else if (n == 4) 
		cout << "Fourth card: ";	
	else if (n == 5) 
		cout << "Fifth card: ";	
	else if (n == 6) 
		cout << "Sixth card: ";
	else if (n == 7) 
		cout << "Seventh card: ";
	else if (n == 8) 
		cout << "Eigth card: ";
	else if (n == 9) 
		cout << "Ninth card: ";
	else 
		cout <<	"Tenth card: ";
}

bool validMeld(vector<card> h, vector<int> i) //Tests whether the meld chosen by the player is valid or not.
{
	vector<card> test;
	vector<int> runTest;
	vector<int> runTestCopy;
	
	bool sameRank = true,
		 sameSuit = true,
		 isRun = true;
		 
	if (i.size() < 3) //If meld is less than 3 cards.
	{
		return false;
	}
		 
	for (int a = 0; a < i.size(); a++) //Stores the card objects of the cards chosen in meld.
	{
		test.push_back(h[(i[a]-1)]);
	}
	
	for (int b = 0; b < test.size(); b++) //Tests to see if the meld cards aren't all same rank.
	{
		if(test[0].getRank() != test[b].getRank())
		{
			sameRank = false;	
		}	
	}
	
	for (int c = 0; c < test.size(); c++) //Tests to see if the meld cards aren't all same suit.
	{
		if(test[0].getSuit() != test[c].getSuit())
		{
			sameSuit = false;	
		}
	}
	
	for (int d = 0; d < test.size(); d++) //Stores the rank number of the cards chosen in meld.
	{
		if (test[d].getRank() == "A")
		{
			runTest.push_back(1);
		}
		else if (test[d].getRank() == "J")
		{
			runTest.push_back(11);
		}
		else if (test[d].getRank() == "Q")
		{
			runTest.push_back(12);
		}
		else if (test[d].getRank() == "K")
		{
			runTest.push_back(13);
		}
		else
		{
			runTest.push_back(stoi(test[d].getRank()));
		}
	}
	
	sort(runTest.begin(), runTest.end()); //Sorts the vector of card rank numbers in ascending order.
	runTestCopy.assign(runTest.begin(), runTest.end()); //Creates a copy of vector containing sorted card rank numbers.
	
	for (int e = 0; e < (runTest.size() - 1); e++) //Tests to see if the meld cards aren't a proper run.
	{
		if (runTest[e] != (runTestCopy[e + 1] - 1))
		{
			isRun = false;
		}
	}
	
	if (sameRank == true) //If all ranks match.
	{
		return true;
	}
	else if ((isRun == true) && (sameSuit == true)) //If meld is a proper run.
	{
		return true;
	}
	else //Meld not all matches or a run.
	{
		return false;
	}
		
}

bool doneMelds() // Menu that asks whether the player is finished making melds.
{
	char answer;
	cout << "Are you done making melds?\n"
		 << "Enter Y or N: ";
		 
	cin >> answer;
	
	while ( (cin.fail()) || ((answer != 'Y') && (answer != 'N') && (answer != 'y') && (answer != 'n')))
	{
		cin.clear();
		cin.ignore(999, '\n');
		
		cout << endl;
		cout << "You have made an invalid entry." << endl
			 << "Please enter Y or N: ";
		cin >> answer;
		//cout << endl; 
	
	}
	
	if((answer == 'Y') || (answer == 'y'))
	{
		cout << endl;
		return true;
	}
	
	if((answer == 'N') || (answer == 'n'))
	{
		cout << endl;
		return false;
	}
}

int playerDw(vector<card> h, vector<int> a, vector<int> b, vector<int> c) //Calculates the amount of deadwood in players hand. Used after valid melds are chosen.
{
	vector<card> meldedCards;
	int deadCount = 0;
	int handVal = 0;
	
	for (int l = 0; l < h.size(); l++) //Calculates deadwood value for entire hand as if there are no melds.
	{
		handVal += h[l].getValue();
	}
	
	if (a.size() == 0) //If there are no melds.
	{
		return handVal;
	}
	
	for (int m = 0; m < a.size(); m++ )	//Stores card objects of cards that are part of 1st meld.
	{
		meldedCards.push_back(h[a[m] - 1]);
	}
	
	if (b.size() != 0) //Stores card objects of cards that are part of 2nd meld.
	{
		for (int n = 0; n < b.size(); n++ )	
		{
			meldedCards.push_back(h[b[n] - 1]);
		}
	}
	
	if (c.size() != 0) //Stores card objects of cards that are part of 3rd meld.
	{
		for (int o = 0; o < c.size(); o++ )	
		{
			meldedCards.push_back(h[c[o] - 1]);
		}
	}

	for(int p = 0; p < meldedCards.size(); p++) //Calculates deadwood value.
	{
		for(int q = 0; q < h.size(); q++)
		{
			if ((meldedCards[p].getRank() == h[q].getRank()) && (meldedCards[p].getSuit() == h[q].getSuit()))
			{
				handVal -= h[q].getValue(); //subtracts value of meld cards from total hand value
			}
		}
	}
	
	deadCount = handVal;
	return deadCount; //Returns deadwood value.
}

void knockDisplay(vector<card> player, vector<card> pcHand, int playerDeadWood, int pcDeadWood, int playerScore, int pcScore)
{
	clearScreen();
	cout << "-----------------------------------------------------------------------------------\n"; 
		 
	for(int l = 0; l < pcHand.size(); l++)
	{
		cout << "|" << pcHand[l].description() << "| ";
	}
	cout << "\n"
		 << "                             Opponent's Hand \n\n";
	cout << "    Your Deadwood                                        Your Opponent's Deadwood  \n"
		 << "         "<<playerDeadWood<<"                                                       "
		 << pcDeadWood << "\n\n";
		 
	cout << "                        Your Score      Opponent's Score\n"
		 << "                            " << playerScore << "                  " << pcScore << "\n\n";
	
	cout << "                                Your Hand \n";
	 
	for(int l = 0; l < player.size(); l++)
	{
		cout << "|" << player[l].description() << "| ";
	}
	cout << endl;
    cout << "\n-----------------------------------------------------------------------------------\n";	
}

int nextRound() // Menu that asks whether the player wants to proceed to the next round.
{
	char answer;
	cout << "Would you like to play the next round?\n"
		 << "Enter Y to play or N to quit the game: ";
		 
	cin >> answer;
	
	while ( (cin.fail()) || ((answer != 'Y') && (answer != 'N') && (answer != 'y') && (answer != 'n')))
	{
		cin.clear();
		cin.ignore(999, '\n');
		
		cout << endl;
		cout << "You have made an invalid entry." << endl
			 << "Enter Y to play or N to quit the game: ";
		cin >> answer;
		//cout << endl; 
	
	}
	
	if((answer == 'Y') || (answer == 'y'))
	{
		cout << endl;
		return 1;
	}
	
	if((answer == 'N') || (answer == 'n'))
	{
		return 2;
	}
}
