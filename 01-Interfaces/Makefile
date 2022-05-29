CC = gcc
CFLAGS = -std=c18 -Wall

all: TablasDeConversion.o ConversionTest.o
	$(CC) ConversionTest.o -o ConversionTest $(CFLAGS)
	$(CC) TablasDeConversion.o -o TablasDeConversion $(CFLAGS)

build: Conversion.c ConversionTest.c TablasDeConversion.c
	$(CC) -c Conversion.c -o Conversion.o $(CFLAGS)
	$(CC) -c ConversionTest.c -o ConversionTest.o $(CFLAGS)
	$(CC) -c TablasDeConversion.c -o TablasDeConversion.o $(CFLAGS)