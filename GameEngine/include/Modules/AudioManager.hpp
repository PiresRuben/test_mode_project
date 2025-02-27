#pragma once
#include <iostream>

#include "Module.hpp"
#include "miniaudio.h"
#include <unordered_map>
#include "InputManager.hpp"

struct AudioStruct {

	std::string name;
	float* x = nullptr;
	float* y = nullptr;
	float* z = nullptr;
	ma_sound* sound;

	float* forwardX = nullptr;
	float* forwardY = nullptr;
	float* forwardZ = nullptr;
};

class AudioManager : public Module {
public:
	enum LoadMethode {
		SYNCHRONE,
		ASYNCHRONE
	};
	enum ReaderMethode {
		STREAMING,
		PRELOADING
	};
	AudioManager();

	void Init() override;
	void Update() override;
	void Shutdown() override;

	/*
	*@brief Creates a sound and adds it to the sound manager
	*
	* @param name : name of the Audio
	* @param link : link to the audio file
	*/
	void AddAudio(std::string name, const char* link);
	/*
	*@brief Creates a sound and adds it to the sound manager
	*
	* @param name : name of the Audio
	*
	* @param link : link to the audio file
	*
	* @param loadMethod : define the load methode (SYNCHRONE, ASYNCHRONE)
	*
	* @param readerMethode : defines how the audio file is played (STREAMING, PRELOADING)
	*
	*/
	void AddAudio(std::string name, const char* link, AudioManager::LoadMethode loadMethode, AudioManager::ReaderMethode readerMethode);

	// Invidual Audio

	/*
	*@brief Start playing a sound
	*
	* @param name : name of the Audio
	*
	*/
	void AudioStart(std::string name);
	/*
	*@brief Pause or restart a sound after pausing it
	*
	* @param name : name of the Audio
	*
	*/
	void AudioPause(std::string name);
	/*
	*@brief Restart a sound from the beginning
	*
	* @param name : name of the Audio
	*
	*/
	void AudioRestart(std::string name);
	/*
	*@brief Adjust the volume of a sound by multiplicative value, if the value is greater than 1 the sound will be amplified and 0 silences him
	*
	* @param name : name of the Audio
	*
	* @param newValue : the new multiplier
	*
	*/
	void AudioSetVolume(std::string name, float newValue);
	/*
	*@brief With this parameter is activated, the sound will loop indefinitely
	*
	* @param name : name of the Audio
	*
	* @param newValue : pass to true or false
	*
	*/
	void AudioSetLooping(std::string name, bool newValue);
	/*
	*@brief Setting the pan to 0 will result in an unpanned sound. Setting it to -1 will shift everything to the left, whereas +1 will shift it to the right
	*
	* @param name : name of the Audio
	*
	* @param newPanningValue : define the new Panning Value cap between -1 and 1 inclusive
	*
	*/
	void AudioSetPanning(std::string name, float newPanningValue);
	/*
	*@brief A larger value will result in a higher pitch.The pitch must be greater than 0.
	*
	* @param name : name of the Audio
	*
	* @param newPitchValue : define the new pitch Value
	*
	*/
	void AudioSetPitch(std::string name, float newPitchValue);
	void SetDopplerEffect(std::string name, float newValue); // Non tester, neccesite de la velociter sur le son 
	/*
	*@brief Defines the coordinates to which the sound will be attached
	*
	* @param name : name of the Audio
	*
	* @param x : pointers to x
	*
	* @param y : pointers to y
	*
	* @param z : pointers to z
	*
	*/
	void AudioSetPosition(std::string name, float* x, float* y, float* z);
	/*
	*@brief Defines the direction where the soudtrack will be attached
	*
	* @param name : name of the Audio
	*
	* @param forwardX : pointers to x
	*
	* @param forwardY : pointers to y
	*
	* @param forwardZ : pointers to z
	*
	*/
	void AudioSetDirection(std::string name, float* forwardX, float* forwardY, float* forwardZ);
	/*
	*@brief Move playback position to timeInMs milliseconds
	*
	* @param name : name of the Audio
	*
	* @param timeInMs : value where the reader will be moved
	*
	*/
	void AudioPlayerSeekTo(std::string name, int timeInMs);

	void AudioSetFadeIn(std::string name, float fadeInValue);

	void AudioSetMinDistance(std::string name, float minValue);

	void AudioSetMaxDistance(std::string name, float maxValue);

	void AudioSetVelocity(std::string name, float velocityX, float velocityY, float velocityZ);

	void SetEngineVolume(float value);

	void test3D();


private:
	void UpdatePositionAudio();
	bool AudioBrowser(std::string name, AudioStruct*& ptr);



	std::vector<AudioStruct> audioList;
	//std::unordered_map<std::string, ma_sound_group*> groupMap;
	std::string test = "";  // pour l'input dans le terminal, a suprimer plus tard
	ma_engine engine;
	ma_engine_config engineConfig;


	static AudioManager* instance;
};

