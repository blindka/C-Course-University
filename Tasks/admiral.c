#include <stdio.h>
#include <stdlib.h>
void main()
{
    char type;
    int liter;
    int sum = 0;
    printf("Please select type to a fuel you want to refuel with:\n");
    printf("The type of fuels: 'A' - lead98, 'B' - octane, 'C' - unleaded, 'D' - diesel, 'X' - end\n");
    scanf("%c",&type);
    printf("Please enter amount of liter:");
    scanf("%d",&liter);
    printf("The prices are: lead98 = 7.5₪, octane = 6.6₪, unleaded = 6.3₪, diesel = 7.2₪\n");
    switch(type)
    {
        case 'A':
        sum = (sum + 7.5) * liter;
        printf("The summary is: %d",sum);
        if(sum>150)
        {
            printf("You have won the price\n");
        }
        break;
        case 'B':
        sum = (sum + 6.6) * liter;
        printf("The summary is: %d",sum);
        if(sum>150)
        {
            printf("You have won the price\n");
        }
        break;
        case 'C':
        sum = (sum + 6.3) * liter;
        printf("The summary is: %d",sum);
        if(sum>150)
        {
            printf("You have won the price\n");
        }
        break;
        case 'D':
        sum = (sum + 7.2) * liter;
        printf("The summary is: %d",sum);
        if(sum>150)
        {
            printf("You have won the price\n");
        }
        break;
        case 'X':
        printf("You have exited the program\n");
        break;
        default: printf("You have selected invalid type of fuel\nPlease select: 'A','B','C','D','X'");
    }
    }