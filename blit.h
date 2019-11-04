#ifndef __BLIT_H__
#define __BLIT_H__

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<time.h>
#include<SDL/SDL.h>


#include "tools.h"
#include "Init_sdl.h"
#include "sprites.h"
#include "event.h"
#include "InitImages.h"

extern void blit_flashR(Sprites* S,dataImageScr* D,InitSdl* A,SDL_Rect pos,int i);
extern void blit_flashL(Sprites* S,dataImageScr* D,InitSdl* A,SDL_Rect pos,int i);
extern void blit_flash(Sprites* S,dataImageScr* D,InitSdl* A,int i);
extern void blit_ball(Sprites* S,dataImageScr* D,InitSdl* A);
extern void blit_ship(Sprites* S,dataImageScr* D,InitSdl* A);
       void blit_shootSound(Sprites* S,dataImageScr* D,InitSdl* A,int i);
extern void blit_shoot(Sprites* S,dataImageScr* D,InitSdl* A,int i);
extern void blit(Sprites* S,dataImageScr* D,InitSdl* A,TimeImgAnim** T);

#endif
