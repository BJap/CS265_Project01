//
//  HCCracker.h
//  HandyCipher
//
//  Created by Bobby Jap on 9/12/16.
//  Copyright © 2016 Bobby Jap. All rights reserved.
//

#include <time.h>

#ifndef HCCracker_h
#define HCCracker_h

// Crack the given cipher text using brute force
char *bruteForce(char *cipher);

// Crack the given cipher text using brute force and known plaintext substring
char *bruteForceWithText(char *cipher, char *known);

// Crack the given cipher assuming a particular time range with which is use for a seed
char *bruteWithSeed(char *cipher, time_t start, time_t end);

// Crack the given cipher assuming a particular time range with which is use for a seed
// and known plaintext substring
char *bruteWithSeedAndText(char *cipher, char *known, time_t start, time_t end);

#endif /* HCCracker_h */
