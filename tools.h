#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <SDL/SDL.h>

#define rc1 printf("\n")
#define rc2 printf("\n\n")

#define TRUE -1
#define FALSE 0
#define LINE_ERROR printf("Line : %d\n",__LINE__)
#define FILE_ERROR printf("File : %s\n",__FILE__)

typedef char bool;
typedef unsigned int color;

typedef uint8_t u8; 
typedef uint16_t u16; 
typedef uint32_t u32; 
typedef int8_t s8; 
typedef int16_t s16; 
typedef int32_t s32; 


typedef struct TimeImgAnim
{
  int time;
  int lastTime;
  /*représente le nbre de case dans un tableau de struct pour chaque fonction utilisé si on utilise
    une fonction timeanim et une fonction lapstime alors index vaudra réspéctivement 0 et 1*/
  int index; 
  int milliSec;
  int i;
}TimeImgAnim;


extern bool lapsTime(TimeImgAnim** T,int milliSec,int index);
/*index représente la position dans un tableau de l'image qui sera blitéea la même position elle 
  et ses soeurs exemple pour créer un flash*/
extern int TimeAnim(TimeImgAnim** T,int nbSpr,int milliSec,int index);
/*nb de struct time*/
extern TimeImgAnim** init_TimeAnim(TimeImgAnim** T,int nbTime);
extern int sdl_error(void *ptr,char *S);


extern void tools_strerror(char *S);
extern void *malloc_error(void *ptr,char* S);
extern void **malloc_error_2d(void **ptr,int size);

extern void *alloc_ptr(size_t _ptr,int size);
extern void **alloc(size_t ptr,int size);

extern int size_string(const char *S);
extern char compared_size_string(const char *S, const char *J);
extern bool compared_string_size_equal(const char *S, const char *J);
extern int read_int_text(FILE *F);
extern void read_copy_string(char *S, FILE *F);
extern char read_next_regular_char(FILE *F,char c);
extern void read_next_digit(FILE *F,char c);

extern void My_SDL_FreeSurface(SDL_Surface* surf);
extern void Free_TimeAnim(TimeImgAnim** T,int nbTime);
extern void Free_Alloc_2d(void **_ptr,int size);
extern void Free_Alloc(void *ptr);

#endif
