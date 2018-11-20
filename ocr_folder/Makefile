CC=gcc
CFLAGS= -g -Wall -Wextra
LDFLAGS= -lm
EXEC=ocr
SRC= Packages/Thomas/TraitementImage.c Packages/Thomas/ImageParser.c Packages/lucas/Binary.c Packages/lucas/Segmentation.c main.c 
OBJ= $(SRC:.c=.o)

all: $(EXEC)

ocr: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: $(SRC)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -fr *.bmp
	rm -rf *.o 
	rm -fr Packages/Thomas/*.o
	rm -fr Packages/Thomas/SaverLoader/*.o
	rm -fr Packages/lucas/*.o

mrproper: clean
	rm -rf $(EXEC)
