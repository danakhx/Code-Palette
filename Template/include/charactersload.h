#pragma once
#include <string>

struct Pixeldata{
    int width; int height; int channels; unsigned char* ppointer;
};

extern Pixeldata web;
extern Pixeldata webimpact;
extern Pixeldata SPstand;
extern Pixeldata SPcrouch;
extern bool loadSPSTAND();
extern bool loadSPCROUCH();
bool loadweb();
bool loadwebimpact();
extern Pixeldata hulk;
bool loadhulk();

extern Pixeldata Capfight;
extern Pixeldata Cap;
extern Pixeldata Ccrouch;
extern Pixeldata Cjump;
bool loadCap();
bool loadfight();
bool loadCjump();
bool loadCcrouch();

//villlllaisnsnn
extern Pixeldata thanos;
extern Pixeldata doom;
extern Pixeldata magneto;

bool loadmagneto();
bool loadthanos();
bool loaddoom();



struct enemyTest{int lane; float x; 
    float w; float h; float speed;int type; //type 1=easy, 2=medium, 3=hard
                  int hp;int maxhp;float projTimer; int move;}; //0 standing 1 moving

enum class PlayerAction {
    RUNNING,
    JUMPING,
    DUCKING
};



struct player{int lane; float x; float w; float h;
float speed; int type; int hp; int maxhp ; float projTimer; int move;
 PlayerAction action; float actionTimer; float jumpOffset; };//type order is captain america, spiderman, hulk

struct arcReactor{int lane; float x; int value;};

struct projectile{int lane; float x; float y; int side; int dmg;}; //zero hero one loser
