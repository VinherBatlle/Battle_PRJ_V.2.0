#include "introductionStage.h"
int key_d_down=0;
//*****************************************
void createIntroduction(introVar* introvar)
{
    introvar->introStage=NULL;
    introvar->music=NULL;
    introvar->bkg=NULL;
    //stage
    introvar->introStage=Stage_create(WIDTH,HEIGHT,"Introduction Battle",0);

    
    
    //background
    introvar->bkg=ImageScrollingV_create(introvar->introStage->screen,"./assets/images/background2.png",-SPEED_SCROLLING/10);
    
    //label titre
    introvar->titre=MoveLabel_create(introvar->introStage->screen,"./assets/fonts/free.ttf",60);
    MoveLabel_setColor(introvar->titre,55,240,217);
    MoveLabel_setText(introvar->titre,"Battle",WIDTH,100);
    MoveLabel_setSpeeds(introvar->titre,-30,0);
    MoveLabel_setFinalPosition(introvar->titre,228,100);

    //label auteur
    introvar->auteur=MoveLabel_create(introvar->introStage->screen,"./assets/fonts/free.ttf",15);
    MoveLabel_setColor(introvar->auteur,255,255,255);
    MoveLabel_setText(introvar->auteur,"Par R. SEVIN, T. ZAPPARRATA,L. WERNER et M. VINH",WIDTH,200);
    MoveLabel_setSpeeds(introvar->auteur,-20,0);
    MoveLabel_setFinalPosition(introvar->auteur,WIDTH/2-195,400);

    //label start
    introvar->start=MoveLabel_create(introvar->introStage->screen,"./assets/fonts/free.ttf",30);
    MoveLabel_setColor(introvar->start,55,240,217);
    MoveLabel_setText(introvar->start,"Appuyez sur echap pour commencer",300,200);
    MoveLabel_setSpeeds(introvar->start,-10, 0);				
    MoveLabel_setFinalPosition(introvar->start,WIDTH/2-270,200);

    //ship
    introvar->ship=ship_create(introvar->introStage->screen,WIDTH/2,HEIGHT-HEIGHT/5);
    ship_setSpeedModule(introvar->ship,0);

    //eaglesp
    introvar->eaglesp=eaglesp_create(introvar->introStage->screen);
    //Heart
    introvar->heart=heart_create(introvar->introStage->screen);
    //BULLET
    introvar->bullets=bullets_create(introvar->introStage->screen);

    //music
    introvar->music=Music_create("./assets/musics/lucgame.ogg");
    Music_setVolume(introvar->music,FORT);
    //Music_play(introvar->music);
}
//*********************
int startIntroduction()
{
    int now=0;
    int ex=0;
    int boucle=33;
    
    float delta_s=0.0;
    //
    introVar introvar;
	
    createIntroduction(&introvar);
    //
    Stage_start(introvar.introStage);
    //
    while(Stage_isRunning(introvar.introStage))
    {
        now=SDL_GetTicks();
		
        if((now-ex) > boucle)
        {
            delta_s=(now-ex)/1000.0;
            
            introvar.event=Stage_processEvent(introvar.introStage);
            
			eventIntroduction(&introvar);
            
            updateIntroduction(delta_s,& introvar);

            renderIntroduction(&introvar);
            			
            ex=now;
        }
        else
        {
            SDL_Delay(boucle-(now-ex));
        }
		

    }
    //
    disposeIntroduction(& introvar);
    return 1;
}

