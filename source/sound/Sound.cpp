#include "Sound.h"

#include "assets/sound/playerhurt_wav.h"
#include "assets/sound/death_wav.h"
#include "assets/sound/monsterhurt_wav.h"
#include "assets/sound/test_wav.h"
#include "assets/sound/pickup_wav.h"
#include "assets/sound/bossdeath_wav.h"
#include "assets/sound/craft_wav.h"

Sound Sound::playerHurt(playerhurt_wav);
Sound Sound::playerDeath(death_wav);
Sound Sound::monsterHurt(monsterhurt_wav);
Sound Sound::test(test_wav);
Sound Sound::pickup(pickup_wav);
Sound Sound::bossdeath(bossdeath_wav);
Sound Sound::craft(craft_wav);
