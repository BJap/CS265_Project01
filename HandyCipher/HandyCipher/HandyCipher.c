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

static char keyTable[5][5];     // key table
static char padTable[15];       // padding table
static int  charMap[128];       // character to number mapping
static char tuple[6];           // the row, column, or diagonal randomly selected
static char subTuple[6];        // the characters matching with '1' bits of the number for the character mapping
static char mixTuple[6];        // the random arragement of the selected characters in eSelect
static char lastTuple[6];       // the last character substitution string created that meets all requirements

#define T keyTable
#define e tuple
#define random() rand()

// The amount of permututations (n!) for characters in subTuple
int permCount[5] = { 1, 2, 6, 24, 120 };

// Permutation Tables
int permTables [120][5] =
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
    int keyPos = 0;
    int padPos = 0;
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char c = key[keyPos++];
            
            if (c == '^') c = key[keyPos++];
            
            if (j < 5) keyTable[i][j] = c;
            else padTable[padPos++] = c;
        }
    }
}

// Check to see if the encoding has only one bit in it
static bool isSingleton(int charValue)
{
    return (charValue == 1) || (charValue == 2) || (charValue == 4) || (charValue == 8) || (charValue == 16);
}

// Assign the tuple to the character tuple array
static void createTuple(int randTup)
{
    switch (randTup)
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
}

// Check to see if the choice of encryption will allow unique reading on decryption
static bool validateLine(int randTup, char next, bool singletonLast)
{
    // the new line is invalid if the first character was in the last line added to the cipher
    if (strchr(lastTuple, mixTuple[0]) != NULL) return false;
    
    if (randTup >= 5 && randTup <= 9 && isSingleton(charMap[next])) return false;
    
    if (singletonLast)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (T[i][j] == mixTuple[0])
                {
                    for (int k = 0; k < 5; k++)
                    {
                        if (T[i][k] == lastTuple[0]) return false;
                        
                        if (T[k][j] == lastTuple[0]) return false;
                        
                        if (T[i + k < 5 ? i + k : i + k - 5][j + k < 5 ? j + k : j + k - 5] == lastTuple[0]) return false;
                        
                        if (T[i + k < 5 ? i + k : i + k - 5][j - k >= 0 ? j - k : j - k + 5] == lastTuple[0]) return false;
                    }
                }
            }
        }
    }
    
    return true;
}

char *encryptText(char *text, char *key)
{
    bool singletonLast = false;
    
    char *cipher = malloc(10 * strlen(cipher));
    cipher[0] = '\0';
    
    char *subKey = generateSubKey(key);
    
    generateTables(key);
    generateSubstitution(subKey, charMap);
    
    size_t textLength = strlen(text);
    
    int cipherPos = 0;
    
    // find a line to substitute in for each character in the text
    for (int i = 0; i < textLength; i++)
    {
        char c = text[i];
        int charValue = charMap[c];
        
        if (charValue == 0) continue;
        
        bool singleton = isSingleton(charValue);
        int randTup;
        
        // generate a line until one satisfies the restrictions for the cipher
        do
        {
            randTup = random() % (singleton ? 5 : 20);
            
            createTuple(randTup);
            
            bool oddPos = (i % 2) == 0;
            int subTupLen = 0;
            
            // select the letters from the tuple that align with the '1's in the binary of the number
            // for the given character and in the correct direction
            for (int j = 0, mask = 0x10; j < 5; j++, mask >>= 1)
            {
                if (charValue & mask) subTuple[subTupLen++] = oddPos ? e[j] : e[4 - j];
            }
            
            subTuple[subTupLen] = '\0';
            
            int randPerm = random() % permCount[subTupLen - 1];
            
            // reorder the line chosen for substitution
            for (int j = 0; j < subTupLen; j++)
            {
                mixTuple[j] = subTuple[permTables[randPerm][j]];
            }
            
            mixTuple[subTupLen] = '\0';
            
        } while (!validateLine(randTup, text[i + 1], singletonLast));
        
        // concatenate the line onto the cipher text
        for (int j = 0; mixTuple[j] != '\0'; j++)
        {
            cipher[cipherPos++] = mixTuple[j];
        }
        
        memcpy(lastTuple, mixTuple, 6);
        
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
