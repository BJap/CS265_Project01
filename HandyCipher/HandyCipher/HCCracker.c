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

#define random() rand()
#define MAX_BRUTE_ATTEMPTS 1000000

static char pKey[KEY_LENGTH + 1];
static int bruteCount = 0;
static time_t bruteStart;

// Check the top 10, 3+ length most commonly used words in the English language
// Source: https://en.wikipedia.org/wiki/Most_common_words_in_English
static bool containsCommonWord(char *text)
{
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
    else return false;
}

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
        
        bool match = containsCommonWord(text);

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
            
            if (permute(cipher, depth + 1)) return true;
        }
    }
    
    return false;
}

char *bruteForce(char *cipher)
{
    memcpy(pKey, ALPHABET, KEY_LENGTH + 1);
    bruteCount = 0;
    bruteStart = time(NULL);
    
    permute(cipher, 0);
    
    printf("Possible key is: %s\n", pKey);
    
    return decryptText(cipher, pKey);
}

char *generateSeededKey(time_t seed)
{
    char *key = malloc(KEY_LENGTH + 1);
    
    srand((unsigned) seed);
    
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        char c;
        
        do
        {
            int r = random() % KEY_LENGTH;
            
            c = ALPHABET[r];
            
        } while (memchr(key, c, i) != NULL);
        
        key[i] = c;
    }
    
    key[KEY_LENGTH] = '\0';
    
    return key;
}

char *bruteWithSeed(char *cipher, time_t start, time_t end)
{
    char *key = NULL;
    char *text = NULL;
    
    for (time_t i = start; i <= end; i++)
    {
        key = generateSeededKey(i);
        text = decryptText(cipher, key);
        
        free(key);
        
        if (text != NULL && containsCommonWord(text)) return text;
        
        free(text);
    }
    
    return NULL;
}

char *bruteWithSeedAndText(char *cipher, char *known, time_t start, time_t end)
{
    char *key = NULL;
    char *text = NULL;
    
    for (time_t i = end; i >= start; i--)
    {
        if (i % 1000 == 0) printf("Date: %li\n", i);
        key = generateSeededKey(i);
        text = decryptText(cipher, key);
        
        if (text != NULL && strstr(text, known))
        {
            printf("Text: %s\n Key: %s\n", text, key);
            
            return text;
        }
        
        free(key);
        free(text);
    }
    
    return NULL;
}