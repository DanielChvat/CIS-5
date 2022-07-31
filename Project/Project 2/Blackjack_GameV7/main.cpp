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
string getCard(string [], int);
string getSuit(string [], int);
int getVal(string[], int, int);
void bblSort(string [], const int);
void linSrch(string [], const int);
void selSort(string [], const int);
//Execution begins here
int main(){
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    bool win; //If the player has won or lost
    const int NCARDS=52;//Number of Cards In the Deck
    char again,//If the player wishes to play again
         hit, //If the player wishes to hit or stay
         info;//If the player wishes to see info about the game
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
           suitSel;//Suit at a specific index in Suits.dat
           //crdwSut;//Card and suit added together to be printed for the player
    string pCards[NCARDS],pSuits[NCARDS];
    //Initialize Variables
    crntIdx=0;
    fileNm1="Cards.dat";
    fileNm2="Suits.dat";
    cards.open(fileNm1,ios::out);
    suits.open(fileNm2,ios::out);
    money=0;
    bet=0;
    //Ask Player to input amount of money they wish to play with
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
        //crdwSut="";
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
            if(crntIdx<NCARDS){
                getline(cards,cardSel);
                //Fill Cards Array
                filArry(cardSel,crd,NCARDS);
                getline(suits,suitSel);
                //Fill suits array
                filArry(suitSel,cSut,NCARDS);
                //Fill cards and Suits Table to be printed later
                filArry(crdTbl,crd,cSut,NCARDS);
                //Display a message of the card and its suit that the player recieved
                pCards[crntIdx]=pCards[crntIdx]=getCard(crd, crntIdx);
                pSuits[crntIdx]=getSuit(cSut,crntIdx);
                //Calculate the current value of all the players cards         
                pVal=pVal=getVal(crd,crntIdx,pVal);
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
                            pCards[crntIdx]=getCard(crd, crntIdx);
                            pSuits[crntIdx]=getSuit(cSut,crntIdx);
                            //Calculate the current value of all the players cards         
                            pVal=getVal(crd,crntIdx,pVal);
                            pVals[crntIdx]=pVal;
                            pVal=CrdVal(pVals,NCARDS);
                            cout<<endl;
                            //Display Message to player saying the card they recieved their current total card value and the dealers show card value
                            cout<<"You Recieved: "<<pCards[crntIdx]<<" of "<<pSuits[crntIdx]<<endl;
                            cout<<endl;
                            cout<<"Your Cards Total Value is Currently: "<<pVal<<endl<<endl;
                            cout<<"The Dealers Shown Card Value is: "<<dVal<<endl<<endl;
                            crntIdx+=1;
                        }else{
                            //Tell the player there are no cards left in the deck and exit program
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
                while(dVal<17)dVal+=rand()%11+1;
            }
            //Check if the player has won
            win=hasWon(pVal, dVal);
            cout<<endl<<endl<<"Results:"<<endl;
            if(win){
                //Pay out the bet at a 3:2 Ratio(found on blackjack.org) if the player has won
                money+=bet/2*3;
                prcChng=money/strtMny*PERCENT;
                strtMny=money;
                //Display message saying player won
                cout<<"Congratulations You Have Won :) "<<endl;
                cout<<"Your Total Card Value Was: "<<pVal<<endl;
                cout<<"The Dealer's Total Card Value Was: "<<dVal<<endl;
                cout<<"Your New Balance is $"<<money<<endl;
                cout<<"Your money increased by around "<<fixed<<setprecision(0)<<round(prcChng)<<"%"<<endl;
            }else if(pVal==dVal ||(pVal>21 && dVal>21)){
                //Display a message saying nobody won
                cout<<"The Dealer's Total Card Value Was: "<<dVal<<endl;
                cout<<"Nobody Wins"<<endl;
            }else{
                money-=bet;
                prcChng=money/strtMny*PERCENT;
                strtMny=money;
                cout<<endl;
                //Display message saying player lost
                cout<<"Sorry You Lost :( "<<endl;
                cout<<"Your Total Card Value Was: "<<pVal<<endl;
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
    //Output info about the game for player to see
    cout<<"Would You Like To See Some Info About The Game?(Y/N)"<<endl;
    cin>>info;
    if(info=='Y' || info=='y'){
        cout<<endl<<"Heres A List Of All The Cards That Were In The Deck With Their Suits"<<endl<<endl;
        cout<<"Card: ";
        for(int i=0; i<NCARDS;i++)cout<<crdTbl[0][i];
        cout<<endl;
        cout<<"Suit: ";
        for(int i=0; i<NCARDS;i++)cout<<crdTbl[1][i];
        cout<<endl<<endl;
        cout<<"Heres the Cards Sorted from Lowest Value to Highest Value using Bubble Sort"<<endl<<endl<<"Cards: ";
        bblSort(crd, NCARDS);
        cout<<endl<<endl;
        cout<<"Heres the Cards Sorted from Lowest Value to Highest Value using Selection Sort"<<endl<<endl<<"Cards: ";
        selSort(crd, NCARDS);
        cout<<endl<<endl;
        linSrch(crd, NCARDS);
    }else cout<<endl<<endl<<"Thanks For Playing!";
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
    if(pVal>dVal && pVal<=limit || (pVal<=21 && dVal>21))return true;
    else return false;
}
string getCard(string cards[], int index){
    string card;
    if(cards[index]=="A")card="Ace";
    if(cards[index]=="2")card="2";
    if(cards[index]=="3")card="3";
    if(cards[index]=="4")card="4";
    if(cards[index]=="5")card="5";
    if(cards[index]=="6")card="6";
    if(cards[index]=="7")card="7";
    if(cards[index]=="8")card="8";
    if(cards[index]=="9")card="9";
    if(cards[index]=="T")card="10";
    if(cards[index]=="Q")card="Queen";
    if(cards[index]=="K")card="King";
    if(cards[index]=="J")card="Jack";
    return card;
}
string getSuit(string suits[], int index){
    string suit;
    suit=suits[index]=="H"?"Hearts":
        suits[index]=="D"?"Diamonds":
        suits[index]=="C"?"Clubs":
        suits[index]=="S"?"Spades":"";
        return suit;
}
int getVal(string cards[], int index, int pVal){
    int value;
    if(cards[index]=="A" && ((pVal+11)<=21))value=11;
    else value=1;
    value=cards[index]=="2"?2:
    cards[index]=="3"?3:
    cards[index]=="4"?4:
    cards[index]=="5"?5:
    cards[index]=="6"?6:
    cards[index]=="7"?7:
    cards[index]=="8"?8:
    cards[index]=="9"?9:
    cards[index]=="T"?10:
    cards[index]=="Q"?10:
    cards[index]=="K"?10:
    cards[index]=="J"?10:value;
    return value;
}
void bblSort(string cards[], const int NCARDS){
    int values[NCARDS];
    bool swapped;
    for(int i=0;i<NCARDS;i++){
        values[i]=getVal(cards,i,0);
    }
    do{
        swapped=false;
        for(int i=0; i<NCARDS-1;i++){
            if(values[i]>values[i+1]){
                swap(values[i],values[i+1]);
                swap(cards[i],cards[i+1]);
                swapped=true;
            }
        }
    }while(swapped);
    for(int i=0;i<NCARDS;i++){
        cout<<cards[i];
    }
}
void linSrch(string cards[], const int NCARDS){
int values[NCARDS];
    short nAs,n2s,n3s,n4s,n5s,n6s,n7s,n8s,n9s,nTs,nQs,nKs,nJs;
    nAs=n2s=n3s=n4s=n5s=n6s=n7s=n8s=n9s=nTs=nQs=nKs=nJs=0;
    bool swapped;
    for(int i=0;i<NCARDS;i++){
        if(cards[i]=="A")nAs++;
        if(cards[i]=="2")n2s++;
        if(cards[i]=="3")n3s++;
        if(cards[i]=="4")n4s++;
        if(cards[i]=="5")n5s++;
        if(cards[i]=="6")n6s++;
        if(cards[i]=="7")n7s++;
        if(cards[i]=="8")n8s++;
        if(cards[i]=="9")n9s++;
        if(cards[i]=="T")nTs++;
        if(cards[i]=="Q")nQs++;
        if(cards[i]=="K")nKs++;
        if(cards[i]=="J")nJs++;
    }
    cout<<"Card Distribution:"<<endl;
    cout<<"Aces:    "<<nAs<<endl;
    cout<<"Twos:    "<<n2s<<endl;
    cout<<"Threes:  "<<n3s<<endl;
    cout<<"Fours:   "<<n4s<<endl;
    cout<<"Fives:   "<<n5s<<endl;
    cout<<"Sixes:   "<<n6s<<endl;
    cout<<"Sevens:  "<<n7s<<endl;
    cout<<"Eights:  "<<n8s<<endl;
    cout<<"Nines:   "<<n9s<<endl;
    cout<<"Tens:    "<<nTs<<endl;
    cout<<"Queens:  "<<nQs<<endl;
    cout<<"Kings:   "<<nKs<<endl;
    cout<<"Jacks:   "<<nAs<<endl;

}
void selSort(string cards[], const int NCARDS){
    int values[NCARDS];
    bool swapped;
    for(int i=0;i<NCARDS;i++){
        values[i]=getVal(cards,i,0);
    }
    for(int a=0; a<NCARDS-1;a++){
        int index=a;
        for(int b=a+1; b<NCARDS; b++){
            if(values[index]>values[b])index=b;
        }
        swap(values[a],values[index]);
        swap(cards[a],cards[index]);
    }
    for(int i=0;i<NCARDS;i++){
        cout<<cards[i];
    }
}