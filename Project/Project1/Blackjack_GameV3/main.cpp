/*
*File: main.cpp
*Author: Daniel Chvat
*Created on July 22 2022, 8:30 AM
*Purpose: Blackjack Card Game
*/

//System Libraries
#include <iostream> //Input Output Library
#include <ctime>    //Time Library
#include <string>   //String Library
#include <cmath>    //Math Library
#include <cstdlib>  //C Standard Library
#include <iomanip>  //Formatting Library
#include <fstream>  //File Input Output Library
using namespace std;
//User Libraries

//Global Constants
//Mathematical/Physics/Conversions/Higher Dimensioned Arrays
const unsigned char PERCENT=100;
//Function Prototypes

//Execution begins here
int main(){
    //Initialize the Random Number Seed
    srand(time(0));
    //Declare Variables
    bool win; //If the player has won or lost
    const int NCARDS=52;//Number of Cards In the Deck
    char again;//If the player wishes to play again
    int pVal,//Current Value of Players Cards
        dVal,//Current Value of Dealers Cards
        crntIdx;//Current Index being used in the file
    float money,//How much money the player currently has
          strtMny, //How much money the player started with
          bet,//How much money the player is willing to bet on a game
          prcChng;//The % change in the players money after the end of a game
    fstream cards,suits;
    string fileNm1,//Name of the file being used the store the cards
           fileNm2,//Name of the file being used to store the suits of each card
           cardSel,//Card at a specific index in Cards.dat
           suitSel,//Suit at a specific index in Suits.dat
           crdwSut;//Card and suit added together to be printed for the player
    //Initialize Variables
    crntIdx=0;
    fileNm1="Cards.dat";
    fileNm2="Suits.dat";
    cards.open(fileNm1,ios::out);
    suits.open(fileNm2,ios::out);
    money=0;
    bet=0;
    cout<<"Blackjack Card Game"<<endl;
    cout<<"Input the Amount of Money in Dollars You Wish to Play With"<<endl;
    cin>>money;
    strtMny=money;
    //Ensure the player is not entering negative amounts of money
    while(money<0){
        cout<<money<<"Is Not a Valid Amount of Money"<<endl;
        cout<<"Input the Amount of Money You Wish to Play With"<<endl;
        cin>>money;
        strtMny=money;
    }
    //Map Inputs to Outputs

    //Generate Random Deck of Cards with suits into two different files
    for(unsigned char card=0; card<NCARDS;card++){
        int cardVal=rand()%13+1;
        //Check to see if the random number generated matches a specific number if it does write down that card into the Cards.dat file
        switch(cardVal){
            case 1:{
                cards<<"A";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 2:{
                cards<<"2";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 3:{
                cards<<"3";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 4:{
                cards<<"4";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 5:{
                cards<<"5";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 6:{
                cards<<"6";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 7:{
                cards<<"7";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 8:{
                cards<<"8";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 9:{
                cards<<"9";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 10:{
                cards<<"T";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 11:{
                cards<<"K";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 12:{
                cards<<"Q";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
            case 13:{
                cards<<"J";
                unsigned char suit=rand()%4+1;
                if(suit==1)suits<<"H";
                else if(suit==2)suits<<"D";
                else if(suit==3)suits<<"C";
                else suits<<"S";
            break;}
        }
    }
    cards.close();
    suits.close();
    //Display Results
    //Game Play
    do{
        pVal=0;
        dVal=0;
        crdwSut="";
        //Open the Cards.dat and Suits.dat files to be read and used later on in the game
        cards.open(fileNm1,ios::in);
        suits.open(fileNm2,ios::in);
        cout<<"You Currently Have "<<fixed<<setprecision(2)<<money<<" Dollars Left!"<<endl;
        //Ensure player has more than 0 Dollars Left
        if(money>0){
            cout<<"How Much Would You Like to Bet on This Game?"<<endl;
            cin>>bet; 
            //Check if the bet is valid
            while(bet>money){
                cout<<"You Don't Have Enough Money to Make That Bet!"<<endl;
                cout<<"Please Enter How Much You Wish to Bet:"<<endl;
                cin>>bet;
            }
            //Grab a card from the cards file to start the player with
            if(crntIdx<52){
                getline(cards,cardSel);
                getline(suits,suitSel);
                //Display a message of the card and its suit that the player recieved
                if(cardSel.at(crntIdx)=='A')crdwSut+="Ace";
                if(cardSel.at(crntIdx)=='2')crdwSut+="2";
                if(cardSel.at(crntIdx)=='3')crdwSut+="3";
                if(cardSel.at(crntIdx)=='4')crdwSut+="4";
                if(cardSel.at(crntIdx)=='5')crdwSut+="5";
                if(cardSel.at(crntIdx)=='6')crdwSut+="6";
                if(cardSel.at(crntIdx)=='7')crdwSut+="7";
                if(cardSel.at(crntIdx)=='8')crdwSut+="8";
                if(cardSel.at(crntIdx)=='9')crdwSut+="9";
                if(cardSel.at(crntIdx)=='T')crdwSut+="10";
                if(cardSel.at(crntIdx)=='Q')crdwSut+="Queen";
                if(cardSel.at(crntIdx)=='K')crdwSut+="King";
                if(cardSel.at(crntIdx)=='J')crdwSut+="Jack";

                crdwSut+=suitSel.at(crntIdx)=='H'?" of Hearts":
                         suitSel.at(crntIdx)=='D'?" of Diamonds":
                         suitSel.at(crntIdx)=='C'?" of Clubs":
                         suitSel.at(crntIdx)=='S'?" of Spades":"";

                //Calculate the current value of all the players cards         
                pVal+=cardSel.at(crntIdx)=='2'?2:
                      cardSel.at(crntIdx)=='3'?3:
                      cardSel.at(crntIdx)=='4'?4:
                      cardSel.at(crntIdx)=='5'?5:
                      cardSel.at(crntIdx)=='6'?6:
                      cardSel.at(crntIdx)=='7'?7:
                      cardSel.at(crntIdx)=='8'?8:
                      cardSel.at(crntIdx)=='9'?9:
                      cardSel.at(crntIdx)=='T'?10:
                      cardSel.at(crntIdx)=='Q'?10:
                      cardSel.at(crntIdx)=='K'?10:
                      cardSel.at(crntIdx)=='J'?10:
                      cardSel.at(crntIdx)=='A'?11:0;
                cout<<endl;
                cout<<"You Recieved: "<<crdwSut<<endl;
                cout<<endl;
                cout<<"Your Cards Total Value is Currently: "<<pVal<<endl<<endl;
                crntIdx+=1;
            }
            dVal+=rand()%11+1;
            cout<<"The Dealers Shown Card Value is: "<<dVal<<endl<<endl;
            //Check if the player has won
            if(pVal>dVal && pVal<=21)win=true;
            else win=false;
            
            if(win){
                //Pay out the bet at a 3:2 Ratio(found on blackjack.org) if the player has won
                money+=bet/2*3;
                prcChng=money/strtMny*PERCENT;
                strtMny=money;
                cout<<"Congratulations You Have Won :) "<<endl;
                cout<<"Your New Balance is $"<<money<<endl;
                if(prcChng>0)cout<<"Your money increased by around "<<fixed<<setprecision(0)<<round(prcChng)<<"%"<<endl;
            }else{
                money-=bet;
                prcChng=money/strtMny*PERCENT;
                strtMny=money;
                cout<<"Sorry You Lost :( "<<endl;
                cout<<"Your New Balance is "<<fixed<<setprecision(2)<<money<<endl;
                //Display how much player's money decreased and round to the nearest integer
                cout<<"Your money decreased by around "<<fixed<<setprecision(0)<<round(PERCENT-prcChng)<<"%"<<endl;
            }

        }
        if(money>0){
            cout<<"Would you like to play again?(Y/N)"<<endl;
            cin>>again;
        }
    }while(money>0 && (again=='Y'||again=='y')); 
    //Exit Stage Right
    cards.close();
    suits.close();
    return 0;
}