#===================================================================
#
#								Makefile
#
#===================================================================

# set compiler and options
GCC=g++
GCC_CFLAGS=-O3 -mtune=native -funroll-all-loops -fexpensive-optimizations -funroll-loops -std=c++11 -ffast-math
GCC_LDFLAGS= -lstdc++

# Objects
OBJECTS= pi.o

# Define the executable
EXECUTABLE=pi.exe

# Set default make target in GNU make > v3.81
.DEFAULT_GOAL := all

# make serial version by default
all: serial

# Serial target
serial: $(OBJECTS)
	$(GCC) $(GCC_LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): %.o: %.cpp
	$(GCC) -c -o $@ $(GCC_CFLAGS) $(OPTIONS) $<

clean:
	@rm -f *.o
