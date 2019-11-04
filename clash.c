
#include "clash.h"

void clash_sortBallSplitScr(dataImageScr* D)
{
  dataImg* C=NULL;
  dataImg* F=NULL;
  int i,j;
  int nb=D->NbBallScr-1;
  int nb1=nb;

  for(j=0;j<nb;j++)
	{
		C=D->ball;
		F=D->ball;

		for(i=0;i<nb1;i++)
		{ 
			if(C->ScrPos > C->next->ScrPos)
			{
				if(i==0)
				{
					D->ball->head=FALSE;
					D->ball=C->next;
					D->ball->head=TRUE;
				}

				F->next=C->next;
				F=C->next;
				C->next=C->next->next;
				F->next=C;
				C=F;
			}
			else
				F=C;

			C=C->next;
		}
		nb1--;
	}
}


void clash_ShootBall(Sprites* S,dataImageScr* D)
{
  int value=0,PtLife=4;
  int XMin1,XMax1,YMin1,YMax1;
  int XMin2,XMax2,YMin2,YMax2;
  dataImg* shoot=D->shoot;
  dataImg* C=D->ball;
  dataImg* tmp=D->ball;

  while(C!=NULL)
	{
		while(shoot!=NULL)
		{
			XMin1=shoot->x;
			XMax1=shoot->x+S->ShootW;
			YMin1=shoot->y;
			YMax1=shoot->y+S->ShootH;
				
			XMin2=C->x;
			XMax2=C->x+S->BallW;
			YMin2=C->y;
			YMax2=C->y+S->BallH;

			if(shoot->ScrPos==C->ScrPos && shoot->y < D->ship.y)
			{
				value=clash_AABB(XMin1,XMax1,YMin1,YMax1,
						XMin2,XMax2,YMin2,YMax2);

				if(value)
				{
					C->count++;
					shoot->y=-S->ShootH-1;
					if(C->count==PtLife)
					{	    
						if(C->head)
						{	
							if(D->NbBallScr>1)
							{
								D->ball=C->next;
								D->ball->head=TRUE;
								Free_dataImgScr(C);
								D->NbBallScr--;
								return;
							}
							else if(D->NbBallScr==1)
							{
								Free_dataImgScr(D->ball);
								D->NbBallScr--;
								return;
							}
						}
						else
						{
							tmp->next=C->next;
							Free_dataImgScr(C);
							D->NbBallScr--;
							return;
						}
					}
				}
			}
			shoot=shoot->next;
		} 
		tmp=C;
		C=C->next;
		shoot=D->shoot;
	}   
}

bool clash_AABB(int XMin1,int XMax1,int YMin1,int YMax1,int XMin2,int XMax2,int YMin2,int YMax2/*,prites* S,dataImageScr* D, Clash_SplitScr* CS,int i*/)
 {
   if(XMax1>XMin2 && XMin1<XMax2 && YMax1>YMin2 && YMin1<YMax2)
     return TRUE;
          
   else 
     return FALSE;
 }

bool clashColorZoneL(Sprites* S,int Hzone, int WzoneL, int StartZoneBallxL, int StartZoneBally,int StartZoneShipxL, int StartZoneShipy)
{
  int ii,jj;
  u8 ColorPixBall;
  u8 ColorPixShip; 
  for(jj=0;jj<Hzone;jj++)
	{
		for(ii=0;ii<WzoneL;ii++)
		{
			ColorPixBall=*((u8*)S->CpySpr->pixels+StartZoneBallxL + StartZoneBally*S->CpySpr->pitch+ii+jj*S->CpySpr->pitch);
					
			ColorPixShip=*((u8*)S->CpySpr->pixels+StartZoneShipxL+StartZoneShipy*S->CpySpr->pitch+ii+jj*S->CpySpr->pitch);

			if(ColorPixBall!=ALPHA1 && ColorPixShip!=ALPHA1)
				return TRUE;
		}
	}
  return FALSE;
}

bool clashColorZoneR(Sprites* S,int Hzone, int WzoneR, int StartZoneBallxR, int StartZoneBally,int StartZoneShipxR, int StartZoneShipy)
{
  int ii,jj;
  u8 ColorPixBall;
  u8 ColorPixShip; 

  for(jj=0;jj<Hzone;jj++)
	{
		for(ii=0;ii<WzoneR;ii++)
		{
			ColorPixBall=*((u8*)S->CpySpr->pixels+StartZoneBallxR+StartZoneBally*S->CpySpr->pitch+ii+jj*S->CpySpr->pitch);
					
			ColorPixShip=*((u8*)S->CpySpr->pixels+StartZoneShipxR+StartZoneShipy*S->CpySpr->pitch+ii+jj*S->CpySpr->pitch);

			if(ColorPixBall!=ALPHA1 && ColorPixShip!=ALPHA1)
				return TRUE;
		}
	}
  return FALSE;
}

