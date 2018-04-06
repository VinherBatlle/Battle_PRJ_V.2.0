#include "GameEngine.h"

//fonctions utiles
void ge_Init()
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK);
	TTF_Init();
	srand(time(NULL));

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);

	SDL_ShowCursor(0);

	
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");

}
//************
void ge_Quit()
{
	SDL_ShowCursor(1);
	TTF_Quit();
	SDL_Quit();
}
//*******************************
int ge_rand(int valMin,int valMax)
{
	int nombre=valMin+(rand()%(valMin-valMax +1));

	return nombre;
}
//*************************************************************************************************
void ge_fillRect(SDL_Surface* screen,int xp,int yp,int width,int height,int red,int green,int blue)
{
	if(screen == NULL)
		return;
	//
	Uint32 color=0;
	color=SDL_MapRGB(screen->format,red,green,blue);
	
	SDL_Rect rect;
	rect.x=xp;
	rect.y=yp;
	rect.w=width;
	rect.h=height;
	
	SDL_FillRect(screen, &rect, color);
}
//**************************************************************************************************
void ge_drawRect(SDL_Surface* screen,int xp,int yp,int width,int height,int red,int green,int blue)
{
	ge_fillRect(screen,xp,yp,width,1,red,green,blue);
	
	ge_fillRect(screen,xp,yp+height-1,width,1,red,green,blue);
	
	ge_fillRect(screen,xp,yp,1,height,red,green,blue);
	
	ge_fillRect(screen,xp+width-1,yp,1,height,red,green,blue);
}
//**********************************************************
//stage
//
Stage* Stage_create(int width,int height, const char* titre,int fullscreen)
{
	Stage* pstage=NULL;

	pstage=(Stage*) malloc(sizeof(Stage));

	if (pstage==NULL)
		return NULL;
	else
	{
		const SDL_VideoInfo* pinfo=SDL_GetVideoInfo();
		int bpp=pinfo->vfmt->BitsPerPixel;

	if(fullscreen >0)
	{
		pstage->screen=SDL_SetVideoMode(width,height,bpp,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	}
	else
	{
		pstage->screen=SDL_SetVideoMode(width,height,bpp,SDL_SWSURFACE);
	}
		SDL_WM_SetCaption(titre,NULL);
		pstage->rect.x=0;
		pstage->rect.y=0;
		pstage->rect.w=width;
		pstage->rect.h=height;

		pstage->bkgImage=NULL;
		pstage->bkgColor=SDL_MapRGB(pstage->screen->format,0,0,0);
		pstage->running=0;
		pstage->paused=0;
	}
	return pstage;
}
//*****************************
void Stage_dispose(Stage* stage)
{
	//
	if(stage->bkgImage != NULL)
	{
		SDL_FreeSurface(stage->bkgImage);
		stage->bkgImage=NULL;
	}

	//
	if(stage->screen != NULL)
	{
		SDL_FreeSurface(stage->screen);
		stage->screen=NULL;
	}
}
//****************************
void Stage_start(Stage* stage)
{
	stage->running=1;
}
//***************************
void Stage_stop(Stage* stage)
{
	stage->running=0;
}
//*************************************
int Stage_isRunning(const Stage* stage)
{
	return stage->running;
}
//****************************
void Stage_pause(Stage* stage)
{
	if(stage->paused==1)
	{
		stage->paused=0;
	}
	else
	{
		stage->paused=1;
	}
}
//*****************************
int Stage_isPaused(Stage* stage)
{
	return stage->paused;
}
//****************************************
SDL_Event Stage_processEvent(Stage* stage)
{
	SDL_PollEvent(& stage->event);
	
		//close
		if(stage->event.type== SDL_QUIT)
			stage->running=0;
		
		//pause
		if(stage->event.type==SDL_KEYDOWN && stage->event.key.keysym.sym==SDLK_p)
		{
			Stage_pause(stage);
		}
return stage->event;
}
//*********************************************************
int Stage_loadImageFromFile(Stage* stage,const char* fiche)
{
	SDL_Surface* tmp=IMG_Load(fiche);
	
	stage->bkgImage=SDL_DisplayFormat(tmp);
	
	SDL_FreeSurface(tmp);

	if (stage->bkgImage==NULL)
		return -1;
	else
	{
		SDL_BlitSurface(stage->bkgImage,NULL,stage->screen,& stage->rect);
	}
	return 0;
}
//*****************************
void Stage_render(Stage* stage)
{
	SDL_FillRect(stage->screen,NULL,stage->bkgColor);

	if(stage->bkgImage != NULL)
	{
		SDL_BlitSurface(stage->bkgImage,NULL,stage->screen,& stage->rect);
	}
}
//***************************
void Stage_flip(Stage* stage)
{
	SDL_Flip(stage->screen);
}
//***************************************************
void Stage_setBkgColor(Stage* stage,int r,int g,int b)
{
	stage->bkgColor=SDL_MapRGB(stage->screen->format,r,g,b);
}
//***************************************
SDL_Surface* Stage_getScreen(Stage* stage)
{
	return stage->screen;
}
//********************************************
Sprite* Sprite_create(SDL_Surface* screen,const char* fiche)
{
	Sprite* ps=NULL;

	ps=(Sprite*) malloc(sizeof(Sprite));

	if(ps==NULL)
		return NULL;
	else
	{
		ps->screen=screen;

		ps->image=NULL;
		SDL_Surface* tmp=IMG_Load(fiche);
		
		ps->image=SDL_DisplayFormatAlpha(tmp);
		SDL_FreeSurface(tmp);
		
		SDL_GetClipRect(ps->image, & (ps->rect));

		ps->rect.x=0;
		ps->rect.y=0;
		ps->dx=0;
		ps->dy=0;
		ps->state=0;
		ps->delta_s=0.0;

		ps->directionDeg=0.0;
		ps->speedModule=0.0;
		ps->sound=NULL;

		//for collide
		ps->xm=0;
		ps->ym=0;
		ps->rectBound.x=0;
		ps->rectBound.y=0;
		ps->rectBound.w=(ps->image->w);
		ps->rectBound.h=ps->image->h;

		//for debug
		ps->surfaceBound=NULL;
		ps->debug=0;

	}
	return ps;
}
//************************************************
void Sprite_setDebugRect(Sprite* sprite,int debug)
{
	sprite->debug=debug;
}
//********************************
void Sprite_dispose(Sprite* sprite)
{
	if(sprite->image != NULL)
	{
		SDL_FreeSurface(sprite->image);
		sprite->image=NULL;
	}
	//
	if(sprite->sound != NULL)
	{
		//Mix_FreeChunk(sprite->sound);
		Sound_dispose(sprite->sound);
		sprite->sound=NULL;
	}
	//
	if(sprite->surfaceBound!=NULL)
	{
		SDL_FreeSurface(sprite->surfaceBound);
		sprite->surfaceBound=NULL;
	}

	free(sprite);
}
//**************************************************
void Sprite_setPosition(Sprite* sprite,int x,int y)
{
	sprite->rect.x=x;
	sprite->rect.y=y;
	//
	sprite->rectBound.x=(sprite->rect.x)+(sprite->xm);
	sprite->rectBound.y=(sprite->rect.y)+(sprite->ym);
}
//************************************************
void Sprite_setSpeeds(Sprite* sprite,int dx,int dy)
{
	sprite->dx=dx;
	sprite->dy=dy;
}
//
void Sprite_changeImage(Sprite* sprite,SDL_Surface* surface)
{
	sprite->image=surface;
}
//
void Sprite_setDirectionDeg(Sprite* sprite,float directionDeg)
{
	sprite->directionDeg=directionDeg;

	float ddx=sprite->speedModule * cos(directionDeg*3.14/180.0);
	float ddy=-sprite->speedModule * sin(directionDeg*3.14/180.0);

	sprite->dx=(int) ddx;
	sprite->dy=(int) ddy;
}
//*****************************************************
void Sprite_setSpeedModule(Sprite* sprite,float module)
{
	sprite->speedModule=module;

	float angle=sprite->directionDeg;

	float ddx=module * cos(angle*3.14/180.0);
	float ddy=-module* sin(angle*3.14/180.0);

	sprite->dx=(int) ddx;
	sprite->dy=(int) ddy;
}
//************************************************
float Sprite_getDirectionDeg(const Sprite* sprite)
{
	return sprite->directionDeg;
}
//***********************************************
float Sprite_getSpeedModule(const Sprite* sprite)
{
	return sprite->speedModule;
}
/////
void Sprite_update(Sprite* sprite)
{
	int xp=sprite->rect.x;
	int yp=sprite->rect.y;

	int dx=sprite->dx;
	int dy=sprite->dy;

	xp = xp + dx;
	yp= yp +dy;

	sprite->rect.x=xp;
	sprite->rect.y=yp;
	//
	sprite->rectBound.x=(sprite->rect.x)+(sprite->xm);
	sprite->rectBound.y=(sprite->rect.y)+(sprite->ym);

}
//********************************
void Sprite_render(Sprite* sprite)
{
	if(sprite->image != NULL)
	{
		SDL_BlitSurface(sprite->image,NULL,sprite->screen, & (sprite->rect));
	}
	//
	if(sprite->debug)
	{
	int w=sprite->rectBound.w;
	int h=sprite->rectBound.h;

	SDL_Rect mrect;
	mrect.x=sprite->xm;
	mrect.y=sprite->ym;

	Uint32 couleur=SDL_MapRGB(sprite->screen->format,255,255,255);

	sprite->surfaceBound=SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,16,0,0,0,0);

	SDL_FillRect(sprite->surfaceBound,NULL,couleur);

		SDL_BlitSurface(sprite->surfaceBound,NULL,sprite->image, &mrect);
	}
}
//********************************************
void Sprite_setState(Sprite* sprite, int state)
{
	sprite->state=state;
}
//***************************************
int Sprite_getState(const Sprite* sprite)
{
	return sprite->state;
}
//*******************************************
SDL_Rect Sprite_getRect(const Sprite* sprite)
{
	return sprite->rect;
}
//***********************************
int Sprite_getX(const Sprite* sprite)
{
	return sprite->rect.x;
}
//***********************************
int Sprite_getY(const Sprite* sprite)
{
	return sprite->rect.y;
}
//****************************************
int Sprite_getSpeedX(const Sprite* sprite)
{
	return sprite->dx;
}
//****************************************
int Sprite_getSpeedY(const Sprite* sprite)
{
	return sprite->dy;
}
//*************************************
int Sprite_getTop(const Sprite* sprite)
{
	return sprite->rect.y;
}
//****************************************
int Sprite_getBottom(const Sprite* sprite)
{
	int yp= sprite->rect.y;

	yp+=sprite->rect.h;
	return yp;
}
//*************************************
int Sprite_getLeft(const Sprite* sprite)
{
	return sprite->rect.x;
}
//***************************************
int Sprite_getRight(const Sprite* sprite)
{
	int xp= sprite->rect.x;

	xp+=sprite->rect.w;
	return xp;
}
//*****************************************
int Sprite_getCenterX(const Sprite* sprite)
{
	int xp=sprite->rect.x;
	int w=sprite->rect.w;

	return (xp+w/2);
}
//*****************************************
int Sprite_getCenterY(const Sprite* sprite)
{
	int yp=sprite->rect.y;
	int h=sprite->rect.h;

	return (yp+h/2);
}
//****************************************
void Sprite_setTop(Sprite* sprite, int top)
{
	sprite->rect.y=top;
	//
	sprite->rectBound.y=(sprite->rect.y)+(sprite->ym);
}
//***********************************************
void Sprite_setBottom(Sprite* sprite, int bottom)
{
	int hp=sprite->rect.h;
	sprite->rect.y=bottom-hp;
	//
	sprite->rectBound.y=(sprite->rect.y)+(sprite->ym);
}
//******************************************
void Sprite_setLeft(Sprite* sprite, int left)
{
	sprite->rect.x=left;
	//
	sprite->rectBound.x=(sprite->rect.x)+(sprite->xm);
}
//*********************************************
void Sprite_setRight(Sprite* sprite, int right)
{
	int wp=sprite->rect.w;
	sprite->rect.x=right - wp;
	//
	sprite->rectBound.x=(sprite->rect.x)+(sprite->xm);
}
//**************************************************
void Sprite_setCenter(Sprite* sprite, int xc,int yc)
{
	Sint16 xp= xc - sprite->rect.w/2;
	Sint16 yp= yc- sprite->rect.h/2;

	sprite->rect.x=xp;
	sprite->rect.y=yp;
	//
	sprite->rectBound.x=(sprite->rect.x)+(sprite->xm);
	sprite->rectBound.y=(sprite->rect.y)+(sprite->ym);
}
//***************************************************************
int Sprite_collidRect(const Sprite* source, const Sprite* target)
{
	int xs=source->rectBound.x;
	int ys=source->rectBound.y;
	int xws=xs+source->rectBound.w;
	int yhs=ys+source->rectBound.h;

	int xt=target->rectBound.x;
	int yt=target->rectBound.y;
	int xwt=xt+target->rectBound.w;
	int yht=yt+target->rectBound.h;

	int collid=0;

	//haut gauche
	if(xs >= xt && xs <= xwt && ys>= yt && ys<= yht)
		return 1;

	//haut droite
	if(xws >= xt && xws <= xwt && ys>= yt && ys<= yht)
		return 1;

	//bas droite
	if(xws >= xt && xws <= xwt && yhs>= yt && yhs<= yht)
		return 1;

	//bad gauche
	if(xs >= xt && xs <= xwt && yhs>= yt && yhs<= yht)
		return 1;

	return collid;
}
//*****************************************
int Sprite_collidRect2(const Sprite* source, const SDL_Rect* target)
{
	int xs=source->rectBound.x;
	int ys=source->rectBound.y;
	int xws=xs+source->rectBound.w;
	int yhs=ys+source->rectBound.h;

	int xt=target->x;
	int yt=target->y;
	int xwt=xt+target->w;
	int yht=yt+target->h;

	int collid=0;

	//haut gauche
	if(xs >= xt && xs <= xwt && ys>= yt && ys<= yht)
		return 1;

	//haut droite
	if(xws >= xt && xws <= xwt && ys>= yt && ys<= yht)
		return 1;

	//bas droite
	if(xws >= xt && xws <= xwt && yhs>= yt && yhs<= yht)
		return 1;

	//bad gauche
	if(xs >= xt && xs <= xwt && yhs>= yt && yhs<= yht)
		return 1;

	return collid;
}
//*****************************************
void Sprite_playSound(const Sprite* sprite)
{
	if(sprite->sound !=NULL)
	{
		//Mix_PlayChannel(-1,sprite->sound,0);
		Sound_play(sprite->sound);
	}
}
//***************************************************
void Sprite_setSound(Sprite* sprite,const char* file)
{
	sprite->sound=Sound_create(file);
}
//************************************************************
void Sprite_setCollidRectInflate(Sprite* sprite,int xm,int ym)
{
	sprite->xm=xm;
	sprite->ym=ym;

	sprite->rectBound.w=(sprite->image->w)-(2*xm);
	sprite->rectBound.h=(sprite->image->h)-(2*ym);
}
//-------------------------------------------------------------------------------
ImageScrollingV* ImageScrollingV_create(SDL_Surface* screen,const char* fiche,int dy)
{
	ImageScrollingV* scroll=NULL;

	scroll=(ImageScrollingV*) malloc(sizeof(ImageScrollingV));

	if(scroll==NULL)
		return NULL;

	//
	else
	{
		scroll->screen=screen;
		SDL_Surface* tmp=IMG_Load(fiche);
		
		scroll->image=SDL_DisplayFormatAlpha(tmp);
		
		SDL_FreeSurface(tmp);
		
		SDL_GetClipRect(scroll->image,& scroll->rect);

		scroll->rect.x=0;
		scroll->rect.y=0;

		scroll->ystart=(scroll->image->h)-(screen->h);

		scroll->rectscroll.x=0;
		scroll->rectscroll.y=scroll->ystart;
		scroll->rectscroll.w=screen->w;
		scroll->rectscroll.h=screen->h;

		scroll->dy=dy;
	}
	return scroll;
}
//**************************************************
void ImageScrollingV_dispose(ImageScrollingV* scroll)
{
	if(scroll->image!=NULL)
	{
		SDL_FreeSurface(scroll->image);
	}
	free(scroll);
}
//**************************************************
void ImageScrollingV_update(ImageScrollingV* scroll)
{
	int yp=scroll->rectscroll.y;
	yp+=scroll->dy;

	if(yp <=0)
	{
		yp=scroll->ystart;
	}

	scroll->rectscroll.y=yp;
}
//*************************************************
void ImageScrollingV_render(ImageScrollingV* scroll)
{
	SDL_BlitSurface(scroll->image,& scroll->rectscroll,scroll->screen,& scroll->rect);
}
//
//**************************************************
//Image scolling horizontal
//-------------------------------------------------------------------------------
ImageScrollingH* ImageScrollingH_create(SDL_Surface* screen,const char* fiche,int dx,int yp)
{
	ImageScrollingH* scroll=NULL;

	scroll=(ImageScrollingH*) malloc(sizeof(ImageScrollingH));

	if(scroll==NULL)
		return NULL;

	//
	else
	{
		scroll->screen=screen;
		SDL_Surface* tmp=IMG_Load(fiche);
		scroll->image=SDL_DisplayFormatAlpha(tmp);
		
		SDL_FreeSurface(tmp);

		//SDL_GetClipRect(scroll->image,& scroll->rect);

		scroll->rect.x=0;
		scroll->rect.y=yp;
		scroll->rect.w=1600;
		scroll->rect.h=70;

		scroll->xstart=0;

		scroll->rectscroll.x=0;
		scroll->rectscroll.y=0;
		scroll->rectscroll.w=screen->w;
		//printf("width= %d \n",scroll->rect.w);

		scroll->rectscroll.h=screen->h;

		scroll->dx=dx;
	}
	return scroll;
}
//**************************************************
void ImageScrollingH_dispose(ImageScrollingH* scroll)
{
	if(scroll->image!=NULL)
	{
		SDL_FreeSurface(scroll->image);
	}
	free(scroll);
}
//*************************************************
void ImageScrollingH_update(ImageScrollingH* scroll)
{
	int xp=scroll->rectscroll.x;

	xp+=scroll->dx;


	if(xp >= scroll->screen->w)
	{
		xp=scroll->xstart;
	}


	scroll->rectscroll.x=xp;
}
//**************************************************
void ImageScrollingH_render(ImageScrollingH* scroll)
{
	SDL_BlitSurface(scroll->image,& scroll->rectscroll,scroll->screen,& scroll->rect);
}
//
//------
//Label
//
Label* Label_create(SDL_Surface* screen,const char* fontfile,int fontsize)
{
	Label* plab=NULL;

	plab=(Label*) malloc(sizeof(Label));

	if (plab == NULL)
	{
		return NULL;
	}
	else
	{
		plab->screen=screen;
		plab->font=TTF_OpenFont(fontfile,fontsize);

		plab->color.r=255;
		plab->color.g=255;
		plab->color.b=255;

		plab->txtSurface=NULL;

		plab->txtSurface=TTF_RenderText_Blended(plab->font,"Label",plab->color);

		SDL_GetClipRect(plab->txtSurface, & plab->rect);

		plab->rect.x=0;
		plab->rect.y=0;
	}

	return plab;
}
//******************************
void Label_dispose(Label* label)
{
	if(label->txtSurface != NULL)
	{
		SDL_FreeSurface(label->txtSurface);
		label->txtSurface=NULL;
	}
	//
	if(label->font != NULL)
	{
		TTF_CloseFont(label->font);
	}
	//
	free(label);
	label=NULL;
}
//*****************************
void Label_render(Label* label)
{
	if(label->txtSurface != NULL)
	{
		SDL_BlitSurface(label->txtSurface,NULL,label->screen, & (label->rect));
	}
}
//***********************************************************
void Label_setText(Label* label,const char* txt,int xp,int yp)
{
	label->txtSurface=TTF_RenderText_Blended(label->font,txt,label->color);

	SDL_GetClipRect(label->txtSurface, & label->rect);

	label->rect.x=xp;
	label->rect.y=yp;
}
//***********************************************************
void Label_setColor(Label* label,int red, int green,int blue)
{
	label->color.r=red;
	label->color.g=green;
	label->color.b=blue;
}
//-----------------------------------------------
//MoveLabel
//
MoveLabel* MoveLabel_create(SDL_Surface* screen,const char* fontfile,int fontsize)
{
	MoveLabel* ml=NULL;

	ml=(MoveLabel*)malloc(sizeof(MoveLabel));

	if(ml==NULL)
		return NULL;
	else
	{
	ml->label=Label_create(screen,fontfile,fontsize);
	ml->dx=0;
	ml->dy=0;
	ml->xfinal=200;
	ml->yfinal=200;
	}
	return ml;
}
//
void MoveLabel_dispose(MoveLabel* movelabel)
{
	if(movelabel->label !=NULL)
	{
	Label_dispose(movelabel->label);
	movelabel->label=NULL;
	}
	//
	free(movelabel);
}
//
void MoveLabel_render(MoveLabel* movelabel)
{
	Label_render(movelabel->label);
}
//
void MoveLabel_update(MoveLabel* movelabel)
{
	int xp=movelabel->label->rect.x;
	int yp=movelabel->label->rect.y;

	int xf=movelabel->xfinal;
	int yf=movelabel->yfinal;

	xp+=movelabel->dx;
	yp+=movelabel->dy;

	if(xp<=xf)
	{
	xp=xf;
	}
	//
	if(yp <= yf)
	{
	yp=yf;
	}

	movelabel->label->rect.x=xp;
	movelabel->label->rect.y=yp;
}
//***********************************************************************
void MoveLabel_setText(MoveLabel* movelabel,const char* txt,int xp,int yp)
{
	Label_setText(movelabel->label,txt,xp,yp);
}
//***********************************************************************
void MoveLabel_setColor(MoveLabel* movelabel,int red, int green,int blue)
{
	Label_setColor(movelabel->label,red,green,blue);
}
//*********************************************************
void MoveLabel_setSpeeds(MoveLabel* movelabel,int dx,int dy)
{
	movelabel->dx=dx;
	movelabel->dy=dy;
}
//*****************************************************************
void MoveLabel_setFinalPosition(MoveLabel* movelabel,int xf,int yf)
{
	movelabel->xfinal=xf;
	movelabel->yfinal=yf;
}
//
//----------
//Particules
//
Particule* Particule_create(SDL_Surface* screen,int xp,int yp,float speed,float direction,float live)
{
	int w=2;
	int h=2;

	Particule* part=NULL;

	part=(Particule*)malloc(sizeof(Particule));

	if(part==NULL)
		return NULL;

	else
	{
		part->screen=screen;
		part->rect.x=xp;
		part->rect.y=yp;
		part->couleur=SDL_MapRGB(screen->format,255,255,250);

		part->rectangleSurface=SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,16,0,0,0,0);

		SDL_FillRect(part->rectangleSurface,NULL,part->couleur);
		//
		part->lives=live;
		part->directionDeg=direction;
		part->speedModule=speed;
		part->state=1;
		part->delta=0;
	}


	return part;
}
//******************************************
void Particule_dispose(Particule* particule)
{
	if(particule->rectangleSurface !=NULL)
	{
		SDL_FreeSurface(particule->rectangleSurface);
	}

	//
	free(particule);
	particule=NULL;
}
//**********************************************************************
void Particule_setColor(Particule* particule,int red,int green,int blue)
{
	particule->couleur=SDL_MapRGB(particule->screen->format,red,green,blue);
	SDL_FillRect(particule->rectangleSurface,NULL,particule->couleur);
}
//
void Particule_update(Particule* particule, float delta_s)
{
	if(particule->state >0)
	{
		particule->delta+=delta_s;
		if(particule->delta >= particule->lives)
		{
			particule->state=0;
			particule->delta=0;
			particule->rect.x=1000;
			particule->rect.y=1000;
		}
		else
		{
			static float module=0;
			module=particule->speedModule;

			static float angle=0;
			angle=particule->directionDeg;

			static float ddx=0;
			ddx=module * cos(angle*3.14/180.0);

			static float ddy=0;
			ddy=-module* sin(angle*3.14/180.0);

			particule->rect.x += (int)ddx;
			particule->rect.y += (int) ddy;
		}
	}
}
//*****************************************
void Particule_render(Particule* particule)
{
	SDL_BlitSurface(particule->rectangleSurface,NULL,particule->screen,& particule->rect);

}
//**************************************************************
void Particule_newParameters(Particule* particule, int xp,int yp)
{
	particule->state=1;
	particule->rect.x=xp;
	particule->rect.y=yp;
	particule->delta=0.0;
}
//--------
//Emitter
Emitter* Emitter_create(SDL_Surface* screen,int nbParticule,int xp,int yp,int angleMin,int angleMax)
{
	int i=0;
	float direction=0;
	float live=0;
	float speed=0;
	//int variation=0;


	Emitter* pemit=NULL;

	pemit=(Emitter*) malloc(sizeof(Emitter));

	if(pemit==NULL)
		return NULL;

	else
	{
		pemit->angleMin=angleMin;
		pemit->angleMax=angleMax;

		pemit->position.x=xp;
		pemit->position.y=yp;
		pemit->nbParticule=nbParticule;

		(pemit->tabParticule)=(Particule**)malloc(sizeof(Particule) * pemit->nbParticule);


		for(i=0; i<pemit->nbParticule; i++)
		
		{
			direction=ge_rand(angleMin,angleMax);

			live=ge_rand(1,10);
			live=live/10;

			speed=ge_rand(1,10);

			pemit->tabParticule[i]=Particule_create(screen,xp,yp,speed,direction,live);
		}

	}
	return pemit;
}
//************************************
void Emitter_dispose(Emitter* emitter)
{
	int i=0;

	for(i=0; i<emitter->nbParticule; i++)
	{
		Particule_dispose(emitter->tabParticule[i]);
		emitter->tabParticule[i]=NULL;
	}
	//
	free(emitter);
	emitter=NULL;
}
//*****************************************************
void Emitter_setPosition(Emitter* emitter,int xp,int yp)
{
	emitter->position.x=xp;
	emitter->position.y=yp;
}
//************************************************
void Emitter_update(Emitter* emitter, float delta)
{
	int i=0;
	Particule* particule=NULL;

	for(i=0; i<emitter->nbParticule; i++)
	{
		particule=emitter->tabParticule[i];

		if(particule->state >0)
		{
			Particule_update(particule,delta);
		}
		else
		{
			Particule_newParameters(particule,emitter->position.x,emitter->position.y);
		}
	}
}
//***********************************
void Emitter_render(Emitter* emitter)
{
	int i=0;

	for(i=0; i<emitter->nbParticule; i++)
	{
		Particule_render(emitter->tabParticule[i]);
	}
}
//**************************************************************************
void Emitter_setParticulesColor(Emitter* emitter,int red,int green,int blue)
{
	int i=0;
	for(i=0; i<emitter->nbParticule; i++)
	{
		Particule_setColor(emitter->tabParticule[i],red,green,blue);
	}

}
//
//----------
//Animation
//
Animation* Animation_create(SDL_Surface* screen,const char* filename,int nbframeX,int nbframeY)
{
//
	Animation* panim=NULL;

	panim=(Animation*)malloc(sizeof(Animation));

	if(panim==NULL)
		return NULL;
	else
	{
		panim->nbframeX=nbframeX;
		panim->nbframeY=nbframeY;

		panim->screen=screen;
		SDL_Surface* tmp=IMG_Load(filename);
		
		panim->image=SDL_DisplayFormatAlpha(tmp);
		
		SDL_FreeSurface(tmp);

		panim->position.x=0;
		panim->position.y=0;

		panim->srcRect.x=0;
		panim->srcRect.y=0;

		SDL_GetClipRect(panim->image, & panim->srcRect);
		panim->frameW=panim->srcRect.w/nbframeX;
		panim->frameH=panim->srcRect.h/nbframeY;

		panim->srcRect.w=panim->frameW;
		panim->srcRect.h=panim->frameH;

		panim->frameX=0;
		panim->frameY=0;

		panim->run=0;
		panim->looping=0;

		panim->sound=NULL;
	}
	return panim;
}
//************************************************************
void Animation_loadSound(Animation* anim,const char* filename)
{
	anim->sound=Sound_create(filename);
}
//*************************************
void Animation_dispose(Animation* anim)
{
	if(anim->image != NULL)
	{
		SDL_FreeSurface(anim->image);
		anim->image=NULL;
	}
	//
	if(anim->sound!=NULL)
	{
		Sound_dispose(anim->sound);
		anim->sound=NULL;
	}

	free(anim);
	anim=NULL;
}
//***********************************
void Animation_update(Animation* anim)
{
	if(anim->run==0)
		return;
	//
	anim->frameX+=1;

	if(anim->frameX == anim->nbframeX)
	{
		anim->frameX=0;

		anim->frameY+=1;

		if(anim->frameY == anim->nbframeY)
		{
			anim->frameY=0;

			if(anim->looping)
			{
				anim->run=1;
			}
			else
			{
				anim->run=0;
			}

		}
	}
}
//********************************************************
void Animation_setPosition(Animation* anim, int xp,int yp)
{
	anim->position.x=xp;
	anim->position.y=yp;
}
//************************************
void Animation_render(Animation* anim)
{
	if(anim->run==0)
		return;

	int w=anim->frameW;
	int h=anim->frameH;

	int x=(anim->frameX)*w;
	int y=(anim->frameY)*h;
	//
	anim->srcRect.x=x;
	anim->srcRect.y=y;

	SDL_BlitSurface(anim->image,&anim->srcRect,anim->screen, &anim->position);
}
//*********************************
void Animation_play(Animation* anim)
{
	anim->run=1;
}
//********************************************
int Animation_isRunning(const Animation* anim)
{
	return anim->run;
}
//
void Animation_setLooping(Animation* anim, int state)
{
	anim->looping=state;
}
//
void Animation_playSound(Animation* anim)
{
	if(anim->sound !=NULL)
	{
		Sound_play(anim->sound);
	}
}
//-----------------------------
// Music
//
Music* Music_create(const char * filename)
{
	Music* pmusic=NULL;

	pmusic=(Music*)malloc(sizeof(Music));

	if(pmusic==NULL)
		return NULL;

	else
	{
		pmusic->musique=Mix_LoadMUS(filename);
		pmusic->fadeIn=500;
		pmusic->fadeOut=500;
		pmusic->loopCmp=-1;     //infini loop default
		pmusic->volume=50;
	}

	return pmusic;
}
//******************************
void Music_dispose(Music* music)
{
	if(music->musique != NULL)
	{
		Mix_FadeOutMusic(music->fadeOut);
		Mix_FreeMusic(music->musique);
		music->musique=NULL;
	}

	free(music);
	music=NULL;
}
//***************************************
void Music_setVolume(Music* music,int amt)
{
	if(music->musique != NULL)
	{
		music->volume=amt;
		Mix_VolumeMusic(amt);
	}
}
//
//*****************************
void Music_pause(Music* music)
{
	if(music->musique != NULL)
	{
		Mix_PauseMusic();
		music->paused=1;
	}
}
//*****************************
void Music_resume(Music* music)
{
	if(music->musique != NULL)
	{
		Mix_ResumeMusic();
		music->paused=0;
	}
}
//*******************************
int Music_isPaused(Music* music)
{
	return music->paused;
}

