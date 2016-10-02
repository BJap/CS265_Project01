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
#include "HCKeyGen.h"

const int KEY_LENGTH = 41;
const int SUBKEY_LENGTH = 31;
const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-?^0123456789";

char *generateKey()
{
    char *key = malloc(KEY_LENGTH);
    
    return key;
}

bool validateKey(char *key)
{
    if (strlen(key) != KEY_LENGTH) return false;
    
    int i;
    char c;
    
    for (i = 0; i < KEY_LENGTH; i++)
    {
        c = key[i];
        
        if (memchr(ALPHABET, c, KEY_LENGTH) == NULL) return false;
        if (memchr(key, c, i) != NULL) return false;
    }
    
    return 1;
}

char *generateSubKey(char *key)
{
    size_t length = strlen(key);
    char *subKey = malloc(SUBKEY_LENGTH);
    
    for (int i = 0, point = 0; i < length; i++)
    {
        if (!isdigit(key[i]))
        {
            subKey[point] = key[i];
            
            point++;
        }
    }
    
    return subKey;
}

void generateSubstitution(char *subKey,  int *substitution)
{
    size_t length = strlen(subKey);
    
    for (int i = 0; i < length; i++)
    {
        substitution[subKey[i]] = i + 1;
    }
}
