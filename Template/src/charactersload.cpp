#include "CharactersLoad.h"

#ifndef CHARACTERS_DIR
#define CHARACTERS_DIR "Template/src/characters/"
#endif

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"


Pixeldata hulk;
//ashrar
Pixeldata magneto;
Pixeldata doom;
Pixeldata thanos;


Pixeldata SPcrouch;
Pixeldata SPstand;
Pixeldata web;
Pixeldata webimpact;

//captain a
Pixeldata Cap;
Pixeldata Capfight;
Pixeldata Cjump;
Pixeldata Ccrouch;



bool loadhulk(){
    hulk.ppointer=stbi_load(CHARACTERS_DIR "hulk/hulk.png",&hulk.width,&hulk.height,&hulk.channels,0);
    if (hulk.ppointer==nullptr){
        return false;
    }
    return true;

}
bool loadfight(){
    Capfight.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/weapon.png",&Capfight.width,&Capfight.height,&Capfight.channels,0);
    if (Capfight.ppointer==nullptr){
        return false;
    }
    return true;
}

bool loadCjump(){
    Cjump.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/jump.png",&Cjump.width,&Cjump.height,&Cjump.channels,0);
    if (Cjump.ppointer==nullptr){
        return false;
    }
    return true;
}

bool loadCcrouch(){
    Ccrouch.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/crouch.png",&Ccrouch.width,&Ccrouch.height,&Ccrouch.channels,0);
    if (Ccrouch.ppointer==nullptr){
        return false;
    }
    return true;
}


bool loadCap(){
    Cap.ppointer=stbi_load(CHARACTERS_DIR "captainAmerica/run.png",&Cap.width,&Cap.height,&Cap.channels,0);
    if (Cap.ppointer==nullptr){
        return false;
    }
    return true;
    
}


bool loadSPCROUCH(){
SPcrouch.ppointer=stbi_load(CHARACTERS_DIR "spiderman/crouch.png",&SPcrouch.width,&SPcrouch.height,&SPcrouch.channels,0);

if (SPcrouch.ppointer == nullptr) {
    return false;
}
return true;

}

bool loadSPSTAND(){
    stbi_set_flip_vertically_on_load(true);
    SPstand.ppointer=stbi_load(CHARACTERS_DIR "spiderman/stand.png",&SPstand.width,&SPstand.height,&SPstand.channels,0);
    if (SPstand.ppointer == nullptr) {
        return false;
    }
    return true;
}


//thanos
bool loadthanos(){
    thanos.ppointer=stbi_load(CHARACTERS_DIR "thanos/thanos.png",&thanos.width,&thanos.height,&thanos.channels,0);
    if (thanos.ppointer == nullptr) {
        return false;
    }
    return true;
}

// magneto
bool loadmagneto(){
    magneto.ppointer=stbi_load(CHARACTERS_DIR "magneto/magneto.png",&magneto.width,&magneto.height,&magneto.channels,0);
    if (magneto.ppointer == nullptr) {
        return false;
    }
    return true;
}

//i am doom
bool loaddoom(){
    doom.ppointer=stbi_load(CHARACTERS_DIR "doom/doom.png",&doom.width,&doom.height,&doom.channels,0);
    if (doom.ppointer == nullptr) {
        return false;
    }
    return true;
}

bool loadweb(){
    web.ppointer=stbi_load(CHARACTERS_DIR "spiderman/web.png",&web.width,&web.height,&web.channels,0);
    if (web.ppointer == nullptr) {
        return false;
    }
    return true;

}
bool loadwebimpact(){
    webimpact.ppointer=stbi_load(CHARACTERS_DIR "spiderman/collision.png",&webimpact.width,&webimpact.height,&webimpact.channels,0);
    if (webimpact.ppointer == nullptr) {
        return false;
    }
    return true;

}