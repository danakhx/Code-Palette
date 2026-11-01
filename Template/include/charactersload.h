#pragma once
#include <string>

struct Pixeldata{
    int width; int height; int channels; unsigned char* ppointer;
};

extern Pixeldata SPweb;
extern Pixeldata SPstand;
extern Pixeldata SPcrouch;
extern bool loadSPSTAND();
extern bool loadSPCROUCH();
extern bool loadSPWEB();

struct enemyTest{int lane; float x; 
    float w; float h; float speed;int type; //type 1=easy, 2=medium, 3=hard
    int hp; int maxHp; int damage; float projTimer;};

struct player{int lane; float x; float w; float h;
float speed; int type; int hp; int maxHp; int damage; float projTimer;};//type order is captain america, spiderman, hulk

struct arcReactor{int lane; int x; int value;};

struct projectile{int lane; float x; float y; int side;}; //zero hero one loser
