# the compiler to use
CC = gcc
  
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -pedantic -ansi -std=c99
  
#files to link:
LFLAGS = -fopenmp
  
# the name to use for both the target source file, and the output file:
TARGET  = q1a
TARGETA = q1b
TARGETB = q2a
TARGETC = q2b
TARGETD = q2c
TARGETE = q3a
TARGETF = q3b
TARGETG = q3c
TARGETH = q4a
TARGETI = q4b
TARGETJ = q4c

.PHONY : clean

all: $(TARGET)  $(TARGETA) $(TARGETB) $(TARGETC) $(TARGETD) $(TARGETE) $(TARGETF) $(TARGETG) $(TARGETH) $(TARGETI) $(TARGETJ)
	  
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET) $(LFLAGS)

$(TARGETA): $(TARGETA).c
	$(CC) $(CFLAGS) $(TARGETA).c -o $(TARGETA) $(LFLAGS)

$(TARGETB): $(TARGETB).c
	$(CC) $(CFLAGS) $(TARGETB).c -o $(TARGETB) $(LFLAGS)

$(TARGETC): $(TARGETC).c
	$(CC) $(CFLAGS) $(TARGETC).c -o $(TARGETC) $(LFLAGS)

$(TARGETD): $(TARGETD).c
	$(CC) $(CFLAGS) $(TARGETD).c -o $(TARGETD) $(LFLAGS)

$(TARGETE): $(TARGETE).c
	$(CC) $(CFLAGS) $(TARGETE).c -o $(TARGETE) $(LFLAGS)

$(TARGETF): $(TARGETF).c
	$(CC) $(CFLAGS) $(TARGETF).c -o $(TARGETF) $(LFLAGS)

$(TARGETG): $(TARGETG).c
	$(CC) $(CFLAGS) $(TARGETG).c -o $(TARGETG) $(LFLAGS)

$(TARGETH): $(TARGETH).c
	$(CC) $(CFLAGS) $(TARGETH).c -o $(TARGETH) $(LFLAGS)

$(TARGETI): $(TARGETI).c
	$(CC) $(CFLAGS) $(TARGETI).c -o $(TARGETI) $(LFLAGS)

$(TARGETJ): $(TARGETJ).c
	$(CC) $(CFLAGS) $(TARGETJ).c -o $(TARGETJ) $(LFLAGS)

clean : 
	-rm  $(TARGET)  $(TARGETA) $(TARGETB) $(TARGETC) $(TARGETD) $(TARGETE) $(TARGETF) $(TARGETG) $(TARGETH) $(TARGETI) $(TARGETJ)
