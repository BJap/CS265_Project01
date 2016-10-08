//
//  HandyCipher.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HandyCipher.h"
#include "HCKeyGen.h"

#pragma mark SHARED VARIABLES
static int  cipherPos = 0;      // current slot in the cipher to encrypt into or from which to decrypt
static char keyTable[5][5];     // key table
static char padTable[15];       // padding table
static char tuple[6];           // the row, column, or diagonal randomly selected

#define T keyTable
#define e tuple
#define random() rand()

#pragma mark ENCRYPTION VARIABLES
static int  charMap[128];       // character to number mapping
static char subTuple[6];        // the characters matching with '1' bits of the number for the character mapping
static char mixTuple[6];        // the random arragement of the selected characters in subTuple
static char lastTuple[6];       // the last character substitution string created that meets all requirements
static char lastMixTuple[6];    // the last random arragement of the selected characters in lastTuple
static char lastPad[6];         // the last padding characters used that cannot be reused

#pragma mark DECRYPTION VARIABLES
static int pairMap[128];        // character to table position encoding mapping

#pragma mark LOOKUP TABLES

// The amount of permututations (n!) for characters in subTuple
const int PERM_COUNT[5] = { 1, 2, 6, 24, 120 };

// Permutation Tables
const int PERM_TABLES [120][5] =
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

// Generate the three tables for encryption/decryption, padding, and number to character mapping
static void generateTables(char *key)
{
    memset(pairMap, -1, 128 * sizeof(int));
    
    int keyPos = 0;
    int padPos = 0;
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char c = key[keyPos++];
            
            if (c == '^') c = key[keyPos++];
            
            if (j < 5)
            {
                keyTable[i][j] = c;
                pairMap[c] = (i << 4) + j;
            }
            else padTable[padPos++] = c;
        }
    }
}

#pragma mark ENCRYPTION STARTS HERE

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
    
    // there is a bug in the cipher for which this check accounts
    if (randTup >= 5 && randTup <= 9 && isSingleton(charMap[next])) return false;
    
    // the first letter of the next tuple cannot be colinear with the previous tuple if it was a singleton
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
                        if (T[i][k] == lastMixTuple[0]) return false;
                        
                        if (T[k][j] == lastMixTuple[0]) return false;
                        
                        if (T[i + k < 5 ? i + k : i + k - 5][j + k < 5 ? j + k : j + k - 5] == lastMixTuple[0]) return false;
                        
                        if (T[i + k < 5 ? i + k : i + k - 5][j - k >= 0 ? j - k : j - k + 5] == lastMixTuple[0]) return false;
                    }
                }
            }
        }
    }
    
    return true;
}

// Find the next valid padding character
static char getNextPadChar()
{
    char next;
    bool valid;
    
    // get a valid null character
    do
    {
        int randPad = random() % 15;
        
        next = padTable[randPad];
        
        // check for the character in the last used table and throw it out
        // with probability relative to how recently it was used
        for (int i = 0; i < 5; i++)
        {
            valid = next == lastPad[i] && random() % 5 > i;
        }
        
        valid = true;
        
    } while (!valid);
    
    // move each padding character forward
    for (int i = 4; i >= 0; i--)
    {
        lastPad[i + 1] = lastPad[i];
    }
    
    lastPad[0] = next;
    lastPad[5] = '\0';
    
    return next;
}

char *encryptText(char *text, char *key)
{
    bool singletonLast = false;
    
    cipherPos = 0;
    
    char *cipher = malloc(10 * strlen(text));
    cipher[0] = '\0';
    
    char *subKey = generateSubKey(key);
    
    generateTables(key);
    generateSubstitution(subKey, charMap);
    
    size_t textLength = strlen(text);
    
    // find a line to substitute in for each character in the text
    for (int i = 0; i < textLength; i++)
    {
        char c = text[i];
        
        // convert spaces into the encryptable character
        if (c == ' ') c = '^';
        
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
            
            int randPerm = random() % PERM_COUNT[subTupLen - 1];
            
            // reorder the line chosen for substitution
            for (int j = 0; j < subTupLen; j++)
            {
                mixTuple[j] = subTuple[PERM_TABLES[randPerm][j]];
            }
            
            mixTuple[subTupLen] = '\0';
            
        } while (!validateLine(randTup, text[i + 1], singletonLast));
        
        bool tupleCp = false;
        int mixPos = 0;
        
        // concatenate the line onto the cipher text with random padding
        while (!tupleCp)
        {
            int randGrab = random() % 8;
            
            // add the next tuple character
            if (randGrab < 5)
            {
                if (mixTuple[mixPos] != '\0') cipher[cipherPos++] = mixTuple[mixPos++];
                else tupleCp = true;
            }
            // add a padding character
            else
            {
                cipher[cipherPos++] = getNextPadChar();
            }
        }
        
        // save current values as last values for the next round comparisons per handy cipher restrictions
        memcpy(lastTuple, tuple, 6);
        memcpy(lastMixTuple, mixTuple, 6);
        
        singletonLast = singleton;
    }
    
    cipher[cipherPos] = '\0';
    
    return cipher;
}

