//
//  main.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/8/16.
//  Copyright © 2016 Bobby Jap. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HandyCipher.h"
#include "HCCracker.h"
#include "HCKeyGen.h"

#pragma mark TIME CONSTANTS

#define SECONDS_IN_A_YEAR 31536000

#pragma mark KEYS

#define TEST_KEY "ON2TP3FLDSMKY,5ACVER7WIH41UG8.960^?-ZXQJB"
#define LOW_BRUTE_FORCE_KEY "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-?^0123456798"
#define HIGH_BRUTE_FORCE_KEY "ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-?^9123456780"

#pragma mark PLAIN TEXT

#define SIMPLE_TEXT "CATS AND DOGS"
#define LONGER_TEXT "IT HAUNTS ME, THE PASSAGE OF TIME. I THINK TIME IS A MERCILESS THING. I THINK LIFE IS A PROCESS OF BURNING ONESELF OUT AND TIME IS THE FIRE THAT BURN-S YOU. BUT I THINK THE SPIRIT OF MAN IS A GOOD ADVERSARY.  -- TENNESSEE WILLIAMS"
#define CHALLENGE_KNOWN_TEXT "PASSAGE OF TIME"

#pragma mark CIPHERS

#define SIMPLE_CIPHER "2NTEU2GX1DSOGE4E2MPYKPE?EM-K"
#define LONGER_CIPHER "Z0XSNDPR?EM-OXE8DOM1?PNZ7YZ8-G0ENUZ7TO2D1ZSCRKZPG8-VP?0S21-TDKNK?72DO148ON0?MD0NMGY1M2DP10PCRNKYN80USO78PMN24NXOUYR814E1XD8DNKT0-SYD8?X-84UG7RX0ZGX1?MY1?NKUMXGRGO0D8U0TM2K?MZXCSZ107OP?D7GPGM?107P0?EKP102OP?28TZK8VDZNMTUXK-RGPVOSP?VNTYDS4OCGY7PS2YOZUPG4PG-0ZXUTYMTECX14-0U2-O?T8XTPMY?RY2S?0KP10E?VNYD1R7VYZG81GPRN02M-E41O40DCX7PM2DNY-TDPCV27OSX1M4SNYTMDXDN4E?SNXOZDP4?8G0TCNO82XY7S0?2SZY01ZDVGXRECNZND7SO1PEYKMN8MR2X0ST1CPO8S20R8NUZ41ZDUN8MZXR7Z1D21D?P?4RCM2-8CKENG-TV4ZK8"
#define CHALLENGE_CIPHER "38P4CR1I?XB,AZFHNGWED5H01X619E35E7.I3J?GEAV1UDETGYASC,5DO8EB39E8F84PLU,60?I.5FEJ29K7OGZWUJQVFRXIZ9K8RP,1,VGFP5XPTME86FYBHNP,Z6V04U2-N50DM.HC2?IJCZXE-IJQCGONEF6L150DV2C1F2,Q7SXC52HFIXRW-SUO313A9LQPX2BD-ERM0KRJQGSONZ7E9WHXC-.QF80LNI9JPDVGIMC,O8WT.?HJZ-CLK1CF-PJK?4ACWVQ6KR1HFR0.IB.HTN?0?EM.C?N7Z5JBEA36UPA-KLFSCETD-W-NYAVPKFOPRH7QN6GW,I1J.9T0UZHAZQ.R25JUIP3QE7B4,YHW2G8UMV,QY9X3U4.Q?TVL-B2ED1PAW.LKG5-D0NQCY-ZYEQX86F-?KPI,H3UPNU?WXM08IAY7Z.F5J,H2MCVJADVQ7IO0T6,?1IYM?3ETB5RI?N0C-BJZY3HU-O1?GN.BJA9518TMNV?4SUT-YX85TD?AI-UH0J1O?E7JUCD.TMRCLHBD9Q47FL506R98F74J53X19,.LV72FZILU2T5MXQHSAB?.K7G4-L3UOMI87N?96,MDMNAO8W,ZSW9RBF4GORS?IP8D,BIT5U4ZB?JMR-,.ZJF2NCW9MK.E6W5PYUBOHKBNXPLKTBWHAGN3OFPYG1,UPW9B4IZ5V7X8-S49TKIZK8ZI7G8625R4WJ,CLIDBO8V34XFIVB7WQT3VBIKG,1UEP,WCA3MHULQC36UL2.F7YEQZWH6Y2?.JI8DGXPJ8MQYLXCJ-ZHUCL1WHFT3R2H8WM38,70L5KZWOBPALG.SH0Y?931.XVRH95DF4GPXKIMLSTA3DF0SKGUN,AE04ROHIMT,BVQPZO9-SRDWU90?ELCK41EMW0Z7TUR4BJ.SNEHCLA150DWCGV2WBI7VO,DQY8ZS-.2ME5Z1UG?RV96X53MD49F28WNH6GJB4U7WH-EMFKUM.RL91HJ72CET9BVX3JIX?RTLY6.D103.JX1PXT5DG6-Y12A48TUEBAO2FYRNVLZ,MY90?W1KQL4CFJQNJP5I4Q6JPM5,H7F3.SXJC1O3EB-QWR24NJUPXQGI7K3CYEW17TKMEY2JB6OYPW?CHVJTWABH2BERGSL8FA4XFG7ZKHYWNELJZPDXN7MG0LDE1OFMNPU.R70OTRXMES?G1U8YH2GMWTCNE2R8VWHGCDF5Y,Z2QMPL-VKN9LG5OB54WDG.B0O4ECRW1VZALXHUPOW0,DIWCU2E-MB483JD,OE0-2DL4P9S08F46-O3U9ZUTDQCLVU.0O12RBN98ILV-5D297KGQ6O75Z8ZSQVYH9DSN4IQEALC0I98B?54BWCPW,IODM.1I?VB2FEZ.DR-61205SAV,FG1MT0ZDETP5X4NEM3QS?FO0M.WSP1UG,XBFW91.43B5WCPHMF4QPFJ?KLJ.X2YD-E48PG6ZK0UTWFVX0Z4,FBG,TS5P7XNVHRF7EJTSRBU8HLWV72UGI?6W.03Q9NLCRTF02D187J4P7L3,5IXR?D2A1S5BSTY2G1A?KNZAOGEJIQWJUQMNL.?SV7QHM0GSK0TUD6J1N0G,1RCQNWYZK95OXPTM-BZ8LX5K23ZA,98R1?,SUG0Q1-JEDY6S8WDLHF0MYBW.RVEJMZGY9OKH7-E89QE?03865TUA03.X9MR-O3C4K1B7W-0DZN75J4GP2-AJLM,LFZAPRKDU,A7.AGYK9CN7HITRK8,Q6PS36?90MZ0T6Q4X3WOPZ2,YV9DF1LWCFD7UVWFI6X2Q1IZ,FDMGR4NB1KXPE9L803RTO-3EUDBXTPGHCRFLMUWR2C?H6.U?T0YU2.NEZD9F3UOMXGCN,OD6I5ZKJE0SVRWO4AP3,WFU48P7GKL0TZN1J-UG?10TZLE4URHMJ-G-2LGPI4K1YI3GPZT4UM8WGPDNQGCRU?1Z0EQUTDXT18VA6LIN?DJLMXPT9?0R6I4YJ38OAV3C,6SDOI2MA-4AQF0VTUCSL1F7PUWFT4U1J2M-,1UCWT.?SJ495CNTFQXRNISP-KGB7VB9OXQRPY978FG71,3X0JNHUO-5TM,EK23ZXC8P84YGP7MKVPIS,K-?F5H3RUK6Y2TIJ6Z2.CYDS?15OKNGJY9Z63X?,V1H6LUO6FENB9DH4?1F.-R6?7W?70IG8TC2LWGIJC6ED-MULS,FXZN-E59HD3,MTE?4S7AZU5N96LQ3CI465BZV0KGNJZ3ITEFK?W8UB46Z1.YMFHN.0WHYQW,G51SRU?PKXTPLG-Z8MTADZ5KXHFCSW4R.4USV89W,2ZMPWLNEH3R-U7BCT?3EU2-L07JKO2-MVO0R.WT3IEJED6R,IYGPRVZ8VUT6N0KPS-6F8Z3JHOV5BU-9OGAZ?STQ8YFAPR?4BQWCKURT7F?-KV01T?.CHKVN4LDFH7Y-H12FXWS-TU?.MNAQ6BIE17CQKXB76EDKZSB7I3GKQO5QNH-KZWK14LC5GQH2RC5.HXQMRPIBVPW.G5WM2JSEXPKO7G.9185XM-CQ7E3Q8A4P5ZMNYBMRE9K8ZV71,SGEVOA3RLFX,JF8XZD-0SGTYQD3ANI-DYW6913ZKE.BQJ?ALHETV7FB?LPCOID?G1STQ6DVA?Y03EVOHMU-I,LKI3?Q,GYU6B-O3A4,L8P5JITW61CP,9QN,3?L-IZ6C-7B.TF,-2PY3,TMDKZ?J6HS.J68XRCF6JEQVP?LB5OKVS5Z3,-VCXK4,U6W8JNG369-FXP6YIQWF5U7QKSGZJLIFBWJE75MUP4,BVYH-,PA271BHDUKO7ELVJYNGACHN8VNIJP348YFJXOMPH-LOR826WVH4Q,PLCHNVS?.T-?2RFNMAYE7AB,.ZEPXAVO7,WDJR9458I90BKYX3W7MVRAN682BG01TU.ZAREFB29KGZO83WUVSXMK5AIT9GOKZ?.GKJ.XQ1LJOGFR,JKQO79ZR3OY-TEN07NZHYJGWKS3VBT2EI1GLUS?3,85Z9U?OYQ9KHCSL.BMR-2WV3P,9D?G671SNFJ?X2K3MFBMVNS6XQIRU728M7GF4VQL.,FV85G.AWN,4PCVH5ELTJA8R,3NM4G8FTNU.BR?WNL?0RLIZ9QUJ45.PREWS,G80BQ9C5TOKGQ9VP56W.-UOHG?1EH5-T0YGK,XIJU91MVE67JE3B0VD1VT3MVI-XZB9IN0V8M?SW.IUWBS-?L74UR7TV89WDNB0-.JAZS,FCMBWYZGK0YNR76J1O9G4AJVTQZL0A3I0B1DA?U1GY7.FVZ?R5MNJH.KGYB-N5SPAHCMQ.E1V6S?QUN2MXFJUIWS?7FTC?DCUY3Z4LVUNP7WN53J-HYRBUO1?W8V2HSK?F-50A?CB8-Q5VY.P0O7LEIY,XRGP945Q2AM6EJUN4G,WAQ98MISHE-IC?YFABP1CR21Z04QX3F49U,9X.183,-7JHQOAUQ1NG?HQ-,P7HFL5JPM,34.OPJW0F4?JVNA8SR95,R?UVY.0?LJQGY1I6UDOQIC39U4.TCHVXLN3E9J1.6GRKH3Q-7WQP5.Z4LH.CQU4JHE,75832AFM,.C-ZWFSCK1,IDC2UMLTF,Y6-0ESNZTX5VECLP83MW6J4E1TIA3K5J8YR4BM5-L296D3R8,0TMY8SG0LD-BT40F,R2UQYEW"

