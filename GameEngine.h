/**
 *GameEngine for SDL1.2
 * A.De Carvalho 
 * version 1.3: 
 * 			Avril 2016: Button+Keyboard
 * 
 * version 1.4: 
 * 			Avril 2017: drawRect, fillRect, colliRect2
 * 			Mai 2017: gestion joystick, input keyboard, input Mouse
 * 	
 * version 1.4.1
 * 			juin 2017: New Keyboard with inputKeyboard and inputJoy
*/

#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

//fonctions utiles
void ge_Init();
void ge_Quit();
int ge_rand(int valMin,int valMax);

void ge_fillRect(SDL_Surface* screen,int xp,int yp,int width,int height,int red,int green,int blue);
void ge_drawRect(SDL_Surface* screen,int xp,int yp,int width,int height,int red,int green,int blue);

//sound and music
enum{MUTE=0,FAIBLE=25,MOYEN=50,FORT=75,TRES_FORT=100};

//
typedef struct InputMouse InputMouse;
typedef struct InputJoystick InputJoystick;
typedef struct InputKeyboard InputKeyboard;

//*************************
//Sound
typedef struct Sound Sound;

struct Sound{
Mix_Chunk* son;
int canal;
int loopCmp;
int volume;
};
//
Sound* Sound_create(const char * filename);
//
void Sound_dispose(Sound* sound);
//
void Sound_play(Sound* sound);
//
void Sound_setVolume(Sound* sound,int amt);

//**************************
//Struct Stage
typedef struct Stage Stage;
struct Stage{
SDL_Surface* screen;
SDL_Surface* bkgImage;
SDL_Rect rect;
SDL_Event event;
Uint32 bkgColor;
int running;
int paused;
};

// Stage
Stage* Stage_create(int width,int height, const char* titre,int fullscreen);
void Stage_dispose(Stage* stage);
void Stage_start(Stage* stage);
void Stage_stop(Stage* stage);

void Stage_pause(Stage* stage);
int Stage_isPaused(Stage* stage);

int Stage_isRunning(const Stage* stage);
SDL_Event Stage_processEvent(Stage* stage);
int Stage_loadImageFromFile(Stage* stage,const char* fiche);
void Stage_render(Stage* stage);
void Stage_flip(Stage* stage);
void Stage_setBkgColor(Stage* stage,int r,int g,int b);
SDL_Surface* Stage_getScreen(Stage* stage);
//
//***************************
//Struct Sprite
typedef struct Sprite Sprite;
struct Sprite
{
SDL_Surface* image;
SDL_Surface* screen;
SDL_Rect rect;
int dx;
int dy;
int state;
float delta_s;
float directionDeg;
float speedModule;
Sound* sound;
//
SDL_Rect rectBound;
SDL_Surface* surfaceBound;
int xm;
int ym;
int debug;
};

//Sprite
Sprite* Sprite_create(SDL_Surface* screen,const char* fiche);
void Sprite_dispose(Sprite* sprite);

void Sprite_setPosition(Sprite* sprite,int x,int y);
void Sprite_setSpeeds(Sprite* sprite,int dx,int dy);
void Sprite_update(Sprite* sprite);
void Sprite_render(Sprite* sprite);
void Sprite_setState(Sprite* sprite,int state);
int Sprite_getState(const Sprite* sprite);
SDL_Rect Sprite_getRect(const Sprite* sprite);

void Sprite_setDirectionDeg(Sprite* sprite,float directionDeg);
void Sprite_setSpeedModule(Sprite* sprite,float module);
float Sprite_getDirectionDeg(const Sprite* sprite);
float Sprite_getSpeedModule(const Sprite* sprite);

int Sprite_getX(const Sprite* sprite);
int Sprite_getY(const Sprite* sprite);
int Sprite_getTop(const Sprite* sprite);
int Sprite_getBottom(const Sprite* sprite);
int Sprite_getLeft(const Sprite* sprite);
int Sprite_getRight(const Sprite* sprite);
int Sprite_getCenterX(const Sprite* sprite);
int Sprite_getCenterY(const Sprite* sprite);
//
int Sprite_getSpeedX(const Sprite* sprite);
int Sprite_getSpeedY(const Sprite* sprite);

