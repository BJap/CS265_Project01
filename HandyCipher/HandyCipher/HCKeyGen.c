//
//  HCKeyGen.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/18/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HCKeyGen.h"

#define random() rand()

char *generateKey()
{
    char *key = malloc(KEY_LENGTH + 1);
    
    srand((unsigned) time(NULL));
    
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

bool validateKey(char *key)
{
    if (strlen(key) != KEY_LENGTH) return false;
    
    char c;
    
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        c = key[i];
        
        if (memchr(ALPHABET, c, KEY_LENGTH) == NULL) return false;
        if (memchr(key, c, i) != NULL) return false;
    }
    
    return 1;
}

char *generateSubKey(char *key)
{
    size_t keyLen = strlen(key);
    char *subKey = malloc(SUBKEY_LENGTH + 1);
    
    for (int i = 0, subKeyPos = 0; i < keyLen; i++)
    {
        if (!isdigit(key[i])) subKey[subKeyPos++] = key[i];
    }
    
    subKey[SUBKEY_LENGTH] = '\0';
    
    return subKey;
}

void generateSubstitution(char *subKey,  int *substitution)
{
    size_t subKeyLen = strlen(subKey);
    
    for (int i = 0; i < subKeyLen; i++)
    {
        substitution[subKey[i]] = i + 1;
    }
}
