//
//  main.c
//  HillCipher
//
//  Created by Matt Taubler on 9/25/14.
//  Copyright (c) 2014 Matt Taubler. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define maxSize = 10000;
#define maxKey = 10;

char inputtext[10000];
char outputtext[10000];
int keyArray[9][9];
int n;

void readKey(FILE *ifp);
void readinput(FILE *fp);
void encrypt();
void pad();


int main(int argc, char *argv[])
{
    FILE *ifp = NULL;
    FILE *fp = NULL;
    int error = 0;
    if( argc != 3 )
    {
        printf("You must apply two file names, 1st is key, 2nd is plaintext.");
    }
    else
    {
        ifp = fopen(argv[1], "r" );
        fp = fopen(argv[2], "r");
        if (ifp == NULL)
        {
            error = 1;
            printf("Could not open the first file");
        }
        if (fp == NULL)
        {
            error = 1;
            printf("Could not open the second file");
        }
        if (!error)
        {
            readKey(ifp);
            readinput(fp);
            pad();
            encrypt();   
        }
    }
    
        
    if(ifp != NULL)
    {
        fclose(ifp);
    }
    if(fp != NULL)
    {
        fclose(fp);
    }
    printf("\n");  
    return 0;
}
void readKey(FILE *ifp)
{
    int i = 0, j = 0;
    n = 0;
    printf("\n"); 
    fscanf(ifp, "%d", &n);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            fscanf(ifp, "%d,", &keyArray[i][j]);
        }
    }
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("%d ", keyArray[i][j]);
        }
        printf("\n");
    }
    fclose(ifp);
}
void readinput(FILE *fp)
{
    char temp = 0;
    int i = 0;
    while ((temp = fgetc(fp)) != EOF)
    {
        if(((int)temp >= 65 && (int)temp <= 90) || ((int)temp >= 97 && (int)temp <= 122))
        {
            inputtext[i++] = tolower(temp);
            temp = tolower(temp);
        }
    }    
    printf("\n\n");
}
void encrypt()
{
    int i = 0, j = 0, k = 0, l = 0;
    int value = 0;
    int charValue = 0;
    int tempMaxtrix[n];
    
    for(i = 0; i < strlen(inputtext); i++)
    {
        tempMaxtrix[i%n] = inputtext[i] - 97;
        if(i%n == n-1)
        {
            for(j = 0; j < n; j++)
            {
                for(k = 0; k < n; k++)
                {
                    value += keyArray[j][k] * tempMaxtrix[k];
                }
                outputtext[l++] = (char)((value % 26) + 97);
                value = 0;
                printf("%c", outputtext[l-1]);
                if(l%80 == 0)
                {
                    printf("\n");
                }
            }
        }
    }
    outputtext[l] = '\0';    
}
void pad()
{
    int oldLength = strlen(inputtext);
    int pad = ((n-(oldLength%n))%n);
    int newLength = oldLength + pad;
    int i;
    for( i = oldLength; i < newLength; i++)
    {
        inputtext[i] = 'x';
    }
    inputtext[newLength] = '\0';
    printf("%s", inputtext);
    printf("\n\n");
}