void Sprite_setTop(Sprite* sprite, int top);
void Sprite_setBottom(Sprite* sprite, int bottom);
void Sprite_setLeft(Sprite* sprite, int left);
void Sprite_setRight(Sprite* sprite, int right);
void Sprite_setCenter(Sprite* sprite, int xc,int yc);

void Sprite_changeImage(Sprite* sprite,SDL_Surface* surface);

int Sprite_collidRect(const Sprite* source, const Sprite* target);

int Sprite_collidRect2(const Sprite* source, const SDL_Rect* target);

void Sprite_playSound(const Sprite* sprite);
void Sprite_setSound(Sprite* sprite,const char* file);

void Sprite_setCollidRectInflate(Sprite* sprite,int xm,int ym);

void Sprite_setDebugRect(Sprite* sprite,int debug);

//*******************************************
//image scrolling
typedef struct ImageScrollingV ImageScrollingV;
struct ImageScrollingV
{
SDL_Surface* image;
SDL_Surface* screen;
SDL_Rect rect;
SDL_Rect rectscroll;

int dy;
int ystart;
};
//
ImageScrollingV* ImageScrollingV_create(SDL_Surface* screen,const char* fiche,int dy);
void ImageScrollingV_dispose(ImageScrollingV* scroll);
void ImageScrollingV_update(ImageScrollingV* scroll);
void ImageScrollingV_render(ImageScrollingV* scroll);

//**************************************
//image scolling horizontal
typedef struct ImageScrollingH ImageScrollingH;
struct ImageScrollingH
{
SDL_Surface* image;
SDL_Surface* screen;
SDL_Rect rect;
SDL_Rect rectscroll;
int dx;
int dy;
int xstart;
};
//
ImageScrollingH* ImageScrollingH_create(SDL_Surface* screen,const char* fiche,int dx,int yp);
void ImageScrollingH_dispose(ImageScrollingH* scroll);
void ImageScrollingH_update(ImageScrollingH* scroll);
void ImageScrollingH_render(ImageScrollingH* scroll);

//************************
//Label
typedef struct Label Label;
struct Label{
SDL_Surface* screen;
TTF_Font* font;
SDL_Color color;
SDL_Rect rect;
SDL_Surface* txtSurface;
};
//
Label* Label_create(SDL_Surface* screen,const char* fontfile,int fontsize);
//
void Label_dispose(Label* label);
//
void Label_render(Label* label);
//
void Label_setText(Label* label,const char* txt,int xp,int yp);
//
void Label_setColor(Label* label,int red, int green,int blue);

//*********************************
//MoveLabel
typedef struct MoveLabel MoveLabel;
struct MoveLabel{
Label* label;
int dx;
int dy;
int xfinal;
int yfinal;
};
//
MoveLabel* MoveLabel_create(SDL_Surface* screen,const char* fontfile,int fontsize);
//
void MoveLabel_dispose(MoveLabel* movelabel);
//
void MoveLabel_render(MoveLabel* movelabel);
//
void MoveLabel_update(MoveLabel* movelabel);
//
void MoveLabel_setText(MoveLabel* movelabel,const char* txt,int xp,int yp);
//
void MoveLabel_setColor(MoveLabel* movelabel,int red, int green,int blue);
//
void MoveLabel_setSpeeds(MoveLabel* movelabel,int dx,int dy);
//
void MoveLabel_setFinalPosition(MoveLabel* movelabel,int xf,int yf);
//
//********************************
//Particule
typedef struct Particule Particule;

