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
#include <string>   //String Library
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
    bool success; //If the line has been successfully grabbed from the file
    const int NCARDS=52;//Number of Cards In the Deck
    char again;//If the player wishes to play again
    int money,bet,pcrdVal,crntLn;//Total amount of money player currently has, how much they wish to bet on a game, and the current value of all their cards combined
    fstream cards,suits;
    string fileNm1,fileNm2,cardSel,suitSel,plrCrds,dlrCrds,plrSuts,dlrSuts; //Cards Player Currently has in their hand
    //Initialize Variables
    crntLn=1;
    fileNm1="Cards.dat";
    fileNm2="Suits.dat";
    cards.open(fileNm1,ios::out);
    suits.open(fileNm2,ios::out);
    money=10;
    bet=0;
    cout<<"Blackjack Card Game"<<endl;
    cout<<"Input the Amount of Money in Dollars You Wish to Play With"<<endl;
    cin>>money;

    while(money<0){
        cout<<money<<"Is Not a Valid Amount of Money"<<endl;
        cout<<"Input the Amount of Money You Wish to Play With"<<endl;
        cin>>money;
    }
    //Map Inputs to Outputs

    //Generate Random Deck of Cards already shuffled
    for(unsigned char card=0; card<NCARDS;card++){
        int cardVal=rand()%13+1;
        switch(cardVal){
            case 1:{
                cards<<"A"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 2:{
                cards<<"2"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 3:{
                cards<<"3"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 4:{
                cards<<"4"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 5:{
                cards<<"5"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 6:{
                cards<<"6"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 7:{
                cards<<"7"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 8:{
                cards<<"8"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 9:{
                cards<<"9"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 10:{
                cards<<"T"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 11:{
                cards<<"K"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 12:{
                cards<<"Q"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
            case 13:{
                cards<<"J"<<endl;
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H"<<endl;
                else if(suit==2)suits<<"D"<<endl;
                else if(suit==3)suits<<"C"<<endl;
                else suits<<"S"<<endl;
            break;}
        }
    }
    cards.close();
    suits.close();
    //Game Play
    do{
        plrCrds="";
        plrSuts="";
        dlrCrds="";
        dlrSuts="";
        cards.open(fileNm1,ios::in);
        suits.open(fileNm2,ios::in);
        cout<<"You Currently Have "<<money<<" Dollars Left"<<endl;
        if(money>0){
            cout<<"How Much Would You Like to Bet on This Game?"<<endl;
            cin>>bet; 
            //Check if the bet is valid
            while(bet>money){
                cout<<"You Don't Have Enough Money to Make That Bet"<<endl;
                cout<<"Please Enter How Much You Wish to Bet:"<<endl;
                cin>>bet;
            }
            //Grab a card for the player to start with
            cout<<"Current Line = "<<crntLn<<endl;
            if(crntLn<=52){
                getline(cards,cardSel);
                plrCrds+=cardSel;
                getline(suits,suitSel);
                plrSuts+=suitSel;
                crntLn+=1;
            }
            //Grab a card for the dealer to start with
            cout<<"Current Line = "<<crntLn<<endl;
            if(crntLn<=52){
                getline(cards,cardSel);
                dlrCrds+=cardSel;
                getline(suits,suitSel);
                dlrSuts+=suitSel;
                crntLn+=1;
            }
        }
        cout<<"Player Cards and suits"<<endl<<plrCrds<<endl<<plrSuts<<endl;
        cout<<"Dealer Cards and suits"<<endl<<dlrCrds<<endl<<dlrSuts<<endl;
        cout<<"Would You Like to Play Again? (Y/N)"<<endl;
        cin>>again;
        if((again=='Y'||again=='y') && money==0)cout<<"Sorry You Don't Have Enough Money to Play Again"<<endl;
    }while(money>0 && (again=='Y'||again=='y')); 
    //Display Results

    //Exit Stage Right
    cards.close();
    suits.close();
    return 0;
}