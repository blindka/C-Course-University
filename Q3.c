#include <stdio.h>
int main()
{
    int option, onedigit, infinity, i,j,k, factorial, fibonacci, multidigit;
    int number1, number2, number3, sumfibonacci;
    char suboption, suboption2, subexit, a, b, c, d, y, n;
    start:
    printf("What is your option:\n");
    printf("1 -one-digit numer\n");
    printf("2 -number with indefinite amount of digits\n");
    scanf("%d",&option);
    switch(option)
    {
    case 1:
    printf("Please enter positive one digit number:\n");
    scanf("%d",&infinity);
    if(((infinity/10)!=0) || (infinity<0))
    {
    if((infinity/10)!=0)
    printf("You have chosen wrong number, please choose a one digit positive number.\n");
    if(infinity<0)
    printf("You have selected a negative number, please choose a one digit positive number.\n");
    scanf("%d",&infinity);
    }
    printf("Enter your choice:\n");
    printf("a - factorial\n");
    printf("b - fibonacci sequence\n");
    printf("c - print triangle\n");
    printf("d - exit\n");
    scanf(" %c", &suboption);
    switch(suboption)
    {
        case 'a':
        factorial = 1;
        for(i = 1;i<=infinity;i++)
            factorial *= i;
        printf("Factorial is: %d.\n",factorial);
        return 0;
        case 'b':
        number1 = 0;
        number2 = 1;
        number3 = 0;
        sumfibonacci = 0;
            while( number1 <= infinity)
            {
                sumfibonacci += number1;
                number3 = number1 + number2;
                number1 = number2;
                number2 = number3;
            }
            printf("The sum of fibonnaci i: %d\n", sumfibonacci);
        return 0;
        case 'c':
        for (i = 1; i <= infinity; i++)
        {
            for (j = 1; j <= i; j++)
                printf(" ");
            for (k = i; k<=infinity; k++)
            printf("*");
        printf("\n");
        }
        return 0;
        case 'd':
        printf("Do you want to continue? \n(if yes, press 'y', if no, press 'n'\n");
        scanf(" %c",&subexit);
        switch(subexit)
        {
            case 'y':
            goto start;
            case 'n':
            printf("You have chosen to exit the program\n");
            return 0;
            default:
            printf("You have choosen wrong options, please select y - for yes or n - for no.\n");
        }
        return 0;
        default:
        printf("You have choosen an option that doesn't exist, please between the characters: a to d.\n");
    }
    return 0;
    case 2:
    printf("Please enter a multi-digit number:\n");
    scanf("%d",&multidigit);
    if(((multidigit/100)>9) || ((multidigit/100)<1))
    {
    if((multidigit/100)<1)
    printf("You have Selected a number that isn't multi-digit, Please select again:\n");
    if((multidigit/100)>9)
    printf("You have Selected a number that isn't multi-digit, Please select again:\n");
    scanf("%d",&multidigit);
    }
    printf("Enter your choice:\n");
    printf("a - check, are the digits in ascending order?\n");
    printf("b - print each dgit on a separate line (left digit will be first)\n");
    printf("c - exit\n");
    scanf(" %c",&suboption2);
    switch(suboption2)
    {
        case 'a':
        i = multidigit/100;
        j = (multidigit/10)%10;
        k = multidigit%10;
        if (i > j && i > k)
        {
            if(j>k)
            printf("The digits are in ascending order\n");
            else
            printf("The digits are ot in ascending order\n");
        }
        else
        printf("The digits are ot in ascending order\n");
        return 0;
        case 'b':
        i = multidigit/100;
        j = (multidigit/10)%10;
        k = multidigit%10;
        printf("Left digit is: %d\n", i);
        printf("Middle digit is: %d\n", j);
        printf("Last digit is: %d\n", k);
        return 0;
        case 'c':
        printf("Do you want to continue? (if yes, press 'y', if no, press 'n'\n");
        scanf(" %c",&subexit);
        switch(subexit)
        {
            case 'y':
            goto start;
            case 'n':
            printf("You have chosen to exit the program.\n");
            return 0;
            default:
            printf("You have choosen wrong options, please select y - for yes or n - for no.\n");
        }
        return 0;
        default:
        printf("You have choosen an option that doesn't exist, please between the characters: a to c.\n");
        return 0;
    }
    default:
    printf("You have choosen an option that doesn't exist, please choose the number 1 or 2.\n");
    return 0;
    }
}