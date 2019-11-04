#ifndef __INIT_SDL_H__
#define __INIT_SDL_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <SDL/SDL.h>

#include "tools.h"


#define WIN_W 640
#define WIN_H 500
#define BPP 8
#define FLAGS SDL_HWSURFACE|SDL_DOUBLEBUF

typedef struct InitSdl
{
  int WIN_w;
  int WIN_h;
  int bpp;
  SDL_Surface* screen;
}InitSdl;

extern InitSdl* Init_Sdl(void);
extern int InitSdl_error(void *ptr,char *S);
extern void Free_InitSdl(InitSdl *J);

#endif

