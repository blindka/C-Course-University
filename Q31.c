#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(){
    /*
    Parameters:
    menu1 - the number the user is entering.
    number1, number2, number3 - are used for calculating the fibonnaci sum.
    loop - parameters for coming back to the menu option (c/d option).
    digit, order, helper,factor,temp - are used in order to check if the digits are in ascending order.
    i,j,k - parameters for the for loops in triangle option.
    subexit - for the exit option in the switch - sub switch for yes/no option.
    letteral1,letteral - input char for the switches.
    negative - flag that tells if the number is negative for option2.
    */
	int menu1 = 0;
	int factorial = 0;
	int i = 0;
	int number1 = 0;
	int number2 = 1;
	int number3 = 0;
	int sumfib = 0;
    int factor = 1;
    int loop = 0;
    int negative = 0;
    int digit, order, helper, submenu1, temp, j, k;
	char subexit, letteral1, letteral;
	/*
	menu1 - option 1 - one digit positive number.
	menu2 - option 2 - multi digit number.
	*/
	while(menu1!= 1 && menu1 != 2)
	{
		printf("what is your option:\n1-one-digit nunber\n2-number with an indefinite amount of digits\n");
		scanf("%d", &menu1);
		if (menu1 != 1 && menu1 != 2)
			printf("You have enterd invalid input, Please Enter again.\n");
	}
	/*
	Option 1: switch - case a - factorial
	                   case b - fibonnaci sum and numbers.
	                   case c - triangle.
	                   case d - exit or restart.
	                   default - wrong option.
	*/
	do
	{
	    if(menu1 == 2)
	    break;
	    loop = 0;
		printf("Enter a single digit number\n");
		scanf("%d" ,&submenu1);
		if(submenu1>9)
		{
		printf("You have entered Invalid number - bigger than 9, Please Enter a positive single digit number.\n");
		return 0;
		}
		if(submenu1<0)
		{
		printf("You have entered Invalid number - negative number, Please Enter a positive single digit number.\n");
		return 0;
		}
		printf("Enter your choice:\na-factorial\nb-fibonacci sequence\nc-print triangle\nd-exit\n");
		scanf(" %c",&letteral);
		switch (letteral)
		{
		case 'a': 
		for (factorial = 1, i = 1; i <= submenu1; i++)
		{
			factorial = factorial * i;
		}
		printf("factorial is %d\n", factorial);
		return 0;
		case 'b':
			while (number1 <= submenu1)
			{
				sumfib += number1;
				printf("%d ", number1);
				number3 = number1 + number2;
				number1 = number2;
				number2 = number3;
			}
			printf("\nThe sum of fibonnaci i: %d\n", sumfib);
			return 0;
		case 'c':
			for (i = 1; i <= submenu1; i++)
			{
				for (j = 1; j <= i; j++)
					printf(" ");
				for (k = i; k <= submenu1; k++)
					printf("*");
				printf("\n");
			}
			return 0;
		case 'd':
			printf("Do you want to continue? (if yes, press 'y', if no, press 'n'\n");
			scanf(" %c", &subexit);
			switch (subexit)
			{
			case 'y':
				loop = 1;
				break;
			case 'n':
				printf("You have chosen to exit the program.\n");
				return 0;
			default:
				printf("You have choosen wrong options, please select y - for yes or n - for no.\n");
			}
			break;
			default:
			printf("You have choosen an option that doesn't exist, please between the characters: a to d.\n");
			return 0;
		}
	}
	while((loop == 1 || menu1 == 1));
	/*
	Option 2: switch - case a - ascending order.
	                   case b - seperate digits.
	                   case c - exit or restart.
	                   default - wrong option.
	*/
    do
	{
        loop = 0;
		if (menu1 == 2)
		{
			printf("please your number: \n");
			scanf("%d", &submenu1);
			if(submenu1<0)
			negative = 1;
			if((submenu1<10 && negative == 0) || (submenu1>-9 && negative == 1))
			{
			    if(submenu1>-9 && negative == 1)
			    printf("You have entered one digit negative number, please enter multi-digit number:\n");
			    if(submenu1<10 && negative == 0)
			    printf("You have entered one digit positive number, please enter multi-digit number:\n");
			    scanf("%d",&submenu1);
			}
			printf("Enter your choice:\n");
			printf("a - check, are the digits in ascending order?\n");
			printf("b - print each dgit on a separate line (left digit will be first)\n");
			printf("c - exit\n");
			scanf(" %c", &letteral1);
			switch (letteral1)
			{
				case 'a':
				if(submenu1<0)
				{
				    while(submenu1<0)
                {
                    digit = submenu1 % 10; /*seperate the digits in the number*/
                    submenu1 = submenu1 / 10; /*to decrese the number*/
                    helper = submenu1 % 10;
                    submenu1 = submenu1 / 10;
                    if(helper < digit || helper == digit)
                    {
                        order = 1;
                        printf("The digits are not in ascending order.\n");
                        break;
                    }
                    else if(helper > digit)
                    order = 0;
                }
                printf("%d %d %d",submenu1,helper,digit);
				}
				while(submenu1>0)
                {
                    digit = submenu1 % 10; /*seperate the digits in the number*/
                    submenu1 = submenu1 / 10; /*to decrese the number*/
                    helper = submenu1 % 10;
                    if(helper > digit || helper == digit)
                    {
                        order = 1;
                        printf("The digits are not in ascending order.\n");
                        break;
                    }
                    else if(helper < digit)
                    order = 0;
                }
                if(order == 0)
                printf("The digits in ascending order.\n");
                return 0;
                case 'b':
                temp=submenu1;
                while(temp){
                temp=temp/10;
                factor = factor*10;
                }
                printf("Each digits of given number are: \n");
                while(factor>1){
                factor = factor/10;
                printf("%d \n",submenu1/factor);
                submenu1 = submenu1 % factor;
                }
                return 0;
            case 'c':
			printf("Do you want to continue? (if yes, press 'y', if no, press 'n'\n");
			scanf(" %c", &subexit);
			switch (subexit)
			{
			case 'y':
				loop = 1;
				break;
			case 'n':
				printf("You have chosen to exit the program.\n");
				return 0;
			default:
				printf("You have choosen wrong options, please select y - for yes or n - for no.\n");
			}
			default:
			printf("You have choosen an option that doesn't exist, please between the characters: a to c.\n");
			return 0;
		}
		}
}
while((loop == 1 || menu1 == 2));
}
