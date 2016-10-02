//
//  HCKeyGen.h
//  HandyCipher
//
//  Created by Bobby Jap on 9/18/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#ifndef HCKeyGen_h
#define HCKeyGen_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *generateKey();
bool validateKey();

char *generateSubKey(char *key);

void generateSubstitution(char *subKey, char *substitution);

#endif /* HCKeyGen_h */
