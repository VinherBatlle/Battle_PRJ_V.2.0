#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>

#include "GameEngine.h"
#include "introductionStage.h"
#include "gameStage.h"
#include "conclusionStage.h"
#include "keyboardStage.h"
int main()
{
	
    ge_Init();
    //
    startKeyboardStage("Entrez votre pseudo:","./assets/files/pseudo.txt");
    printf("start intro\n");
    startIntroduction();
    printf("start game\n");
    startGame();
    startConclusion();
    //    
    ge_Quit();

    printf("Exit \n");
    return 0 ;
}

