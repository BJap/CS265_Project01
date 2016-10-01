//
//  HCKeyGen.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/18/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include "HCKeyGen.h"

const int KEY_LENGTH = 41;
const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-?^0123456789";

char *generateKey()
{
    char *subKey = malloc(31);
    
    return subKey;
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
