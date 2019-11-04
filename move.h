#ifndef __MOVE_H__
#define __MOVE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL.h>


#include "tools.h"
#include "Init_sdl.h"
#include "sprites.h"
#include "event.h"
#include "InitImages.h"
#include "clash.h"
#include "blit.h"

extern void move_ship(Sprites* S,dataImageScr* D,InitSdl* A,EventsKeyMouse* E);
extern bool move_shootKey_V(dataImageScr* D);
extern void move_shootStart(Sprites* S,dataImageScr* D,int i);
extern void move_shoot_aux(Sprites* S,dataImageScr* D,dataImg* C);
extern void move_shoot(Sprites* S,dataImageScr* D);
extern void move_ball(Sprites* S,dataImageScr* D,Clash_SplitScr* CS,InitSdl *A);
extern void move(Sprites* S,dataImageScr* D, Clash_SplitScr* CS,InitSdl* A,EventsKeyMouse* E,int* i);

#endif

