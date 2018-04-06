#include "keyboardStage.h"

//
int startKeyboardStage(const char* titre,const char* file)
{
	SDL_ShowCursor(1);
	
	int now=0;
	int ex=0;
	int boucle=10;
	float delta_s=0.0;
	//
	mVar mvar;

	mvar.file=file;
	//
	mvar.mScreen=NULL;
	//
	mvar.mScreen=Stage_create(700,520,"pseudostage",0);
	Stage_setBkgColor(mvar.mScreen,56,150,136);
	
	mvar.mkeyboard=Keyboard_create(Stage_getScreen(mvar.mScreen),titre);
	
	//
	Stage_start(mvar.mScreen);

	//
	while(Stage_isRunning(mvar.mScreen))
	{
		now=SDL_GetTicks();

		if((now-ex) >= boucle)
		{
			delta_s=(now-ex)/1000.0;

			mvar.mEvent=Stage_processEvent(mvar.mScreen);

			eventKeyboardStage(& mvar);

			updateKeyboardStage(& mvar);

			renderKeyboardStage(& mvar);

			ex=now;
		}
		else
		{
			SDL_Delay(boucle-(now-ex));
		}
	}
	//
	disposeKeyboardStage(& mvar);
	SDL_ShowCursor(0);
	return 1;
}
//******************************************
void disposeKeyboardStage(mVar* mvar)
{
	//button
	Keyboard_dispose(mvar->mkeyboard);
	//
	Stage_dispose(mvar->mScreen);
}
//*****************************************
void renderKeyboardStage(mVar* mvar)
{
	Stage_render(mvar->mScreen);
	//
	Keyboard_render(mvar->mkeyboard);
	//
	Stage_flip(mvar->mScreen);
}
//*******************************************************
void updateKeyboardStage(mVar* mvar)
{
	int i=0;
	
	if(Keyboard_isEnter(mvar->mkeyboard))
	{
		FILE* fiche=NULL;
		fiche=fopen(mvar->file,"w");
			if(fiche==NULL)
				printf("erreur fichier message");
			else
			{
			fputs(mvar->mkeyboard->buffer,fiche);
			fclose(fiche);
			}
		
		//
		Stage_stop(mvar->mScreen);
	}
}
//****************************************
void eventKeyboardStage(mVar* mvar)
{
	Keyboard_event(mvar->mkeyboard,& mvar->mEvent);
	//
	switch(mvar->mEvent.type)
	{
	//
	case SDL_KEYDOWN:
		//
		switch(mvar->mEvent.key.keysym.sym)
		{
		//
		case SDLK_ESCAPE:
			Stage_stop(mvar->mScreen);
			break;
		//
	
		default:
			break;
		}
		break;

	//
	default:
		break;
	}
	//
}
//fin
