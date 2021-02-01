# the compiler: gcc for C program, define as g++ for C++
CC = gcc
LD = pq

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -l$(LD)

# the build target executable:
TARGET = backlash

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c machine.c

clean:
	$(RM) $(TARGET)