#pragma mark TESTS

static void testKeyGen()
{
    char *key = generateKey();
    bool validKey = validateKey(key);
    
    assert(validKey && "The key generator generated an invalid key");
    
    free(key);
}

static void testEncryption(char *text)
{
    char *cipher = encryptText(text, TEST_KEY);
    
    assert(strcmp(text, cipher) != 0 && "Text did not encrypt and is still the same");
    assert(strlen(text) < strlen(cipher) && "Text did not encrypt correctly and is still the same length");
    
    free(cipher);
}

static void testInvalidBigrams()
{
    char *cipher = NULL;
    int s[5] = { 0, 1, 4, 9, 18 };
    
    for (int i = 0; i < 5; i++)
    {
        char c[3];
        c[0] = TEST_KEY[s[0 + i]];
        c[1] = TEST_KEY[s[4 - i]];
        c[2] = '\0';
        
        cipher = encryptText(c, TEST_KEY);
        
        assert(cipher == NULL && "Text should not have been able to be encrypted");
    }
    
    free(cipher);
}

static void testInvalidChars()
{
    char *cipher = NULL;
    
    for (int i = 0; i <= 255; i++)
    {
        if (i == '^' || (!strchr(ALPHABET, i) && i != ' '))
        {
            char c[2];
            c[0] = i;
            c[1] = '\0';
            
            cipher = encryptText(c, TEST_KEY);
            
            assert(cipher == NULL && "Text should not have been able to be encrypted");
        }
        
    }
    
    free(cipher);
}

