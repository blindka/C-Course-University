#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() 
{
    /* H - hours, M - minutes, S - Seconds, Flight - Flight time, leftover - if it is more than 24 hours - days*/
    int H, M, S, Flight, leftover;
    printf("Enter START TIME (H,M,S): \n");
    scanf("%d %d %d",&H, &M, &S);
    /* checks if the value of hours, minutes, seconds is valid, otherwise - exit and stop the program*/
    if(H < 24 || H > 0 || M < 60 || M > 0 || S < 60 || S > 0)
    {
        if((H >= 24 || H < 0)&&(M >= 60 || M < 0)&&(S >= 60 || S < 0))
        {
          printf("You Enter Invalid Inputs: Please Enter Hours between 0-23, Minutes and Seconds between 0-59.");
          return 0;
        }
        if((M >= 60 || M < 0)&&(S >= 60 || S < 0))
        {
           printf("You Enter Invalid Inputs: Minutes and Seconds Input, Please Enter between 0-59.\n");
           return 0;
        }
        if((H >= 24 || H < 0)&&(M >= 60 || M < 0))
        {
          printf("You Enter Invalid Inputs: Please Enter Hours between 0-24, Minutes  between 0-59.\n");
          return 0;
        }
        if((H >= 24 || H < 0)&&(S >= 60 || S < 0))
        {
          printf("You Enter Invalid Inputs: Please Enter Hours between 0-23, Seconds  between 0-59.\n");
          return 0;
        }
        if(H >= 24 || H < 0)
        {
          printf("You Enter Invalid Hours Input: Please Enter Between 0-23.\n");
          return 0;
        }
        if(M >= 60 || M < 0)
        {
           printf("You Enter Invalid Minutes Input: Please Enter Between 0-59.\n");
           return 0;
        }
        if(S >= 60 || S < 0)
        {
          printf("You Enter Invalid Seconds Input: Please Enter Between 0-59.\n");
          return 0;
        }
    }
    printf("Enter FLIGHT TIME in seconds: \n");
    scanf("%d", &Flight);
    /* flight time is only in seconds (less than minute) */
        if(Flight<=60)
        {
            S = S + Flight;
            if(S>60) /* after adding value - if the seconds greater than 60 - adding to minutes */
            {
               M = M + (S/60);
               S = S - 60;
            }
        }
        /* flight time is in minutes (less than hours) */
        if(Flight>60 && Flight<3600)
        {
            M = M + (Flight/60);
            if(M>60) /* after adding value - if the minues greater than 60 - adding to hours*/
            {
               H = H + (M/60);
               M = M - 60;
            }
            S = S + (Flight%60);
            if(S>60) /* after adding value - if the seconds greater than 60 - adding to minutes*/
            {
              M = M + (S/60);
              S = S - 60;
            }
        }
        /* flight time is in hours */
        if(Flight>3600)
        {
            H = H + (Flight/3600); /* adding the value to hours */
            M = M + ((Flight/60) % 60); /* adding the value to minutes */
            
        }
    if(H > 0 && M == 0 && S == 0)
    {
        if(H == 1)
        printf("The LANDING will take place at %d hour exactly",H);
    printf("The LANDING will take place at %d hours exactly",H);
    }
    if(H > 0 && M > 0 && S > 0)
    {
        if(H == 1 && !(M==1))
        printf("The LANDING will take place at %d hour, %d minutes",H,M);
        if(H == 1 && M==1)
        printf("The LANDING will take place at %d hour, %d minute",H,M);
        if(!(H == 1) && M==1)
        printf("The LANDING will take place at %d hours, %d minute",H,M);
        if(H == 1 && !(S==1))
        printf("The LANDING will take place at %d hour, %d seconds",H,S);
        if(H == 1 && S==1)
        printf("The LANDING will take place at %d hour, %d second",H,S);
        if(!(H == 1) && S==1)
        printf("The LANDING will take place at %d hours, %d second",H,S);
        if(H>24) /* if we get more than 24 hours - than outputting +days */
        {
        leftover = H / 24;
        H = H % 24;
        if(leftover == 1)
        {
         printf("The LANDING will take place at %d hours, %d minutes, %d seconds (+%d day)", H, M, S, leftover); 
         return 0;
        }
        else
        {
         printf("The LANDING will take place at %d hours, %d minutes, %d seconds (+%d days)", H, M, S, leftover); 
         return 0;
        }
        }
    printf("The LANDING will take place at %d hours, %d minutes, %d seconds",H,M,S);
    }
    if(H > 0 && M == 0 && S == 0)
    printf("The LANDING will take place at %d hours, %d seconds",H,S);
    return 0;
}
