#pragma once

struct Pixeldata{
    int width; int height; int channels; unsigned char* ppointer;
};

extern Pixeldata SPweb;
extern Pixeldata SPstand;
extern Pixeldata SPcrouch;
extern bool loadSPSTAND();
extern bool loadSPCROUCH();
extern bool loadSPWEB();