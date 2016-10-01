//
//  HandyCipher.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include "HandyCipher.h"

struct table
{
    char *table[5][8];
};

static struct table generateTable(char *key)
{
    struct table keyTable;
    
    // TODO
    
    return keyTable;
}

static char *subKey(char *key)
{
    char *subKey[31];
    
    for (int i = 0; i < strlen(key); i++)
    {
        // TODO
    }
    
    return *subKey;
}

static char *tuple(struct table keyTable, char letter)
{
    char *tuple;
    
    // TODO
    
    return tuple;
}

void encryptText(char *text, char *key)
{
    // TODO
}

void decryptText(char *text, char *key)
{
    // TODO
}
