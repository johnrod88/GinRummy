#include "points.h"
#include <iostream>
using namespace std;

// Function that determines whether player or computer gets under cut and points to add.
 void addPoints(int& userScore, int& pcScore, int& userDeadwood, int& pcDeadwood, int knock)	
 {
	
	int undercutPoints = 25;
	int ginPoints = 25;
	int pointDiff = 0;
	
	if (knock == 2 || knock ==3){
	if ((pcDeadwood < userDeadwood) && (pcDeadwood == 0)) {
		pcScore = pcScore + ginPoints + userDeadwood;
	}
	else if(pcDeadwood < userDeadwood){
		pointDiff = userDeadwood - pcDeadwood;
		pcScore = pcScore + pointDiff;
	}
	else {
		pointDiff = pcDeadwood - userDeadwood;
		userScore = userScore + undercutPoints + pointDiff;
	}
	}
	
	if (knock == 1){
	if ((userDeadwood < pcDeadwood) && (userDeadwood == 0)){
		userScore = userScore + ginPoints + pcDeadwood;
	}
	else if(userDeadwood < pcDeadwood){
		pointDiff = pcDeadwood - userDeadwood;
		userScore = userScore + pointDiff;
	}
	else {
		pointDiff = userDeadwood - pcDeadwood;
		pcScore = pcScore + undercutPoints + pointDiff;
	}
	}
}

