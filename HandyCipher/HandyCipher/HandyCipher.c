//
//  HandyCipher.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include "HandyCipher.h"
#include "HCKeyGen.h"

static char keyTable[5][5];
static char padTable[15];
static char substitution[128];

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

static char *tuple(int letterNum)
{
    char *tuple;
    
    // TODO
    
    return tuple;
}

char *encryptText(char *text, char *key)
{
    char *cipher = malloc(10 * strlen(cipher));
    cipher[0] = '\0';
    
    char *subKey = generateSubKey(key);
    
    generateTables(key);
    generateSubstitution(subKey, substitution);
    
    // TODO
    
    return cipher;
}

char *decryptText(char *cipher, char *key)
{
    char *text = malloc(strlen(cipher));
    text[0] = '\0';
    
    generateTables(key);
    
    // TODO
    
    return text;
}
