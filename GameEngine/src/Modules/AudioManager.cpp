#include "Modules/AudioManager.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager() {

    if (instance != nullptr) { throw std::runtime_error("FFS"); }

    instance = this;
}

void AudioManager::Init() {

    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize the audio engine. " << std::endl;
        abort();  // Erreur critique
    }

    AddAudio("mario64", "Assets/Sounds/Dire_Dire_Docks.mp3", AudioManager::ASYNCHRONE, AudioManager::PRELOADING);

}

void AudioManager::Update() {
    UpdatePositionAudio();

    // Code temporaire
    //std::cout << "Entrez : ";
    //std::cin >> test;

    //if (test == "pause") {
    //    AudioPause("mario64");
    //}
    //else if (test == "start") {
    //    AudioStart("mario64");
    //    //test3D();
    //    AudioSetFadeIn("mario64", 10000);
    //}
    //else if (test == "z") {
    //    AudioStruct* currentAudio = nullptr;
    //    if (AudioBrowser("mario64", currentAudio)) {
    //        ma_sound_set_position(currentAudio->sound, 0, 1, 0);
    //    }
    //}
    //else if (test == "q") {
    //    AudioStruct* currentAudio = nullptr;
    //    if (AudioBrowser("mario64", currentAudio)) {
    //        ma_sound_set_position(currentAudio->sound, -1, 0, 0);
    //    }
    //}
    //else if (test == "s") {
    //    AudioStruct* currentAudio = nullptr;
    //    if (AudioBrowser("mario64", currentAudio)) {
    //        ma_sound_set_position(currentAudio->sound, 0, -1, 0);
    //    }
    //}
    //else if (test == "d") {
    //    AudioStruct* currentAudio = nullptr;
    //    if (AudioBrowser("mario64", currentAudio)) {
    //        ma_sound_set_position(currentAudio->sound, 1, 0, 0);
    //    }
    //}
}


void AudioManager::AddAudio(std::string name, const char* link) {

    AudioStruct* nameChek = nullptr;
    if (AudioBrowser(name, nameChek)) {
        std::cerr << "Audioalready exist" << std::endl;
        return;
    }
    delete nameChek; // plus besoin

    ma_sound* sound = new ma_sound;
    ma_result result;

    result = ma_sound_init_from_file(&engine, link, 0, NULL, NULL, sound);
    if (result != MA_SUCCESS) {
        std::cerr << "Incorect path : " << std::endl;
        return;
    }
    ma_sound_set_volume(sound, 0.5f);

    AudioStruct currentAudio;
    currentAudio.name = name;
    currentAudio.sound = sound;
    audioList.push_back(currentAudio);
}
void AudioManager::AddAudio(std::string name, const char* link, AudioManager::LoadMethode loadMethode, AudioManager::ReaderMethode readerMethode) {

    AudioStruct* nameChek = nullptr;
    if (AudioBrowser(name, nameChek)) {
        std::cerr << "Audio already exist" << std::endl;
        return;
    }
    delete nameChek; // plus besoin



    ma_sound* sound = new ma_sound;
    ma_result result;

    if (loadMethode == AudioManager::LoadMethode::ASYNCHRONE) {
        if (readerMethode == AudioManager::ReaderMethode::PRELOADING) {
            result = ma_sound_init_from_file(&engine, link, MA_SOUND_FLAG_ASYNC | MA_SOUND_FLAG_DECODE, NULL, NULL, sound);
        }
        else {
            result = ma_sound_init_from_file(&engine, link, MA_SOUND_FLAG_ASYNC, NULL, NULL, sound);
        }
    }
    else if (readerMethode == AudioManager::ReaderMethode::PRELOADING) {
        result = ma_sound_init_from_file(&engine, link, MA_SOUND_FLAG_DECODE, NULL, NULL, sound);
    }
    else
        result = ma_sound_init_from_file(&engine, link, 0, NULL, NULL, sound);  //Basic methode

    if (result != MA_SUCCESS) {
        std::cerr << "Incorect path : " << link << std::endl;
        return;
    }
    ma_sound_set_volume(sound, 0.5f);

    AudioStruct currentAudio;
    currentAudio.name = name;
    currentAudio.sound = sound;
    audioList.push_back(currentAudio);
}

bool AudioManager::AudioBrowser(std::string name, AudioStruct*& ptr) {
    for (auto& audio : audioList) {
        if (audio.name == name) {
            ptr = &audio;
            return true;
        }
    }
    return false;
}

