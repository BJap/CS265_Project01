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
#include <time.h>

#define KEY_LENGTH 41
#define SUBKEY_LENGTH 31
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-?^0123456789"

// Generate a random key for HC encryption
char *generateKey();

// Generate a key with a unix time srand seed
char *generateSeededKey(time_t seed);

// Validate that the key matches HandyCipher standards
bool validateKey();

// Generate a subkey from the given key
char *generateSubKey(char *key);

// Generate the substitution array to be able to map each char to a number
void generateSubstitution(char *subKey, int *substitution);

#endif /* HCKeyGen_h */