struct Particule{
SDL_Surface* screen;
SDL_Surface* rectangleSurface;
SDL_Rect rect;
Uint32 couleur;

float speedModule;
float directionDeg;
float lives;
int state;
float delta;
};
//
Particule* Particule_create(SDL_Surface* screen,int xp,int yp,float speed,float direction,float live);
//
void Particule_dispose(Particule* particule);
//
void Particule_setColor(Particule* particule,int red,int green,int blue);
//
void Particule_update(Particule* particule, float delta_s);
//
void Particule_render(Particule* particule);
//
void Particule_newParameters(Particule* particule, int xp,int yp);
//
//*******************************
//Emitter
//
typedef struct Emitter Emitter;

struct Emitter{
int nbParticule;
Particule** tabParticule;
SDL_Rect position;
float angleMin;
float angleMax;
};
//
Emitter* Emitter_create(SDL_Surface* screen,int nb_Particule,int xp,int yp,int angleMin,int angleMax);
//
void Emitter_dispose(Emitter* emitter);
//
void Emitter_setPosition(Emitter* emitter,int xp,int yp);
//
void Emitter_setParticulesColor(Emitter* emitter,int red,int green,int blue);
//
void Emitter_update(Emitter* emitter, float delta);
//
void Emitter_render(Emitter* emitter);

//*********************************
//Animation
//
typedef struct Animation Animation;

struct Animation{
SDL_Surface* screen;
SDL_Surface* image;
SDL_Rect position;
SDL_Rect srcRect;
Sound* sound;

int nbframeX;
int nbframeY;
int frameX;
int frameY;
int frameW;
int frameH;

int run;
int looping;
};
//
//
Animation* Animation_create(SDL_Surface* screen,const char* filename,int nbframeX,int nbframeY);
//
void Animation_loadSound(Animation* anim,const char* filename);
//
void Animation_dispose(Animation* anim);
//
void Animation_update(Animation* anim);
//
void Animation_setPosition(Animation* anim,int xp,int yp);
//
void Animation_render(Animation* anim);
//
void Animation_play(Animation* anim);
//
int Animation_isRunning(const Animation* anim);
//
void Animation_setLooping(Animation* anim, int state);
//
void Animation_playSound(Animation* anim);
//
//*************************
//Music
//
typedef struct Music Music;

struct Music{
Mix_Music* musique;
int fadeIn;
int fadeOut;
int loopCmp;
int volume;
int paused;
};
//
Music* Music_create(const char * filename);
//
void Music_dispose(Music* music);
//
void Music_setVolume(Music* music,int amt);
//
void Music_play(Music* music);
//
void Music_pause(Music* music);
//
int Music_isPaused(Music* music);
//
void Music_resume(Music* music);
//
//****************************
//Button
enum{BUTTON_STATE_UP=1,BUTTON_STATE_DOWN};

//
typedef struct Button Button;

struct Button{
	SDL_Surface* screen;
	TTF_Font* font;
	SDL_Color colorTxt;
	SDL_Color colorBkg;
	SDL_Rect rect;

	SDL_Surface* surfacetxt;
	int state;
	int id;
	
	char text[10];
};
//
Button* Button_create(SDL_Surface* screen,int id, const char* fontfile, int fontsize,const char* text,int xp,int yp);
//
void Button_dispose(Button* button);
//
void Button_render(Button* button);
//
void Button_setColorText(Button* button,int red, int green, int blue);
//
void Button_setColorBkg(Button* button,int red, int green, int blue);
//
void Button_setState(Button* button,int state);
//
//******************************
//keyboard
#define XSAISIE		300
#define YSAISIE		20
#define NB_BUTTON	40
//
#define BTN_0_ID	0

#define BTN_A_ID	BTN_0_ID+10
#define BTN_K_ID	BTN_A_ID+10
#define BTN_U_ID	BTN_K_ID+10

#define BTN_POINT_ID		BTN_U_ID+6
#define BTN_SUPPRIME_ID		BTN_POINT_ID+1
#define BTN_ESPACE_ID		BTN_SUPPRIME_ID+1
#define BTN_ENTER_ID		BTN_ESPACE_ID+1
//
typedef struct Keyboard Keyboard;
struct Keyboard{
	SDL_Surface* screen;
	Label* labelTitre;
	Label* labelSaisie;
	
