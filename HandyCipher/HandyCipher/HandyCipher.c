//
//  HandyCipher.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "HandyCipher.h"
#include "HCKeyGen.h"

static char keyTable[5][5];
static char padTable[15];
static int substitution[128];
static char cEncrypt[6];
static char eSelect[6];
static char ePermute[6];
static char eLast[6];

#define T keyTable
#define e cEncrypt
#define random() rand()

int pCount[5] = { 1, 2, 6, 24, 120 };

// Permutation Tables
int perm [120][5] =
{
    { 0, 1, 2, 3, 4 },
    { 1, 0, 2, 3, 4 },
    { 1, 2, 0, 3, 4 },
    { 0, 2, 1, 3, 4 },
    { 2, 0, 1, 3, 4 },
    { 2, 1, 0, 3, 4 },
    
    { 0, 1, 3, 2, 4 },
    { 1, 0, 3, 2, 4 },
    { 1, 2, 3, 0, 4 },
    { 0, 2, 3, 1, 4 },
    { 2, 0, 3, 1, 4 },
    { 2, 1, 3, 0, 4 },
    
    { 0, 3, 1, 2, 4 },
    { 1, 3, 0, 2, 4 },
    { 1, 3, 2, 0, 4 },
    { 0, 3, 2, 1, 4 },
    { 2, 3, 0, 1, 4 },
    { 2, 3, 1, 0, 4 },
    
    { 3, 0, 1, 2, 4 },
    { 3, 1, 0, 2, 4 },
    { 3, 1, 2, 0, 4 },
    { 3, 0, 2, 1, 4 },
    { 3, 2, 0, 1, 4 },
    { 3, 2, 1, 0, 4 },
    //
    { 0, 1, 2, 4, 3 },
    { 1, 0, 2, 4, 3 },
    { 1, 2, 0, 4, 3 },
    { 0, 2, 1, 4, 3 },
    { 2, 0, 1, 4, 3 },
    { 2, 1, 0, 4, 3 },
    
    { 0, 1, 3, 4, 2 },
    { 1, 0, 3, 4, 2 },
    { 1, 2, 3, 4, 0 },
    { 0, 2, 3, 4, 1 },
    { 2, 0, 3, 4, 1 },
    { 2, 1, 3, 4, 0 },
    
    { 0, 3, 1, 4, 2 },
    { 1, 3, 0, 4, 2 },
    { 1, 3, 2, 4, 0 },
    { 0, 3, 2, 4, 1 },
    { 2, 3, 0, 4, 1 },
    { 2, 3, 1, 4, 0 },
    
    { 3, 0, 1, 4, 2 },
    { 3, 1, 0, 4, 2 },
    { 3, 1, 2, 4, 0 },
    { 3, 0, 2, 4, 1 },
    { 3, 2, 0, 4, 1 },
    { 3, 2, 1, 4, 0 },
    //
    { 0, 1, 4, 2, 3 },
    { 1, 0, 4, 2, 3 },
    { 1, 2, 4, 0, 3 },
    { 0, 2, 4, 1, 3 },
    { 2, 0, 4, 1, 3 },
    { 2, 1, 4, 0, 3 },
    
    { 0, 1, 4, 3, 2 },
    { 1, 0, 4, 3, 2 },
    { 1, 2, 4, 3, 0 },
    { 0, 2, 4, 3, 1 },
    { 2, 0, 4, 3, 1 },
    { 2, 1, 4, 3, 0 },
    
    { 0, 3, 4, 1, 2 },
    { 1, 3, 4, 0, 2 },
    { 1, 3, 4, 2, 0 },
    { 0, 3, 4, 2, 1 },
    { 2, 3, 4, 0, 1 },
    { 2, 3, 4, 1, 0 },
    
    { 3, 0, 4, 1, 2 },
    { 3, 1, 4, 0, 2 },
    { 3, 1, 4, 2, 0 },
    { 3, 0, 4, 2, 1 },
    { 3, 2, 4, 0, 1 },
    { 3, 2, 4, 1, 0 },
    //
    { 0, 4, 1, 2, 3 },
    { 1, 4, 0, 2, 3 },
    { 1, 4, 2, 0, 3 },
    { 0, 4, 2, 1, 3 },
    { 2, 4, 0, 1, 3 },
    { 2, 4, 1, 0, 3 },
    
    { 0, 4, 1, 3, 2 },
    { 1, 4, 0, 3, 2 },
    { 1, 4, 2, 3, 0 },
    { 0, 4, 2, 3, 1 },
    { 2, 4, 0, 3, 1 },
    { 2, 4, 1, 3, 0 },
    
    { 0, 4, 3, 1, 2 },
    { 1, 4, 3, 0, 2 },
    { 1, 4, 3, 2, 0 },
    { 0, 4, 3, 2, 1 },
    { 2, 4, 3, 0, 1 },
    { 2, 4, 3, 1, 0 },
    
    { 3, 4, 0, 1, 2 },
    { 3, 4, 1, 0, 2 },
    { 3, 4, 1, 2, 0 },
    { 3, 4, 0, 2, 1 },
    { 3, 4, 2, 0, 1 },
    { 3, 4, 2, 1, 0 },
    //
    { 4, 0, 1, 2, 3 },
    { 4, 1, 0, 2, 3 },
    { 4, 1, 2, 0, 3 },
    { 4, 0, 2, 1, 3 },
    { 4, 2, 0, 1, 3 },
    { 4, 2, 1, 0, 3 },
    
    { 4, 0, 1, 3, 2 },
    { 4, 1, 0, 3, 2 },
    { 4, 1, 2, 3, 0 },
    { 4, 0, 2, 3, 1 },
    { 4, 2, 0, 3, 1 },
    { 4, 2, 1, 3, 0 },
    
    { 4, 0, 3, 1, 2 },
    { 4, 1, 3, 0, 2 },
    { 4, 1, 3, 2, 0 },
    { 4, 0, 3, 2, 1 },
    { 4, 2, 3, 0, 1 },
    { 4, 2, 3, 1, 0 },
    
    { 4, 3, 0, 1, 2 },
    { 4, 3, 1, 0, 2 },
    { 4, 3, 1, 2, 0 },
    { 4, 3, 0, 2, 1 },
    { 4, 3, 2, 0, 1 },
    { 4, 3, 2, 1, 0 },
};

