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

///cutscene
extern Pixeldata d1;
extern Pixeldata d2;
extern Pixeldata kneel;
extern Pixeldata thought;
bool load1();
bool load2();
bool load3();
extern Pixeldata u;//up dom
extern Pixeldata f;//final doom
extern Pixeldata m1;
extern Pixeldata m2;
extern Pixeldata t1;
extern Pixeldata t2;
extern Pixeldata background;
bool loadback();
bool loadm1();
bool loadm2();
bool loadt1();
bool loadt2();
struct enemyTest{int lane; float x; 
    float w; float h; float speed;int type; //type 1=easy, 2=medium, 3=hard
                  int hp;int maxhp;float projTimer; int move;}; //0 standing 1 moving

enum class PlayerAction {
    RUNNING,
    JUMPING,
    DUCKING
};



struct player{int lane; float x; float w; float h;
float speed; int type; int hp; int maxhp ; float projTimer; int move;   // we added fighting w keda ashan captain america each yoba leeh fight frame
 PlayerAction action; float actionTimer; float jumpOffset; bool fighting = false;int fightFrame = 0;float fightTimer = 0.0f;};//type order is captain america, spiderman, hulk

struct arcReactor{int lane; float x; int value;};

struct projectile{int lane; float x; float y; int side; int dmg;}; //zero hero one loser

bool loadthought();
bool loadu();
bool loadf();