void clash_ShipBall(int XMin1,int XMax1,int YMax1,int XMin2,int XMax2,int YMin2,int YMax2,int vx,int vy,Sprites* S,dataImg* C)
{ 
  int a=0;

  int BallCX=XMin1+S->BallW/2; /*C = Center Ball*/
  int ShipCX=XMin2+S->ShipW/2;
  int SideShipL=XMin2+ValueShipX;/*Side of ship at left*/
  int SideShipR=XMax2-ValueShipX;

  int WzoneL=XMax1-XMin2;
  int WzoneR=XMax2-XMin1;
  int Hzone=YMax1-YMin2;

  int StartZoneBallxL=S->ClipSpr[grey].x+S->BallW-WzoneL;
  int StartZoneBallxR=S->ClipSpr[grey].x;
  int StartZoneShipxL=S->ClipSpr[ship].x;
  int StartZoneShipxR=S->ClipSpr[ship].x+S->ShipW-WzoneR;

  int StartZoneBally=S->ClipSpr[grey].y+S->BallH-Hzone;
  int StartZoneShipy=S->ClipSpr[ship].y;

  if(YMax1 >= YMin2 &&
     YMax1 <= YMax2 &&
     XMax1 > SideShipL &&
     XMin1 < SideShipR)
	{
		/*Down side left*/
		if(BallCX <= ShipCX-ValueShipX)
		{
			if(vx>0 && vy>0)
			{
				C->vx =- vx;
				C->vy =- vy;
			}
			else if(vx<0 && vy>0)
				C->vy =- vy;
		}

		/*Down side right*/
		else if(BallCX >=ShipCX+ValueShipX)
		{
			if(vx>0 && vy>0)
				C->vy =- vy;

			else if(vx<0 && vy>0)
			{
				C->vx =- vx;
				C->vy =- vy;
			}
		}
		/*Down Center*/
		else if(BallCX > ShipCX-ValueShipX && BallCX <=ShipCX+ValueShipX)
		{
			if(vx>0 && vy>0)
			{
				C->vx = vx;
				C->vy =-vy;
			}

			else if(vx<0 && vy>0)
			{
				C->vx =-vx;
				C->vy =-vy;
			}
		}
	}

  /*Left*/
  else if(YMax1 >= YMin2 &&
	  YMax1 <= YMax2 &&
	  XMax1 >= XMin2 &&
	  XMax1 <= SideShipL)
	{ 
		if(vx>0 && vy>0)
		{                                    
			a=clashColorZoneL(S,Hzone,WzoneL,StartZoneBallxL,StartZoneBally,StartZoneShipxL,StartZoneShipy);
			if(a)
			{
				C->vx =- vx;	
				C->vy =- vy;
			}
		}
	}

/*Right*/
  else if(YMax1 >= YMin2 &&
	  YMax1 <= YMax2 &&
	  XMin1 <= XMax2 &&
	  XMin1 >= SideShipR)
	{ 
		if(vx<0 && vy>0)
		{                                    
			a=clashColorZoneR(S,Hzone,WzoneR,StartZoneBallxR,StartZoneBally,StartZoneShipxR,StartZoneShipy);
			if(a)
			{
				C->vx =- vx;	
				C->vy =- vy;
			}
		}
	}
}

/*replacement of ball*/
bool clash_BallEdgesScrL(dataImg* C)
{
  if(C->x <= 0 && C->vx<0)
    return TRUE;
  
  else 
    return FALSE;
}

bool clash_BallEdgesScrR(Sprites* S,InitSdl* A,dataImg* C)
{
  if(C->x+S->BallW >= A->WIN_w && C->vx>0)
    return TRUE;
  
  else 
    return FALSE;
}

bool clash_BallEdgesScrD(dataImg* C)
{
  if(C->y<= 0 && C->vy<0)
    return TRUE;
  
  else 
    return FALSE;
}

bool clash_BallEdgesScrU(Sprites* S,InitSdl* A,dataImg* C)
{
  if(C->y+S->BallH >= A->WIN_h && C->vy>0)
    return TRUE;
  
  else 
    return FALSE;
}

void clash_ballEdgesScr(Sprites* S,InitSdl* A,dataImg* C)
{
  if(clash_BallEdgesScrL(C))
	{
		C->x=0;
		C->vx =- C->vx;
	}

  else if(clash_BallEdgesScrR(S,A,C))
	{
		C->x=A->WIN_w-S->BallW;
		C->vx =- C->vx;
	}

  else if(clash_BallEdgesScrD(C))
	{
		C->y=0;
		C->vy =- C->vy;
	}

  else if(clash_BallEdgesScrU(S,A,C))
	{
		C->y=A->WIN_h-S->BallH;
		C->vy=-C->vy;
	}
}

