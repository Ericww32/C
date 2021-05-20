//  ZackGoesToTrack.finalVersion
/*
 Written by: Eric Willoughby, Michael Quinones, Hugo Lotina
 Date written: September 15, 2014
 Purpose: Zack goes to the TRACK assignment
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define pause system("pause")
#define cls system("cls")
#define flush fflush(stdin)
#define SIZE 9
#define startAmount 1000

void accessBank(float *wallet, float *account);
int bankChoice(float wallet, float account);
void bankDeposit(float *wallet, float *account);
void bankwithdraw(float *wallet, float *account);
void displayWinners(int horses[]);
void error();
int getChoice(float wallet);
int horseChoice(float wallet, float account);
void payout(int choice, int horses[], float bet, float *wallet, int result, float win);
void placeBet(int choice, int horses[], float *wallet, float account);
void race(int choice, int horses[], float bet, float *wallet, float account);
void selectHorse(int horses[], float *wallet, float account);
int randomCalc ();

int main(){
    int horses[SIZE] = {0}, choice;
    float wallet = 0.00, account = startAmount;
    
    do{
        choice = getChoice(wallet);
        switch(choice){
            case 1: //Access bank account
                accessBank(&wallet, &account);
                break;
            case 2: //Place a bet
                selectHorse(horses, &wallet, account);
                break;
            case 3: //View past winners
                displayWinners(horses);
                break;
            case 4: //Quit
                break;
            default:
                error();
                break;
        }
    }while(choice != 4);
} //End main

void accessBank(float *wallet, float *account){
    int choice;
    do{
        choice = bankChoice(*wallet, *account);
        switch(choice){
            case 1: //Access bank account
                bankwithdraw(wallet, account);
                break;
            case 2:
                bankDeposit(wallet, account);
                break;
            case 3:
                break;
            default:
                error();
                break;
        }
    }while(choice != 3);
} //End accessBank

int bankChoice(float wallet, float account){
    int result;
    
    cls;
    printf("\n ============= Bank Account =============\n\n");
    printf(" Account Balance: $%.2f\n", account);
    printf(" Wallet Balance: $%.2f\n\n", wallet);
    printf(" 1. Withdraw\n");
    printf(" 2. Deposit\n");
    printf(" 3. Quit\n\n");
    printf(" Enter choice: ");
    scanf("%i", &result);
    flush;
    
    return result;
} //End bankChoice

void bankDeposit(float *wallet, float *account){
    float num;
    
    cls;
    printf("\n ========== Bank Account - Deposit ==========\n\n");
    printf(" Account Balance: $%.2f\n", *account);
    printf(" Wallet Balance: $%.2f\n\n", *wallet);
    printf(" Please enter the amount you would like to deposit to your account: $");
    scanf("%f", &num);
    
    cls;
    if(num > *wallet){
        printf("\n Sorry, insufficient funds.\n\n ");
        pause;
    }
    else{
        *wallet -= num;
        *account += num;
        
        printf("\n $%.2f has been successfully deposited to your account.\n\n ", num);
        pause;
    }
} //end bankDeposit

void bankwithdraw(float *wallet, float *account){
    float num;
    
    cls;
    printf("\n ========== Bank Account - Withdraw ==========\n\n");
    printf(" Account Balance: $%.2f\n", *account);
    printf(" Wallet Balance: $%.2f\n\n", *wallet);
    printf(" Please enter the amount you would like to withdraw from your account: $");
    scanf(" %f", &num);
    
    cls;
    if(num > *account){
        printf("\n Sorry, insufficient funds.\n\n ");
        pause;
    }
    else{
        *account -= num;
        *wallet += num;
        printf("\n $%.2f has been successfully withdrawn from your account.\n\n ", num);
        pause;
    }
} //End bankWithdraw

void displayWinners(int horses[]){
    int i, x = 0;
    
    cls;
    for(i = 0; i < SIZE; i++){
        if(horses[i] == 0){x++;}
    }
    
    if(x == SIZE){
        printf("\n Your horses have not won any races.\n\n ");
        pause;
    }
    else{
        printf("\n ============= All past Winners =============\n\n");
        for(i = 0; i < SIZE; i++){
            if(horses[i] == 0){}
            else{
                printf(" Horse %i won %i times.\n\n ", i+1, horses[i]);
                pause;
            }
        }
    }
} //End displayWinners

void error(){
    cls;
    printf("\n Enter a valid input.\n\n (!_!) ");
    pause;
} //End error

int getChoice(float wallet){
    int result;
    
    cls;
    printf("\n ============= Horse Race =============\n\n");
    printf(" 1. Access bank account \t\t Wallet: $%.2f\n", wallet);
    printf(" 2. Place a bet\n");
    printf(" 3. View all past winners\n");
    printf(" 4. Quit\n\n");
    printf(" Enter choice: ");
    scanf("%i", &result);
    flush;
    
    return result;
} //End getChoice

int horseChoice(float wallet, float account){
    int result = 10;
    
    if(wallet == 0 && account == 0){
        cls;
        printf("\n GAME OVER!\n\n ");
        pause;
        exit(0);
    }
    else if(wallet == 0 && account > 0){
        cls;
        printf("\n You do not have any money in your wallet.\n\n ");
        pause;
    }
    else{
        cls;
        printf("\n ============= Horses =============\n\n");
        printf(" 1. Horse 1\n");
        printf(" 2. Horse 2\n");
        printf(" 3. Horse 3\n");
        printf(" 4. Horse 4\n");
        printf(" 5. Horse 5\n");
        printf(" 6. Horse 6\n");
        printf(" 7. Horse 7\n");
        printf(" 8. Horse 8\n");
        printf(" 9. Horse 9\n");
        printf(" 10. Quit\n\n");
        printf(" Enter choice of who you would like to bet on: ");
        scanf("%i", &result);
        flush;
    }
    return result;
} //End horseChoice

void payout(int choice, int horses[], float bet, float *wallet, int result, float win){
    if(result == choice){
        *wallet += win;
        (horses[choice - 1])++;
        printf("\n Congratulations! Horse %i won! You have won $%.2f. Wallet balance is now $%.2f.\n\n ", result, win, *wallet);
        pause;
    }
    else{
        printf("\n I'm sorry, Horse %i won. You have lost $%.2f. Wallet balance is now $%.2f.\n\n ", result, bet, *wallet);
        pause;
    }
} //End payout

void placeBet(int choice, int horses[], float *wallet, float account){
    float bet;
    
    cls;
    printf("\n Wallet: %.2f\n\n", *wallet);
    printf(" How much would you like to bet on Horse %i: $", choice);
    scanf("%f", &bet);
    
    if(bet > *wallet){
        cls;
        printf("\n Sorry, insufficient funds.\n\n ");
        pause;
        placeBet(choice, horses, wallet, account);
    }
    else{
        *wallet -= bet;
        
        printf("\n Bet placed on Horse %i ($%.2f).\n\n ", choice, bet);
        pause;
        
        race(choice, horses, bet, wallet, account);
    }
} //End placeBet

void race(int choice, int horses[], float bet, float *wallet, float account){
    float win;
    int result;
    
    cls;
    result = randomCalc();
    
    if(result == 1){win = bet * 2;}
    else if(result == 2){win = bet * 5;}
    else if(result == 3){win = bet * 10;}
    else if(result == 4){win = bet * 15;}
    else if(result == 5){win = bet * 50;}
    else if(result == 6){win = bet * 20;}
    else if(result == 7){win = bet * 10;}
    else if(result == 8){win = bet * 5;}
    else if(result == 9){win = bet * 3;}
    
    payout(choice, horses, bet, wallet, result, win);
} //End race

void selectHorse(int horses[], float *wallet, float account){
    int choice;
    
    do{
        choice = horseChoice(*wallet, account);
        switch(choice){
            case 1:
                placeBet(choice, horses, wallet, account);
                break;
            case 2:
                placeBet(choice, horses, wallet, account);
                break;
            case 3:
                placeBet(choice, horses, wallet, account);
                break;
            case 4:
                placeBet(choice, horses, wallet, account);
                break;
            case 5:
                placeBet(choice, horses, wallet, account);
                break;
            case 6:
                placeBet(choice, horses, wallet, account);
                break;
            case 7:
                placeBet(choice, horses, wallet, account);
                break;
            case 8:
                placeBet(choice, horses, wallet, account);
                break;
            case 9:
                placeBet(choice, horses, wallet, account);
                break;
            case 10:
                break;
            default:
                break;
        }
    }while(choice != 10);
} //End selectHorse

int randomCalc () {
    int randomNum, result;
    
    srand((unsigned)time(NULL));
    randomNum = 1 + rand() % (100 - 1 + 1);
    
    if(randomNum <= 35){
        result = 1;
    }
    else if(randomNum > 35 && randomNum <= 47){
        result = 2;
    }
    else if(randomNum > 47 && randomNum <= 55){
        result = 3;
    }
    else if(randomNum > 55 && randomNum <= 61){
        result = 4;
    }
    else if(randomNum == 62){
        result = 5;
    }
    else if(randomNum > 62 && randomNum <= 66){
        result = 6;
    }
    else if(randomNum > 66 && randomNum <= 74){
        result = 7;
    }
    else if(randomNum > 74 && randomNum <= 86){
        result = 8;
    }
    else{
        result = 9;
    }
    
    return result;
}//end of randomCalc