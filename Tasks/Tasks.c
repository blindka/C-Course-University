Q1
#include <stdio.h>
int isDivisor(int a, int b){
    if(a%b==0)
    return 1;
    else
    return 0;
}
void main()
{
    int a, b;
    printf("Please enter two numbers:\n");
    printf("a = ");
    scanf("%d",&a);
    printf("b = ");
    scanf("%d",&b);
    printf("%d",isDivisor(a,b));
}

Q2:
int len (int a)
{
    int counter = 0;
    while(a!= 0)
    {
        counter ++;
        
        a=a/10 ;
        
    }
    return counter ;
}
void main ()
{
    int a,counter;
    
    printf("Enter number \n");
    
    scanf ("%d",&a);
    
    printf("%d", len(a));
}

Q3:
#include <stdio.h>
void reverse(int n)
{
    int rev = 0, remainder;
    while (n != 0) {
        remainder = n % 10;
        rev = rev * 10 + remainder;
        n /= 10;
    }
    printf("Reversed number = %d", rev);
}
int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    reverse(n);
    return 0;
}

Q4:
#include <stdio.h>
int max(double a,double b, double number, int i)
{
    double number1 = 0;
    if((a!=0)||(b!=0))
    {
    if(a>b)
    {
        printf("A is bigger: a = %lf",a);
    }
    if (a==b)
    {
        printf("both numbers are equals: %lf",a);
    }
    if(a<b)
    {
        printf("B is bigger: b = %lf",b);
    }
    }
    if((a==0)&&(b==0)&&(number!=0))
    {
      for(i = 2; i<=10; i++)
    {
        printf("Number %d: ", i);
        scanf("%lf",&number1);
        if(number<number1)
        {
            number = number1;
        }
    }
    printf("The largest number is %lf ", number);  
    }
    return 0;
}
int main()
{
    double a, b;
    int i;
    double big;
    printf("Please enter two numbers:\n");
    printf("a = ");
    scanf("%lf",&a);
    printf("b = ");
    scanf("%lf",&b);
    max(a,b,0,0);
    i = 0;
    printf("\nNumber 1:");
    scanf("%lf",&big);
    max(0,0,big,i);
}

Q5:
#include <stdio.h>
#include <math.h>
int ispow(double a, int b, double a1, double q, int n)
{
    double sn = 0;
    if((a!=0) || (b!=0) || (q==0))
    {
       printf("The result is: %lf", pow(a,b)); 
    }
    if((a==0) && (b==0) && (q!=0))
    {
        sn = (a1*((pow(q,(n+1)))-1))/(q-1);
        printf("%lf",sn);
    }
}
int main(){
    double a, a1, q;
    int b, n;
    printf("Please enter a (double)number: ");
    scanf("%lf",&a);
    printf("Please enter the (int)amount of times you multiply: ");
    scanf("%d",&b);
    ispow(a,b,0,0,0);
    printf("\nPlease enter the (a1)first member of the series: ");
    scanf("%lf",&a1);
    printf("Please enter the (q)difference of the series: ");
    scanf("%lf",&q);
    printf("Please enter the (n)amount of members: ");
    scanf("%d",&n);
    ispow(0,0,a1,q,n);
}
