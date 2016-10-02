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

char TEST_KEY[] = "ON2TP3FLDSMKY,5ACVER7WIH41UG8.960^?-ZXQJB";
char SIMPLE_TEXT[] = "CATS AND DOGS";
char LONGER_TEXT[] = "IT HAUNTS ME, THE PASSAGE OF TIME. I THINK TIME IS A MERCILESS THING. I THINK LIFE IS A PROCESS OF BURNING ONESELF OUT AND TIME IS THE FIRE THAT BURNS YOU. BUT I THINK THE SPIRIT OF MAN IS A GOOD ADVERSARY. -- TENNESSEE WILLIAMS";
char SIMPLE_CIPHER[] = "2NTEU2GX1DSOGE4E2MPYKPE?EM-K";
char LONG_CIPHER[] = "Z0XSNDPR?EM-OXE8DOM1?PNZ7YZ8-G0ENUZ7TO2D1ZSCRKZPG8-VP?0S21-TDKNK?72DO148ON0?MD0NMGY1M2DP10PCRNKYN80USO78PMN24NXOUYR814E1XD8DNKT0-SYD8?X-84UG7RX0ZGX1?MY1?NKUMXGRGO0D8U0TM2K?MZXCSZ107OP?D7GPGM?107P0?EKP102OP?28TZK8VDZNMTUXK-RGPVOSP?VNTYDS4OCGY7PS2YOZUPG4PG-0ZXUTYMTECX14-0U2-O?T8XTPMY?RY2S?0KP10E?VNYD1R7VYZG81GPRN02M-E41O40DCX7PM2DNY-TDPCV27OSX1M4SNYTMDXDN4E?SNXOZDP4?8G0TCNO82XY7S0?2SZY01ZDVGXRECNZND7SO1PEYKMN8MR2X0ST1CPO8S20R8NUZ41ZDUN8MZXR7Z1D21D?P?4RCM2-8CKENG-TV4ZK8";

static void testKeyGen()
{
    char *key = generateKey();
    bool validKey = validateKey(key);
    
    assert(validKey && "The key generator generated an invalid key");
}

static void testEncryption()
{
    char *cipher = encryptText(SIMPLE_TEXT, TEST_KEY);
    
    assert(strcmp(SIMPLE_TEXT, cipher) != 0 && "Text did not encrypt and is still the same");
    assert(strlen(SIMPLE_TEXT) < strlen(cipher) && "Text did not encrypt correctly and is still the same length");
}

static void testDecryption()
{
    char *text = decryptText(SIMPLE_CIPHER, TEST_KEY);

    assert(strcmp(SIMPLE_TEXT, text) == 0 && "Text did not decrypt correctly");
}

static void testCracker()
{
    char *text = crackCipherText(SIMPLE_CIPHER);
    
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
