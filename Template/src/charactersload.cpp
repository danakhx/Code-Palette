#include "CharactersLoad.h"

#ifndef CHARACTERS_DIR
#define CHARACTERS_DIR "Template/src/characters/"
#endif

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"




Pixeldata SPcrouch;
Pixeldata SPstand;
Pixeldata SPweb;
Pixeldata Hulk;

//captain a
Pixeldata Cap;
Pixeldata Capfight;
Pixeldata Cjump;
Pixeldata Ccrouch;

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

bool loadSPWEB(){
    SPweb.ppointer=stbi_load(CHARACTERS_DIR "spiderman/web.png",&SPweb.width,&SPweb.height,&SPweb.channels,0);
    if (SPweb.ppointer == nullptr) {
        return false;
    }
    return true;
}

