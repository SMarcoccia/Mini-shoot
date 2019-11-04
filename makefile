CC=gcc

COPTS= -c -O3 -g -DDEBUG -W -Wall -Werror -pedantic

OBJS=main.o Init_sdl.o event.o tools.o InitImages.o sprites.o clash.o move.o blit.o

shoot : $(OBJS)
	$(CC) -lmingw32 $(OBJS) -o shoot -L/mingw/lib -lSDLmain -lSDL -lmingw32

main.o : main.c Init_sdl.h event.h tools.h InitImages.h sprites.h clash.h move.h blit.h
	$(CC) $(COPTS) -c main.c

Init_sdl.o : Init_sdl.c Init_sdl.h tools.h
	$(CC) $(COPTS) -c Init_sdl.c

event.o : event.c event.h tools.h
	$(CC) $(COPTS) -c event.c

tools.o : tools.c tools.h
	$(CC) $(COPTS) -c tools.c

InitImages.o : InitImages.c InitImages.h tools.h Init_sdl.h sprites.h 
	$(CC) $(COPTS) -c InitImages.c

blit.o : blit.c tools.h Init_sdl.h sprites.h event.h InitImages.h
	$(CC) $(COPTS) -c blit.c

clash.o : clash.c tools.h sprites.h Init_sdl.h InitImages.h move.h
	$(CC) $(COPTS) -c clash.c

move.o : move.c tools.h sprites.h Init_sdl.h event.h InitImages.h clash.h blit.h
	$(CC) $(COPTS) -c move.c

sprites.o : sprites.c sprites.h tools.h InitImages.h
	$(CC) $(COPTS) -c sprites.c

.PHONY : clean mrproper

clean : 
	del -f *.o *~ *.stackdump 

mrproper : clean
	del *.exe 
