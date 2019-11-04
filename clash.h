#ifndef __CLASH_H__
#define __CLASH_H__

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<time.h>
#include<SDL/SDL.h>


#include"tools.h"
#include"Init_sdl.h"
#include"sprites.h"
#include"InitImages.h"


typedef struct Clash_SplitScr
{
  int tabIndex[4][NB_BALLSCR];
  int tabLen[4];
  u32 j;
  u32 j1;
  u32 j2;
  u32 j3;
  int shipBorderXMIN;
  int shipBorderXMAX;
  int shipBorderYMIN;
}Clash_SplitScr;

extern void clash_sortBallSplitScr(dataImageScr* D);
extern bool clash_AABB(int XMin1,int XMax1,int YMin1,int YMax1,int XMin2,int XMax2,int YMin2,int YMax2/*,Sprites* S,dataImageScr* D, Clash_SplitScr* CS,int i*/);
extern bool clashColorZoneL(Sprites* S,int Hzone, int WzoneL, int StartZoneBallxL, int StartZoneBally,int StartZoneShipxL, int StartZoneShipy);
extern bool clashColorZoneR(Sprites* S,int Hzone, int WzoneR, int StartZoneBallxR, int StartZoneBally,int StartZoneShipxR, int StartZoneShipy);
extern void clash_ShipBall(int XMin1,int XMax1,int YMax1,int XMin2,int XMax2,int YMin2,int YMax2,int vx,int vy,Sprites* S,dataImg* C);
extern void clashBall_AABB(Sprites* S,dataImageScr* D,Clash_SplitScr* CS);
extern void clash_ShootBall(Sprites* S,dataImageScr* D);
extern void clash_splitScrShoot(int XMin,int XMax,int YMin,int YMax,dataImg* C,dataImageScr* D);
extern void clash_ballAux(Sprites* S,dataImg* C1,dataImg* C2);
extern void clash_ball(Sprites* S,dataImageScr* D);
extern void clash_splitScrPos(int XMin,int XMax,int YMin,int YMax,dataImg* C,dataImageScr* D);
extern bool clash_BallEdgesScrL(dataImg* C);
extern bool clash_BallEdgesScrR(Sprites* S,InitSdl* A,dataImg* C);
extern bool clash_BallEdgesScrD(dataImg* C);
extern bool clash_BallEdgesScrU(Sprites* S,InitSdl* A,dataImg* C);
extern void clash_ballEdgesScr(Sprites* S,InitSdl* A,dataImg* C);
extern Clash_SplitScr* clash_init_SplitSrc(Sprites* S,dataImageScr* D);
extern void Free_clash_SplitSrc(Clash_SplitScr* S);
#endif


