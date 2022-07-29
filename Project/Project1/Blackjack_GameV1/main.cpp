/*
*File: main.cpp
*Author: Daniel Chvat
*
*Created on July 22 2022, 8:30 AM
*Purpose: Create some kind of card game
*/

//System Libraries
#include <iostream> //Input Output Library
#include <ctime>    //Time Library
#include <cstdlib>  //C Standard Library
#include <iomanip>  //Formatting Library
#include <cmath>    //Math Library
#include <fstream>  //File Input Output Library
using namespace std;
//User Libraries

//Global Constants
//Mathematical/Physics/Conversions/Higher Dimensioned Arrays

//Function Prototypes

//Execution begins here
int main(){
    //Initialize the Random Number Seed
    srand(time(0));
    //Declare Variables
    const int NCARDS=52;//Number of Cards In the Deck
    char again;//If the player wishes to play again
    int money,bet,cardVal;//Total amount of money player currently has, how much they wish to bet on a game, and the current value of all their cards combined
    fstream cards;
    string fileName;
    //Initialize Variables
    fileName="Cards.dat";
    cards.open(fileName,ios::out);
    money=0;
    bet=0;
    cout<<"Blackjack Card Game"<<endl;
    cout<<"Input the Amount of Money in Dollars You Wish to Play With"<<endl;
    cin>>money;
    //Map Inputs to Outputs

    //Generate Random Deck of Cards
    for(unsigned char card=0; card<NCARDS;card++){
        int cardVal=rand()%11+1;
        switch(cardVal){
            case 1:cards<<"A"<<endl;break;
            case 2:cards<<2<<endl;break;
            case 3:cards<<3<<endl;break;
            case 4:cards<<4<<endl;break;
            case 5:cards<<5<<endl;break;
            case 6:cards<<6<<endl;break;
            case 7:cards<<7<<endl;break;
            case 8:cards<<8<<endl;break;
            case 9:cards<<9<<endl;break;
            case 10:{
                int random=rand()%4+1;
                if(random==1)cards<<10<<endl;
                else if(random==2)cards<<"K"<<endl;
                else if(random==3)cards<<"Q"<<endl;
                else cards<<"J"<<endl;

            break;}
            case 11:cards<<"A"<<endl;break;
        }
    }

    //Game Play
    do{
        cout<<"You Currently Have "<<money<<" Dollars"<<endl;
        cout<<"How Much Would You Like to Bet on This Game?"<<endl;
        cin>>bet; 
        money=0;
    }while(money>0);
    //Display Results

    //Exit Stage Right
    cards.close();
    return 0;
}