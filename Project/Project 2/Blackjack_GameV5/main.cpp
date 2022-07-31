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
#include <vector>   //Vector Library
using namespace std;
//User Libraries

//Global Constants
//Mathematical/Physics/Conversions/Higher Dimensioned Arrays
const unsigned char PERCENT=100;
const int COLMAX=52;
//Function Prototypes
int CrdVal(vector <int>,const int);
void genCrds(fstream &, fstream &, const int);
void filArry(string, string [], const int);
void filArry(string[][COLMAX],string [], string [], const int);
bool hasWon(int, int, int limit=21);
//Execution begins here
int main(){
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    bool win; //If the player has won or lost
    const int NCARDS=52;//Number of Cards In the Deck
    char again,//If the player wishes to play again
         hit; //If the player wishes to hit or stay
    int pVal,//Current Value of Players Cards
        dVal,//Current Value of Dealers Cards
        crntIdx;//Current Index being used in the file
    vector<int> pVals(NCARDS);
    string crdTbl[2][NCARDS];
    string crd[NCARDS], cSut[NCARDS];
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
    string pCards[NCARDS],pSuits[NCARDS];
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
        cout<<money<<" Is Not a Valid Amount of Money"<<endl;
        cout<<"Input the Amount of Money You Wish to Play With"<<endl;
        cin>>money;
        strtMny=money;
    }
    //Map Inputs to Outputs

    //Generate Random Deck of Cards with suits into two different files
    genCrds(cards, suits, NCARDS);
    cards.close();
    suits.close();
    //Display Results
    //Game Play
    do{
        pVal=0;
        dVal=0;
        crdwSut="";
        for(int i=0; i<NCARDS;i++){
            pVals[i]=0;
        }
        //Open the Cards.dat and Suits.dat files to be read and used later on in the game
        cards.open(fileNm1,ios::in);
        suits.open(fileNm2,ios::in);
        cout<<endl;
        cout<<"You Currently Have "<<fixed<<setprecision(2)<<money<<" Dollars Left!"<<endl;
        //Ensure player has more than 0 Dollars Left
        if(money>0){
            cout<<"How Much Would You Like to Bet on This Game?"<<endl;
            cin>>bet; 
            //Check if the bet is valid
            while(bet>money || bet<0){
                cout<<"That Bet is Not Valid!"<<endl;
                cout<<"Please Enter How Much You Wish to Bet:"<<endl;
                cin>>bet;
            }
            //Grab a card from the cards file to start the player with
            if(crntIdx<52){
                getline(cards,cardSel);
                //Fill Cards Array
                filArry(cardSel,crd,NCARDS);
                getline(suits,suitSel);
                //Fill suits array
                filArry(suitSel,cSut,NCARDS);
                //Fill cards and Suits Table to be printed later
                filArry(crdTbl,crd,cSut,NCARDS);
                //Display a message of the card and its suit that the player recieved
                if(cardSel.at(crntIdx)=='A')pCards[crntIdx]="Ace";
                if(cardSel.at(crntIdx)=='2')pCards[crntIdx]="2";
                if(cardSel.at(crntIdx)=='3')pCards[crntIdx]="3";
                if(cardSel.at(crntIdx)=='4')pCards[crntIdx]="4";
                if(cardSel.at(crntIdx)=='5')pCards[crntIdx]="5";
                if(cardSel.at(crntIdx)=='6')pCards[crntIdx]="6";
                if(cardSel.at(crntIdx)=='7')pCards[crntIdx]="7";
                if(cardSel.at(crntIdx)=='8')pCards[crntIdx]="8";
                if(cardSel.at(crntIdx)=='9')pCards[crntIdx]="9";
                if(cardSel.at(crntIdx)=='T')pCards[crntIdx]="10";
                if(cardSel.at(crntIdx)=='Q')pCards[crntIdx]="Queen";
                if(cardSel.at(crntIdx)=='K')pCards[crntIdx]="King";
                if(cardSel.at(crntIdx)=='J')pCards[crntIdx]="Jack";

                pSuits[crntIdx]=suitSel.at(crntIdx)=='H'?"Hearts":
                         suitSel.at(crntIdx)=='D'?"Diamonds":
                         suitSel.at(crntIdx)=='C'?"Clubs":
                         suitSel.at(crntIdx)=='S'?"Spades":"";

                //Calculate the current value of all the players cards         
                pVal=cardSel.at(crntIdx)=='2'?2:
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
                pVals[crntIdx]=pVal;
                pVal=CrdVal(pVals,NCARDS);
                cout<<endl;
                cout<<"You Recieved: "<<pCards[crntIdx]<<" of "<<pSuits[crntIdx]<<endl;
                cout<<endl;
                cout<<"Your Cards Total Value is Currently: "<<pVal<<endl<<endl;
                crntIdx+=1;
            }else{
                cout<<"No cards left in deck to draw from";
                exit(0);
            }
            dVal+=rand()%11+1;
            cout<<"The Dealers Shown Card Value is: "<<dVal<<endl<<endl;
            cout<<"Would You Like to Hit (Y/N)"<<endl;
            cin>>hit;
            if(crntIdx<52){
                do{
                    if(hit=='Y'||hit=='y'){
                        if(crntIdx<52){
                            getline(cards,cardSel);
                            getline(suits,suitSel);
                            //Display a message of the card and its suit that the player recieved
                            if(cardSel.at(crntIdx)=='A')pCards[crntIdx]="Ace";
                            if(cardSel.at(crntIdx)=='2')pCards[crntIdx]="2";
                            if(cardSel.at(crntIdx)=='3')pCards[crntIdx]="3";
                            if(cardSel.at(crntIdx)=='4')pCards[crntIdx]="4";
                            if(cardSel.at(crntIdx)=='5')pCards[crntIdx]="5";
                            if(cardSel.at(crntIdx)=='6')pCards[crntIdx]="6";
                            if(cardSel.at(crntIdx)=='7')pCards[crntIdx]="7";
                            if(cardSel.at(crntIdx)=='8')pCards[crntIdx]="8";
                            if(cardSel.at(crntIdx)=='9')pCards[crntIdx]="9";
                            if(cardSel.at(crntIdx)=='T')pCards[crntIdx]="10";
                            if(cardSel.at(crntIdx)=='Q')pCards[crntIdx]="Queen";
                            if(cardSel.at(crntIdx)=='K')pCards[crntIdx]="King";
                            if(cardSel.at(crntIdx)=='J')pCards[crntIdx]="Jack";

                        pSuits[crntIdx]=suitSel.at(crntIdx)=='H'?"Hearts":
                            suitSel.at(crntIdx)=='D'?"Diamonds":
                            suitSel.at(crntIdx)=='C'?"Clubs":
                            suitSel.at(crntIdx)=='S'?"Spades":"";

                        //Calculate the current value of all the players cards         
                        pVal=cardSel.at(crntIdx)=='2'?2:
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
                            pVals[crntIdx]=pVal;
                            pVal=CrdVal(pVals,NCARDS);
                            cout<<endl;
                            cout<<"You Recieved: "<<pCards[crntIdx]<<" of "<<pSuits[crntIdx]<<endl;
                            cout<<endl;
                            cout<<"Your Cards Total Value is Currently: "<<pVal<<endl<<endl;
                            cout<<"The Dealers Shown Card Value is: "<<dVal<<endl<<endl;
                            crntIdx+=1;
                        }else{
                            cout<<"No cards left in deck to draw from";
                            exit(0);
                        }
                        if(pVal<21){
                            cout<<"Would you like to hit (Y/N)"<<endl;
                            cin>>hit;
                        }else hit='N';
                    }
                }while(crntIdx<52 && (hit=='Y'||hit=='y'));
                //Increase dealers card value by a random value from 1 to 10 if their total card value is less than 17
                while(dVal<17)dVal+=rand()%10+1;
            }
            //Check if the player has won
            win=hasWon(pVal, dVal);
            
            if(win){
                //Pay out the bet at a 3:2 Ratio(found on blackjack.org) if the player has won
                money+=bet/2*3;
                prcChng=money/strtMny*PERCENT;
                strtMny=money;
                cout<<endl;
                cout<<"Congratulations You Have Won :) "<<endl;
                cout<<"The Dealer's Total Card Value Was: "<<dVal<<endl;
                cout<<"Your New Balance is $"<<money<<endl;
                cout<<"Your money increased by around "<<fixed<<setprecision(0)<<round(prcChng)<<"%"<<endl;
            }else{
                money-=bet;
                prcChng=money/strtMny*PERCENT;
                strtMny=money;
                cout<<endl;
                cout<<"Sorry You Lost :( "<<endl;
                cout<<"The Dealer's Total Card Value Was: "<<dVal<<endl;
                cout<<"Your New Balance is "<<fixed<<setprecision(2)<<money<<endl;
                //Display how much player's money decreased and round to the nearest Value
                cout<<"Your money decreased by around "<<fixed<<setprecision(0)<<round(PERCENT-prcChng)<<"%"<<endl;
            }

        }
        if(money>0){
            cout<<"Would you like to play again?(Y/N)"<<endl;
            cin>>again;
        }
    }while(money>0 && (again=='Y'||again=='y')); 
    //Exit Stage Right
    //Close Files Correctly
    cards.close();
    suits.close();
    //Output table of cards and suits for player to see
    cout<<endl<<"Heres A List Of All The Cards That Were In The Deck With Their Suits"<<endl<<endl;
    cout<<"Card: ";
    for(int i=0; i<NCARDS;i++)cout<<crdTbl[0][i];
    cout<<endl;
    cout<<"Suit: ";
    for(int i=0; i<NCARDS;i++)cout<<crdTbl[1][i];
    cout<<endl;
    return 0;
}
int CrdVal(vector<int> cards,const int NCARDS){
    int pVal=0;
    for(int i=0; i<NCARDS;i++){
        pVal+=cards[i];
    }
    return pVal;
}
void genCrds(fstream &cards, fstream &suits, const int NCARDS){
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
}
void filArry(string text, string array[], const int NCARDS){
    for(int i=0; i<NCARDS;i++){
        array[i]=text[i];
    }
}
void filArry(string crdTbl[][COLMAX],string card[], string suit[], const int NCARDS){
    for(int i=0;i<NCARDS;i++){
        crdTbl[0][i]=card[i];
        crdTbl[1][i]=suit[i];
    }
}
bool hasWon(int pVal, int dVal, int limit){
    if(pVal>dVal && pVal<=limit ||(dVal>21 && pVal<=21))return true;
    else return false;
}