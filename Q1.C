#include <stdio.h>
#include <math.h>
main()
{
    int units;
    double price;
    printf("Enter number units of charges: \n");
    scanf("%d",&units);
    if(units<=50)
    {
        price = 0.6;
        price = units * price;
    }
    else if(units <= 150)
    {
        price = 30 + ((units - 50) * 0.85);
    }
    else if(units <= 250)
    {
        price = 115 + ((units - 150) * 1.50);
    }
    else if(units > 250)
    {
        price = 265 + ((units - 250) * 2.75);
    }
    printf("Your payment: %f shek.", price);
    return 0;
}