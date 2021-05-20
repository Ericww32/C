//Eric Willoughby
//professor hunchuck
//9 sept. 2014

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define pause system("pause")
#define cls system("cls")
#define GAMES 1000

void displayRes(int *team1, int *team2, int *numGames);
void mainScreen();

int main()
{
	char answer;
	int numGames = 0;
	int team1[GAMES] = {0};
	int team2[GAMES] = {0};
	int wins = 0;
	int losses = 0;

	do{
		mainScreen();
		scanf(" %c", &answer);
		answer = toupper(answer);
		cls;

		switch(answer)
        {
    case 'A' :
        if(numGames < 1000)
            {
                printf("***Scores*** \n Team One: ");
                scanf(" %i", &team1[numGames]);
                printf(" Team two: ");
                scanf(" %i", &team2[numGames]);
                if(team1[numGames] > team2[numGames])
                    {
                    wins++;
                    }
                else
                    {
                    losses++;
                    }
            }

        numGames++;
        cls;
        break;

    case 'B' : printf("Number of wins: %i *** Number of losses: %i \n", wins, losses);
        pause;
        cls;
        break;

    case 'C' :  printf("Number of total wins: %i \n", wins);
        pause;
        cls;
        break;

    case 'D' : displayRes(team1, team2, numGames);
        pause;
        cls;
			break;
		}

    }while(answer != 'Q');

	printf("....well I guess this is goodbye, ");
		pause;

	return 0;
}//end of main

void displayRes(int *team1, int *team2, int *numGames)
{
    int i;
	for( i = 1; i <  numGames;i++)
    {
		printf("Game #%i - %i : %i\n", i, team1[i], team2[i]);
    }

}//end of displayRes

void mainScreen()
{
		printf("*****Main Menu:*****\n");
		printf("A) enter game results: \n");
		printf("B) current record (# of wins and # of losses)\n");
		printf("C) Display all results from games won \n");
		printf("D) Display all results \n");
		printf("Q) Quit \n");

}//end of mainScreen
