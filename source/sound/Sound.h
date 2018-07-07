#ifndef SOUND_SOUND_H
#define SOUND_SOUND_H

#include <nds.h>

//-----------------------------------------------------------------------------
class Sound {
//-----------------------------------------------------------------------------

  s16 *data;
  u32 size;
  u32 rate;

  int soundId;

  Sound(const u8 *wavData) {
    rate = *(u32 *)(wavData + 24);
    size = *(u32 *)(wavData + 40);
    data = (int16 *)(wavData + 44);
  }

  static const auto format = SoundFormat_16Bit;

public:

//-----------------------------------------------------------------------------
  static Sound playerHurt;
  static Sound playerDeath;
  static Sound monsterHurt;
  static Sound test;
  static Sound pickup;
  static Sound bossdeath;
  static Sound craft;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
  void play() {
//-----------------------------------------------------------------------------
    soundKill(soundId);
    soundEnable();
    soundId = soundPlaySample(data, format, size, rate, 127, 64, false, 0);
  }
};

#endif
