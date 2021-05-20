/*
    Created by Eric Willoughby
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define pause system("pause")
#define cls system("clear")
#define flush fflush(stdin)

// begin struct definitions

typedef struct{
	   char first[18];
	   char midI[3];
	   char last[40];
}PLAYERNAME;

typedef struct{
	   PLAYERNAME name;
	   int lives;
	   int money;
	   int strength;
	   int chances; //%chance of winning a battle
}PLAYERINFO;

typedef struct{
	   PLAYERNAME name;
	   int score;
}HIGHSCORES, TEMP; //temp to be used for bubble sort

typedef struct{
	   int numWin;
	   int numLose;
	   int winStreak;
	   int loseStreak;
	   int currentStreak;
	   int streakFlag; //check this
}RESULTS; //for ease of passing

// begin function prototypes
void battle(PLAYERINFO *p, RESULTS *r, int c, HIGHSCORES hs[]);
void buy(PLAYERINFO *p);
void displayBattleResults(PLAYERINFO p, RESULTS r);
void displayHighScores(PLAYERINFO p, int c, HIGHSCORES hs[]);
void displayIntroduction();
void displayMenu(PLAYERINFO p);
void displayStats(PLAYERINFO p);
void displayStoreMenu(PLAYERINFO p);
void displayTitle();
void finalResults(RESULTS r, PLAYERINFO p);
void gameOver(PLAYERINFO p, RESULTS r, int c, HIGHSCORES hs[]);
int getChoice();
void highScoreSort(PLAYERINFO p, int c, HIGHSCORES hs[]);
PLAYERNAME getUserName();
void quitGame(PLAYERINFO p, RESULTS r, int c, HIGHSCORES hs[]);

int main(){
    int choice = 0;
    int count = 0;
    HIGHSCORES highScores[10] = {0};
    PLAYERINFO player = {0};
    RESULTS results = {0};
    FILE *game;

    // set original conditions of player
	   player.lives = 4; player.chances = 50;

    game = fopen("highscores.bin", "rb");
    if(game != NULL){ // if bin already exists, read in info
        fread(&count, sizeof(int), 1, game);
        fread(highScores, sizeof(HIGHSCORES), count, game);
        fclose(game);
    }

    // seed random variable for future use
	   srand((unsigned) time(NULL));

    displayTitle();
    displayIntroduction();
    player.name = getUserName();

    do{
        displayMenu(player);
        choice = getChoice();

        switch(choice){
            case 1: // battle!
                battle(&player, &results, count, highScores);
                break;
            case 2: // buy
                buy(&player);
                break;
            case 3: // current results
                displayBattleResults(player, results);
                break;
            case 4: // top 10
                displayHighScores(player, count, highScores);
                break;
            case 5: // quit
                quitGame(player, results, count, highScores);
                break;
            default: // invalid input
                printf("INVALID INPUT\n");
                pause;
                break;
        } // end switch
    }while(choice != 5); // end do-while
} // end main

void battle(PLAYERINFO *p, RESULTS *r, int c, HIGHSCORES hs[]){
    int randBattle;

    cls;
    displayStats(*p);
    printf("Words talking about how battling is a thing you're doing now\n");

    randBattle = rand() % 100 + 1; //rand # from 1-100

    if(p->chances <= randBattle){ // you win the battle
        printf("WIN!!!!\n");
        printf("        _______________ \n");
        printf("       |@@@@|     |####| \n");
        printf("       |@@@@|     |####| \n");
        printf("       |@@@@|     |####| \n");
        printf("        \\@@@@|     |####/ \n");
        printf("         \\@@@|     |###/ \n");
        printf("         `@@|_____|##' \n");
        printf("              (O) \n");
        printf("           .-'''''-. \n");
        printf("         .'  * * *  `. \n");
        printf("        :  *       *  : \n");
        printf("        :~W I N N E R~: \n");
        printf("        : ~A W A R D~ : \n");
        printf("        :  *      *   : \n");
        printf("         '.  * * *  .' \n");
        printf("           `-.....-' \n");
        r->numWin++; //increment win count
        p->money += 50; // get money
        if(p->strength < 95) // get strength if not maxed
            p->strength += 5;
        if(p->chances < 95) // get chance if not maxed
            p->chances += 5;

        if(r->streakFlag > -1)
            r->currentStreak++; // if a streak is already going
        else
            r->currentStreak = 1; // 1 to begin new winning streak
        if(r->currentStreak > r->winStreak)
            r->winStreak = r->currentStreak; //checks if new win streak record
        r->streakFlag = 1; // raises flag for win
    }
    else{ // you lose the battle
        printf("LOSER!!!!\n");
        printf("                              .___. \n");
        printf("          //)               ,-^     ^-. \n");
        printf("         ///              /           \\  \n");
        printf(".-------| |--------------/  __     __  \\-------------------.__ \n");
        printf("|WMWMWMW| |>>>>>>>>>>>>> | />>\\   />>\\ |>>>>>>>>>>>>>>>>>>>>>>:> \n");
        printf("`-------| |--------------| \\__/   \\__/ |-------------------'^^ \n");
        printf("         \\\\               \\   /|\\   // \n");
        printf("          \\)               \\       // \n");
        printf("                            |       | \n");
        printf("                            |+X+X+X+| \n");
        printf("                             \\       / \n");
        printf("                             ^-----^ \n");
        r->numLose++; // increment loss count
        p->lives--; // lose a life

        if(p->strength > 0) // strength decremented if not zero
            p->strength -= 5;
        if(p->chances > 0) // chance decremented if not zero
            p->chances -= 5;

        if(r->streakFlag < 1)
            r->currentStreak++; // if a streak is already going
        else
            r->currentStreak = 1; //1 to begin new losing streak
        if(r->currentStreak > r->loseStreak)
            r->loseStreak = r->currentStreak; // checks if new loss streak record
        r->streakFlag = -1; // raises flag for loss

        if(p->lives == 0){ //triggers game over screen
            pause;
            gameOver(*p, *r, c, hs);
        }

    }
    pause;
} // end battle

void buy(PLAYERINFO *p){
    int choice = 0;

    do{
        displayStoreMenu(*p);
        choice = getChoice();

        switch(choice){
            case 1: // strength potion
                if(p->money >= 50 && p->strength < 95){ // you buy a strength potion
                    printf("Sales person thanks them. Not sure what writing style I want to go with for this.\n");
                    p->money -= 50;
                    p->strength += 5;
                    if(p->chances < 95)
                        p->chances += 5;
                }
                else if(p->strength == 95){ // your strength is maxed out
                    printf("Sales person claims that the potion won't do any good!\n");
                    printf("Perhaps you should try something else?\n");
                }
                else{ // not enough money
                    printf("The sales person apologizes. You don't have enough money.\n");
                }
                pause;
                break;
            case 2: // life potion
                if(p->money >= 100){ // you buy a life potion
                    printf("Sales person thanks you\n");
                    p->money -= 100;
                    p->lives++;
                }
                else{ // not enough money
                    printf("Not enough money...\n");
                    printf("Try something else?\n");
                }
                pause;
                break;
            case 3: // you leave
                printf("Exposition about leaving\n");
                pause;
                break;
            default: // invalid
                printf("Exposition about something idk this is invalid input so??\n");
                printf("Try something else.\n");
                pause;
                break;
        } // end switch

    }while(choice != 3);
} // end buy

void displayBattleResults(PLAYERINFO p, RESULTS r){
    cls;
    displayStats(p);
    printf("Talk about assessing progress or w/e\n\n");
    printf("Number of wins:\t\t%i\n", r.numWin);
    printf("Number of losses:\t%i\n", r.numLose);
    printf("Longest winning streak:\t%i\n", r.winStreak);
    printf("Longest losing streak:\t%i\n", r.loseStreak);
    pause;
} // end displayBattle Results

void displayHighScores(PLAYERINFO p, int c, HIGHSCORES hs[]){
    int i = 0;
    cls;
    displayStats(p);

    printf("Talk about heros or some shit\n");

    if(c == 0){
        printf("inspirational/depressing stuff about how you can't think of heroes lol\n");
    }
    else{
        for(i = 0; i < c; i++){
            printf("%i. %i\t%s %s. %s\n", i + 1,
                   hs[i].score, hs[i].name.first, hs[i].name.midI, hs[i].name.last);
        }
    }

    pause;
} // end displayHighScores

void displayIntroduction(){
    cls;
    printf("\n");
    printf("All of the fun exposition will go here that leads into naming the player.\n\n");
    pause;
} // end displayIntroduction

void displayMenu(PLAYERINFO p){
    cls;
    displayStats(p);
    printf("Make your choice, %s.\n\n", p.name.first);
    printf("1. Battle\n");
    printf("2. Buy something\n");
    printf("3. Display the results of all battles\n");
    printf("4. Display top 10 previous high scores\n");
    printf("5. Quit\n\n");
} // end displayMenu

void displayStoreMenu(PLAYERINFO p){
    cls;
    displayStats(p);
    printf("Exposition about the store.\n\n");
    printf("1. Buy strength potion (+5 strength) - $50\n");
    printf("2. Buy extra life - $100\n");
    printf("3. Leave\n\n");
} // end displayStoreMenu

void displayStats(PLAYERINFO p){
    printf("Lives: %i\tStrength: %i\tMoney: $%i",
           p.lives, p.strength, p.money);
    printf("\n\n");
} // end displayStats

void displayTitle(){

    printf(" _______           _______  _______  _______  \n");
    printf("(  ___ \'|\'    /|(  ____ )(  ____ \(  ____ ) \n");
    printf("| (   \'/| )   ( || (    )|| (   \'/| (    )| \n");
    printf("| (_____ | |   | || (____)|| (__    | (____)| \n");
    printf("(_____  )| |   | ||  _____)|  __)   |     __) \n");
    printf("      ) || |   | || (      | (      | (\'(   \n");
    printf("/\'___) || (___) || )      | (___/\'| )\' \'__ \n");
    printf("\'______)(_______)|/       (_______/|/  \'__/ \n\n");
    printf(" _______           _______  _______  _______  _______  _______  \n");
    printf("(  ___  )|\'    /|(  ____ \(  ____ \(  ___  )(       )(  ____ \' \n");
    printf("| (   ) || )   ( || (   \'/| (   \'/| (   ) || () () || (    \'/ \n");
    printf("| (___) || | _ | || (__    | (_____ | |   | || || || || ( \n");
    printf("|  ___  || |( )| ||  __)   (_____  )| |   | || |(_)| ||  __)  \n");
    printf("| (   ) || || || || (            ) || |   | || |   | || (  \n");
    printf("| )   ( || () () || (____/\'/\'__) || (___) || )   ( || (____/\' \n");
    printf("|/    \'|(_______)(_______/\'______)(_______)|/     \'|(_______/ \n\n");
    printf(" ______   _______ __________________ _        _______  \n");
    printf("(  ___ \'(  ___  )\'__  __/\'__  __/( \'     (  ____ \' \n");
    printf("| (   ) )| (   ) |   ) (      ) (   | (      | (    \'/ \n");
    printf("| (__/ / | (___) |   | |      | |   | |      | (__ \n");
    printf("|  __ (  |  ___  |   | |      | |   | |      |  __)  \n");
    printf("| (  \'\'| (   ) |   | |      | |   | |      | (    \n");
    printf("| )___) )| )   ( |   | |      | |   | (____/\'| (____/\' \n");
    printf("|/ \'___/|/    \'|   )_(      )_(   (_______/(_______/ \n\n");
    printf(" _______  _______  _______  \n");
    printf("(  ____ )(  ____ )(  ____ \' \n");
    printf("| (    )|| (    )|| (   \'/ \n");
    printf("| (____)|| (____)|| |  \n");
    printf("|     __)|  _____)| |  \n");
    printf("| (\' (   | (     | | \'_ ) \n");
    printf("| ) \' \'__| )    | (___) | \n");
    printf("|/   \'__/|/      (_______) \n");
    printf("******************************************************************");

    printf("\n\n\n");

    pause;
} // end displayTitle

void finalResults(RESULTS r, PLAYERINFO p){
    cls;
    printf("YOUR RESULTS:\n\n");
    printf("Battles won:\t\t%i\n", r.numWin);
    printf("Battles lost:\t\t%i\n", r.numLose);
    printf("Longest winning streak:\t%i\n", r.winStreak);
    printf("Longest losing streak:\t%i\n", r.loseStreak);
    printf("Final score:\t\t%i\n", p.money);
} // end finalResults

void gameOver(PLAYERINFO p, RESULTS r, int c, HIGHSCORES hs[]){
    cls;
    printf("Dialog about dying in battle. Make it tragic as heck\n");
    pause;

    finalResults(r, p);
    highScoreSort(p, c, hs);

    exit(1);
} // end gameOver

int getChoice(){
    int result = 0;
    printf("Input your choice: ");
    scanf("%i", &result);
    return result;
} // end getChoice

PLAYERNAME getUserName(){
    PLAYERNAME result;
    cls;
    printf("Enter your first name: ");
    scanf("%s", result.first);
    flush;
    printf("\nEnter your middle name: ");
    scanf("%s", result.midI);
    flush;
    printf("\nEnter your last name: ");
    scanf("%s", result.last);
    flush;

    return result;
} // end getUserName

void highScoreSort(PLAYERINFO p, int c, HIGHSCORES hs[]){
    FILE *game;
    int i = 0, j = 0;
    TEMP temp;


    if(c < 10){
        hs[c].score = p.money;
        strcpy(hs[c].name.first, p.name.first);
        strcpy(hs[c].name.midI, p.name.midI);
        strcpy(hs[c].name.last, p.name.last);
        c++;
        printf("You have made history and have entered into the hall of heroes.\n");
    }
    else{
        if(p.money > hs[9].score){
            hs[9].score = p.money;
            strcpy(hs[9].name.first, p.name.first);
            strcpy(hs[9].name.midI, p.name.midI);
            strcpy(hs[9].name.last, p.name.last);
            printf("You have made history and have entered into the hall of heroes.\n");
        }
    }
    pause;

    for(i = 1; i < c; i++){ // bubble sort
        for(j = 0; j < c - i; j++){
            if(hs[j].score < hs[j + 1].score){
                temp = hs[j];
                hs[j] = hs[j + 1];
                hs[j + 1] = temp;
            }
        }
    }

    game = fopen("highscores.bin", "wb");
    fwrite(&c, sizeof(int), 1, game);
    fwrite(hs, sizeof(HIGHSCORES), c, game);
    fclose(game);

} // end highScoreSort

void quitGame(PLAYERINFO p, RESULTS r, int c, HIGHSCORES hs[]){
    cls;
    printf("Dialog about quitting the game, blha blha blahablabalbalbaha\n");
    pause;

    finalResults(r, p);
    highScoreSort(p, c, hs);
} // end endGame
