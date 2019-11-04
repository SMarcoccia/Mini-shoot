#ifndef __EVENT_H__
#define __EVENT_H__

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<errno.h>
#include<string.h>
#include<time.h>

#include"tools.h"

#define NB_KEY 4

typedef struct EventsKeyMouse
{
  char key[SDLK_LAST];
  int tabkey[NB_KEY];
  int k_left,k_right,k_v;
  int k_p;
}EventsKeyMouse;

extern void Free_events(EventsKeyMouse* E);
extern EventsKeyMouse* init_events(void);
extern bool loop_event(EventsKeyMouse* E);
#endif
