//
//  HCCracker.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "HandyCipher.h"
#include "HCCracker.h"
#include "HCKeyGen.h"

#define MAX_BRUTE_ATTEMPTS 1000000

static char pKey[KEY_LENGTH + 1];
static int bruteCount = 0;
static time_t bruteStart;

// Recursively check every key until the first possible candidate is found
static bool permute(char *cipher, int depth)
{
    if (depth == KEY_LENGTH)
    {
        
        if (bruteCount == MAX_BRUTE_ATTEMPTS)
        {
            time_t bruteEnd = time(NULL);
            int time = (int) (bruteEnd - bruteStart);
            
            printf("%d keys tried already with %d second(s) passed\n", MAX_BRUTE_ATTEMPTS , time);
        }
        
        bruteCount++;
        
        char *text = decryptText(cipher, pKey);
        
        // Check the top 10, 3+ length most commonly used words in the English language
        // Source: https://en.wikipedia.org/wiki/Most_common_words_in_English
        if (strstr(text, " THE ") != NULL) return true;
        else if (strstr(text, " AND ") != NULL) return true;
        else if (strstr(text, " THAT ") != NULL) return true;
        else if (strstr(text, " HAVE ") != NULL) return true;
        else if (strstr(text, " FOR ") != NULL) return true;
        else if (strstr(text, " NOT ") != NULL) return true;
        else if (strstr(text, " WITH ") != NULL) return true;
        else if (strstr(text, " YOU ") != NULL) return true;
        else if (strstr(text, " THIS ") != NULL) return true;
        else if (strstr(text, " BUT ") != NULL) return true;

        free(text);
    }
    else
    {
        for (int i = depth; i < KEY_LENGTH; i++)
        {
            char temp = pKey[depth];
            
            pKey[depth] = pKey[i];
            pKey[i] = temp;
            
            if (permute(cipher, depth + 1)) return true;
        }
    }
    
    return false;
}

// Brute force approach to try every possible key until one is found
static void bruteForce(char *cipher)
{
    memcpy(pKey, ALPHABET, KEY_LENGTH + 1);
    bruteCount = 0;
    bruteStart = time(NULL);
    
    permute(cipher, 0);
}

char *crackCipherText(char *cipher)
{
    bruteForce(cipher);
    
    printf("Possible key is: %s\n", pKey);
    
    return decryptText(cipher, pKey);
}
