#pragma once

bool initAudio();

bool loadSound(const char* name, const char* filePath, bool loop = false);

void playSound(const char* name);

void stopSound(const char* name);

void shutdownAudio();