#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

//Window size
#define WIDTH   620
#define HEIGHT  620

//scrolling
#define SPEED_SCROLLING 10

//eagle
#define SPEED_EAGLE   2

//ship
#define SHIP_SPEED 12

//boss

//bullet
#define BULLET1_SPEED 10
#define BULLET2_SPEED 5


//Ship Dir
enum{DIRECTION_UP=0,DIRECTION_DOWN,DIRECTION_RIGHT,DIRECTION_LEFT};

//Ship collide
enum{SHIP_STATE_ON=1,SHIP_STATE_TOUCHED};

//Eagle
enum{EAGLE_TYPE_1=1,EAGLE_TYPE_2};

//Bullet
enum{BULLET_TYPE_1=1,BULLET_TYPE_2};

//Boss
enum{BOSS_TYPE_1=1,BOSS_TYPE_2=2,BOSS_TYPE_3=3};


#endif // CONSTANTES_H_INCLUDED
