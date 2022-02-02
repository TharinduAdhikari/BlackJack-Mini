/*

BlackJack Mini Team

1.	IM/2019/055 - Tharindu Sankarshana Herath
2.	IM/2019/028 - waruna Sri Wickramasinghe
3.	IM/2019/052 - Tharindu Sachintha Adhikari
4.	IM/2019/004 - Binura Yasith Gunasena
*/

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

using std::cout;
using std::endl;

//variables for store wins losses and draws
int wins, draws, losses;

//variable for FOR loops
int i;

//Temp variable for store both scores
int score;

//variables for store scores
int dscore, uscore;

//Variables for move card hitting possition
int xx, yy;

//Varuables for take card count
int ucount,dcount;

/*
player = 0 means user
player = 55 means dealer
*/
int player;

//variable for take list size
int size;

/*
status=0 means before start
status=1 means still playing
status=2 means busted
status=3 means win,lost or draw
*/
int status=0;

//Card pack
std::string cards[]={"H2","H3","H4","H5","H6","H7","H8","H9","HJ","HQ","HK","HA","H10",
                    "D2","D3","D4","D5","D6","D7","D8","D9","DJ","DQ","DK","DA","D10",
                    "C2","C3","C4","C5","C6","C7","C8","C9","CJ","CQ","CK","CA","C10",
                    "S2","S3","S4","S5","S6","S7","S8","S9","SJ","SQ","SK","SA","S10"};

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


//function for move cursor
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}


//function for print UI
void printUI(){
    //scores
    gotoxy(23,9);
	cout<<"You : "<<uscore;
    gotoxy(77,9);
	cout<<"Dealer : "<<dscore;

    //Horizontal Borders
	for(i=2; i<=110; i++){
		gotoxy(i,2);
		cout<<"#";
		gotoxy(i,25);
		cout<<"#";
	}

    //Vertical Borders
	for(i=2; i<=25; i++){
		gotoxy(2,i);
		cout<<"#";
		gotoxy(110,i);
		cout<<"#";
	}
    //Vertical Middle Borders
	for(i=9; i<=20; i++){
		gotoxy(54,i);
		cout<<"|";
	}

    //Score bord Horizontal Borders
	for(i=40; i<=68; i++){
		gotoxy(i,4);
		cout<<"-";
		gotoxy(i,8);
		cout<<"-";
        gotoxy(i,6);
		cout<<"-";
	}

    //Score bord Vertical Borders
	for(i=5; i<=7; i++){
		gotoxy(40,i);
		cout<<"|";
		gotoxy(49,i);
		cout<<"|";
        gotoxy(59,i);
		cout<<"|";
		gotoxy(68,i);
		cout<<"|";
	}

    //Table Caption
    gotoxy(45,3);
    cout<<"** BlackJack Mini **";
    
    //Table Headers
    gotoxy(44,5);
    cout<<"Wins";
    gotoxy(45,7);
    cout<<wins;
    
    gotoxy(52,5);
    cout<<"Draws";
    gotoxy(54,7);
    cout<<draws;

    gotoxy(61,5);
    cout<<"Losses";
    gotoxy(63,7);
    cout<<losses;

    //Print Game Controler
    gotoxy(12,22);
    cout<<"1.Press A to HIT a card.   2.Press S to STAND.   3.Press D to DEAL   4.Press Esc to EXIT"<<endl;
}

