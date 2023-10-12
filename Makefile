CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: walk2 burger_dash

walk2: walk2.cpp log.cpp cmcdaniel.cpp cmcdaniel.h cestes.cpp cestes.h mjimenez.cpp mjimenez.h jbaltazarrob.cpp jbaltazarrob.h
	g++ $(CFLAGS) walk2.cpp log.cpp cmcdaniel.cpp cestes.cpp mjimenez.cpp jbaltazarrob.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -owalk2

burger_dash: burger_dash.cpp log.cpp cmcdaniel.cpp cmcdaniel.h cestes.cpp cestes.h mjimenez.cpp mjimenez.h jbaltazarrob.cpp jbaltazarrob.h
	g++ $(CFLAGS) burger_dash.cpp cmcdaniel.cpp cestes.cpp mjimenez.cpp jbaltazarrob.cpp libggfonts.a -Wall -oburger_dash -lX11 -lGL -lGLU -lm -lc

clean:
	rm -f walk2 burger_dash

