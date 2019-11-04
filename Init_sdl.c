#include"Init_sdl.h"


InitSdl* Init_Sdl(void)
{     
  /*Struct qui permet donc la création de la Fenêtre SDL*/
  InitSdl* J=malloc(sizeof*J);
  
  if(SDL_Init(SDL_INIT_VIDEO==-1))
  { 
    tools_strerror("SDL_Init failed : %s\n");
    atexit(SDL_Quit);
  }
  
  if(WIN_W<=0 || WIN_H<=0 || BPP<=0 || BPP>32)
  {  
    tools_strerror("In InitSdl.c : Invalid window size or bpp.\n");
    atexit(SDL_Quit);
  }

  else
  {  
    J->WIN_w=WIN_W;
    J->WIN_h=WIN_H;
    J->bpp=BPP;
    J->screen=SDL_SetVideoMode(J->WIN_w, J->WIN_h, J->bpp, FLAGS);

    if(J->screen==NULL)
    {
      tools_strerror("SDL_SetVideoMode Failed display window SDL failed: %s\n");
      atexit(SDL_Quit);
    }

    SDL_WM_SetCaption("Collision",NULL);
    
    return J;
  }	
}

int InitSdl_error(void *ptr,char *S)
{
  if(ptr==NULL)
  {
    tools_strerror(S);
    return -1;
  }
  return 0;
}

void Free_InitSdl(InitSdl *J)
{
  My_SDL_FreeSurface(J->screen);
  Free_Alloc(J);
  atexit(SDL_Quit);
}
