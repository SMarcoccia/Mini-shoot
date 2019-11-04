#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

/*#define SDL */
 
#ifdef SDL
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include"Init_sdl.h"
#include"event.h"
#include"tools.h"
#include"InitImages.h"
#include"sprites.h"
#include"move.h"
#include"clash.h"
#include"blit.h"

#define TIME 16
#define filename "gfx/sprites.bmp"
#define nbTime 4 /*represente le nb de struct Time d'un tableau*/


int main(int argc, char *argv[])
{
  InitSdl* initSdl=NULL;
  Sprites* BoardSpr=NULL;
  EventsKeyMouse* events=NULL;
  dataImageScr* ImgScr=NULL; 
  Clash_SplitScr* ClashSplit=NULL;
  TimeImgAnim** time=NULL;

  bool stop=TRUE, pause=FALSE;
  int timeA=0, lasttimeA=0;
  int i=0;

  initSdl=Init_Sdl();
  BoardSpr=LoadBMP_spr(filename);
  events=init_events();
  ImgScr=init_dataImageScr(BoardSpr,initSdl);
  ClashSplit=clash_init_SplitSrc(BoardSpr,ImgScr);
  time=init_TimeAnim(time,nbTime);
  
  while(stop)
  {  
    timeA  = SDL_GetTicks(); 

    if(timeA-lasttimeA>TIME)
    {
      stop=loop_event(events);
      if(ImgScr->NbBallScr)
        {
          if(!pause)
          {  
            move(BoardSpr,ImgScr,ClashSplit,initSdl,events,&i);
            blit(BoardSpr,ImgScr,initSdl,time);
          }
        }
      lasttimeA=timeA;
    }
    pause=events->key[events->tabkey[events->k_p]];
  }
  
  Free_dataImageScr(ImgScr);
  Free_events(events);
  Free_Sprites(BoardSpr);
  Free_InitSdl(initSdl);
  Free_TimeAnim(time,nbTime);
  SDL_FreeSurface(initSdl->screen);

  if(argc==-1) printf(argv[0]);
  return EXIT_SUCCESS;
}

