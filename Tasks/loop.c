#include <stdio.h>
Q1:
int main()
{
    int i;
    for(i = 1; i<=100; i++)
    {
        if(i%6==0)
        {
            printf("%d ",i);
        }
    }
    return 0;
}
Q2:
int main()
{
    int number;
    char operator;
    printf("Please Choose between two options:\n");
    printf("'a' - from the 0 to 20 in Ascending\n");
    printf("'b' - from the 20 to 0 in Descending\n");
    scanf("%c", &operator);
    switch(operator)
    {
    case 'a':
    for(number = 0; number<=20; number++)
    {
        if(number%2==0)
        {
        printf("%d ",number);
        }
    }
    break;
    case 'b':
    for(number = 20; number>=0; number--)
    {
        if(number%2==0)
        {
        printf("%d ",number);  
        }
    }
    break;
    default: printf("You have entered wrong option, Please enter 'a' or 'b'");
    break;
 }
}

Q4:
int main()
{
    int number;
    for(number=1000;number<10000;number++)
    {
        if((number%7==0)&&(number%11==2||number%11==3)&&(number%10 != 8))
        {
            printf("%d\n",number);
        }
        }
    }
Q9:
   int main()
   {
       int number;
       for(number = 1; number<=100;number++)
       {
           if(number%3==0&&number%7==0)
           {
               printf("%d ",number);
           }
       }
   }
Q12:
  int main()
  {
      int number1, number2;
      for(number1 = 1; number1<=3;number1++)
      {
          for(number2 = 1; number2<=3;number2++)
          {
              printf("First is %d, and second is %d, and their multiplying result is %d\n",number1,number2,number1*number2);
          }
      }
  }
Q35: for loop
The program prints the powers of 2 which are < 100.
void main()
{
int i;
for (i=1; i<100; i=i*2)
printf("%d\n",i);
}
int i =1 ;
while(i<100)
{
    printf(%d\n,i);
    i=i*2;
}
Q23:
int main()
{
    int number = 1;
    while(number<=50)
    {
        if(number%2==0)
        {
            printf("%d ",number);
        }
        number++;
    }
}
