#include<stdio.h>
#define min(x,y) ((x)<(y)?(x):(y))

int main()
{
    int cap,rate,b=0,n=0,a[25],ch,i,d;

    printf("Bucket size: ");
    scanf("%d",&cap);
    printf("Output rate: ");
    scanf("%d",&rate);

    do{
        printf("Packets at %d sec: ",n+1);
        scanf("%d",&a[n++]);
        printf("Continue(1/0): ");
        scanf("%d",&ch);
    }while(ch);

    printf("\nSec\tRecv\tSent\tLeft\tDrop\n");

    for(i=0;i<n;i++)
    {
        b+=a[i]; d=0;
        if(b>cap){ d=b-cap; b=cap; }

        printf("%d\t%d\t%d\t%d\t%d\n",
               i+1,a[i],min(b,rate),
               b-min(b,rate),d);

        b-=min(b,rate);
    }

    while(b)
    {
        i++;
        printf("%d\t0\t%d\t%d\t0\n",
               i,min(b,rate),b-min(b,rate));
        b-=min(b,rate);
    }
}