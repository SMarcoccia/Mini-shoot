#ifndef __IMAGES_H__
#define __IMAGES_H__

#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<time.h>

#include"tools.h"
#include"Init_sdl.h"
#include"sprites.h"

#define HALF_W WIN_W/2
#define HALF_H WIN_H/2

#define NB_BALLSCR 5
#define Nb_SHOOTSCR 4
#define BorderSCR  40
#define BorderShip 50
#define VALUE 100 /*Position Ball at WIN_H-100 Max*/


typedef struct dataImg dataImg;

struct dataImg
{
  int x, y;
  int vx, vy;
  char count; /*ball destroy if count==4 shoot peut servir a autre chose*/
  char ScrPos; /*localisation ball in one of the 4 side of the screen*/
  SDL_Rect ImgSpr;
  char head;/*head of the list if TRUE else FALSE*/
  dataImg* next;
};

typedef struct dataImageScr
{
  dataImg* ball;
  dataImg ship;
  dataImg* shoot;
  dataImg flashShipL;
  dataImg flashShipR;
  int NbBallScr;
  int NbShootScr;
  int count0,count1,count2,count3;/*Nb ball in each of 4 section of screen */
}dataImageScr;


extern void init_ImgShootNoList(dataImageScr* D);
extern void init_ImgShootListAux(Sprites* S,dataImageScr* D);
extern void init_ImgShootList(Sprites* S,dataImageScr* D);
extern void init_ImgFlashShip(Sprites* S,dataImageScr* D);
extern void init_ImgShip(Sprites* S,dataImageScr* D,InitSdl* A);                                         
extern void init_ImgBall(Sprites* S,InitSdl* A,dataImg* C,int j,int i);

extern dataImageScr* alloc_dataImageScr(dataImageScr* D);

extern void init_dataImg(dataImageScr* D);

extern dataImageScr* init_dataImageScr(Sprites* S,InitSdl* A);

extern void Free_ball(dataImageScr* D);
extern void Free_Shoot(dataImageScr* D);
extern void Free_dataImgScr(dataImg* C);
extern void Free_dataImgGlobal(dataImageScr* D);
extern void Free_dataImageScr(dataImageScr* D);
#endif










/*extern SDL_Rect *sdl_rect_alloc(SDL_Rect *ptr,int size);
  extern SDL_Rect **sdl_rect_alloc2d(SDL_Rect **ptr,int size1,int size2);*/

/*
SDL_Rect **sdl_rect_alloc2d(SDL_Rect **ptr,int size1, int size2)
{
  int i;
  assert(size1>0);
  assert(size2>0);

  if(!(ptr=malloc(size1*sizeof*ptr)))
    {
      tools_strerror("The allocation failed, the block(s) was released : %s");
      free_alloc(ptr);
      return NULL;
    }

  for(i=0;i<size1;i++)
    {
      if(!(ptr[i]=sdl_rect_alloc(ptr[i],size2)))
	{
	  for(i=i-1;i>=0;i--)
	    free_alloc(ptr[i]); 
	  free_alloc(ptr);
	  return NULL;
	}
    }
  return ptr;
}*/

/*
SDL_Rect *sdl_rect_alloc(SDL_Rect *ptr,int size)
{
  if(!(ptr=malloc(size*sizeof*ptr)))
    {
      tools_strerror("The allocation failed, the block(s) was released : %s");
      free_alloc(ptr);
      return NULL;
    }

  return ptr;
}*/