void clash_ballAux(Sprites* S,dataImg* C1,dataImg* C2)
{
  int r1=S->BallW/2;
  int r2=S->BallW/2;
  int r=(r1+r2)*(r1+r2);

  int cx1 = C1->x+r1;
  int cy1 = C1->y+r1;
  int cx2 = C2->x+r2;
  int cy2 = C2->y+r2;
      
  int vx1 = C1->vx;
  int vy1 = C1->vy;
  int vx2 = C2->vx;
  int vy2 = C2->vy;

  if(((cx1-cx2)*(cx1-cx2))+((cy1-cy2)*(cy1-cy2))<=r)
	{
		if(cx1>cx2 && cy1>cy2)
		{
			if(vx2>0 && vy2>0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;
			}
			else if(vx2<0 && vy2<0)
			{
				C1->vx=-vx1;
				C2->vy=-vy1;
			}
			else if(vx2<0 && vy2>0)
			{
				C1->vy=-vy1;
				C2->vy=-vy2;
			}
			else if(vx2>0 && vy2<0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;
			}
		}

		else if(cx1<cx2 && cy1>cy2)
		{
			if(vx2>0 && vy2>0)
			{
				C1->vy=-vy1;
				C2->vy=-vy2;
			}
			else if(vx2<0 && vy2<0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;
			}
			else if(vx2<0 && vy2>0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;		    
			}
			else if(vx2>0 && vy2<0)
			{
				C1->vx=-vx1;
				C2->vy=-vy1;		    
			}
		}

		else if(cx1<cx2 && cy1<cy2)
		{
			if(vx2>0 && vy2>0)
			{
				C1->vx=-vx1;
				C2->vy=-vy1;
			}
			else if(vx2<0 && vy2<0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;
			}
			else if(vx2<0 && vy2>0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;
			}
			else if(vx2>0 && vy2<0)
			{
				C1->vy=-vy1;
				C2->vy=-vy2;
			}
		}

		else if(cx1>cx2 && cy1<cy2)
		{
			if(vx2>0 && vy2>0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;
			}
			else if(vx2<0 && vy2<0)
			{
				C1->vy=-vy1;
				C2->vy=-vy2;
			}
			else if(vx2<0 && vy2>0)
			{
				C1->vx=-vx1;
				C2->vy=-vy1;
			}
			else if(vx2>0 && vy2<0)
			{
				C1->vx=-vx1;
				C2->vx=-vx2;
			}
		}
	}
}

void clash_ball(Sprites* S,dataImageScr* D)
{
  int i;
  bool stop=TRUE;
  dataImg* C1=D->ball;
  dataImg* C2=D->ball->next;

  if(D->count0>1)
	{
		while(stop)
		{
			stop=FALSE;
			for(i=1;i<D->count0;i++)
			{
				clash_ballAux(S,C1,C2);
				C2=C2->next;
				stop=TRUE;
			}
			D->count0--;
			C1=C1->next;
			C2=C1->next;
			if(C2==NULL)
				stop=FALSE;
		}
	}

  if(D->count1>1)
	{
		stop=TRUE;
		while(stop)
		{
			stop=FALSE;
			for(i=1;i<D->count1;i++)
				{
					clash_ballAux(S,C1,C2);
					C2=C2->next;
					stop=TRUE;
				}
			D->count1--;
			C1=C1->next;
			C2=C1->next;
			if(C2==NULL)
				stop=FALSE;
		}
	}

  if(D->count2>1)
	{
		stop=TRUE;
		while(stop)
		{
			stop=FALSE;
			for(i=1;i<D->count2;i++)
			{
				clash_ballAux(S,C1,C2);
				C2=C2->next;
				stop=TRUE;
			}
			D->count2--;
			C1=C1->next;
			C2=C1->next;
			if(C2==NULL)
				stop=FALSE;
		}
	}

  if(D->count3>1)
	{
		stop=TRUE;
		while(stop)
		{
			stop=FALSE;
			for(i=1;i<D->count3;i++)
				{
					clash_ballAux(S,C1,C2);
					C2=C2->next;
					stop=TRUE;
				}
			D->count3--;
			C1=C1->next;
			C2=C1->next;
			if(C2==NULL)
				stop=FALSE;
		}
	}
}
    


