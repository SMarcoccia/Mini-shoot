
#include "sprites.h"


void recoveryDataImg(Sprites* S)
{
  int i,j,xi=0,yi=0;
  int PtRefX=0,PtRefY=0;
  int imgW=0,imgH=0;
  u8* pix=(u8*)S->spr->pixels;

  for(j=0;j<S->spr->h;j++) 
    for(i=0;i<S->spr->w;i++)
    {  	    
      if(*(pix+i+S->spr->pitch*j)==ALPHA)
      {
        xi=i;
        yi=j;
        while(*(pix+(S->spr->pitch*yi)+xi)==ALPHA)
          imgW=xi++;
        
        while(*(pix+(xi-1)+S->spr->pitch*yi)==ALPHA)
          imgH=yi++;

        /*erase the image*/
        for(yi=j;yi<=imgH;yi++) 
          for(xi=i;xi<=imgW;xi++)
      *(pix+(S->spr->pitch*yi)+xi)=BACKROUND;

        S->ClipSpr[S->nbImg].x=PtRefX=i+1;
        S->ClipSpr[S->nbImg].y=PtRefY=j+1;
        S->ClipSpr[S->nbImg].w=xi-PtRefX-1;
        S->ClipSpr[S->nbImg].h=yi-PtRefY-1;
        S->nbImg++;
      }
    }

  S->BallW=S->ClipSpr[grey].w;
  S->BallH=S->ClipSpr[grey].h;
  S->ShipW=S->ClipSpr[ship].w;
  S->ShipH=S->ClipSpr[ship].h;
  S->ShootW=S->ClipSpr[shoot].w;
  S->ShootH=S->ClipSpr[shoot].h;

  My_SDL_FreeSurface(S->spr);
}

void save_spr(Sprites* S)
{
  int bpp = 8;
  u8 rmask = 0xE0;
  u8 gmask = 0x1C;
  u8 bmask = 0x3;
  u8 amask = 0;
  
  int r=0xFF;
  int g=0x0;
  int b=0xFF;
  
  S->CpySpr = SDL_CreateRGBSurface(SDL_HWSURFACE,S->spr->w,S->spr->h,bpp,rmask,gmask,bmask,amask);
  
  SDL_BlitSurface(S->spr,NULL,S->CpySpr,0);
  
  SDL_SetColorKey(S->CpySpr,SDL_SRCCOLORKEY,SDL_MapRGB(S->CpySpr->format,r,g,b));
}

void init_ClipSpr(Sprites* S)
{
  malloc_error(S->ClipSpr=malloc(NbImgSprMAX*sizeof*S->ClipSpr),"Alloc of table of struct Clips_spr failed\n");
}

Sprites* init_StructSprites(Sprites* S)
{
  return malloc_error(S=malloc(sizeof*S),"alloc of struct Sprites failed\n");
}

void LoadBMP_spr_aux(char* filename,Sprites* S)
{
  S->spr=SDL_LoadBMP(filename);
}

Sprites* LoadBMP_spr(char* filename)
{
  Sprites* BoardSpr = NULL;
  BoardSpr=init_StructSprites(BoardSpr);

  LoadBMP_spr_aux(filename,BoardSpr);
  save_spr(BoardSpr);
  init_ClipSpr(BoardSpr);
  BoardSpr->nbImg=0;
  recoveryDataImg(BoardSpr);

  return BoardSpr;
}

void Free_ClipSpr(SDL_Rect* S)
{
  Free_Alloc(S);
}

void Free_PtrSpr(Sprites* S)
{
  Free_Alloc(S);
}

void Free_Sprites(Sprites* S)
{
  Free_ClipSpr(S->ClipSpr);
  My_SDL_FreeSurface(S->CpySpr);
  Free_PtrSpr(S);
}