//******************************************
void disposeIntroduction(introVar* introvar)
{
    Music_dispose(introvar->music);
    //
    ImageScrollingV_dispose(introvar->bkg);
    //
    MoveLabel_dispose(introvar->titre);
    //
    MoveLabel_dispose(introvar->auteur);
    //
    MoveLabel_dispose(introvar->start);
    //
    ship_dispose(introvar->ship);
    //
    eaglesp_dispose(introvar->eaglesp);
    //
    heart_dispose(introvar->heart);
    //
    bullets_dispose(introvar->bullets);
    //
    Stage_dispose(introvar->introStage);
}
//*****************************************
void renderIntroduction(introVar* introvar)
{
	
    Stage_render(introvar->introStage);
    //
    ImageScrollingV_render(introvar->bkg);
    //
    eaglesp_render(introvar->eaglesp);
    //
    heart_render(introvar->heart);
    //
    bullets_render(introvar->bullets);
    //
    ship_render(introvar->ship);
    //
    MoveLabel_render(introvar->titre);
    //
    MoveLabel_render(introvar->auteur);
    //
    MoveLabel_render(introvar->start);
    //
    Stage_flip(introvar->introStage);
    //
     
}
//*******************************************************
void updateIntroduction(float delta_s,introVar* introvar)
{
    //
    bullets_update(NULL,introvar->bullets,delta_s);
    //
    eaglesp_update(NULL,introvar->eaglesp,delta_s);
    //
    heart_update(introvar->heart);
    //
    ship_update(introvar->ship,delta_s);
    //
    MoveLabel_update(introvar->titre);
    //
    MoveLabel_update(introvar->auteur);
    //
    ImageScrollingV_update(introvar->bkg);
    //
    MoveLabel_update(introvar->start);
}
//****************************************
void eventIntroduction(introVar* introvar)
{
    switch(introvar->event.type)
    {
    //*************************KEYDOWN**********************************
    case SDL_KEYDOWN:
        
        switch(introvar->event.key.keysym.sym)

        {
        //
        case SDLK_ESCAPE:
            Stage_stop(introvar->introStage);
            printf("close intro\n");
            break;
            
        //SHOOT
        case SDLK_SPACE:
                    
				if(introvar->bullets->canshoot==1)
				{
				bullets_setPosSpeed(introvar->bullets,Sprite_getCenterX(introvar->ship->sprite)-3,Sprite_getCenterY(introvar->ship->sprite)-10);
			    introvar->bullets->shoot_i++;
			    introvar->bullets->canshoot=0;
			    }			  		
            break;

		//******************MOUVEMENT***********************************
        //
        case SDLK_UP:
			 ship_setSpeedModule(introvar->ship,SHIP_SPEED);
             ship_setDirection(introvar->ship,DIRECTION_UP);
            break;
        //
        case SDLK_DOWN:
			 ship_setSpeedModule(introvar->ship,SHIP_SPEED);
             ship_setDirection(introvar->ship,DIRECTION_DOWN);
            break;
        //
        case SDLK_RIGHT:
        	ship_setSpeedModule(introvar->ship,SHIP_SPEED);
             ship_setDirection(introvar->ship,DIRECTION_RIGHT);
            break;
        //
        case SDLK_LEFT:
			ship_setSpeedModule(introvar->ship,SHIP_SPEED);
             ship_setDirection(introvar->ship,DIRECTION_LEFT);
            break;
         //*************************************************************   

		case SDLK_d:
			if(key_d_down !=1){
			introvar->eaglesp->nbr_eagles_now++;
			key_d_down = 1;
			}
            break;
        default:
            break;

        }
        break;

    //******************KEYUP*******************************************
    case SDL_KEYUP:
        switch(introvar->event.key.keysym.sym)

        {
		//
        case SDLK_UP:
			if(introvar->ship->direction == DIRECTION_UP)
			{ship_setSpeedModule(introvar->ship,0);}
			 
            break;
        //
        case SDLK_DOWN:
				if(introvar->ship->direction == DIRECTION_DOWN)	
				{ship_setSpeedModule(introvar->ship,0);}
            break;
        //
        case SDLK_RIGHT:        			
			if(introvar->ship->direction == DIRECTION_RIGHT)	
			{ship_setSpeedModule(introvar->ship,0);}
			
            break;
        //
        case SDLK_LEFT:
			if(introvar->ship->direction == DIRECTION_LEFT)	
			{ship_setSpeedModule(introvar->ship,0);}
            break;
        //
		case SDLK_d:
			key_d_down = 0;
            break;
		//
          
        default: 
            break;

        }
    break;

    default:
        break;
    }
}
//**********************************************************************
