#include "InitImages.h"

void init_ImgShootListAux(Sprites* S,dataImageScr* D)
{
  int i=0;
  dataImg* C=D->shoot;

  while(C!=NULL)
  {
    C->x=D->ship.x+S->ClipSpr[ship].w/2-S->ClipSpr[shoot].w/2;
    C->y=D->ship.y+1;
    C->vy=10;
    C->count=i++;
    C->ScrPos=-1;
    C=C->next;
  }
}

void init_ImgShootList(Sprites* S,dataImageScr* D)
{
  int i;
  dataImg* C=NULL;
  for(i=0;i<D->NbShootScr;i++)
  {
    if(i==0)
    {
      D->shoot=malloc(sizeof*D->shoot);
      D->shoot->next=NULL;
    }
    else
    {
      C=malloc(sizeof*C);
      C->next=D->shoot->next;
      D->shoot->next=C;
    }
  }
  init_ImgShootListAux(S,D);
}

void init_ImgFlashShip(Sprites* S,dataImageScr* D)
{
  D->flashShipL.x=D->ship.x;
  D->flashShipL.y=D->ship.y;
  
  D->flashShipR.x=D->ship.x+S->ClipSpr[ship].w;
  D->flashShipR.y=D->ship.y;
}

void init_ImgShip(Sprites* S,dataImageScr* D,InitSdl* A)
{
  D->ship.x=A->WIN_w/2-S->ClipSpr[ship].w/2;
  D->ship.y=A->WIN_h-50;
  D->ship.vx=10;
}

void init_ImgBall(Sprites* S,InitSdl* A,dataImg* C,int j,int i)
{
  C->count=0;
  C->ScrPos=0;
  C->ImgSpr.x=S->ClipSpr[j].x;
  C->ImgSpr.y=S->ClipSpr[j].y;
  C->ImgSpr.w=S->ClipSpr[j].w;
  C->ImgSpr.h=S->ClipSpr[j].h;

  if(i==0)
    C->head=TRUE;
  else 
    C->head=FALSE;

  if((C->x=rand()%(A->WIN_w))>=A->WIN_w-S->BallW)
    C->x=A->WIN_w-S->BallW;
 
  if((C->y=rand()%(A->WIN_h-VALUE))>=A->WIN_h-S->BallH)
    C->y=A->WIN_h-S->BallH;

  if((C->vx=rand()%10-5)==0)
    C->vx=rand()%1+1;

  if((C->vy=rand()%10-5)==0)
    C->vy=rand()%1+1;
}

void init_dataImg(dataImageScr* D)
{
  int i;

  for(i=0;i<NB_BALLSCR;i++)
  {
    if(i==0)
    {
      D->ball=malloc(sizeof*D->ball);
      D->ball->next=NULL;
    }
    else
    {
      dataImg* C=malloc(sizeof*C);
      C->next=D->ball->next;
      D->ball->next=C;
    }
  }
}

dataImageScr* alloc_dataImageScr(dataImageScr* D)
{
  D = malloc(sizeof*D);
  init_dataImg(D);
  return D;
}

dataImageScr* init_dataImageScr(Sprites* S,InitSdl* A)
{ 
  int i,j=0;
  dataImageScr* D = NULL;
  D = alloc_dataImageScr(D);
  dataImg* C=D->ball;

  srand((unsigned int)time(NULL));      

  D->NbBallScr=NB_BALLSCR;
  D->NbShootScr=Nb_SHOOTSCR;
  D->count0=0;
  D->count1=0;
  D->count2=0;
  D->count3=0;

  for(i=0;i<D->NbBallScr;i++)
  {
    init_ImgBall(S,A,C,j,i);
    C=C->next;
    if(j==11)
      j=0;
    j++;
  }

  init_ImgShip(S,D,A);
  init_ImgShootList(S,D);
  init_ImgFlashShip(S,D);

  return D;
}


void Free_Shoot(dataImageScr* D)
{
  while(D->shoot!=NULL)
  {
    dataImg* C=D->shoot;
    D->shoot=D->shoot->next;
    Free_Alloc(C);
  }
}

void Free_dataImgScr(dataImg* C)
{
  Free_Alloc(C);
}

void Free_dataImgGlobal(dataImageScr* D)
{
  Free_Shoot(D);
}

void Free_dataImageScr(dataImageScr* D)
{
  Free_dataImgGlobal(D);
  Free_Alloc(D);
}
