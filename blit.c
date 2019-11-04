
#include "blit.h"

void blit_shoot(Sprites* S,dataImageScr* D,InitSdl* A,int i)
{
  SDL_Rect pos;
  dataImg* C=D->shoot;
  while(C!=NULL)
  {
    if(C->y+S->ShootH>0)
    {  
      pos.x=C->x;
      pos.y=C->y;
      if(C->y<D->ship.y)
        SDL_BlitSurface(S->CpySpr,&S->ClipSpr[shoot+i],A->screen,&pos);
    }
    C=C->next;
  }
}

void blit_ship(Sprites* S,dataImageScr* D,InitSdl* A)
{
  SDL_Rect pos;

  if(D->ship.x<0)
    pos.x=0;
  else if(D->ship.x+S->ShipW>A->WIN_w)
  {
    pos.x=A->WIN_w-S->ShipW;
  }
  else
    pos.x=D->ship.x;

  pos.y=D->ship.y;

  SDL_BlitSurface(S->CpySpr,&S->ClipSpr[ship],A->screen,&pos);
}

void blit_ball(Sprites* S,dataImageScr* D,InitSdl* A)
{
  SDL_Rect pos;
  dataImg* C=D->ball;
      
  while(C!=NULL)
  {
    pos.x=C->x;
    pos.y=C->y;

    SDL_BlitSurface(S->CpySpr,&C->ImgSpr,A->screen,&pos);
    C=C->next;
  }  
}

void blit_flashR(Sprites* S,dataImageScr* D,InitSdl* A,SDL_Rect pos,int i)
{
  int ii = flashR+i;

  pos.x=D->ship.x+S->ShipW-S->ClipSpr[flashR].w;
  pos.y=D->ship.y;

  if(D->ship.x<0)
    pos.x=D->ship.x+S->ShipW-S->ClipSpr[flashR].w+1;

  else if(D->ship.x+S->ShipW>A->WIN_w)
    pos.x=D->ship.x+S->ShipW-S->ClipSpr[flashR].w-1;

  SDL_BlitSurface(S->CpySpr,&S->ClipSpr[ii],A->screen,&pos);
}

void blit_flashL(Sprites* S,dataImageScr* D,InitSdl* A,SDL_Rect pos,int i)
{
  int ii = flashL+i;
  	  
  pos.x=D->ship.x;
  pos.y=D->ship.y;

  if(D->ship.x<0)
    pos.x=0;

  else if(D->ship.x+S->ShipW>A->WIN_w)
    pos.x=D->ship.x-1;

  SDL_BlitSurface(S->CpySpr,&S->ClipSpr[ii],A->screen,&pos);
}

void blit_flash(Sprites* S,dataImageScr* D,InitSdl* A,int i)
{
  SDL_Rect pos;
  
  blit_flashL(S,D,A,pos,i);
  blit_flashR(S,D,A,pos,i);
}

void blit(Sprites *S,dataImageScr* D,InitSdl* A,TimeImgAnim** T)
{
  if(D->NbBallScr)
    blit_ball(S,D,A);

  blit_ship(S,D,A);
  if(D->NbBallScr)
  {
    T[ShootTime]->i=TimeAnim(T,ShootImg,20,0);
    blit_shoot(S,D,A,T[ShootTime]->i);
  }
  
  T[FlashTime]->i=TimeAnim(T,FlashImg,100,1);
  blit_flash(S,D,A,T[FlashTime]->i);

  SDL_Flip(A->screen);
  SDL_FillRect(A->screen,NULL,0);
}