// Generate the two tables for encryption/decryption, and padding
static void generateTables(char *key)
{
    int kp = 0;
    int pp = 0;
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char c = key[kp++];
            
            if (c == '^') c = key[kp++];
            
            if (j < 5) keyTable[i][j] = c;
            else padTable[pp++] = c;
        }
    }
}

// Check to see if the encoding has only one bit in it
static bool isSingleton(int sub)
{
    return (sub == 1) || (sub == 2) || (sub == 4) || (sub == 8) || (sub == 16);
}

// Check to see if the choice of encryption will allow unique reading on decryption
static bool validateLine(int rTup, char next, bool singletonLast)
{
    if (strchr(eLast, ePermute[0]) != NULL) return false;
    
    if (rTup >= 5 && rTup <= 9 && isSingleton(substitution[next])) return false;
    
    if (singletonLast)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (T[i][j] == ePermute[0])
                {
                    for (int k = 0; k < 5; k++)
                    {
                        if (T[i][k] == eLast[0]) return false;
                        
                        if (T[k][j] == eLast[0]) return false;
                        
                        if (T[i + k < 5 ? i + k : i + k - 5][j + k < 5 ? j + k : j + k - 5] == eLast[0]) return false;
                        
                        if (T[i + k < 5 ? i + k : i + k - 5][j - k >= 0 ? j - k : j - k + 5] == eLast[0]) return false;
                    }
                }
            }
        }
    }
    
    return true;
}

// TODO
static char *tuple(int letterNum)
{
    char *tuple;
    
    // TODO
    
    return tuple;
}

