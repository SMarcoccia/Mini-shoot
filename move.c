#include"move.h"


extern void move_ship(Sprites* S,dataImageScr* D,InitSdl* A,EventsKeyMouse* E)
{
  if(D->ship.x>=0)
    if(E->key[E->tabkey[0]])
    {
      D->ship.x-=D->ship.vx;
      if(D->shoot->y+S->ClipSpr[shoot].h<=0 || D->shoot->y>=D->ship.y)
        D->shoot->x=D->ship.x+S->ShipW/2-S->ShootW/2;	  
    }
  
  if(D->ship.x+S->ShipW<=A->WIN_w)
    if(E->key[E->tabkey[1]])
    {
      D->ship.x+=D->ship.vx;
      if(D->shoot->y+S->ClipSpr[shoot].h<=0 || D->shoot->y>=D->ship.y)
        D->shoot->x=D->ship.x+S->ShipW/2-S->ShootW/2;
    }
}

bool move_shootKey_V(dataImageScr* D)
{ 
  int i=0;
  dataImg* C=D->shoot;
	  
  while(C)
  {
    if(C->y < D->ship.y)
      i++;
    C=C->next;
  }

  if( ! i)
    return TRUE;
  else 
    return FALSE;
}  


void move_shootStart(Sprites* S,dataImageScr* D,int i)
{ 
  int ii=0;
  dataImg* C0=D->shoot;
  char gap1=10;
  char gap2=S->ShootH-D->shoot->vy;
 
  while(ii<=i)
  {
    C0->y -= C0->vy+gap2;
    if(ii<i && ii<D->NbShootScr)      
      C0->y-=gap1; 
      
    C0=C0->next;
    ii++;
  }
}

void move_shoot_aux(Sprites* S,dataImageScr* D,dataImg* C)
{
  if((C->y+S->ShootH >0 && C->y < D->ship.y))
    C->y -= C->vy;
  else
  {
    C->y=D->ship.y;
    C->x=D->ship.x+S->ShipW/2-S->ShootW/2;
    C->ScrPos=-1;
  }
}

void move_shoot(Sprites* S,dataImageScr* D)
{
  int XMin,YMin,XMax,YMax;
  dataImg* C0=D->shoot;
  
  while(C0)
  {
    XMin=C0->x;
    YMin=C0->y;
    XMax=C0->x+S->ShootW;
    YMax=C0->y+S->ShootH;

    move_shoot_aux(S,D,C0);
    clash_splitScrShoot(XMin,XMax,YMin,YMax,C0,D);
    clash_ShootBall(S,D);
    C0=C0->next;
  }
}


void move_ball(Sprites* S,dataImageScr* D,Clash_SplitScr* CS,InitSdl *A)
{
  int vx, vy;
  int XMin1,YMin1,XMax1,YMax1;
  int XMin2=D->ship.x;
  int XMax2=D->ship.x+S->ShipW;
  int YMin2=D->ship.y;
  int YMax2=D->ship.y+S->ShipH;
  dataImg* C=D->ball;
 
  D->count0=0;  D->count1=0;  D->count2=0;  D->count3=0;

  while(C != NULL)
    {      
      XMin1=C->x;
      YMin1=C->y;
      XMax1=XMin1+S->BallW;
      YMax1=YMin1+S->BallH;
      vx=C->vx;
      vy=C->vy;

      C->x += vx;
      C->y += vy;

      clash_splitScrPos(XMin1,XMax1,YMin1,YMax1,C,D);
      
      if( XMax1 <= BorderSCR ||
	        XMin1 >= A->WIN_w-BorderSCR || 
	        YMax1 <= BorderSCR || 
	        YMax1 >= A->WIN_h-BorderSCR)
      {
        clash_ballEdgesScr(S,A,C);
      }

      if( YMax1 >= CS->shipBorderYMIN ||
	        XMax1 >= CS->shipBorderXMIN ||
	        XMin1 <= CS->shipBorderXMAX)
      {
        clash_ShipBall(XMin1,XMax1,YMax1,
          XMin2,XMax2,YMin2,YMax2,
          vx,vy,S,C);
      }
      C=C->next;
    }
}

void move(Sprites* S,dataImageScr* D, Clash_SplitScr* CS,InitSdl* A,EventsKeyMouse* E,int* i)
{
  move_ball(S,D,CS,A);
  if(D->NbBallScr>=2)
  {
    clash_sortBallSplitScr(D);
    clash_ball(S,D);
  }

  move_ship(S,D,A,E);
  if(E->key[E->tabkey[E->k_v]])
  {
    if(*i<D->NbShootScr)
    {
      move_shootStart(S,D,*i);
      (*i)++;
    }
  }

  move_shoot(S,D);
  if(move_shootKey_V(D))
    *i=0;

  if(D->NbBallScr==0)
    printf("Vous avez gagner\n");
}