//***************************
void Music_play(Music* music)
{
	if(music->musique != NULL)
	{
		Mix_FadeInMusic(music->musique,music->loopCmp,music->fadeIn);
	}
}
//-----------------------------------
//Sound
//
Sound* Sound_create(const char * filename)
{
	Sound* pson=NULL;

	pson=(Sound*)malloc(sizeof(Sound));

	if(pson==NULL)
		return NULL;

	else
	{
		pson->son=Mix_LoadWAV(filename);
		pson->canal=-1;
		pson->loopCmp=0;
		pson->volume=50;

	}
	return pson;
}
//*****************************
void Sound_dispose(Sound* sound)
{
	if(sound->son !=NULL)
	{
		Mix_FreeChunk(sound->son);
		sound->son=NULL;
	}

	free(sound);
	sound=NULL;
}
//**************************
void Sound_play(Sound* sound)
{
	if(sound->son !=NULL)
	{
		Mix_PlayChannel(sound->canal,sound->son,sound->loopCmp);
	}
}
//****************************************
void Sound_setVolume(Sound* sound,int amt)
{
	if(sound->son !=NULL)
	{
		sound->volume=amt;
		Mix_VolumeChunk(sound->son,sound->volume);
	}
}
//
//----------------------------------
//button
Button* Button_create(SDL_Surface* screen,int id, const char* fontfile, int fontsize,const char* text,int xp,int yp)
{
	Button* pbtn=NULL;
	
	pbtn=(Button*) malloc(sizeof(Button));
	
	if(pbtn==NULL)
	{
		return NULL;
	}
	//
	else
	{
		pbtn->screen=screen;
		pbtn->font=TTF_OpenFont(fontfile,fontsize);
		
		//
		int k=0;
		for(k=0;k<10;k++)
		{
			pbtn->text[k]=text[k];
		}
		pbtn->state=BUTTON_STATE_UP;
		
		pbtn->colorTxt.r=255;
		pbtn->colorTxt.g=255;
		pbtn->colorTxt.b=255;
		
		pbtn->colorBkg.r=56;
		pbtn->colorBkg.g=150;
		pbtn->colorBkg.b=136;
		
		pbtn->surfacetxt=NULL;
		
		pbtn->surfacetxt=TTF_RenderText_Shaded(pbtn->font,pbtn->text,pbtn->colorTxt,pbtn->colorBkg);
		
		SDL_GetClipRect(pbtn->surfacetxt, & pbtn->rect);
		pbtn->rect.x=xp;
		pbtn->rect.y=yp;
	
		pbtn->id=id;
	}
	return pbtn;
}
//*********************************
void Button_dispose(Button* button)
{
	if(button->surfacetxt != NULL)
	{
		SDL_FreeSurface(button->surfacetxt);
		button->surfacetxt=NULL;
	}
	//
	if(button->font != NULL)
	{
		TTF_CloseFont(button->font);
	}
	
	free(button);
}
//********************************
void Button_render(Button* button)
{
	if(button->surfacetxt !=NULL) 
	{
		SDL_BlitSurface(button->surfacetxt,NULL,button->screen, & (button->rect));
	}
}
//******************************************************************
void Button_setColorText(Button* button,int red, int green, int blue)
{
	button->colorTxt.r=red;
	button->colorTxt.g=green;
	button->colorTxt.b=blue;
}
//*****************************************************************
void Button_setColorBkg(Button* button,int red, int green, int blue)
{
	button->colorBkg.r=red;
	button->colorBkg.g=green;
	button->colorBkg.b=blue;
}
//********************************************
void Button_setState(Button* button,int state)
{
	button->state=state;
	
	if(button->state==BUTTON_STATE_UP)
		button->surfacetxt=TTF_RenderText_Shaded(button->font,button->text,button->colorTxt,button->colorBkg);
		
	else
		button->surfacetxt=TTF_RenderText_Shaded(button->font,button->text,button->colorBkg,button->colorTxt);
	
}
//
///////////////////////////////////////////
//Keyboard
//
Keyboard* Keyboard_create(SDL_Surface* screen,const char* titre)
{
	Keyboard* pkey=NULL;
	
	pkey=(Keyboard*) malloc(sizeof(Keyboard));
	
	if(pkey==NULL)
	{
		return NULL;
	}
	else
	{
		pkey->screen=screen;
		//titre
		pkey->labelTitre=Label_create(screen,"./assets/fonts/free.ttf",25);
		Label_setColor(pkey->labelTitre,255,255,128);
		Label_setText(pkey->labelTitre,titre,20,30);
		
		//saisie
		pkey->labelSaisie=Label_create(screen,"./assets/fonts/free.ttf",40);
		Label_setColor(pkey->labelSaisie,255,255,128);
		Label_setText(pkey->labelSaisie,"?",XSAISIE,YSAISIE);
	
		//buttons
		int i=0;
		for(i=0;i<NB_BUTTON;i++)
		{
			pkey->tabBtn[i]=NULL;
		}
		//
		pkey->buffer[0]='?';
		for(i=1;i<50;i++)
		{
		pkey->buffer[i]='\0';
		}
		
		pkey->pointer=0;
		
		//les nombres
		char buf[10]="";
		int x=60;
		int y=100;
		int pointeur=0;
		for(i=0;i<10;i++)
		{
			sprintf(buf,"%d",i);
			pkey->tabBtn[pointeur]=Button_create(screen,BTN_0_ID+i,"./assets/fonts/free.ttf",50,buf,x+60*i,y);
			pointeur++;
		}
		//A--J
		y+=80;
		
		for(i=0;i<10;i++)
		{
			sprintf(buf,"%c",'A'+i);
			pkey->tabBtn[pointeur]=Button_create(screen,BTN_A_ID+i,"./assets/fonts/free.ttf",50,buf,x+60*i,y);
			pointeur++;
		}
		//K--T
		y+=80;
		for(i=0;i<10;i++)
		{
			sprintf(buf,"%c",'K'+i);
			pkey->tabBtn[pointeur]=Button_create(screen,BTN_K_ID+i,"./assets/fonts/free.ttf",50,buf,x+60*i,y);
			pointeur++;
		}
		//U--Z
		y+=80;
		for(i=0;i<6;i++)
		{
			sprintf(buf,"%c",'U'+i);
			pkey->tabBtn[pointeur]=Button_create(screen,BTN_U_ID+i,"./assets/fonts/free.ttf",50,buf,x+60*i,y);
			pointeur++;
		}
		//point
		x=60+60*6;
		sprintf(buf,"%c",'.');
		pkey->tabBtn[pointeur]=Button_create(screen,BTN_POINT_ID,"./assets/fonts/free.ttf",50,buf,x,y);
		pointeur++;
		
		//Sup
		x+=60;
		sprintf(buf,"%s","Suppr");
		pkey->tabBtn[pointeur]=Button_create(screen,BTN_SUPPRIME_ID,"./assets/fonts/free.ttf",36,buf,120,440);
		pointeur++;
		
		//espace
		y+=80;
		x=120;
		sprintf(buf,"%s","Espace");
		pkey->tabBtn[pointeur]=Button_create(screen,BTN_ESPACE_ID,"./assets/fonts/free.ttf",36,buf,280,440);
		pointeur++;
		
		//enter
		x+=60*4;
		sprintf(buf,"%s","Jouer");
		pkey->tabBtn[pointeur]=Button_create(screen,BTN_ENTER_ID,"./assets/fonts/free.ttf",36,buf,460,440);
		pkey->isEnter=0;
		
		//
		pkey->souris=NULL;
		pkey->souris=inputMouse_create();
		
		pkey->joystick=NULL;
		pkey->joystick=inputJoystick_create();
		
		pkey->input=NULL;
		pkey->input=inputKeyboard_create();
		
	}
	return pkey;
}
//**************************************
void Keyboard_render(Keyboard* keyboard)
{
	int i=0;
	
	if(keyboard->labelTitre!=NULL)
	{
		Label_render(keyboard->labelTitre);
	}
	//
	if(keyboard->labelSaisie!=NULL)
	{
		Label_render(keyboard->labelSaisie);
	}
	//
	for(i=0;i<NB_BUTTON;i++)
	{
		if(keyboard->tabBtn[i] != NULL)
		{
			Button_render(keyboard->tabBtn[i]);
		}
	}
}
//***************************************
void Keyboard_dispose(Keyboard* keyboard)
{
	int i=0;
	if(keyboard->labelTitre!=NULL)
	{
		Label_dispose(keyboard->labelTitre);
	}
	//
	if(keyboard->labelSaisie!=NULL)
	{
		Label_dispose(keyboard->labelSaisie);
	}
	//
	for(i=0;i<NB_BUTTON;i++)
	{
		if(keyboard->tabBtn[i] != NULL)
		{
			Button_dispose(keyboard->tabBtn[i]);
			keyboard->tabBtn[i]=NULL;
		}
	}
	//
	if(keyboard->souris !=NULL)
	{
		inputMouse_dispose(keyboard->souris);
		keyboard->souris=NULL;
	}
	//
	if(keyboard->joystick !=NULL)
	{
		inputJoystick_dispose(keyboard->joystick);
		keyboard->joystick=NULL;
	}
	//
	if(keyboard->input != NULL)
	{
		inputKeyboard_dispose(keyboard->input);
		keyboard->input=NULL;
	}
	//
	free(keyboard);
}
//********************************************
int Keyboard_isEnter(const Keyboard* keyboard)
{
	return keyboard->isEnter;
}
//************************************************************
int Keyboard_findButtonId(const Keyboard* keyboard,int x,int y)
{
	int res=-1;
	int i=0;
	int xd=0;
	int yd=0;
	int xf=0;
	int yf=0;

	Button* item=NULL;
	
	for(i=0;i<NB_BUTTON;i++)
	{
		if(keyboard->tabBtn[i] != NULL)
		{
			item=keyboard->tabBtn[i];
			xd=item->rect.x;
			yd=item->rect.y;
			xf=xd+item->rect.w;
			yf=yd+item->rect.h;
			
			if(x>= xd && x <=xf && y>=yd && y<= yf)
			{
				return item->id;
			}
		}
	}
	return res;
}
//*************************************************
void Keyboard_affiche(Keyboard* keyboard, char val)
{
	keyboard->buffer[keyboard->pointer]=val;
	keyboard->pointer++;
	
	if(keyboard->pointer >50)
		keyboard->pointer=0;
				
	Label_setText(keyboard->labelSaisie,keyboard->buffer,XSAISIE,YSAISIE);
}
//*****************************************
void Keyboard_supp_last(Keyboard* keyboard)
{
	keyboard->pointer--;
	
	if(keyboard->pointer <0)
		keyboard->pointer=0;
		
	keyboard->buffer[keyboard->pointer]='\0';

	Label_setText(keyboard->labelSaisie,keyboard->buffer,XSAISIE,YSAISIE);
}
//******************************************
void Keyboard_resetState(Keyboard* keyboard)
{
	int i=0;
	Button* item=NULL;
	
	for(i=0;i<NB_BUTTON;i++)
	{
		item=keyboard->tabBtn[i];
		//
		if(item->state==BUTTON_STATE_DOWN)
			Button_setState(item,BUTTON_STATE_UP);
	}
}
//*****************************************************
void Keyboard_event(Keyboard* keyboard,SDL_Event* event)
{
	static int id=0;
	
	static int set=0;
	
	static Button* item=NULL;
	
	//
	static int cmp=10;
	static int actionx=0;
	static int actiony=0;
	
	static int action=0;
	
	static Button* ancien=NULL;
	static Button* nouveau=NULL;
	
	ancien=keyboard->tabBtn[cmp-1];
	nouveau=keyboard->tabBtn[cmp];
	
	static int premier=1;
	if(premier==1)
	{
		Button_setState(nouveau,BUTTON_STATE_DOWN);
		Button_setState(ancien,BUTTON_STATE_UP);
		premier=0;
	}
	//
	static int ecriture=0;
	//////////////////////////////////////////
	//inputKeyboard
	if(keyboard->input != NULL)
	{
		inputKeyboard_updateEvent(keyboard->input,event);
		//
		
		//>>> right
		if(inputKeyboard_get_key_state(keyboard->input,SDLK_RIGHT))
		{
			if(action==0)
			{
				action=1;
				ancien=keyboard->tabBtn[cmp];
				
					cmp++;
					if(cmp> NB_BUTTON-1)
						cmp=0;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
			}
		}
		//
		//<<< left
		else if(inputKeyboard_get_key_state(keyboard->input,SDLK_LEFT))
		{
			if(action==0)
			{
				action=1;
				ancien=keyboard->tabBtn[cmp];
				
					cmp--;
					if(cmp <0)
						cmp=NB_BUTTON-1;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
			}
		}
		//^^^ up
		else if(inputKeyboard_get_key_state(keyboard->input,SDLK_UP))
		{
			if(action==0)
				{
					action=1;
					ancien=keyboard->tabBtn[cmp];
				
					cmp-=10;
					if(cmp<0)
						cmp=0;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
				}
		}
		//!!!! down
		else  if (inputKeyboard_get_key_state(keyboard->input,SDLK_DOWN))
		{
			if(action==0)
				{
					action=1;
					ancien=keyboard->tabBtn[cmp];
				
					cmp+=10;
					if(cmp> NB_BUTTON-1)
						cmp=NB_BUTTON-1;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
				}
		}
		// space pour valider
		else if(inputKeyboard_get_key_state(keyboard->input,SDLK_SPACE))
		{
			if(action==0 && ecriture==0)
			{
				ecriture=1;
				
				//les nombres
				if(cmp>=0 && cmp<10)
				{
					Keyboard_affiche(keyboard,'0'+cmp);
				return;
				}
				//les lettres
				if(cmp >=10 && cmp <36)
				{
					Keyboard_affiche(keyboard,'A'+cmp-10);
				return;
				}
				//point
				if(cmp==BTN_POINT_ID)
				{
					Keyboard_affiche(keyboard,'.');
				return;
				}
				//espace
				if(cmp==BTN_ESPACE_ID)
				{
					Keyboard_affiche(keyboard,'_');
				return;
				}
				//del last
				if(cmp==BTN_SUPPRIME_ID)
				{
				Keyboard_supp_last(keyboard);
				return;
				}
				//enter
				if(cmp==BTN_ENTER_ID)
				{
					keyboard->isEnter=1;
				}
			}
		}
		// press enter clavier pour aller plus vite
		else if(inputKeyboard_get_key_state(keyboard->input,SDLK_RETURN))
		{
			keyboard->isEnter=1;
		}
		//
		else
		{
			action=0; 
			ecriture=0;
		}
	}
	
	
	//////////////////////////////////////////
	//////////////////////////////////////////
	//joystick
	if(keyboard->joystick != NULL && SDL_JoystickOpened(keyboard->joystick->numero))
	{
		// mise a jour des events
		inputJoystick_updateEvent(keyboard->joystick,event);
		//
		
		// choix axe X
		int valx=inputJoystick_get_Axe_state(keyboard->joystick, JOYSTICK_LEFT_ANALOG_AXE_X);
		//
		switch(valx)
		{
			//vers la droite
			case -1:
				if(actionx==0)
				{
					actionx=1;
					ancien=keyboard->tabBtn[cmp];
				
					cmp++;
					if(cmp> NB_BUTTON-1)
						cmp=0;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
				}
			break;
			//
			//vers la gauche
			case 1:
				if(actionx==0)
				{
					actionx=1;
					ancien=keyboard->tabBtn[cmp];
				
					cmp--;
					if(cmp <0)
						cmp=NB_BUTTON-1;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
				}
			break;
			//
			default:
			actionx=0;
			break;
		}
		//
		// choix axe Y
		int valy=inputJoystick_get_Axe_state(keyboard->joystick, JOYSTICK_LEFT_ANALOG_AXE_Y);
		//
		switch(valy)
		{
			//vers le bas
			case -1:
				if(actiony==0)
				{
					actiony=1;
					ancien=keyboard->tabBtn[cmp];
				
					cmp+=10;
					if(cmp> NB_BUTTON-1)
						cmp=NB_BUTTON-1;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
				}
			break;
			
			//vers le haut
			case 1:
				if(actiony==0)
				{
					actiony=1;
					ancien=keyboard->tabBtn[cmp];
				
					cmp-=10;
					if(cmp<0)
						cmp=0;
					
					nouveau=keyboard->tabBtn[cmp];
				
					Button_setState(nouveau,BUTTON_STATE_DOWN);
					Button_setState(ancien,BUTTON_STATE_UP);
				}
			break;
			//
			default:
			actiony=0;
			break;
		}
		//*************************************
		//Etat des differents btn
		//A btn
		if(inputJoystick_get_button_state(keyboard->joystick,JOYSTICK_A_BTN))
		{
			if(actionx==0 && ecriture==0)
			{
				ecriture=1;
				
				//les nombres
				if(cmp>=0 && cmp<10)
				{
					Keyboard_affiche(keyboard,'0'+cmp);
				return;
				}
				//les lettres
				if(cmp >=10 && cmp <36)
				{
					Keyboard_affiche(keyboard,'A'+cmp-10);
				return;
				}
				//point
				if(cmp==BTN_POINT_ID)
				{
					Keyboard_affiche(keyboard,'.');
				return;
				}
				//espace
				if(cmp==BTN_ESPACE_ID)
				{
					Keyboard_affiche(keyboard,'_');
				return;
				}
				//del last
				if(cmp==BTN_SUPPRIME_ID)
				{
				Keyboard_supp_last(keyboard);
				return;
				}
				//enter
				if(cmp==BTN_ENTER_ID)
				{
					keyboard->isEnter=1;
				//printf("-> Enter \n");
				}
			}
		}
		else
		{
			ecriture=0;
		}
		//
		//B btn
		if(inputJoystick_get_button_state(keyboard->joystick,JOYSTICK_B_BTN))
		{
			keyboard->isEnter=1;
		}
	}
	/////////////////////////////////////////
	// Utilisation de la souris
	/////////////////////////////////////////
	Vector2D vecteur={0,0};
	int val=0;
	
	inputMouse_updateEvent(keyboard->souris,event);
	//
	val=inputMouse_get_key_state(keyboard->souris,SDL_BUTTON_LEFT);
	
	//la souris a bougee ?
	if(inputMouse_get_position(keyboard->souris,&vecteur))
	{
		id=Keyboard_findButtonId(keyboard,vecteur.x,vecteur.y);
	
		if(id>=0)
		{
			item=keyboard->tabBtn[id];
			Button_setState(item,BUTTON_STATE_DOWN);
		}
		//
		else
		{
			//Keyboard_resetState(keyboard);
			if(item != NULL)
			Button_setState(item,BUTTON_STATE_UP);
		}
	}
	//
	//////////////////////////////////
	if(val && set==1)
	{
		set=0;
		//les nombres
		if(id>=0 && id<10)
		{
			Keyboard_affiche(keyboard,'0'+id);
			return;
		}
		//les lettres
		if(id >=10 && id <36)
		{
			Keyboard_affiche(keyboard,'A'+id-10);
			return;
		}
		//point
		if(id==BTN_POINT_ID)
		{
			Keyboard_affiche(keyboard,'.');
			return;
		}
		//espace
		if(id==BTN_ESPACE_ID)
		{
			Keyboard_affiche(keyboard,'_');
			return;
		}
		//del last
		if(id==BTN_SUPPRIME_ID)
		{
			Keyboard_supp_last(keyboard);
			return;
		}
		//enter
		if(id==BTN_ENTER_ID)
		{
			keyboard->isEnter=1;
			//printf("-> Enter \n");
		}
	}
	else if(val==0 && set==0)
	{
		set=1;
	}
}
//*********************************************************
//**********************************************************
InputJoystick* inputJoystick_create()
{
	//
	InputJoystick* pinputjoy=NULL;
	//
	pinputjoy=(InputJoystick*) malloc(sizeof(InputJoystick));
	
if(pinputjoy==NULL)
		return NULL;
//
else
{
	//
	pinputjoy->numero=0;
		
	pinputjoy->mjoystick=NULL;
		
	//allocation memoire
	pinputjoy->mboutons=NULL;
	//
	pinputjoy->maxes=NULL;

	pinputjoy->mchapeaux=NULL;
		
	SDL_JoystickEventState(SDL_IGNORE);
	//
	if(SDL_NumJoysticks()>0 && SDL_JoystickName(pinputjoy->numero)[0]!='S' && SDL_JoystickName(pinputjoy->numero)[1]!='T')
	{
		pinputjoy->numero=0;
		pinputjoy->mjoystick=SDL_JoystickOpen(pinputjoy->numero);
		
		//allocation memoire
		pinputjoy->mboutons=(char*)malloc(SDL_JoystickNumButtons(pinputjoy->mjoystick)*sizeof(char));
		
		pinputjoy->maxes=(int*)malloc(SDL_JoystickNumAxes(pinputjoy->mjoystick)*sizeof(int));
		
		pinputjoy->mchapeaux=(int*)malloc(SDL_JoystickNumHats(pinputjoy->mjoystick)*sizeof(int));
		
		//raz
		int max=0;
		int i=0;
		max=SDL_JoystickNumButtons(pinputjoy->mjoystick);
		
		//bouttons
		for(i=0;i<max;i++)
			pinputjoy->mboutons[i]=0;
			
		//axes
		max=SDL_JoystickNumAxes(pinputjoy->mjoystick);
		for(i=0;i<max;i++)
			pinputjoy->maxes[i]=0;
		
		//chapeaux
		max=SDL_JoystickNumHats(pinputjoy->mjoystick);
		for(i=0;i<max;i++)
			pinputjoy->mchapeaux[i]=0;
		//
		SDL_JoystickEventState(SDL_ENABLE);
		SDL_EventState(SDL_JOYAXISMOTION,SDL_DISABLE);
	}
}
return pinputjoy;
}
//**************************************************
void inputJoystick_dispose(InputJoystick* inputJoy)
{
	if(inputJoy->mjoystick != NULL)
	{
		SDL_JoystickClose(inputJoy->mjoystick);
	}
	//
	if(inputJoy->mboutons !=NULL)
	{
		free(inputJoy->mboutons);
		inputJoy->mboutons=NULL;
	}
	//
	if(inputJoy->maxes != NULL)
	{
		free(inputJoy->maxes);
		inputJoy->maxes=NULL;
	}
	//
	if(inputJoy->mchapeaux != NULL)
	{
		free(inputJoy->mchapeaux);
		inputJoy->mchapeaux=NULL;
	}
	//
	free(inputJoy);
	inputJoy=NULL;
	//inputJoy->numero=0;
}
//****************************************************
void inputJoystick_updateEvent(InputJoystick* inputJoy,SDL_Event* event)
{
	
	if(inputJoy==NULL || inputJoy->mjoystick ==NULL)
	return;
	
	//
	int num=inputJoy->numero;
	
	int val=0;
	
	if(inputJoy->mjoystick != NULL)
	{
		switch(event->type)
		{
			//
			case SDL_JOYBUTTONDOWN:
			inputJoy->mboutons[event->jbutton.button]=1;
			//printf("Bouton : %d ->down \n\r",event->jbutton.button);
			break;
				
			//
			case SDL_JOYBUTTONUP:
			inputJoy->mboutons[event->jbutton.button]=0;
			//printf("Bouton : %d ->up \n\r",event->jbutton.button);
			break;
				
			
			case SDL_JOYAXISMOTION:
			val=event->jaxis.value;

			inputJoy->maxes[event->jaxis.axis]=val;
				
			printf("Axe : %d ->%d \n\r",event->jaxis.axis,inputJoy->maxes[event->jaxis.axis]);
			break;
			
			//
			case SDL_JOYHATMOTION:
			inputJoy->mchapeaux[event->jhat.hat]=event->jhat.value;
			//printf("Chapeau : %d ->%d \n\r",event->jhat.hat,event->jhat.value);
			break;
				
			//
			default:
			break;
		}
	}
}

