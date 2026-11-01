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

extern Pixeldata Capfight;
extern Pixeldata Cap;
extern Pixeldata Ccrouch;
extern Pixeldata Cjump;
bool loadCap();
bool loadfight();
bool loadCjump();
bool loadCcrouch();

struct enemyTest{int lane; float x; 
    float w; float h; float speed;int type; //type 1=easy, 2=medium, 3=hard
 int hp;float projTimer; int move;}; //0 standing 1 moving

enum class PlayerAction {
    RUNNING,
    JUMPING,
    DUCKING
};



struct player{int lane; float x; float w; float h;
float speed; int type; int hp;  float projTimer; int move;
 PlayerAction action; float actionTimer; float jumpOffset; };//type order is captain america, spiderman, hulk

struct arcReactor{int lane; int x; int value;};

struct projectile{int lane; float x; float y; int side; int dmg;}; //zero hero one loser
