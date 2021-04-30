#include <stdio.h>
#include <math.h>
/**
 __________________________________________________________________________________________________________________
| This Program calculates sinus value of x using the taylor series formula                                        |
| in the procesion of 0.000001 meaning until the abstract value of x is lesser than 0.000001                      |
| we are comparing the two values: 1. is the original formula using math library with the fuction: 'sin'          |
| the other one is the one we calculating with the formula: x * (-1) * (x * x) / (j * (j+1))                      |
| This programs is written by Eyal Haimov, I.D - 316316868                                                        |
|_________________________________________________________________________________________________________________|

**/
double abst(double x);
double my_Sin(double x);
/**
 _________________________________________________________________________________________________
| This fuction is replacement to the abstract fuction: it output the number accordingly:          |
| if it is negative it returns the same value (negative), otherwise returns the positive value    |
| if it is 0 - it returns 0                                                                       |
|_________________________________________________________________________________________________|
**/
double abst(double x)
{
	if(x<0)
	return -x;
	return x;
}
/**
 ________________________________________________________________________________________
| This fuction calculate sinus using the taylor series formula                           |
| the formula: x * (-1) * (x * x) / (j * (j+1))                                          |
| it adding up the number until abstract value of x is lower than 0.000001               |
| it prints the value of the number we inputting                                         |
| it prints the value after it lower than 0.000001 and the value after using sin fuction |
| Parameters:                                                                            |
| j - replacing the factorial action in the formula                                      |
| x - the number we are inputting                                                        |
| to_add - the value after using the formula                                             |
| result - adding up the result of each time                                             |
| taylor - calculating the sin value of x                                                |
|________________________________________________________________________________________|
**/
double my_Sin(double x)
{
	int j = 2;
	double taylor, to_add = x, result = x;
	do{
	to_add = to_add * (-1) * (x * x) / (j * (j+1));
	result = result + to_add;
	j = j + 2;
	}while(abst(to_add) > 0.000001);
	taylor = sin(x);
	printf("The number that is entered is: %f\n",x);
	printf("The original sin is: %f\n",taylor);
	printf("The result is: %f\n", result);
	return 0;
}
/**
 _______________________________________________________________________________________________
| This fuction inputting a number (radian), the number must be limited to a limit of -25 - +25  |
| if the number is higher than 25: the fuction changing the value of x to 25                    |
| if the number is lower than -25: the fuction changing the value of x to -25                   |
| the fuction calling to my_sin fuction and inputting the value of x                            |
|_______________________________________________________________________________________________|
**/
int main()
{
	double x;
	printf(" __________________________________________________________________________\n");
	printf("| This programs calculate the sinus value of x using taylor series formula |\n");
	printf("| the formula: x * (-1) * (x * x) / (j * (j+1))                            |\n");
	printf("| The number inputted must be between -25 to 25!                           |\n");
	printf("| If the number is above than 25 - the fuction change it to 25             |\n");
	printf("| If the number is lesser than -25 - the fuction change it to -25          |\n");
	printf("| The output prints the values of:                                         |\n");
	printf("| 1.The number we inputted                                                 |\n");
	printf("| 2.The sinus value of x - using fuction sin(x)                            |\n");
	printf("| 3.The value of x after using the taylor series formula                   |\n");
	printf("|__________________________________________________________________________|\n");
	printf("Please enter a number according to the request above:\n");
	scanf("%lf",&x);
	if(x>25)
	{
	x=25;
	printf("The number that is entered is above than 25, it changed to 25\n");	
	}
	if(x<-25)
	{
	x=-25;
	printf("The number that is entered is lower than -25, it changed to -25\n");
	}
	my_Sin(x);
	return 0;
}
