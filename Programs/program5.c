#include <stdio.h>

int h[12];

void gen()
{
    h[1]=(h[3]+h[5]+h[7]+h[9]+h[11])%2;
    h[2]=(h[3]+h[6]+h[7]+h[10]+h[11])%2;
    h[4]=(h[5]+h[6]+h[7])%2;
    h[8]=(h[9]+h[10]+h[11])%2;
}

void error()
{
    int p;
    printf("\nEnter error position: ");
    scanf("%d",&p);
    h[p]=!h[p];
}

void check()
{
    int p;

    p=((h[8]+h[9]+h[10]+h[11])%2)*8
     +((h[4]+h[5]+h[6]+h[7])%2)*4
     +((h[2]+h[3]+h[6]+h[7]+h[10]+h[11])%2)*2
     +((h[1]+h[3]+h[5]+h[7]+h[9]+h[11])%2);

    printf("\nError position = %d",p);

    if(p)
        h[p]=!h[p];

    printf("\nCorrect codeword: ");
    for(int i=1;i<12;i++)
        printf("%d ",h[i]);
}

int main()
{
    int i,ch;

    printf("Enter 7 data bits: ");
    for(i=1;i<12;i++)
        if(i!=1 && i!=2 && i!=4 && i!=8)
            scanf("%d",&h[i]);

    gen();

    printf("Transmitted codeword: ");
    for(i=1;i<12;i++)
        printf("%d ",h[i]);

    printf("\nDo you want to make error? (1/0): ");
    scanf("%d",&ch);

    if(ch)
    {
        error();

        printf("Error codeword: ");
        for(i=1;i<12;i++)
            printf("%d ",h[i]);

        check();
    }
    else
        printf("\nNo error");

    return 0;
}

// It generates a Hamming Code for 7 data bits, adds 4 parity bits, and creates an 11-bit codeword.

// Then it can:

// Introduce an error at a chosen position.
// Detect the error position.
// Correct the error and print the original codeword.

// In one line:
// 👉 Generate Hamming code → introduce error → detect error → correct error.