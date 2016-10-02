//
//  HandyCipher.h
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#ifndef HandyCipher_h
#define HandyCipher_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encryptText(char *text, char *key);
char *decryptText(char *cipher, char *key);

#endif /* HandyCipher_h */
