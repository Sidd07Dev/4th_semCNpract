# include <stdio.h>
# define  bool int
 
bool getParity(unsigned int n)
{
    bool parity = 0;
    while (n)
    {
        parity = !parity;
        n      = n & (n - 1);
    }       
    return parity;
}
 
int main()
{
     int n;
     printf("enter a number:");
     scanf("%d",&n);
    printf("Parity of no %d = %s",  n,
             (getParity(n)? "odd": "even"));
     
    getchar();
    return 0;
}