int inputJoystick_get_Axe_state(InputJoystick* inputJoy, int axe)
{
	int res=0;
	res=SDL_JoystickGetAxis(inputJoy->mjoystick,axe);
	//
	if(res >20000)
	{
		inputJoy->maxes[axe]=JOYSTICK_ANALOG_AXE_RIGHT_VALUE;
	}
	//
	else if(res <-20000)
	{
		inputJoy->maxes[axe]=JOYSTICK_ANALOG_AXE_LEFT_VALUE;
	}
	//
	else
	{
		inputJoy->maxes[axe]=JOYSTICK_ANALOG_AXE_CENTERED_VALUE;
	}
	//
	return inputJoy->maxes[axe];
	 }

int inputJoystick_get_button_state(InputJoystick* inputJoy, int button)
{
	int res=-1;
	
	res=inputJoy->mboutons[button];
	//
	return res;
}

int inputJoystick_get_hat_state(InputJoystick* inputJoy)
{
	int res=-1;
	
	res=inputJoy->mchapeaux[0];
	//
	return res;
}

int inputJoystick_isOpened(const InputJoystick* inputJoy)
{
	int res=0;
	
	if(SDL_JoystickOpened(inputJoy->numero))
	{
		res=1;
	}
	return res;
}

void inputJoystick_printInfo(InputJoystick* inputJoy)
{
	if(inputJoy->mjoystick != NULL)
	{
		printf("Nom du joystick:%s \n\r",SDL_JoystickName(inputJoy->numero));
		
		printf("Nombre de boutons: %d \n\r",SDL_JoystickNumButtons(inputJoy->mjoystick));
		
		printf("Nombre d axes: %d \n\r",SDL_JoystickNumAxes(inputJoy->mjoystick));
		
		printf("Nombre de chapeaux: %d \n\r",SDL_JoystickNumHats(inputJoy->mjoystick));
	}
}

