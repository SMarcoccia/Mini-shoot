
#include"tools.h"

/*liste chainé"*/
/*
- creation d'une liste
- ajout d'une cellule en entête
- suppression
*/
/*index max == 0*/

bool lapsTime(TimeImgAnim** T,int milliSec,int index)
{
  T[index]->time=SDL_GetTicks();

  if(T[index]->time-T[index]->lastTime>=milliSec)
  {
    T[index]->lastTime=T[index]->time;
    return TRUE;
  }
  return FALSE;
}

int TimeAnim(TimeImgAnim** T,int nbSpr,int milliSec,int index)
{
  T[index]->time=SDL_GetTicks();
  
  if(T[index]->time-T[index]->lastTime>=milliSec)
  {
    T[index]->i++;
    T[index]->lastTime=T[index]->time;
    if(T[index]->i==nbSpr)
      T[index]->i=0;
  }
  return T[index]->i;
}

TimeImgAnim** init_TimeAnim(TimeImgAnim** T,int nbTime)
{
  int ii;
  T=malloc(nbTime*sizeof*T);
  for(ii=0;ii<nbTime;ii++)
  {
    T[ii]=malloc(sizeof*(T[ii]));
    T[ii]->time=0;
    T[ii]->lastTime=0;
    T[ii]->index=0;
    T[ii]->milliSec=0;
    T[ii]->i=0;
  }
  return T;
}

void Free_TimeAnim(TimeImgAnim** T,int nbTime)
{
  int i;
  for(i=0;i<nbTime;i++)
    Free_Alloc(T[i]);
  Free_Alloc(T);
}

void tools_strerror(char *S)
{
  fprintf(stderr,S,strerror(errno));
}

void* malloc_error(void *ptr,char* S)
{
  if(ptr==NULL)
  {
    if(S!=NULL)
      tools_strerror(S);
    else      
      tools_strerror("The allocation failed, the block(s) was released. \n");
    Free_Alloc(ptr);
    return NULL;
  }
  return ptr;
}

SDL_Rect** SDL_Rect_alloc_2d(SDL_Rect** ptr,int size1,int size2)
{
  int i;
  assert(size1>0);
  assert(size2>0);
 
  if( !(ptr=malloc(size1*sizeof*ptr)))
  {
    malloc_error(ptr,NULL);
    return NULL;
  }

  for(i=0;i<size1;i++)
  {
    if( !(ptr[i]=malloc(size2*sizeof(**ptr))))
    {
      for(i=i-1;i>=0;i--)
        malloc_error(ptr[i],NULL);
      Free_Alloc(ptr);
      return NULL;
    }
  }
  return ptr;
}

void **alloc(size_t _ptr,int size)
{
  void **ptr=NULL;
  assert(size>0);

  return ptr=malloc_error(calloc(size,sizeof(_ptr)),NULL);
}

void *alloc_ptr(size_t _ptr,int size)
{
  void *ptr=NULL;
  assert(size>0);

  return ptr=malloc_error(calloc(size,sizeof(_ptr)),NULL);
}


void Free_Alloc_2d(void **_ptr,int size)
{
  int i;
  void **ptr = (void**) _ptr;
  for(i=0;i<size;i++)
  {
    free(ptr[i]);
    ptr[i]=NULL;
  }

  free(ptr);
  ptr=NULL;
}

void Free_Alloc(void* _ptr)
{
  void *ptr = (void*) _ptr;
  free(ptr);
  ptr=NULL;
}

void My_SDL_FreeSurface(SDL_Surface *I)
{
  SDL_FreeSurface(I);
}




