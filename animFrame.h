#ifndef ANIMFRAME_H_INCLUDED
#define ANIMFRAME_H_INCLUDED

#include "GameEngine.h"

typedef struct AnimFrame AnimFrame;
struct AnimFrame{
//SDL_Surface* tabFrame[3];
SDL_Surface** tabFrame;
float delta;
float delay;
int sizeTab;
int frame;
int looping;
int running;
};

//
AnimFrame* animFrame_create(char* tabfile[],int tabsize);
//
void animFrame_dispose(AnimFrame* anim);
//
void animFrame_update(AnimFrame* anim,float delta);
//
SDL_Surface* animFrame_getframe(const AnimFrame* anim);
//
void animFrame_play(AnimFrame* anim);
//
int animFrame_isRunning(const AnimFrame* anim);
//
void animFrame_setLooping(AnimFrame* anim,int loop);
//
int animFrame_isLooping(const AnimFrame* anim);
//

#endif // ANIMFRAME_H_INCLUDED