//**************************
InputKeyboard* inputKeyboard_create()
{
	InputKeyboard* pinput=NULL;
	int i=0;
	
	pinput=(InputKeyboard*)malloc(sizeof(InputKeyboard));
	
	if(pinput==NULL)
	{
		return NULL;
	}
	//
	else
	{
		pinput->mtouches=NULL;
		
		pinput->mtouches=(char*)malloc(SDLK_LAST * sizeof(char));
		
		//raz
		for(i=0;i<SDLK_LAST;i++)
		{
			pinput->mtouches[i]=0;
		}
	}
	
	return pinput;
}
//*******************************
void inputKeyboard_dispose(InputKeyboard* input)
{
	//mtouches
	if(input->mtouches !=NULL)
	{
		free(input->mtouches);
		input->mtouches=NULL;
	}
	
	//
	if(input != NULL)
	{
		free(input);
		input=NULL;
	}
}
//****************************************************
void inputKeyboard_updateEvent(InputKeyboard* input,SDL_Event* event)
{
	int val=0;
	
	if(input != NULL)
	{
		switch(event->type)
		{
			//
			case SDL_KEYDOWN:
			val=input->mtouches[event->key.keysym.sym];
			if(val)
				return;
			else
				input->mtouches[event->key.keysym.sym]=1;
			break;
			
			
			//
			case SDL_KEYUP:
			val=input->mtouches[event->key.keysym.sym];
			if(val==0)
				return;
			else
				input->mtouches[event->key.keysym.sym]=0;
			break;
			
			//
			default:
			break;
		}
	}
}
//***************************************************
char inputKeyboard_get_key_state(const InputKeyboard* input,int key)
{
	char res=-1;
	
	res=input->mtouches[key];
	
	return res;
}
//***********************************************
//inputMouse
//******************************
InputMouse* inputMouse_create()
{
	int i=0;
	
	InputMouse* pinput=NULL;
	//
	pinput=(InputMouse*)malloc(sizeof(InputMouse));
	
	if(pinput ==NULL)
	{
		return NULL;
	}
	else
	{
		pinput->sourisBoutons=(int*)malloc(8*sizeof(int));
		
		//raz
		for(i=0;i<8;i++)
		{
			pinput->sourisBoutons[i]=0;
		}
		//
		pinput->sourisPosi.x=0;
		pinput->sourisPosi.y=0;
		
		pinput->moving=0;
	}
	
	return pinput;
}
//*****************************************
void inputMouse_dispose(InputMouse* input)
{
	//
	if(input->sourisBoutons !=NULL)
	{
		free(input->sourisBoutons);
		input->sourisBoutons=NULL;
	}
	//
	if(input!=NULL)
	{
		free(input);
		input=NULL;
	}
}
//*************************************************************
void inputMouse_updateEvent(InputMouse* input,SDL_Event* event)
{
	int val=0;
	
	int dx=0;
	int dy=0;
	
	if(input != NULL)
	{
		switch(event->type)
		{
			//
			case SDL_MOUSEBUTTONDOWN:
			val=input->sourisBoutons[event->button.button];
			if(val)
				return;
			else
				input->sourisBoutons[event->button.button]=1;
			break;
			
			
			//
			case SDL_MOUSEBUTTONUP:
			val=input->sourisBoutons[event->button.button];
			if(val==0)
				return;
			else
				input->sourisBoutons[event->button.button]=0;
			break;
			
			/////////////////////
			case SDL_MOUSEMOTION:
			dx=event->motion.xrel;
			dy=event->motion.yrel;
			
			if(dx <0)
				dx=-dx;
			
			if(dy <0)
				dy=-dy;
				
			if(dx >0 || dy >0)
			{
				input->sourisPosi.x=event->motion.x;
				input->sourisPosi.y=event->motion.y;
				
				//printf("x= %d  y= %d \n\r",input->sourisPosi.x,input->sourisPosi.y);
				
				input->moving=1;
			}
			else
			{
				input->moving=0;
			}
			break;
			//
			default:
			break;
		}
	}
}
//************************************************************
int inputMouse_get_key_state(const InputMouse* input,int key)
{
	int res=-1;
	
	res=input->sourisBoutons[key];
	
	return res;
}
//********************************************************************
int inputMouse_get_position(const InputMouse* input,Vector2D* vector)
{
	vector->x=input->sourisPosi.x;
	vector->y=input->sourisPosi.y;
	
	return input->moving;
}
//***************************************************
//fin
