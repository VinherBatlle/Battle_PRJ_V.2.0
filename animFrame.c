#include "animFrame.h"

//****************************
AnimFrame* animFrame_create( char* tabfile[],int tabsize)
{
	int i=0;

	AnimFrame* anim=NULL;

	anim=(AnimFrame*) malloc(sizeof(AnimFrame));

	if(anim==NULL)
		return NULL;

	else
	{
	   anim->sizeTab=tabsize;
		
		
		anim->tabFrame=(SDL_Surface**) malloc(tabsize* sizeof(SDL_Surface));
		
		SDL_Surface* tmp=NULL;

		for(i=0;i<tabsize;i++)
		{
		tmp=IMG_Load(tabfile[i]);
		anim->tabFrame[i]=SDL_DisplayFormatAlpha(tmp);
		}
		SDL_FreeSurface(tmp);
		
		anim->delta=0;
		anim->delay=0.05;

		anim->frame=0;
		anim->looping=1;
		anim->running=0;
	}

	return anim;
}
//*************************************
void animFrame_dispose(AnimFrame* anim)
{
	int i=0;

	//tab[0] supprimer dans l'objet ship
	for(i=1; i<anim->sizeTab; i++)
	{
		if(anim->tabFrame[i]!=NULL)
		{
			SDL_FreeSurface(anim->tabFrame[i]);
			anim->tabFrame[i]=NULL;
		}
	}
	//
	free(anim->tabFrame);
	//
	free(anim);
}
//***********************************************
void animFrame_update(AnimFrame* anim,float delta)
{
	if(anim->running==0)
		return;


	anim->delta+=delta;

	if(anim->delta >= anim->delay)
	{
		anim->frame++;

		if(anim->frame >=anim->sizeTab)
		{
			anim->frame=0;

			if(anim->looping==0)
			{
			anim->running=0;
			}
		}
		//
		anim->delta=0;

	}

}
//**********************************************
SDL_Surface* animFrame_getframe(const AnimFrame* anim)
{
	return anim->tabFrame[anim->frame];
}
//**********************************
void animFrame_play(AnimFrame* anim)
{
	anim->running=1;
}
//
int animFrame_isRunning(const AnimFrame* anim)
{
	return anim->running;
}
//
void animFrame_setLooping(AnimFrame* anim,int loop)
{
	anim->looping=loop;
}
//
int animFrame_isLooping(const AnimFrame* anim)
{
	return anim->looping;
}
//