	char buffer[50];
	int pointer;
	
	int isEnter;
	
	Button* tabBtn[NB_BUTTON];
	
	InputMouse* souris;
	InputJoystick* joystick;
	InputKeyboard* input;
};
//
Keyboard* Keyboard_create(SDL_Surface* screen,const char* titre);
//
void Keyboard_render(Keyboard* keyboard);
//
void Keyboard_dispose(Keyboard* keyboard);
//
void Keyboard_event(Keyboard* keyboard,SDL_Event* event);
//
int Keyboard_findButtonId(const Keyboard* keyboard,int x,int y);
//
void Keyboard_affiche(Keyboard* keyboard, char val);
//
void Keyboard_supp_last(Keyboard* keyboard);
//
int Keyboard_isEnter(const Keyboard* keyboard);
//
void Keyboard_resetState(Keyboard* keyboard);
//
//***************************************************
//Input joystick
//
#define JOYSTICK_A_BTN	0
#define JOYSTICK_B_BTN	1
#define JOYSTICK_X_BTN	2
#define JOYSTICK_Y_BTN	3

#define JOYSTICK_LB_BTN	4
#define JOYSTICK_RB_BTN	5

#define JOYSTICK_ENABLE_BTN	6
#define JOYSTICK_START_BTN	7

#define JOYSTICK_LEFT_ANALOG_AXE_X		0
#define JOYSTICK_LEFT_ANALOG_AXE_Y		1

#define JOYSTICK_RIGHT_ANALOG_AXE_X		3
#define JOYSTICK_RIGHT_ANALOG_AXE_Y		4

#define JOYSTICK_ANALOG_AXE_LEFT_VALUE		1
#define JOYSTICK_ANALOG_AXE_RIGHT_VALUE		-1
#define JOYSTICK_ANALOG_AXE_UP_VALUE		1
#define JOYSTICK_ANALOG_AXE_DOWN_VALUE		-1
#define JOYSTICK_ANALOG_AXE_CENTERED_VALUE	0

typedef struct InputJoystick InputJoystick;
//
struct InputJoystick
{
	SDL_Joystick* mjoystick;
	char* mboutons;
	int* maxes;
	int* mchapeaux;
	
	int numero;
};
//
InputJoystick* inputJoystick_create();
//
int inputJoystick_isOpened(const InputJoystick* inputJoy);
//
void inputJoystick_dispose(InputJoystick* inputJoy);
//
void inputJoystick_updateEvent(InputJoystick* inputJoy,SDL_Event* event);
//
void inputJoystick_printInfo(InputJoystick* inputJoy);
//
int inputJoystick_get_button_state(InputJoystick* inputJoy, int button);
//
int inputJoystick_get_hat_state(InputJoystick* inputJoy);
//
int inputJoystick_get_Axe_state(InputJoystick* inputJoy, int axe);
//
//************************
//Input keyboard 
//
typedef struct InputKeyboard InputKeyboard;
//
struct InputKeyboard
{
	char* mtouches;
};
//
InputKeyboard* inputKeyboard_create();
//
void inputKeyboard_dispose(InputKeyboard* input);
//
void inputKeyboard_updateEvent(InputKeyboard* input,SDL_Event* event);
//
char inputKeyboard_get_key_state(const InputKeyboard* input,int key);
//
//******************************
// Input Mouse
//
typedef struct Vector2D Vector2D;
//
struct Vector2D
{
	int x;
	int y;
};
//***************
//
typedef struct InputMouse InputMouse;
//
struct InputMouse
{
	int* sourisBoutons;
	//
	Vector2D sourisPosi;
	//
	int moving;
};
//
InputMouse* inputMouse_create();
//
void inputMouse_dispose(InputMouse* input);
//
void inputMouse_updateEvent(InputMouse* input,SDL_Event* event);
//
int inputMouse_get_key_state(const InputMouse* input,int key);
//
int inputMouse_get_position(const InputMouse* input,Vector2D* vector);
//
////////////////////////////
#endif // GAMEENGINE_H_INCLUDED



























