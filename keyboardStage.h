#ifndef KEYBOARDSTAGE_H_INCLUDED
#define KEYBOARDSTAGE_H_INCLUDED

#include "GameEngine.h"


///////////////////
typedef struct mVar mVar;

struct mVar{
Stage* mScreen;

Keyboard* mkeyboard;

SDL_Event mEvent;

const char* file;
};

//
int startKeyboardStage(const char* titre,const char* file);
//
void disposeKeyboardStage(mVar* mvar);
//
void renderKeyboardStage(mVar* mvar);
//
void updateKeyboardStage(mVar* mvar);
//
void eventKeyboardStage(mVar* mvar);

#endif // INTRODUCTIONSTAGE_H_INCLUDED
