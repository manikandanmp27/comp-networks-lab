#include<stdio.h>
#include<string.h>

char data[100], divisor[]="10001000000100001";

void crc(char *s)
{
    int i,j;
    char temp[100];

    strcpy(temp,s);

    for(i=0; i<=strlen(temp)-17; i++)
    {
        if(temp[i]=='1')
            for(j=0;j<17;j++)
                temp[i+j]=(temp[i+j]==divisor[j])?'0':'1';
    }

    printf("CRC = ");
    for(i=strlen(temp)-16;i<strlen(temp);i++)
        printf("%c",temp[i]);
}

int main()
{
    printf("Enter data: ");
    scanf("%s",data);

    strcat(data,"0000000000000000");

    crc(data);

    return 0;
}