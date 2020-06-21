#include <iostream>
#include <algorithm>
#include <vector>
#include "card.h"
#include "pcMoves.h"

int pcMove(vector<card>& d, vector<card>& pcHand, vector<card>& discard, int& deadwood, int&pcDraw){
    deadwood = 0;
    vector<int> meldA;
    vector<int> meld2;
    vector<int> meld3;
    vector<int> meld4;
    vector<int> meld5;
    vector<int> meld6;
    vector<int> meld7;
    vector<int> meld8;
    vector<int> meld9;
    vector<int> meld10;
    vector<int> meldJ;
    vector<int> meldQ;
    vector<int> meldK;
    vector<card> pcReveal;
    vector<int> dwPosition;
        
//for testing
//	cout << "\nPC hand has " << pcHand.size() << " cards.\n\n";
//    for(int i = 0; i < pcHand.size(); i++)
//    {
//    	cout << "|" << pcHand[i].description() << "| ";
//	}
//	cout <<"\n\n";
//	cout <<"PC deadwood is " << deadwood << ".\n\n";
	
	
	//decides if pc wants card from discard pile
    for(int i = 0; i < 10; i++)
    {
    	if (discard.size() !=0)
		{		
			if((discard[discard.size()-1].getRank() == pcHand[i].getRank()) && (pcHand.size() == 10))
	    	{
	    		pcHand.push_back(discard.back()); //Draws from dicard pile
	    		discard.pop_back(); //Deletes the drawn card from discard pile
	    		pcDraw = 1;
			}
		}
	}
    
	if(pcHand.size() == 10) //if card wasn't drawn from discard pile
	{
		pcHand.push_back(d.back()); //Draws from deck
    	d.pop_back(); //Deletes the drawn card from deck
    	pcDraw = 2;
	}

//for testing	
//    cout << "\nPC hand has " << pcHand.size() << " cards.\n\n";
//    for(int i = 0; i < pcHand.size(); i++)
//    {
//    	cout << "|" << pcHand[i].description() << "| ";
//	}
//	cout <<"\n\n";
//	cout <<"PC deadwood is " << deadwood << ".\n\n";

    for(int z = 0; z <pcHand.size(); z++){ //finds matching ranks and stores indices in a set
        if(pcHand[z].getRank() == "A"){
            meldA.push_back(z);
        }   
        else if(pcHand[z].getRank() == "2"){
            meld2.push_back(z);
        }
        else if(pcHand[z].getRank() == "3"){
            meld3.push_back(z);
        }
        else if(pcHand[z].getRank() == "4"){ 
            meld4.push_back(z);
        }
        else if(pcHand[z].getRank() == "5"){
            meld5.push_back(z);
        }    
        else if(pcHand[z].getRank() == "6"){
            meld6.push_back(z);
        }    
        else if(pcHand[z].getRank() == "7"){
            meld7.push_back(z);
        }
        else if(pcHand[z].getRank() == "8"){ 
            meld8.push_back(z);
        }
        else if(pcHand[z].getRank() == "9"){
            meld9.push_back(z);
        }    
        else if(pcHand[z].getRank() == "10"){
            meld10.push_back(z);
        }
        else if(pcHand[z].getRank() == "J"){
            meldJ.push_back(z);
        }
        else if(pcHand[z].getRank() == "Q"){ 
            meldQ.push_back(z);
        }    
        else if(pcHand[z].getRank() == "K"){
            meldK.push_back(z);
        }
    }   
	 
    for(int z = 1; pcHand.size() == 11; z++){
		if(meldK.size() == z){ // discard the highest value card
	        //discard 
	        discard.push_back(pcHand[meldK[0]]);
			pcHand.erase(pcHand.begin() + meldK[0]);        
	    }
	    else if(meldQ.size() == z){
	        //discard
	        //pcHand[meldQ[0]];
	        discard.push_back(pcHand[meldQ[0]]);
	        pcHand.erase(pcHand.begin() + meldQ[0]); 
	    }
	    else if(meldJ.size() == z){
	        //discard
	        //pcHand[meldJ[0]];
	        discard.push_back(pcHand[meldJ[0]]);
	        pcHand.erase(pcHand.begin() + meldJ[0]); 
	    }
	    else if(meld10.size() == z){
	        //discard
	        //pcHand[meld10[0]];
	        discard.push_back(pcHand[meld10[0]]);
	        pcHand.erase(pcHand.begin() + meld10[0]); 
	    }
	    else if(meld9.size() == z){
	        //discard
	        //pcHand[meld9[0]];
	        discard.push_back(pcHand[meld9[0]]);
	        pcHand.erase(pcHand.begin() + meld9[0]); 
	    }
	    else if(meld8.size() == z){
	        //discard
	        //pcHand[meld8[0]];
	        discard.push_back(pcHand[meld8[0]]);
	        pcHand.erase(pcHand.begin() + meld8[0]);
	    }
	    else if(meld7.size() == z){
	        //discard
	        //pcHand[meld6[0]];
	        discard.push_back(pcHand[meld7[0]]);
	        pcHand.erase(pcHand.begin() + meld7[0]);
	    }
	    else if(meld6.size() == z){
	        //discard
	        //pcHand[meld5[0]];
	        discard.push_back(pcHand[meld6[0]]);
	        pcHand.erase(pcHand.begin() + meld6[0]);
	    }
	    else if(meld5.size() == z){
	        //discard
	        //pcHand[meld4[0]];
	        discard.push_back(pcHand[meld5[0]]);
	        pcHand.erase(pcHand.begin() + meld5[0]);
	    }
	    else if(meld4.size() == z){
	        //discard
	        //pcHand[meld3[0]];
	        discard.push_back(pcHand[meld4[0]]);
	        pcHand.erase(pcHand.begin() + meld4[0]);
	    }
	    else if(meld3.size() == z){
	        //discard
	        //pcHand[meld2[0]];
	        discard.push_back(pcHand[meld3[0]]);
	        pcHand.erase(pcHand.begin() + meld3[0]);
	    }
	    else if(meld2.size() == z){
	        //discard
	        //pcHand[meld2[0]];
	        discard.push_back(pcHand[meld2[0]]);
	        pcHand.erase(pcHand.begin() + meld2[0]);
	    }
	    else if (meldA.size() == z){
	        //discard
	        //pcHand[meldA[0]];
	        discard.push_back(pcHand[meldA[0]]);
	        pcHand.erase(pcHand.begin() + meldA[0]);
	    }
	}
    pcHand.shrink_to_fit();

//for testing    
//	cout << "PC hand has " << pcHand.size() << " cards.\n\n";
//    for(int i = 0; i < pcHand.size(); i++)
//    {
//    	cout << "|" << pcHand[i].description() << "| ";
//	}
//	cout <<"\n\n";
    
    
    //clear the meld vectors
    meldA.clear();
    meld2.clear();
    meld3.clear();
    meld4.clear();
    meld5.clear();
    meld6.clear();
    meld7.clear();
    meld8.clear();
    meld9.clear();
    meld10.clear();
    meldJ.clear();
    meldQ.clear();
    meldK.clear();
        
    //finds matching ranks and stores indices in a set
    //again after a card is discarded
	for(int z = 0; z < pcHand.size(); z++){ 
        if(pcHand[z].getRank() == "A"){
            meldA.push_back(z);
        }   
        else if(pcHand[z].getRank() == "2"){
            meld2.push_back(z);
        }
        else if(pcHand[z].getRank() == "3"){
            meld3.push_back(z);
        }
        else if(pcHand[z].getRank() == "4"){ 
            meld4.push_back(z);
        }
        else if(pcHand[z].getRank() == "5"){
            meld5.push_back(z);
        }    
        else if(pcHand[z].getRank() == "6"){
            meld6.push_back(z);
        }    
        else if(pcHand[z].getRank() == "7"){
            meld7.push_back(z);
        }
        else if(pcHand[z].getRank() == "8"){ 
            meld8.push_back(z);
        }
        else if(pcHand[z].getRank() == "9"){
            meld9.push_back(z);
        }    
        else if(pcHand[z].getRank() == "10"){
            meld10.push_back(z);
        }
        else if(pcHand[z].getRank() == "J"){
            meldJ.push_back(z);
        }
        else if(pcHand[z].getRank() == "Q"){ 
            meldQ.push_back(z);
        }    
        else if(pcHand[z].getRank() == "K"){
            meldK.push_back(z);
        }
    } 
    
    if(meldK.size() <= 2){// count deadwood
        for(int z = 0; z < meldK.size(); z++)
        {
        //add to count 
        deadwood = deadwood + pcHand[meldK[z]].getValue();   
		dwPosition.push_back(meldK[z]);
		}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meldK.size(); z++)
        { 
        pcReveal.push_back(pcHand[meldK[z]]);
		}
	}
    
	if(meldQ.size() <= 2){
        for(int z = 0; z < meldQ.size(); z++)
        {
		//add to count 
        deadwood = deadwood + pcHand[meldQ[z]].getValue();
        dwPosition.push_back(meldQ[z]);
		}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meldQ.size(); z++)
        { 
        pcReveal.push_back(pcHand[meldQ[z]]);
		}
	}
    
    if(meldJ.size() <= 2){
        for(int z = 0; z < meldJ.size(); z++)
        {
        //add to count 
        deadwood = deadwood + pcHand[meldJ[z]].getValue();
		dwPosition.push_back(meldJ[z]);
		}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meldJ.size(); z++)
        { 
        pcReveal.push_back(pcHand[meldJ[z]]);
		}
	}
    
    if(meld10.size() <= 2){
        for(int z = 0; z < meld10.size(); z++)
        {		
        //add to count 
        deadwood = deadwood + pcHand[meld10[z]].getValue(); 
   		dwPosition.push_back(meld10[z]);
		}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld10.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld10[z]]);
		}
	}
    
    if(meld9.size() <= 2){
        for(int z = 0; z < meld9.size(); z++)
        {
        //add to count 
        deadwood = deadwood + pcHand[meld9[z]].getValue();
        dwPosition.push_back(meld9[z]);
    	}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld9.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld9[z]]);
		}
	}
    
    if(meld8.size() <= 2){
        for(int z = 0; z < meld8.size(); z++)
        {
        //add to count 
        deadwood = deadwood + pcHand[meld8[z]].getValue(); 
        dwPosition.push_back(meld8[z]);
    	}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld8.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld8[z]]);
		}
	}
    
    if(meld7.size() <= 2){
        for(int z = 0; z < meld7.size(); z++)
        {
        //add to count 
        deadwood = deadwood + pcHand[meld7[z]].getValue(); 
        dwPosition.push_back(meld7[z]);
    	}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld7.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld7[z]]);
		}
	}
    
    if(meld6.size() <= 2){
        for(int z = 0; z < meld6.size(); z++)
        {
		//add to count 
        deadwood = deadwood + pcHand[meld6[z]].getValue(); 
        dwPosition.push_back(meld6[z]);
    	}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld6.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld6[z]]);
		}
	}
    
    if(meld5.size() <= 2){
        for(int z = 0; z < meld5.size(); z++)
        {		
        //add to count 
        deadwood = deadwood + pcHand[meld5[z]].getValue();
        dwPosition.push_back(meld5[z]);
    	}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld5.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld5[z]]);
		}
	}
    
    if(meld4.size() <= 2){
        for(int z = 0; z < meld4.size(); z++)
        {		
        //add to count 
        deadwood = deadwood + pcHand[meld4[z]].getValue();
        dwPosition.push_back(meld4[z]);
    	}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld4.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld4[z]]);
		}
	}
    
    if(meld3.size() <= 2){
        for(int z = 0; z < meld3.size(); z++)
        {		
        //add to count 
        deadwood = deadwood + pcHand[meld3[z]].getValue();
        dwPosition.push_back(meld3[z]);
    	} 
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld3.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld3[z]]);
		}
	}
    
    if(meld2.size() <= 2){
       for(int z = 0; z < meld2.size(); z++)
        {		
        //add to count 
        deadwood = deadwood + pcHand[meld2[z]].getValue();
        dwPosition.push_back(meld2[z]);
    	}
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meld2.size(); z++)
        { 
        pcReveal.push_back(pcHand[meld2[z]]);
		}
	}
    
    if (meldA.size() <= 2){
        for(int z = 0; z < meldA.size(); z++)
        {		
        //add to count 
        deadwood = deadwood + pcHand[meldA[z]].getValue();
        dwPosition.push_back(meldA[z]);
    	} 
    }
    else //group valid meld together for reveal
    {
    	for(int z = 0; z < meldA.size(); z++)
        { 
        pcReveal.push_back(pcHand[meldA[z]]);
		}
	}

	//throw non melded cards on end of pcReveal vector
	if(dwPosition.size() != 0) 
	{
		for(int i = 0; i < dwPosition.size(); i++)
		{
			pcReveal.push_back(pcHand[dwPosition[i]]);
		}
	}
	
	pcHand.clear();//empties pcHand
	pcHand.shrink_to_fit();
	
	//pcHand becomes rearranged with melded cards first followed by dw cards
	for(int i = 0; i < pcReveal.size(); i++)
	{
		pcHand.push_back(pcReveal[i]);
	}

//for testing	
//	cout << "PC hand has " << pcHand.size() << " cards.\n\n";
//	for(int i = 0; i < pcHand.size(); i++)
//    {
//    	cout << "|" << pcHand[i].description() << "| ";
//	}
//	cout <<"\n\n";
//	cout <<"PC deadwood is " << deadwood << ".\n";
	
	
    if(deadwood == 0)
	{
        return 3;
    }
    else if(deadwood <= 10)
    {
        return 2;
    }
    else
    {
    	return 0;
	}
}

