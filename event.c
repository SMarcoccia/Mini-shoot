#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <SDL/SDL.h>

#include"tools.h"  
#include"event.h"


EventsKeyMouse* init_events(void)
{
  EventsKeyMouse* E=NULL;

  if( !(malloc_error(E=malloc(sizeof*E),"Alloc struct EventsKeyMouse failed\n")))
	{
		LINE_ERROR; FILE_ERROR;
		return NULL;
	}

  E->tabkey[0]=SDLK_LEFT;
  E->tabkey[1]=SDLK_RIGHT;
  E->tabkey[2]=SDLK_v;
  E->tabkey[3]=SDLK_p;
  E->k_left=0;
  E->k_right=1;
  E->k_v=2;
  E->k_p=3;
  return E;
}

bool loop_event(EventsKeyMouse* E)
{
  SDL_Event event;
  bool quit=TRUE;

  while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_KEYDOWN :
			if(event.key.keysym.sym !=SDLK_p)
				E->key[event.key.keysym.sym]=TRUE;

			else
			{
				if(E->key[event.key.keysym.sym]==FALSE && SDLK_p)
					E->key[event.key.keysym.sym]=TRUE;
				
				else if(E->key[event.key.keysym.sym]==TRUE && SDLK_p)
					E->key[event.key.keysym.sym]=FALSE;
			}
			break;
		case SDL_KEYUP :
			if(event.key.keysym.sym !=SDLK_p)
				E->key[event.key.keysym.sym]=FALSE;
			break;
		case SDL_MOUSEBUTTONDOWN :
			E->key[event.button.button]=TRUE;
			break;
		case SDL_MOUSEBUTTONUP :
			if(event.button.button==SDL_BUTTON_RIGHT)
				quit=FALSE;
			break;
		case SDL_QUIT :
			quit=FALSE;
			break;
		}
	}
  return quit;
}

void Free_events(EventsKeyMouse* E)
{
  Free_Alloc(E);
}



