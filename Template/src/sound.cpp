#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "sound.h"

#include <string>
#include <unordered_map>
#include <memory>

ma_engine soundEngine;
bool audioReady = false;
int voLevel=10;
bool mute=false;

std::unordered_map<std::string, std::unique_ptr<ma_sound>> sounds;


// Initialize audio
bool initAudio()
{
    if (ma_engine_init(NULL, &soundEngine) != MA_SUCCESS)
        return false;

    audioReady = true;
    return true;
}


// Load any sound
bool loadSound(const char* name, const char* filePath, bool loop)
{
    if (!audioReady || name == nullptr || filePath == nullptr)
        return false;

    if (sounds.find(name) != sounds.end())
        return false;

    auto sound = std::make_unique<ma_sound>();

    if (ma_sound_init_from_file(
        &soundEngine, filePath, 0, NULL, NULL, sound.get()
    ) != MA_SUCCESS)
        return false;

    ma_sound_set_looping(sound.get(), loop ? MA_TRUE : MA_FALSE);

    sounds[name] = std::move(sound);
    return true;
}


// Play a sound
void playSound(const char* name)
{
    auto it = sounds.find(name);

    if (it == sounds.end())
        return;

    ma_sound* sound = it->second.get();

    ma_sound_seek_to_pcm_frame(sound, 0);
    ma_sound_start(sound);

}


// Stop a sound
void stopSound(const char* name)
{
    auto it = sounds.find(name);

    if (it != sounds.end())
        ma_sound_stop(it->second.get());
}


// Close audio
void shutdownAudio()
{
    for (auto& sound : sounds)
        ma_sound_uninit(sound.second.get());

    sounds.clear();

    if (audioReady)
    {
        ma_engine_uninit(&soundEngine);
        audioReady = false;
    }
}

static void applyVolume(){
    if(!audioReady){
        return;
    }
    float soundValue= mute? 0.0f : (float)voLevel/10.0f;
    ma_engine_set_volume(&soundEngine, soundValue);
}

void increaseVol(){
    if(voLevel<10){
        voLevel++;
    }
    mute = false;
    applyVolume();

}

void decreaseVol(){
    if(voLevel>0){
        voLevel--;
    }
    mute=false;
    applyVolume();
}

void toggleMute(){
    mute=!mute;
    applyVolume();
}