void AudioManager::UpdatePositionAudio() { // Va update la position des sons
    for (auto Audio : audioList) {
        if (Audio.x != nullptr) {
            ma_sound_set_position(Audio.sound, *Audio.x, *Audio.y, *Audio.z);
        }
    }
}

void AudioManager::SetEngineVolume(float value) {
    ma_engine_set_volume(&engine, value);
}

void AudioManager::Shutdown() {

    for (auto& audio : audioList) {
        delete audio.sound;
    }
    audioList.clear();
}

#pragma region Basic Methode

void AudioManager::AudioStart(std::string name) {
    ma_result result;
    AudioStruct* currentaudio = nullptr;
    if (AudioBrowser(name, currentaudio)) {

        result = ma_sound_start(currentaudio->sound);
    }
    else {
        std::cerr << "Name not found in AudioStart" << std::endl;
    }
}

void AudioManager::AudioPause(std::string name) {
    ma_result result;
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {

        if (ma_sound_is_playing(currentAudio->sound)) {
            ma_sound_stop(currentAudio->sound);
        }
        else {
            ma_sound_start(currentAudio->sound);
        }
    }
}

void AudioManager::AudioRestart(std::string name) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_seek_to_pcm_frame(currentAudio->sound, 0);
        ma_sound_start(currentAudio->sound);
    }
}

void AudioManager::AudioSetVolume(std::string name, float newValue) {
    if (newValue < 0.0f) {
        std::cerr << "Negative value in AudioSetVolume" << std::endl;
        return;
    }
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_volume(currentAudio->sound, newValue);
    }
}


#pragma endregion
#pragma region Advance Methode

void AudioManager::AudioSetLooping(std::string name, bool newValue) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_looping(currentAudio->sound, newValue);
    }
}

void AudioManager::AudioSetPanning(std::string name, float newPanningValue) {

    if (newPanningValue > 1.0f)
        newPanningValue = 1.0f;
    else if (newPanningValue < -1.0f ) {
        newPanningValue = -1.0;
    }

    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_pan(currentAudio->sound, newPanningValue);
    }
}

void AudioManager::AudioSetPitch(std::string name, float newPitchValue) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_pitch(currentAudio->sound, newPitchValue);
    }

}

void AudioManager::SetDopplerEffect(std::string name, float newValue) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_doppler_factor(currentAudio->sound, newValue);
    }
}

void AudioManager::AudioSetPosition(std::string name, float* x, float* y, float* z){
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        currentAudio->x = x;
        currentAudio->y = y;
        currentAudio->z = z;
    }
}

void AudioManager::AudioSetDirection(std::string name, float* forwardX, float* forwardY, float* forwardZ) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        currentAudio->forwardX = forwardX;
        currentAudio->forwardY = forwardY;
        currentAudio->forwardZ = forwardZ;
    }
}

void AudioManager::AudioPlayerSeekTo(std::string name, int timeInMs) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_uint32 sampleRate;
        ma_sound_get_data_format(currentAudio->sound, NULL, NULL, &sampleRate, NULL, 0);

        ma_sound_seek_to_pcm_frame(currentAudio->sound, (timeInMs * sampleRate) / 1000);
    }
}

void AudioManager::test3D() {
    ma_engine_listener_set_position(&engine, 0, 0, 0, 0);

    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser("mario64", currentAudio)) {
        ma_sound_set_positioning(currentAudio->sound, ma_positioning_absolute);
        ma_sound_set_position(currentAudio->sound, 1, 0, 0);
        //ma_sound_set_direction(currentAudio->sound, 1, 0, 0);
    }
}

void AudioManager::AudioSetFadeIn(std::string name, float fadeInValue) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_fade_in_milliseconds(currentAudio->sound, 0, -1, fadeInValue);
    }
}

void AudioManager::AudioSetMinDistance(std::string name, float minValue) {

    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_min_distance(currentAudio->sound, minValue);
    }
}

void AudioManager::AudioSetMaxDistance(std::string name, float maxValue) {

    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_max_distance(currentAudio->sound, maxValue);
    }
}

void AudioManager::AudioSetVelocity(std::string name, float velocityX, float velocityY, float velocityZ) {
    AudioStruct* currentAudio = nullptr;
    if (AudioBrowser(name, currentAudio)) {
        ma_sound_set_velocity(currentAudio->sound, velocityX, velocityY, velocityZ);
    }

}

#pragma endregion