//
//  main.c
//  HandyCipher
//
//  Created by Bobby Jap on 9/8/16.
//  Copyright © 2016 Bobby Jap, Ravee Khandagale. All rights reserved.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "HCKeyGen.h"

const char TEST_KEY[] = "QjufGCtwbUSNLqHAgVDOoansIhyBKJWFdxvPk^peXMTlirYRmcE";
const char SIMPLE_TEXT[] = "CATS AND DOGS";
const char LONGER_TEXT[] = "IT HAUNTS ME, THE PASSAGE OF TIME. I THINK TIME IS A MERCILESS THING. I THINK LIFE IS A PROCESS OF BURNING ONESELF OUT AND TIME IS THE FIRE THAT BURNS YOU. BUT I THINK THE SPIRIT OF MAN IS A GOOD ADVERSARY. -- TENNESSEE WILLIAMS";
const char SIMPLE_CIPHER[] = "rinqNxFvaWLnGnMFNxsdTFaoFLfNlxsnNrLFa";
const char LONG_CIPHER[] = "isWxqLfdWrlMriHudfTiaGnldHSNqxsoHlfLWflrMiTSsFdIvWMSWQfxWoTQSnMTsrQLHLSTqFNnFNLfjSriTMlouMiFNnNrTaGQfuFiqxGfrNfxnsaHIFSWlMoGQLGjqufiGadILjvsndflQuWusTnqMLudMLnxsNiMQLGuSQfLMuvjqlFoHqxiMFGnfqlNjaTMLvsIqFGLMnvasiadGrTinvNuMoTiTjWaFviLGqdFnLQuGsfjaFnaHisfxGWfLIrlSdHjQsaFTqdunLHfolLlQdnanoIxrNQjxuFnMqSIjflqrfLaSsaoGnQondLGulIxjlauILWqsduLolnjqNiqsfliMouxivLlnMTHTdfsQNLvsTqIuiSanMosFnIlvdGniMFdxvoWQISaWrNsvjMnGFiWoMNlusLQndFnfNvnoGiLuLTIoWMuQjsWvHLdHQaTxufSGsQHFxsioWFoflGxrNQTdHasiSdrulaLGndMaiQSnGnldLaSQGurflLuHdGjMLsvjoxdWsvITNxnrGufQWSMojQnGTqMSMWjQjxvNTiroMnMFGinrTaFsjMvfsroHvdfxWfGuMNLFHouFQWSoIjlGSQaflxHSjafruLHqLNifqsQNxrGdFNalTHofulHTQsMvLjFfaGSiFdujQiGadsiqSxGIlQiaGdLWlraIsoaidIaqGndufoQujiGdQFHvNxiIsTsSQHoWSMdqISqHnLvNQrnxqaSifoqFinaGjoQiuNqxdLdlTiQrlMLNSHsqNvxsfiQlTvMLsvMdrxQInjoSQMqfdrWuGfQLTriQMjaNfFTuNonsIqisxfWaTlxvdfFWnflHoFMruilSGivsMHLWNsdQHqNFMqWI";

static void testKeyGen()
{
    char *key = generateKey();
    size_t length = strlen(key);
    
    assert(length == 51 && "The key generator generated a key of incorrect length");
}

static void testEncryption()
{
    assert(0 == 1 && "Test not yet implemented for Handy Cypher encryption with a key");
}

static void testDecryption()
{
    assert(0 == 1 && "Test not yet implemented for Handy Cypher decryption with a key");
}

static void testCracker()
{
    assert(0 == 1 && "Test not yet implemented for Handy Cypher decryption with a cracker");
}

int main(int argc, const char * argv[])
{
    testKeyGen();
    testEncryption();
    testDecryption();
    testCracker();
    
    return 0;
}
