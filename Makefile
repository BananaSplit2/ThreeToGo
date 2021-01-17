CC = gcc
CFLAGS = -Wall -Wfatal-errors 
LDFLAGS = -lm -lMLV
OBJFILES = src/token.o src/moteur.o src/graphique.o src/audio.o src/fileio.o src/threetogo.o src/main.o
TARGET = threetogo

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

src/main.o : src/main.c src/threetogo.h src/graphique.h src/audio.h
	$(CC) $(CFLAGS) -o src/main.o -c src/main.c $(LDFLAGS)

src/token.o : src/token.c src/token.h src/threetogo.h
	$(CC) $(CFLAGS) -o src/token.o -c src/token.c $(LDFLAGS)

src/graphique.o : src/graphique.c src/graphique.h src/threetogo.h
	$(CC) $(CFLAGS) -o src/graphique.o -c src/graphique.c $(LDFLAGS)

src/moteur.o : src/moteur.c src/moteur.h src/token.h src/threetogo.h
	$(CC) $(CFLAGS) -o src/moteur.o -c src/moteur.c $(LDFLAGS)

src/threetogo.o : src/threetogo.c src/threetogo.h src/token.h src/graphique.h src/moteur.h src/token.h
	$(CC) $(CFLAGS) -o src/threetogo.o -c src/threetogo.c $(LDFLAGS)

src/audio.o : src/audio.c src/audio.h
	$(CC) $(CFLAGS) -o src/audio.o -c src/audio.c $(LDFLAGS)

src/fileio.o : src/fileio.c src/fileio.h
	$(CC) $(CFLAGS) -o src/fileio.o -c src/fileio.c $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~