/*No utility*/
void clashBall_AABB(Sprites* S,dataImageScr* D,Clash_SplitScr* CS)
{
  int h, i, j;
  int XMin1, XMax1, YMin1, YMax1;
  int XMin2, XMax2, YMin2, YMax2;
  int vx1, vx2, vy1, vy2;
  dataImg* C=D->ball;

  for(j=0;j<4;j++)
	{
    for(i=0;i<CS->tabLen[j];i++)
		{
      for(h=0;h<CS->tabLen[j];h++)
			{
				XMin1 = C->x;
				YMin1 = C->y;
				XMin2 = D->ball->next->x;
				YMin2 = D->ball->next->y;

				XMax1 = C->x+S->BallW;
				YMax1 = C->y+S->BallH;
				XMax2 = D->ball->next->x+S->BallW;
				YMax2 = D->ball->next->y+S->BallH;

				vx1 = C->vx;
				vy1 = C->vy;
				vx2 = D->ball->next->vx;
				vy2 = D->ball->next->vy;

				/*side right*/
				if(XMin1<=XMax2 && XMin1>=XMin2 && YMax1>=YMin2 && YMin1<=YMax2)
				{
					if(vx1<0 && vx2>0)
					{
						C->vx   =- C->vx;
						D->ball->next->vx =- D->ball->next->vx;
					}
					else
						D->ball->next->vx =- D->ball->next->vx;
				}
				
				/*side left*/
				if(XMax1>=XMin2 && XMax1<=XMax2 && YMin1<=YMax2 && YMax1>=YMin2)
				{
					if(vx1>0 && vx2<0) 
					{
						C->vx   =- C->vx;
						D->ball->next->vx =- D->ball->next->vx;
					}
					else
						C->vx   =- C->vx;
				}
				
				/*side down*/
				if(YMax1>=YMin2  && YMax1<=YMax2 && XMin1<XMax2 && XMax1>XMin2)
				{
					if(vy1>0 && vy2<0)
					{
						C->vy   =- C->vy;
						D->ball->next->vy =- D->ball->next->vy;
					}
					else 
						D->ball->next->vy =- D->ball->next->vy;
				}
						
				/*side up*/
				if(YMin1<=YMax2 && YMin1>=YMin2 && XMin1<XMax2 && XMax1>XMin2)
				{
					if(vy1<0 && vy2>0)
					{
						C->vy   =- C->vy;
						D->ball->next->vy =- D->ball->next->vy;
					}
					else
						C->vy =- C->vy;
				}
      }
    }
  }
}

/*Warning basé sur coordonnée origin SDL*/
void clash_splitScrShoot(int XMin,int XMax,int YMin,int YMax,dataImg* C,dataImageScr* D)
{
  /*corner lower Right*/
  if(XMax >= HALF_W && YMin <= HALF_H)
    C->ScrPos=0;

  /*corner lower Left*/
  else if(XMin <= HALF_W && YMin <= HALF_H)
    C->ScrPos=1;
    
  /*corner superior Left*/
  else if(XMin <= HALF_W && YMax >= HALF_H && C->y < D->ship.y)
    C->ScrPos=2;
    
  /*corner superior Right*/
  else if(XMax >= HALF_W && YMax >= HALF_H && C->y < D->ship.y)
    C->ScrPos=3;
}

/*découpage écran en 4 recense le nombre de balle dans les 4 partie de l'écran*/
void clash_splitScrPos(int XMin,int XMax,int YMin,int YMax,dataImg* C,dataImageScr* D)
{
  /*corner lower Right*/
  if(XMax >= HALF_W && YMin <= HALF_H)
    {
      C->ScrPos=0;
      ++D->count0;
    }

  /*corner lower Left*/
  else if(XMin <= HALF_W && YMin <= HALF_H)
    {
      C->ScrPos=1;
      ++D->count1;
    }


  /*corner superior Left*/
  else if(XMin <= HALF_W && YMax >= HALF_H)
        {
      C->ScrPos=2;
      ++D->count2;
    }

  /*corner superior Right*/
  else if(XMax >= HALF_W && YMax >= HALF_H)
    {
      C->ScrPos=3;
      ++D->count3;
    }
}

Clash_SplitScr* clash_init_SplitSrc(Sprites* S,dataImageScr* D)
{
  Clash_SplitScr* CS=malloc_error((CS=malloc(sizeof*CS)),NULL);
  CS->shipBorderXMIN = D->ship.x-BorderShip;
  CS->shipBorderXMAX = D->ship.x+S->ShipW+BorderShip;
  CS->shipBorderYMIN = D->ship.y-BorderShip;

  return CS;
}

void Free_clash_SplitSrc(Clash_SplitScr* CS)
{
  Free_Alloc(CS);
}