static void testDecryption(char *cipher, char *expected)
{
    char *text = decryptText(cipher, TEST_KEY);

    assert(strcmp(expected, text) == 0 && "Text did not decrypt correctly");
    
    free(text);
}

static void testEncryptionDecryption(char *plainText)
{
    char *cipher = encryptText(plainText, TEST_KEY);
    char *text = decryptText(cipher, TEST_KEY);
    
    assert(strcmp(plainText, text) == 0 && "Text did not encrypt then decrypt correctly");
    
    free(text);
    free(cipher);
}

static void testBruteCracker(char *expected)
{
    char *cipher = encryptText(expected, LOW_BRUTE_FORCE_KEY);
    char *text = bruteForce(cipher);

    assert(strcmp(expected, text) == 0 && "Text did not crack correctly");
    
    cipher = encryptText(expected, HIGH_BRUTE_FORCE_KEY);
    text = bruteForceWithText(cipher, "DOGS");
    
    assert(strcmp(expected, text) == 0 && "Text did not crack correctly");
    
    free(text);
}

static void testPRNCracker(char *text)
{
    char *key = "7WYJB,MS28^U3P6QDG05C9REK.OX-41HT?ZVFINAL"; // Made at 1476243040
    char *cipher = encryptText(text, key);
    time_t start = 1476243030;
    time_t end = 1476243050;
    char *crack = bruteWithSeed(cipher, start, end);
    
    assert(strcmp(text, crack) == 0 && "Text did not crack correctly");
}