char *encryptText(char *text, char *key)
{
    bool singletonLast = false;
    
    char *cipher = malloc(10 * strlen(cipher));
    cipher[0] = '\0';
    
    char *subKey = generateSubKey(key);
    
    generateTables(key);
    generateSubstitution(subKey, substitution);
    
    size_t length = strlen(text);
    
    int iCipher = 0;
    
    for (int i = 0; i < length; i++)
    {
        char c = text[i];
        int sub = substitution[c];
        
        if (sub == 0) continue;
        
        bool singleton = isSingleton(sub);
        int rTup;
        
        do
        {
            rTup = random() % (singleton ? 5 : 20);
            
            switch (rTup)
            {
                // Columns
                case  0: e[0] = T[0][0]; e[1] = T[1][0]; e[2] = T[2][0]; e[3] = T[3][0]; e[4] = T[4][0]; break;
                case  1: e[0] = T[0][1]; e[1] = T[1][1]; e[2] = T[2][1]; e[3] = T[3][1]; e[4] = T[4][1]; break;
                case  2: e[0] = T[0][2]; e[1] = T[1][2]; e[2] = T[2][2]; e[3] = T[3][2]; e[4] = T[4][2]; break;
                case  3: e[0] = T[0][3]; e[1] = T[1][3]; e[2] = T[2][3]; e[3] = T[3][3]; e[4] = T[4][3]; break;
                case  4: e[0] = T[0][4]; e[1] = T[1][4]; e[2] = T[2][4]; e[3] = T[3][4]; e[4] = T[4][4]; break;
                    
                // Rows
                case  5: e[0] = T[0][0]; e[1] = T[0][1]; e[2] = T[0][2]; e[3] = T[0][3]; e[4] = T[0][4]; break;
                case  6: e[0] = T[1][0]; e[1] = T[1][1]; e[2] = T[1][2]; e[3] = T[1][3]; e[4] = T[1][4]; break;
                case  7: e[0] = T[2][0]; e[1] = T[2][1]; e[2] = T[2][2]; e[3] = T[2][3]; e[4] = T[2][4]; break;
                case  8: e[0] = T[3][0]; e[1] = T[3][1]; e[2] = T[3][2]; e[3] = T[3][3]; e[4] = T[3][4]; break;
                case  9: e[0] = T[4][0]; e[1] = T[4][1]; e[2] = T[4][2]; e[3] = T[4][3]; e[4] = T[4][4]; break;
                    
                // Right Diagonal
                case 10: e[0] = T[0][0]; e[1] = T[1][1]; e[2] = T[2][2]; e[3] = T[3][3]; e[4] = T[4][4]; break;
                case 11: e[0] = T[0][1]; e[1] = T[1][2]; e[2] = T[2][3]; e[3] = T[3][4]; e[4] = T[4][0]; break;
                case 12: e[0] = T[0][2]; e[1] = T[1][3]; e[2] = T[2][4]; e[3] = T[3][0]; e[4] = T[4][1]; break;
                case 13: e[0] = T[0][3]; e[1] = T[1][4]; e[2] = T[2][0]; e[3] = T[3][1]; e[4] = T[4][2]; break;
                case 14: e[0] = T[0][4]; e[1] = T[1][0]; e[2] = T[2][1]; e[3] = T[3][2]; e[4] = T[4][3]; break;
                    
                // Left Diagonal
                case 15: e[0] = T[0][0]; e[1] = T[1][4]; e[2] = T[2][3]; e[3] = T[3][2]; e[4] = T[4][1]; break;
                case 16: e[0] = T[0][1]; e[1] = T[1][0]; e[2] = T[2][4]; e[3] = T[3][3]; e[4] = T[4][2]; break;
                case 17: e[0] = T[0][2]; e[1] = T[1][1]; e[2] = T[2][0]; e[3] = T[3][4]; e[4] = T[4][3]; break;
                case 18: e[0] = T[0][3]; e[1] = T[1][2]; e[2] = T[2][1]; e[3] = T[3][0]; e[4] = T[4][4]; break;
                case 19: e[0] = T[0][4]; e[1] = T[1][3]; e[2] = T[2][2]; e[3] = T[3][1]; e[4] = T[4][0]; break;
            }
            
            bool odd = (i % 2) == 0;
            int count = 0;
            
            for (int j = 0, mask = 0x10; j < 5; j++, mask >>= 1)
            {
                if (sub & mask) eSelect[count++] = odd ? e[j] : e[4 - j];
            }
            
            eSelect[count] = '\0';
            
            int rPerm = random() % pCount[count - 1];
            
            for (int j = 0; j < count; j++)
            {
                ePermute[j] = eSelect[perm[rPerm][j]];
            }
            
            ePermute[count] = '\0';
            
        } while (!validateLine(rTup, text[i + 1], singletonLast));
        
        for (int j = 0; ePermute[j] != '\0'; j++)
        {
            cipher[iCipher++] = ePermute[j];
        }
        
        memcpy(eLast, ePermute, 6);
        
        singletonLast = singleton;
    }
    
    return cipher;
}

char *decryptText(char *cipher, char *key)
{
    char *text = malloc(strlen(cipher));
    text[0] = '\0';
    
    char *subKey = generateSubKey(key);
    
    generateTables(key);
    
    // TODO
    
    return text;
}
