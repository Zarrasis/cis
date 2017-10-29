//
//  main.c
//  Checker Program
//
//  Created by Matt Taubler on 11/4/14.
//  Copyright (c) 2014 Matt Taubler. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Intial Function Delclartions. 
int hextobin(char* hex);
void pad(int placeholder);
void XOR(int placeholder);
int validation(int placeholder, char hex);
void bintohex(char* hex, int placeholder);
void stringtobinary(char* string2);

// Because global variables are fun, 
// and these don't get modified more than once.
int decimalArray[1000] = {0};
int crcPoly[] = {1,0,1,0,0,1,0,1,0,1,0,0,0,1,1,0,1};
char hexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
int xorResult[100] = {0};
int decArray2[1000] = {0}; 
int count = 0;
char choice;
char str4[4] = {0};
char string2[3] = {0};

int main(int argc, char * argv[])
{
    int i = 0;
    int stringlength = 0;
    char yesorno[10];
    FILE *ifp;
    choice = argv[1][0];
    char * fileName = argv[2];
    char hex[1000];
    int placeholder = 0;
    if (choice != 'c' && choice != 'v')
    {
        printf("Error: Invalid input.");
        return 0;
    }
    ifp = fopen(fileName,"r");
    // scans in hexadermal code
    if(ifp == NULL)
    {
        printf("File not opened.\n");
        return 1;
    }
    
    switch (choice)
    {
    case 'c':
    fscanf(ifp,"%s", hex);
    printf("\nThe input file (hex): ");
    i = 0;
    for(i=0; i<strlen(hex); i++)
        printf("%c", hex[i]);
    printf("\n\nThe input file (bin): ");
    printf("\n");
    placeholder = hextobin(hex);
    printf("\n\n");
    printf("The polynomial that was used (binary bit string):\n");
    for(i = 0; i < 17; i++)
    {
        printf("%d", crcPoly[i]);
        if((i+1)%4 == 0)
            printf(" ");
    }
    placeholder = placeholder*4;
    printf("\n\n");
    pad(placeholder);
    printf("\n");
    placeholder = placeholder + 16;
    decimalArray[placeholder] = 3;
    printf("\n");
    printf("The binary string difference after each XOR step of the CRC calculation: \n\n");
    XOR(placeholder);
    bintohex(hex, placeholder);
    break;
    
    
    
    case 'v':
    fscanf(ifp,"%s", hex);
    printf("\nThe input file (hex): ");
    i = 0;
    for(i=0; i<strlen(hex); i++)
        printf("%c", hex[i]);
     printf("\n\nThe input file (bin): ");
    printf("\n");
    placeholder = 0;
    placeholder = hextobin(hex);
    printf("\n\n");
    printf("The polynomial that was used (binary bit string):\n");
    for(i = 0; i < 17; i++)
    {
        printf("%d", crcPoly[i]);
        if((i+1)%4 == 0)
            printf(" ");
    }
    placeholder = placeholder*4;
    printf("\n\n");
    printf("The 16-bit CRC observed at the end of the file: ");
    stringlength = strlen(hex);
    for(i=stringlength;i<stringlength+5;i++)
        string2[i-stringlength] = hex[i-4];
    stringtobinary(string2);
    printf(" (bin) = ");
    for(i=stringlength;i<stringlength+4;i++)
        printf("%c", hex[i-4]);
    printf(" (hex)\n");
    printf("The binary string difference after each XOR step of the CRC calculation: \n\n");
    XOR(placeholder);
    bintohex(hex, placeholder);
    printf("The computed CRC for the input file is: ");
    stringtobinary(string2);
    printf(" (bin) = ");
    for(i=stringlength;i<stringlength+4;i++)
        printf("%c", hex[i-4]);
    printf(" (hex)\n");
    printf("Did the CRC check pass? (Yes or No): \n");
    scanf("%s", yesorno);
    printf("Thank you!\n");
    break;
    
    
    
    
    default: printf("Need a valid input.");
    }
    if (ifp != NULL)
    {
        fclose(ifp);
    }
    return 0;
    
}
int hextobin(char* hex)
{
    
    int i = 0;
    double times = strlen(hex);
    for(i = 0; i < times; i++)
    {
        // 0
        if(hex[i] == '0')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 0;
        }
        // 1
        else if(hex[i] == '1')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 1;
        }
        // 2
        else if(hex[i] == '2')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 0;
        }
        // 3
        else if(hex[i] == '3')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 1;
        }
        // 4
        else if(hex[i] == '4')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 0;
        }
        // 5
        else if(hex[i] == '5')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 1;
        }
        // 6
        else if(hex[i] == '6')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 0;
        }
        // 7
        else if(hex[i] == '7')
        {
            decimalArray[i*4] = 0;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 1;
        }
        // 8
        else if(hex[i] == '8')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 0;
        }
        // 9
        else if(hex[i] == '9')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 1;
        }
        // A
        else if(hex[i] == 'a' || hex[i] == 'A')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 0;
        }
        // B
        else if(hex[i] == 'b' || hex[i] == 'B')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 0;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 1;
        }
        // C
        else if(hex[i] == 'c' || hex[i] == 'C')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 0;
        }
        // D
        else if(hex[i] == 'd' || hex[i] == 'D')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 0;
            decimalArray[(i*4)+3] = 1;
        }
        // E
        else if(hex[i] == 'e' || hex[i] == 'E')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 0;
        }
        // F
        else if(hex[i] == 'f' || hex[i] == 'F')
        {
            decimalArray[i*4] = 1;
            decimalArray[(i*4)+1] = 1;
            decimalArray[(i*4)+2] = 1;
            decimalArray[(i*4)+3] = 1;
        }
    }
    int j = 0;
    for(j = 1; j <= times*4; j++)
    {
        printf("%d",decimalArray[j-1]);
        if(j % 4 == 0)
            printf(" ");
    }

    return i;
}
void pad(int placeholder)
{
    int i = 0;
    printf("We will now append 16 0s for CRC 16:\n");
    for(i = 0; i < placeholder; i++)
    {
        decimalArray[placeholder+i] = 0;
    }
    int j = 0;
    for(j = 1; j <= placeholder+16; j++)
    {
        printf("%d",decimalArray[j-1]);
        if(j % 4 == 0)
            printf(" ");
    }
}
void XOR(int placeholder)
{
    int i, j;
    int sum = 0;
    for(i = 0; i < placeholder; i++)
    {
        printf("%d", decimalArray[i]);
        if((i+1) % 4  == 0)
            printf(" ");
    }
    printf("\n");
    //i = 0;
//    printf(" ");
//    while(decimalArray[i] == 0)
//        i++;
//    for(j = 0; j < i; j++)
//        printf("0 ");
//    for(i = 0; i < 17; i++)
//        printf("%d ", crcPoly[i]);
//
//    printf("\n ");
    i = 0;
    while(decimalArray[i] == 0)
        i++;
    for(j = 0; j < i; j++)
    {
        count = count + i;
       // printf("0 "); 
    }

    for(i=0; i < 17; i++)  
    {   // If statements
        if(decimalArray[j+i] == 0 && crcPoly[i] == 0)
        {
            xorResult[i] = 0;
        }
        if(decimalArray[j+i] == 1 && crcPoly[i] == 0)
        {
            xorResult[i] = 1;
        }   
        else if(decimalArray[j+i] == 0 && crcPoly[i] == 1)
        {
            xorResult[i] = 1;
        }   
        else if(decimalArray[j+i] == 1 && crcPoly[i] == 1)
        {
            xorResult[i] = 0;
        }     
    
    }
    for(i=0; i<17; i++)
    decimalArray[i+j] = xorResult[i];
 //   for(i = 0; i < placeholder; i++)
//        printf(" %d", decimalArray[i]);
//    printf("\n");
    if(choice == 'c')
    {
    i = 0;
    while(decimalArray[i] == 0)
        i++;
    if(decimalArray[placeholder-1] == 1)
    {
        for(i = 0; i < placeholder; i++)
        {
        printf("%d", decimalArray[i]);
        if((i+1) % 4  == 0)
        {
            printf(" ");
        }
        }
        printf("\n");
        return;
    }   
    if(decimalArray[placeholder-1] == 0)
        XOR(placeholder);
    }
    else if(choice == 'v')
    {
    for(i = 0; i < placeholder; i++)
        sum = decimalArray[i] + sum;
    i = 0;
    while(decimalArray[i] == 0)
        i++;
    if(sum == 0)
    {
        for(i = 0; i < placeholder; i++)
        {
        printf("%d", decimalArray[i]);
        if((i+1) % 4  == 0)
        {
            printf(" ");
        }
        }
        printf("\n");
        return;
    }
    else if(sum != 0)
        XOR(placeholder);
    }
    
}
int validation(int placeholder, char hex)
{
    printf("Calculating fresh CRC yo.\n");
    return 0;
}
void bintohex(char* hex, int placeholder)
{
    int sum = 0;
    int i = 0;
    
    for(i = 1; i < 5; i++)
    {
        if (decimalArray[placeholder-i] == 1) sum += (int)pow(2.0, i - 1);
        //if(decimalArray[placeholder-i] == 0)
//            str1[4-i] = '0';
//        if(decimalArray[placeholder-i] == 1)
//            str1[4-i] = '1';
    }
    str4[3] = hexChars[sum];
    sum = 0;
    for(i = 1; i < 5; i++)
    {
       if (decimalArray[placeholder-i-4] == 1) sum += (int)pow(2.0, i - 1);
    }
    str4[2] = hexChars[sum];
    sum = 0;
    for(i = 1; i < 5; i++)
    {
        if (decimalArray[placeholder-i-8] == 1) sum += (int)pow(2.0, i - 1);
    }
    str4[1] = hexChars[sum];
    sum = 0;
    for(i = 1; i < 5; i++)
    {
        if (decimalArray[placeholder-i-12] == 1) sum += (int)pow(2.0, i - 1);
    }
    str4[0] = hexChars[sum];
    sum = 0;
    int k = 0;
    if(choice == 'v')
        return;
    printf("\nThe computed CRC for the input file is: ");
    for(i=placeholder-16; i < placeholder; i++)
    {
        printf("%d", decimalArray[i]);
        decArray2[k] = decimalArray[i];
        k++;
        if((i+1) % 4  == 0)
        {
            printf(" ");
        }
    }
    printf("(bin) = ");
    printf("%s", str4);
    printf(" (hex)\n");
    if(choice == 'c')
    printf("The appended message is %s%s\n", hex, str4);
    
}
void stringtobinary(char* string2)
{
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        // 0
        if(string2[i] == '0')
        {
            printf("0000 ");
        }
        // 1
        else if(string2[i] == '1')
        {
            printf("0001 ");
        }
        // 2
        else if(string2[i] == '2')
        {
            printf("0010 ");
        }
        // 3
        else if(string2[i] == '3')
        {
            printf("0011 ");
        }
        // 4
        else if(string2[i] == '4')
        {
            printf("0100 ");
        }
        // 5
        else if(string2[i] == '5')
        {
            printf("0101 ");
        }
        // 6
        else if(string2[i] == '6')
        {
            printf("0110 ");
        }
        // 7
        else if(string2[i] == '7')
        {
            printf("0111 ");
        }
        // 8
        else if(string2[i] == '8')
        {
            printf("1000 ");
        }
        // 9
        else if(string2[i] == '9')
        {
            printf("1001 ");
        }
        // A
        else if(string2[i] == 'a' || string2[i] == 'A')
        {
            printf("1010");
        }
        // B
         else if(string2[i] == 'b' || string2[i] == 'B')
        {
            printf("1011");
        }
        // C
        else if(string2[i] == 'c' || string2[i] == 'C')
        {
            printf("1100");
        }
        // D
         else if(string2[i] == 'd' || string2[i] == 'D')
        {
            printf("1101");
        }
        // E
         else if(string2[i] == 'e' || string2[i] == 'E')
        {
            printf("1110");
        }
        // F
         else if(string2[i] == 'f' || string2[i] == 'F')
        {
            printf("1111");
        }
    }
}