#pragma mark DECRYPTION STARTS HERE

// Find the next non-padding character's encoding pair or EOF at end of string
static char getNextChar(char *cipher)
{
    char c;
    
    while ((c = cipher[cipherPos]) != '\0')
    {
        cipherPos++;
        
        int pair = pairMap[c];
        
        // the character is in the key table and not the padding table
        if (pair != -1) return c;
    }
    
    return EOF;
}

char *decryptText(char *cipher, char *key)
{
    int textPos = 0;
    char *text = malloc(strlen(cipher));
    char *subKey = generateSubKey(key);
    
    cipherPos = 0;
    generateTables(key);
    
    // decrypt each character in the cipher
    while (true)
    {
        int charInPos = 0;
        char charIn[6];
        char c1 = getNextChar(cipher);
        
        // no more cipher text to decrypt
        if (c1 == EOF) break;
        
        int pair1 = pairMap[c1];
        int i1 = (pair1 >> 4) & 0x7;
        int j1 = pair1 & 0x7;
        
        charIn[charInPos++] = c1;
        
        char c2 = getNextChar(cipher);
        
        int pair2 = pairMap[c2];
        int i2 = (pair2 >> 4) & 0x7;
        int j2 = pair2 & 0x7;
        
        // not a singleton
        if (c2 != EOF && pair2 != -1) charIn[charInPos++] = c2;

        // end of text singleton
        if (charInPos == 1)
        {
            for (int i = 0; i < 5; i++)
            {
                e[i] = T[i][j1];
            }
        }
        // same column
        else if (j1 == j2)
        {
            for (int i = 0; i < 5; i++)
            {
                e[i] = T[i][j1];
            }
        }
        // same row
        else if (i1 == i2)
        {
            for (int j = 0; j < 5; j++)
            {
                e[j] = T[i1][j];
            }
        }
        // same right diagonal
        else if ((((i2 - i1) - (j2 - j1)) % 5) == 0)
        {
            for (int i = 0; i < 5; i++)
            {
                e[i] = T[i][(j1 - i1 + i + 5) % 5];
            }
        }
        // same left diagonal
        else if ((((i2 - i1) + (j2 - j1)) % 5) == 0)
        {
            for (int i = 0; i < 5; i++)
            {
                e[i] = T[i][(j1 + i1 - i + 5) % 5];
            }
        }
        // non-colinear
        else
        {
            for (int i = 0; i < 5; i++)
            {
                e[i] = T[i][j1];
            }
            
            charIn[charInPos] = '\0';
            
            cipherPos--;
        }
        
        e[5] = '\0';
        
        // grab all the remaining characters for the current letter substitution
        while ((c1 = getNextChar(cipher)) != EOF)
        {
            // the next character is in the next substitution and should be put back
            if (memchr(e, c1, 5) == NULL)
            {
                cipherPos--;
                break;
            }
            // this character belongs in this substition so store it
            else
            {
                charIn[charInPos++] = c1;
                
                // something is wrong if we get more than 5 characters from a substitution
                if (charInPos > 5)
                {
                    fprintf(stderr, "Too many characters\n");
                    
                    text[textPos] = '\0';
                    
                    return NULL;
                }
            }
        }
        
        charIn[charInPos] = '\0';
        
        int b = 0;
        bool oddPos = (textPos % 2) == 0;
        int mask = oddPos ? 0x10 : 0x01;
        
        // calculate b for the characters given in the tuple
        for (int i = 0; i < 5; i++)
        {
            // add a '1' bit if the character is in the substitution
            if (memchr(charIn, e[i], charInPos) != NULL) b |= mask;
            
            mask = oddPos ? mask >> 1 : mask << 1;
        }
        
        char decodedChar = subKey[b - 1];
        
        // convert spaces back into the proper character
        if (decodedChar == '^') decodedChar = ' ';
        
        text[textPos++] = decodedChar;
    }
    
    text[textPos] = '\0';
    
    return text;
}
