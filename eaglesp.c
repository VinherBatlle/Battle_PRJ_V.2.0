#include "eaglesp.h"
#include "Constantes.h"
int Sw_d=0;

//
Eaglesp* eaglesp_create(SDL_Surface* screen)
{
	
    Eaglesp* eaglesp=NULL;

    eaglesp=(Eaglesp*) malloc(sizeof(Eaglesp));

    if(eaglesp==NULL)
        return NULL;

    else
    {
		eaglesp->nbr_eagles=50;
		eaglesp->nbr_eagles_now=3;
		eaglesp->tabeagle = NULL;
		eaglesp->tabeagle = (Eagle**) malloc(eaglesp->nbr_eagles * sizeof(Eagle*));
		if(eaglesp->tabeagle == NULL){
			exit(0);
		}
		
		for(int i = 0 ; i < eaglesp->nbr_eagles ; i++ ) {
        eaglesp->tabeagle[i]=eagle_create(screen,EAGLE_TYPE_2);
        eagle_setPosition(eaglesp->tabeagle[i],ge_rand(30,WIDTH-30),ge_rand(15,230));
        eagle_setSpeed(eaglesp->tabeagle[i],0,SPEED_EAGLE);
		}
		
		/*eaglesp->eagle1=eagle_create(screen,EAGLE_TYPE_2);
        eagle_setPosition(eaglesp->eagle1,ge_rand(30,WIDTH/3),100);
        eagle_setSpeed(eaglesp->eagle1,0,5);
        
        eaglesp->eagle2=eagle_create(screen,EAGLE_TYPE_2);
        eagle_setPosition(eaglesp->eagle2,ge_rand(WIDTH/3,2*WIDTH/3),230);
        eagle_setSpeed(eaglesp->eagle2,0,5);
        
        eaglesp->eagle3=eagle_create(screen,EAGLE_TYPE_2);
        eagle_setPosition(eaglesp->eagle3,ge_rand(2*WIDTH/3,WIDTH-30),0+15);
        eagle_setSpeed(eaglesp->eagle3,0,5);
        */
    }

    return eaglesp;
}
//**********************************************************************
void eaglesp_dispose(Eaglesp* eaglesp)
{
	for(int i = 0 ; i < eaglesp->nbr_eagles ; i++) {
		if( &eaglesp->tabeagle[i] != NULL)
        eagle_dispose(eaglesp->tabeagle[i]);
	}
    //
   // if(eaglesp->tabeagle != NULL)
	//free(eaglesp->tabeagle);
    //
    free(eaglesp);
}
//**********************************************************************
void eaglesp_render(Eaglesp* eaglesp)
{
	for(int i = 0 ; i < eaglesp->nbr_eagles_now ; i++) {
		eagle_render(eaglesp->tabeagle[i]);
	}

}
//**********************************************************************
void eaglesp_update(Scores* scores,Eaglesp* eaglesp,int playsound)
{


	Sw_d++;
	if(eaglesp->nbr_eagles_now >= eaglesp->nbr_eagles)
	eaglesp->nbr_eagles_now = eaglesp->nbr_eagles;
	if(Sw_d==3)
	{
		eaglesp_swDir(eaglesp);
		Sw_d=0;
	}
	
	for(int i = 0 ; i < eaglesp->nbr_eagles_now ; i++) {
		eagle_update(eaglesp->tabeagle[i]);
	if(eagle_touchBotScreen(eaglesp->tabeagle[i]))
	{	
		
        eagle_reset(eaglesp->tabeagle[i]);
        eaglesp_newWave(eaglesp,i);
    }
	}
    //
    

}
//**************************NEW WAVE************************************
void eaglesp_newWave(Eaglesp* eaglesp,int n)
{
	//tabeagle
		eagle_setPosition(eaglesp->tabeagle[n],ge_rand(30+10*n,WIDTH-150+10*n),0+15);
		eagle_setSpeed(eaglesp->tabeagle[n],0,SPEED_EAGLE);
		
	
/*	//Eagle1
	if(n==1)
    {		
		eagle_setPosition(eaglesp->eagle1,ge_rand(30,WIDTH/3),0+15);
		eagle_setSpeed(eaglesp->eagle1,0,SPEED_EAGLE);
	}
    //Eagle2
    if(n==2)
    {			
		eagle_setPosition(eaglesp->eagle2,ge_rand(WIDTH/3,2*WIDTH/3),0+15);
		eagle_setSpeed(eaglesp->eagle2,0,SPEED_EAGLE);
	}
    //Eagle3 
    if(n==3)  
    {		
		eagle_setPosition(eaglesp->eagle3,ge_rand(2*WIDTH/3,WIDTH-30),0+15);
		eagle_setSpeed(eaglesp->eagle3,0,SPEED_EAGLE);		
	}
	*/
}
void eaglesp_swDir(Eaglesp* eaglesp)
{
	int nb=ge_rand(0,eaglesp->nbr_eagles_now);
	
	eagle_setSpeed(eaglesp->tabeagle[nb],ge_rand(-4,4),SPEED_EAGLE);

	

    /*if(nb%3 ==2)
    { 
		eagle_setSpeed(eaglesp->eagle1,ge_rand(-4,4),SPEED_EAGLE);
    }
    if(nb%3 ==1)
    {
        eagle_setSpeed(eaglesp->eagle2,ge_rand(-4,4),SPEED_EAGLE);

    }
    if(nb%3 ==0)
    {
        eagle_setSpeed(eaglesp->eagle3,ge_rand(-4,4),SPEED_EAGLE);

    }
    */
}
//