#pragma mark RUNNER

int main(int argc, const char * argv[])
{
    testKeyGen();
    printf(("Key Generation: PASS\n"));
    
    testEncryption(SIMPLE_TEXT);
    testEncryption(LONGER_TEXT);
    printf(("\nEncryption: PASS\n"));
    
    testInvalidBigrams();
    printf(("\nCheck for Invalid Bigrams: PASS\n"));
    
    testInvalidChars();
    printf(("\nCheck for Invalid Characters: PASS\n"));
    
    testDecryption(SIMPLE_CIPHER, SIMPLE_TEXT);
    testDecryption(LONGER_CIPHER, LONGER_TEXT);
    printf(("\nDecryption: PASS\n"));
    
    testEncryptionDecryption(SIMPLE_TEXT);
    testEncryptionDecryption(LONGER_TEXT);
    printf(("\nEncryption Decryption: PASS\n"));
    
    testBruteCracker(SIMPLE_TEXT);
    printf(("\nBrute Force: PASS\n"));
    
    testPRNCracker(SIMPLE_TEXT);
    printf(("\nPRN Weakness: PASS\n\n"));
    
    // This was an attempt at an PRN weakness on the challenge cipher from the date it was posted until
    // the forum post Jan 1 2015 - Mar 4 2015 (I also tried all of 2014 previously)
    // bruteWithSeedAndText(CHALLENGE_CIPHER, CHALLENGE_KNOWN_TEXT, 1420070400, 1425513599);
    
    return 0;
}
