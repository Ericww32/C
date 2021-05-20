//  CarSaleProg.c
//  prof. Hunchuck
//  Created by Eric Willoughby on 9/2/14.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define pause system("pause")
#define cls system("cls")

//prototype functions here
  void displayMenu();
  int getChoice();
  void displayOutPut(int, float);
  float getNewSale(int *);
  float lastOfMonth();
  int firstTimebuyer();
  int student();
  int veteran();

int main()
{
    int choice;
    float stickerPrice;
    int totalCarSold = 0;
    float totalAdjRev = 0.0;

    do{
       choice = getChoice();
        switch(choice){

            //new sale
            case 1 : 
                stickerPrice = getNewSale(&totalCarSold);
                stickerPrice *= lastOfMonth();
                stickerPrice -= firstTimebuyer();
                stickerPrice -= student();
                //student&FirstTimeBuyer();
                stickerPrice -= veteran();
                totalAdjRev += stickerPrice;
                break;

            //display
            case 2 : displayOutPut(totalCarSold, totalAdjRev);
                break;

            //quit
            case 3 : printf("program is over \n");
                pause;
                break;

            default : printf("bad choice \n");
                pause;
                break;

        }//end switch
    }while(choice!=3);

    pause;
    return 0;
}//end main

void displayMenu()
{    
    cls;
    printf("***********main menu: **************\n");
    printf("1) choice 1 add a car \n");
    printf("2) choice 2 display output \n");
    printf("3) choice 3 quit \n\n");
    printf("enter choice: \n");
 // end dislpaymenu
    return;
}//end displayMenu

void displayOutPut(int count, float rev)
{
    if (count > 0)
    {
        printf("total cars sold %i \n", count);
        printf("average car sold price %.2f \n", rev/count);
        printf("total revenue %.2f \n", rev);
        printf("dealer profit %.2f \n", rev*.05);
    }else { printf("must sell one car \n");
        pause;
    
    }

}//end displayOutPut

float getNewSale(int *total)
{
    int result;

    printf("enter sticker price: ");
    scanf(" %i", &result);
    *total = *total + 1;

    return result;
}//end of getNewSale

int getChoice()
{
    int result;
    displayMenu();
    scanf(" %i", &result);


    return result;

}//end getChoice

float lastOfMonth()
{
    int result = 1.0;// no discount
    char choice;
    scanf(" %c", choice);
    if (choice == 'Y' || choice == 'y')
    {
        result = .95;// this is a 5% discount
    }

    return result;
}//end of lastOfMonth

int firstTimebuyer()
{
    int result;
    char choice;
    scanf(" %c", choice);
    if (choice == 'Y' || choice == 'y')
    {
        result = 0;
    }

    return result;
}//end of firstTimebuyer

int student()
{
    int result;
    char choice;
    scanf(" %c", choice);
    if (choice == 'Y' || choice == 'y')
    {
        result = 0;
    }

    return result;
}//end of student

int veteran()
{
    int result;
    char choice;
    scanf(" %c", choice);
    if (choice == 'Y' || choice == 'y')
    {
        result = 0;
    }

    return result;
}//end of veteran
