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
#include "HandyCipher.h"
#include "HCCracker.h"
#include "HCKeyGen.h"

static char pKey[KEY_LENGTH + 1];

// Recursively check every key until the first possible candidate is found
static bool permute(char *cipher, int depth)
{
    if (depth == KEY_LENGTH)
    {
        printf("Attempt to crack using key: %s\n", pKey);
        
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
            
            bool found = permute(cipher, depth + 1);
            
            if (found) return found;
        }
    }
    
    return false;
}

// Brute force approach to try every possible key until one is found
static void bruteForce(char *cipher)
{
    memcpy(pKey, ALPHABET, KEY_LENGTH + 1);
    
    permute(cipher, 0);
}

char *crackCipherText(char *cipher)
{
    bruteForce(cipher);
    
    printf("Possible key is: %s\n", pKey);
    
    return decryptText(cipher, pKey);
}
