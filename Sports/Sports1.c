//Eric Willoughby
//professor hunchuck
//9 sept. 2014

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define pause system("pause")
#define cls system("cls")
#define GAMES 1000

void displayRes(int *wins, int *losses, int numGames);
void displayWon(int *wins);
void mainScreen();


main()
{
	char answer;
	int results = 0;
	int numGames = 0;
	int team1[GAMES] = {0};
	int team2[GAMES] = {0};
	int wins = 0, losses = 0;

	do{
		mainScreen();
		scanf(" %c", &answer);
		answer = toupper(answer);
		pause;
		cls;
		

		switch(answer)
		{
		case 'A' : 
			if(numGames < 1000)
			{
				printf("Scores \nTeam One: ");
				scanf(" %i", &team1[numGames]);
				printf("Team two: ");
				scanf(" %i", &team2[numGames]);\
					if(team1>team2)
					{
						wins++;
					}
					else
					{
						losses++;
					}
				numGames++;
			}
			else
			{
				printf("Error\n");
			}
			pause;
			cls;
			break;

		case 'B' : printf("# of wins = %i and # of losses = %i \n",wins,losses);
			pause;
			cls;
			break;

		case 'C' : displayWon(&wins);
			pause;
			cls;
			break;

		case 'D' : displayRes(team1, team2, numGames);
			pause;
			cls;
			break;
		}
		
	}while(answer != 'Q');

	printf("....well I guess this is goodbye ");
		pause;

	return 0;
}//end of main

void displayWon(int *wins)
{
	int allWins;
	printf("wins: %i", allWins);

}//end of displayWon

void displayRes(int *wins, int *losses, int numGames)
{
	int allresults = 0, i = 0;

	for(i = 0; i <  numGames;i++)
		printf("Game #%i - %i : %i\n", i+1, wins[i], losses[i]);
	

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