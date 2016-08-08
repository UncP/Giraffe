###			https://www.github.com/UncP/Mini_Ray_Tracer			###

CPP 		 = g++
CPPFLAGS = -std=c++11 -Wall -O3 -fopenmp
LDFLAGS  = -lSDL -lSDLmain -lpng

DIR 		 = math utility object

all:module

module:
	for dir in $(DIR); do \
		(cd $$dir && make && cd ..); \
	done

clean:
	for dir in $(DIR); do \
		(cd $$dir && make clean) || continue ; \
	done
