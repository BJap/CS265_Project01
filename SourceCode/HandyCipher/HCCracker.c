//
//  HCCracker.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "HandyCipher.h"
#include "HCCracker.h"
#include "HCKeyGen.h"

#pragma mark CONSTANTS AND VARIABLES

#define random() rand()
#define MAX_BRUTE_ATTEMPTS 1000000

static char pKey[KEY_LENGTH + 1];
static int bruteCount = 0;
static time_t bruteStart;

#pragma mark TEXT VALIDATION

// Check the top 10, 3+ length most commonly used words in the English language
// Source: https://en.wikipedia.org/wiki/Most_common_words_in_English
static bool containsCommonWord(char *text)
{
    if (text == NULL) return false;
    else if (strstr(text, " THE ") != NULL) return true;
    else if (strstr(text, " AND ") != NULL) return true;
    else if (strstr(text, " THAT ") != NULL) return true;
    else if (strstr(text, " HAVE ") != NULL) return true;
    else if (strstr(text, " FOR ") != NULL) return true;
    else if (strstr(text, " NOT ") != NULL) return true;
    else if (strstr(text, " WITH ") != NULL) return true;
    else if (strstr(text, " YOU ") != NULL) return true;
    else if (strstr(text, " THIS ") != NULL) return true;
    else if (strstr(text, " BUT ") != NULL) return true;
    else return false;
}

#pragma mark BRUTE FORCE ATTACK

// Recursively check every key until the first possible candidate is found
static bool permute(char *cipher, int depth, char *known)
{
    if (depth == KEY_LENGTH)
    {
        
        if (bruteCount == MAX_BRUTE_ATTEMPTS)
        {
            time_t bruteEnd = time(NULL);
            int time = (int) (bruteEnd - bruteStart);
            
            printf("\n%d keys tried already with %d second(s) passed\n", MAX_BRUTE_ATTEMPTS , time);
        }
        
        bruteCount++;
        
        char *text = decryptText(cipher, pKey);
        
        bool match = false;
        
        if (text != NULL)
        {
            if (known != NULL) match = strstr(text, known);
            else match = containsCommonWord(text);
        }

        free(text);
        
        return match;
    }
    else
    {
        for (int i = depth; i < KEY_LENGTH; i++)
        {
            char temp = pKey[depth];
            
            pKey[depth] = pKey[i];
            pKey[i] = temp;
            
            if (permute(cipher, depth + 1, known)) return true;
        }
    }
    
    return false;
}

char *bruteForce(char *cipher)
{
    return bruteForceWithText(cipher, NULL);
}

char *bruteForceWithText(char *cipher, char *known)
{
    memcpy(pKey, ALPHABET, KEY_LENGTH + 1);
    bruteCount = 0;
    bruteStart = time(NULL);
    
    permute(cipher, 0, known);
    
    char *text = decryptText(cipher, pKey);
    
    printf("\nCipher: %s\nPossible Text: %s\nPossible Key: %s\n", cipher, text, pKey);
    
    return decryptText(cipher, pKey);
}

#pragma mark PRN WEAKNESS ATTACK

char *bruteWithSeed(char *cipher, time_t start, time_t end)
{
    return bruteWithSeedAndText(cipher, NULL, start, end);
}

char *bruteWithSeedAndText(char *cipher, char *known, time_t start, time_t end)
{
    char *key = NULL;
    char *text = NULL;
    
    // check all unix times in a given range as srand seeds
    for (time_t i = start; i <= end; i++)
    {
        // progress indicator to appease the user
        if (i % 1000 == 0) printf("Date: %li\n", i);
        
        key = generateSeededKey(i);
        text = decryptText(cipher, key);
        
        // the text and key are found
        if (text != NULL)
        {
            if (known != NULL && strstr(text, known))
            {
                printf("\nCipher: %s\nText: %s\nPossible Key: %s\n", cipher, text, key);
                
                return text;
            }
            else if (known == NULL && containsCommonWord(text))
            {
                printf("\nCipher: %s\nPossible Text: %s\nPossible Key: %s\n", cipher, text, key);
                
                return text;
            }
        }
        
        free(key);
        free(text);
    }
    
    return NULL;
}
