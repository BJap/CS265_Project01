//
//  main.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/8/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include "HandyCipher.h"
#include "HCCracker.h"
#include "HCKeyGen.h"

const char TEST_KEY[] = "ON2TP3FLDSMKY,5ACVER7WIH41UG8.96Ø^?-ZXQJB";
const char SIMPLE_TEXT[] = "CATS AND DOGS";
const char LONGER_TEXT[] = "IT HAUNTS ME, THE PASSAGE OF TIME. I THINK TIME IS A MERCILESS THING. I THINK LIFE IS A PROCESS OF BURNING ONESELF OUT AND TIME IS THE FIRE THAT BURNS YOU. BUT I THINK THE SPIRIT OF MAN IS A GOOD ADVERSARY. -- TENNESSEE WILLIAMS";
const char SIMPLE_CIPHER[] = "2NTEU2GX1DSOGE4E2MPYKPE?EM-K";
const char LONG_CIPHER[] = "ZØXSNDPR?EM-OXE8DOM1?PNZ7YZ8-GØENUZ7TO2D1ZSCRKZPG8-VP?ØS21-TDKNK?72DO148ONØ?MDØNMGY1M2DP1ØPCRNKYN8ØUSO78PMN24NXOUYR814E1XD8DNKTØ-SYD8?X-84UG7RXØZGX1?MY1?NKUMXGRGOØD8UØTM2K?MZXCSZ1Ø7OP?D7GPGM?1Ø7PØ?EKP1Ø2OP?28TZK8VDZNMTUXK-RGPVOSP?VNTYDS4OCGY7PS2YOZUPG4PG-ØZXUTYMTECX14-ØU2-O?T8XTPMY?RY2S?ØKP1ØE?VNYD1R7VYZG81GPRNØ2M-E41O4ØDCX7PM2DNY-TDPCV27OSX1M4SNYTMDXDN4E?SNXOZDP4?8GØTCNO82XY7SØ?2SZYØ1ZDVGXRECNZND7SO1PEYKMN8MR2XØST1CPO8S2ØR8NUZ41ZDUN8MZXR7Z1D21D?P?4RCM2-8CKENG-TV4ZK8";

char *strCopy(char const *src, size_t len)
{
    char *s = malloc(len *sizeof(char));
    
    memcpy(s, src, len *sizeof(char));
    
    return s;
}

static void testKeyGen()
{
    char *key = generateKey();
    bool validKey = validateKey(key);
    
    assert(validKey && "The key generator generated an invalid key");
}

static void testEncryption()
{
    char *text = strCopy(SIMPLE_TEXT, strlen(SIMPLE_TEXT));
    char *key = strCopy(TEST_KEY, strlen(TEST_KEY));
    
    encryptText(text, key);
    
    assert(strcmp(SIMPLE_TEXT, text) != 0 && "Text did not encrypt and is still the same");
    assert(strlen(SIMPLE_TEXT) < strlen(text) && "Text did not encrypt correctly and is still the same length");
}

static void testDecryption()
{
    char *text = strCopy(SIMPLE_CIPHER, strlen(SIMPLE_CIPHER));
    char *key = strCopy(TEST_KEY, strlen(TEST_KEY));
    
    decryptText(text, key);

    assert(strcmp(SIMPLE_TEXT, text) == 0 && "Text did not decrypt correctly");
}

static void testCracker()
{
    char *text = strCopy(SIMPLE_CIPHER, strlen(SIMPLE_CIPHER));
    
    crackCipherText(text);
    
    assert(strcmp(SIMPLE_TEXT, text) == 0 && "Text did not crack correctly and is still the same");
}

int main(int argc, const char * argv[])
{
    testKeyGen();
    testEncryption();
    testDecryption();
    testCracker();
    
    return 0;
}