//Function for checking score Levels and make decisions.
void checker(string card){

//switch case for calculate scores
    switch(card[1]){

        case '1':
        score=score+10;
        break;

        case '2':
        score=score+2;
        break;

        case '3':
        score=score+3;
        break;

        case '4':
        score=score+4;
        break;

        case '5':
        score=score+5;
        break;

        case '6':
        score=score+6;
        break;

        case '7':
        score=score+7;
        break;

        case '8':
        score=score+8;
        break;

        case '9':
        score=score+9;
        break;

        case 'J':
        score=score+10;
        break;

        case 'Q':
        score=score+10;
        break;

        case 'K':
        score=score+10;
        break;

        case 'A':
//When score level is below 11 Ace is 11, Above 11 Ace is 1
        if(score<11){
            score=score+11;
        }
        else{
            score=score+11;
        }
        break;
    }

//assign scores to player and dealer
    if(player==0){
        uscore=score;
    }
    else{
        dscore=score;
    }
//print scores    
    gotoxy(23,9);
	cout<<"You : "<<uscore;
    gotoxy(77,9);
	cout<<"Dealer : "<<dscore;

    gotoxy(20,24);
    cout<<"                                                                                     ";

//checking score levels

    //Check the player busted or not
    if(uscore>21){
        losses=losses+1;
        status=2;
        gotoxy(51,24);
        cout<<"Busted!!!";
        
    }

    //Check the player win or not
    else if(dscore>21){
        gotoxy(48,24);
        cout<<"Congratulation!!!";
        wins=wins+1;
        status=3;
    }

    //Check the player lost or not
    else if(dscore>uscore){
        status=3;
        gotoxy(50,24);
        cout<<"You Lost!!!"<<endl;
        losses=losses+1;
    }
    //Check the scores are equal or not.
    else if(dscore==21 && uscore==21){
        gotoxy(47,24);
        cout<<"Scores are Level!!!"<<endl;
        draws=draws+1;
        status=3;
    }

//Printing scores
    gotoxy(43,5);
    cout<<"Wins";
    gotoxy(45,7);
    cout<<wins;
    
    gotoxy(52,5);
    cout<<"Draws";
    gotoxy(54,7);
    cout<<draws;

    gotoxy(61,5);
    cout<<"Losses";
    gotoxy(63,7);
    cout<<losses;

}

//Function for hitting cards
void hitcard(int player, string card){

//Counting the card count each player hit
    if(player==0){
        ucount++;
    }
    else{
        dcount++;
    }

//after hitting 4 cards break the card line
    if(ucount>4){
        yy=yy+5;
        xx=0;
        ucount=ucount-4;
    }

    if(dcount>4){
        yy=yy+5;
        xx=0;
        dcount=dcount-4;
    }


    //Card Horizontal border
    for(i=10+xx+player; i<=16+xx+player; i++){
		gotoxy(i,12+yy);
		cout<<"-";
		gotoxy(i,16+yy);
		cout<<"-";
    }

    //Card Vertical border
    for(i=13+yy; i<=15+yy; i++){
		gotoxy(10+xx+player,i);
		cout<<"|";
		gotoxy(16+xx+player,i);
		cout<<"|";
    }

    //Card number
    gotoxy(13+xx+player,14+yy);
    cout<<card;
    checker(card);

}

//Function for control the gameplay
void gameplay(){
    //Infinite loop for gameplay
    while (1){
        int size = sizeof(cards)/32;
        int i = rand() % size;
        gotoxy(1,26);
        int op=getch();
        

        //When press A
	    if (op==65 || op==97){
            
            if(status!=2 && status!=3){
                status=1;
                hitcard(player,cards[i]);
                xx=xx+8;
            }
            else{
                gotoxy(20,24);
                cout<<"                                                                                     ";
                gotoxy(35,24);
                cout<<"Invalid Input. Please Re-Try.. Press D to DEAL";
                
            }
            continue;
        }

        //When press S
	    if (op==83 || op==115){
            if (status==1){
                if (player==0){
                    player=player+55;
                    xx=0;
                    score=0;
                    yy=0;
                    while(1){
                        if (dscore>21 || uscore<dscore){
                            break;
                        }
                        int i = rand() % size;
                        xx=xx+8;
                        hitcard(player,cards[i]);
                    }
                }
            }
            else{
                gotoxy(20,24);
                cout<<"                                                                                     ";
                gotoxy(30,24);
                cout<<"Invalid Input. Please Re-Try.. Press A to HIT a card";
            }

                
              
        }

        //When press D
	    if (op==68 || op==100){

            

            if(status!=1 && status!=0){
                system("cls");  //cleaning the console screen
            
            //When starting the next round
                xx=0;
                yy=0;
                player=0;
                score=0;
                uscore=0;
                dscore=0;
                ucount=0;
                dcount=0;
                printUI();
                status=0;
            }
            else{
                gotoxy(22,24);
                cout<<"Invalid Input. Please Re-Try.. Can't DEAL Please complete the round"<<endl;
            }
        }

        //When press Esc
        if(op==27){
            system("cls");  //cleaning the console screen
            break; //break the infinite loop when player need to exit from the game
        }
         
    }
    exit(0);
}

int main() {
	srand((unsigned) time(NULL));
	system("cls");  //cleaning the console screen
    printUI();  //calling printUI() to print UI
    gameplay(); //Starts game play
	return 0;
}
