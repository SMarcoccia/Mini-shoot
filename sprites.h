#ifndef __SPRITES_H__
#define __SPRITES_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <SDL/SDL.h>

#include "tools.h"

#define ALPHA 253 /*SprOriginal*/
#define ALPHA1 227 /*CopySpr*/
#define BACKROUND 252
#define NbImgSprMAX 1024
#define ValueShipX 12 /*Ecart entre ship.x ship.X+ValueShipX*/
#define ValueShipY 12 

typedef enum NoCellShoot
  {
    shoot0,
    shoot1,
    shoot2,
    shoot3
  }NoCellShoot;

typedef enum NbTimeImgAnim
  {
    ShootTime,
    FlashTime,
    LapsTime
  }NbTimeImgAnim;

typedef enum NbImg
  {
    ShipImg=1,
    ShootImg=3,
    FlashImg=5,
    BallImg=12
  }NbSpr;

typedef enum name_img
  {
    grey,
    red,
    red_clear,
    orange,
    yellow,
    green,
    turquoise,
    blue,
    purple,
    grey_clear,
    dark_yellow,
    brown=11,
    ship,
    shoot,
    flashL=16,
    flashR=21
    }name_img;

typedef struct Sprites
{
  SDL_Surface* spr;
  SDL_Surface* CpySpr;
  SDL_Rect* ClipSpr;
  name_img Enum;
  int nbImg;
  int BallW,BallH;
  int ShipW,ShipH;
  int ShootW,ShootH;
}Sprites;


extern void Free_ClipSpr(SDL_Rect* S);
extern void Free_PtrSprites(Sprites* S);
extern void Free_Sprites(Sprites* S);

extern void save_spr(Sprites* S);
extern void recoveryDataImg(Sprites* S);

extern void LoadBMP_spr_aux(char* filename,Sprites* S);
extern Sprites* LoadBMP_spr(char* filename);

extern void init_ClipSpr(Sprites* S);
extern Sprites* init_StructSprites(Sprites* S);

#endif
