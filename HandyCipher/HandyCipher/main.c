//
//  main.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/8/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
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
#define CHALLENGE_CIPHER "38P4C R1I?X B,AZF HNGWE D5H01 X619E 35E7. I3J?G EAV1U DETGY ASC,5 DO8EB 39E8F 84PLU ,60?I .5FEJ 29K7O GZWUJ QVFRX IZ9K8 RP,1, VGFP5 XPTME 86FYB HNP,Z 6V04U 2-N50 DM.HC 2?IJC ZXE-I JQCGO NEF6L 150DV 2C1F2 ,Q7SX C52HF IXRW- SUO31 3A9LQ PX2BD -ERM0 KRJQG SONZ7 E9WHX C-.QF 80LNI 9JPDV GIMC, O8WT. ?HJZ- CLK1C F-PJK ?4ACW VQ6KR 1HFR0 .IB.H TN?0? EM.C? N7Z5J BEA36 UPA-K LFSCE TD-W- NYAVP KFOPR H7QN6 GW,I1 J.9T0 UZHAZ Q.R25 JUIP3 QE7B4 ,YHW2 G8UMV ,QY9X 3U4.Q ?TVL- B2ED1 PAW.L KG5-D 0NQCY -ZYEQ X86F- ?KPI, H3UPN U?WXM 08IAY 7Z.F5 J,H2M CVJAD VQ7IO 0T6,? 1IYM? 3ETB5 RI?N0 C-BJZ Y3HU- O1?GN .BJA9 518TM NV?4S UT-YX 85TD? AI-UH 0J1O? E7JUC D.TMR CLHBD 9Q47F L506R 98F74 J53X1 9,.LV 72FZI LU2T5 MXQHS AB?.K 7G4-L 3UOMI 87N?9 6,MDM NAO8W ,ZSW9 RBF4G ORS?I P8D,B IT5U4 ZB?JM R-,.Z JF2NC W9MK. E6W5P YUBOH KBNXP LKTBW HAGN3 OFPYG 1,UPW 9B4IZ 5V7X8 -S49T KIZK8 ZI7G8 625R4 WJ,CL IDBO8 V34XF IVB7W QT3VB IKG,1 UEP,W CA3MH ULQC3 6UL2. F7YEQ ZWH6Y 2?.JI 8DGXP J8MQY LXCJ- ZHUCL 1WHFT 3R2H8 WM38, 70L5K ZWOBP ALG.S H0Y?9 31.XV RH95D F4GPX KIMLS TA3DF 0SKGU N,AE0 4ROHI MT,BV QPZO9 -SRDW U90?E LCK41 EMW0Z 7TUR4 BJ.SN EHCLA 150DW CGV2W BI7VO ,DQY8 ZS-.2 ME5Z1 UG?RV 96X53 MD49F 28WNH 6GJB4 U7WH- EMFKU M.RL9 1HJ72 CET9B VX3JI X?RTL Y6.D1 03.JX 1PXT5 DG6-Y 12A48 TUEBA O2FYR NVLZ, MY90? W1KQL 4CFJQ NJP5I 4Q6JP M5,H7 F3.SX JC1O3 EB-QW R24NJ UPXQG I7K3C YEW17 TKMEY 2JB6O YPW?C HVJTW ABH2B ERGSL 8FA4X FG7ZK HYWNE LJZPD XN7MG 0LDE1 OFMNP U.R70 OTRXM ES?G1 U8YH2 GMWTC NE2R8 VWHGC DF5Y, Z2QMP L-VKN 9LG5O B54WD G.B0O 4ECRW 1VZAL XHUPO W0,DI WCU2E -MB48 3JD,O E0-2D L4P9S 08F46 -O3U9 ZUTDQ CLVU. 0O12R BN98I LV-5D 297KG Q6O75 Z8ZSQ VYH9D SN4IQ EALC0 I98B? 54BWC PW,IO DM.1I ?VB2F EZ.DR -6120 5SAV, FG1MT 0ZDET P5X4N EM3QS ?FO0M .WSP1 UG,XB FW91. 43B5W CPHMF 4QPFJ ?KLJ. X2YD- E48PG 6ZK0U TWFVX 0Z4,F BG,TS 5P7XN VHRF7 EJTSR BU8HL WV72U GI?6W .03Q9 NLCRT F02D1 87J4P 7L3,5 IXR?D 2A1S5 BSTY2 G1A?K NZAOG EJIQW JUQMN L.?SV 7QHM0 GSK0T UD6J1 N0G,1 RCQNW YZK95 OXPTM -BZ8L X5K23 ZA,98 R1?,S UG0Q1 -JEDY 6S8WD LHF0M YBW.R VEJMZ GY9OK H7-E8 9QE?0 3865T UA03. X9MR- O3C4K 1B7W- 0DZN7 5J4GP 2-AJL M,LFZ APRKD U,A7. AGYK9 CN7HI TRK8, Q6PS3 6?90M Z0T6Q 4X3WO PZ2,Y V9DF1 LWCFD 7UVWF I6X2Q 1IZ,F DMGR4 NB1KX PE9L8 03RTO -3EUD BXTPG HCRFL MUWR2 C?H6. U?T0Y U2.NE ZD9F3 UOMXG CN,OD 6I5ZK JE0SV RWO4A P3,WF U48P7 GKL0T ZN1J- UG?10 TZLE4 URHMJ -G-2L GPI4K 1YI3G PZT4U M8WGP DNQGC RU?1Z 0EQUT DXT18 VA6LI N?DJL MXPT9 ?0R6I 4YJ38 OAV3C ,6SDO I2MA- 4AQF0 VTUCS L1F7P UWFT4 U1J2M -,1UC WT.?S J495C NTFQX RNISP -KGB7 VB9OX QRPY9 78FG7 1,3X0 JNHUO -5TM, EK23Z XC8P8 4YGP7 MKVPI S,K-? F5H3R UK6Y2 TIJ6Z 2.CYD S?15O KNGJY 9Z63X ?,V1H 6LUO6 FENB9 DH4?1 F.-R6 ?7W?7 0IG8T C2LWG IJC6E D-MUL S,FXZ N-E59 HD3,M TE?4S 7AZU5 N96LQ 3CI46 5BZV0 KGNJZ 3ITEF K?W8U B46Z1 .YMFH N.0WH YQW,G 51SRU ?PKXT PLG-Z 8MTAD Z5KXH FCSW4 R.4US V89W, 2ZMPW LNEH3 R-U7B CT?3E U2-L0 7JKO2 -MVO0 R.WT3 IEJED 6R,IY GPRVZ 8VUT6 N0KPS -6F8Z 3JHOV 5BU-9 OGAZ? STQ8Y FAPR? 4BQWC KURT7 F?-KV 01T?. CHKVN 4LDFH 7Y-H1 2FXWS -TU?. MNAQ6 BIE17 CQKXB 76EDK ZSB7I 3GKQO 5QNH- KZWK1 4LC5G QH2RC 5.HXQ MRPIB VPW.G 5WM2J SEXPK O7G.9 185XM -CQ7E 3Q8A4 P5ZMN YBMRE 9K8ZV 71,SG EVOA3 RLFX, JF8XZ D-0SG TYQD3 ANI-D YW691 3ZKE. BQJ?A LHETV 7FB?L PCOID ?G1ST Q6DVA ?Y03E VOHMU -I,LK I3?Q, GYU6B -O3A4 ,L8P5 JITW6 1CP,9 QN,3? L-IZ6 C-7B. TF,-2 PY3,T MDKZ? J6HS. J68XR CF6JE QVP?L B5OKV S5Z3, -VCXK 4,U6W 8JNG3 69-FX P6YIQ WF5U7 QKSGZ JLIFB WJE75 MUP4, BVYH- ,PA27 1BHDU KO7EL VJYNG ACHN8 VNIJP 348YF JXOMP H-LOR 826WV H4Q,P LCHNV S?.T- ?2RFN MAYE7 AB,.Z EPXAV O7,WD JR945 8I90B KYX3W 7MVRA N682B G01TU .ZARE FB29K GZO83 WUVSX MK5AI T9GOK Z?.GK J.XQ1 LJOGF R,JKQ O79ZR 3OY-T EN07N ZHYJG WKS3V BT2EI 1GLUS ?3,85 Z9U?O YQ9KH CSL.B MR-2W V3P,9 D?G67 1SNFJ ?X2K3 MFBMV NS6XQ IRU72 8M7GF 4VQL. ,FV85 G.AWN ,4PCV H5ELT JA8R, 3NM4G 8FTNU .BR?W NL?0R LIZ9Q UJ45. PREWS ,G80B Q9C5T OKGQ9 VP56W .-UOH G?1EH 5-T0Y GK,XI JU91M VE67J E3B0V D1VT3 MVI-X ZB9IN 0V8M? SW.IU WBS-? L74UR 7TV89 WDNB0 -.JAZ S,FCM BWYZG K0YNR 76J1O 9G4AJ VTQZL 0A3I0 B1DA? U1GY7 .FVZ? R5MNJ H.KGY B-N5S PAHCM Q.E1V 6S?QU N2MXF JUIWS ?7FTC ?DCUY 3Z4LV UNP7W N53J- HYRBU O1?W8 V2HSK ?F-50 A?CB8 -Q5VY .P0O7 LEIY, XRGP9 45Q2A M6EJU N4G,W AQ98M ISHE- IC?YF ABP1C R21Z0 4QX3F 49U,9 X.183 ,-7JH QOAUQ 1NG?H Q-,P7 HFL5J PM,34 .OPJW 0F4?J VNA8S R95,R ?UVY. 0?LJQ GY1I6 UDOQI C39U4 .TCHV XLN3E 9J1.6 GRKH3 Q-7WQ P5.Z4 LH.CQ U4JHE ,7583 2AFM, .C-ZW FSCK1 ,IDC2 UMLTF ,Y6-0 ESNZT X5VEC LP83M W6J4E 1TIA3 K5J8Y R4BM5 -L296 D3R8, 0TMY8 SG0LD -BT40 F,R2U QYEW"

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

static void testInvalidBigram(char *text)
{
    char *cipher = encryptText(text, TEST_KEY);
    
    assert(cipher == NULL && "Text should not have been able to be encrypted");
    
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
    
    testInvalidBigram("CHLOE");     // OE
    testInvalidBigram("BURNS");     // NS
    testInvalidBigram("PEPPER");    // PP
    testInvalidBigram("SNAP");      // SN
    testInvalidBigram("RODEO");     // EO
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
