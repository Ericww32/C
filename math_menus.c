//  main.c
//  menu&&Math
//  prof. Hunchuck
//  Created by Eric Willoughby on 9/2/14.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define pause system("pause")
#define cls system("cls")

void threeNum(int* num1, int* num2, int* num3);
int lowest(int num1, int num2, int num3);

int main()
{
    //declare values
    char letter;
    int num1, num2, num3;
    int sum, prod;
    float avg;



do{     //display menu
        printf("Choose wisely: \n");
        printf("A) Get three integers \n");
        printf("B) Display sum \n");
        printf("C) Display product \n");
        printf("D) Display Average \n");
        printf("E) Display the lowest \n");
        printf("Q) Quit \n");
        scanf(" %c", &letter);
        letter = toupper(letter);

        cls;
        switch(letter)
        {
            case 'A' : // get some numbers
                threeNum(&num1, &num2, &num3);

                break;
			//get sum
            case 'B' : sum = num1 + num2 + num3;
                printf("the sum of %i, %i & %i = %i \n", num1, num2, num3, sum);
                pause;
                cls;

                break;
			//get product
            case 'C' : prod = num1 * num2 * num3;
                printf("the product of %i, %i & %i = %i \n", num1, num2, num3,prod);
                pause;
                cls;

                break;
			//get average
            case 'D' :  avg = (float)(num1 + num2 + num3)/3;
                printf("the average of of %i, %i & %i = %.2f \n", num1, num2, num3, avg);
                pause;
                cls;

                break;
			//find lowest
            case 'E' : printf("the lowest is %i \n", lowest(num1, num2, num3));
                pause;
                cls;

                break;
			//quit
            case 'Q' : printf("thanks for checking this out! \n");
                break;


            default: printf("well that did nothing! \n\n\n");
                pause;
                cls;
        }

}while(letter != 'Q');


    return 0;
} //end of main

void threeNum(int* num1, int* num2, int* num3)
{
    printf("give me 3 numbers: \n");
                scanf(" %i", num1);
                scanf(" %i", num2);
                scanf(" %i", num3);
    cls;


}//end of threeNum

int lowest(int num1, int num2, int num3)
{
    int result;
     if (num1 < num2 && num1 < num3)
                {
                    result = num1;
                }
                else if (num1 < num3)
                {
                    result = num2;
                }
                else
                {
                    result = num3;
                }

    return result;
}//end of lowest
