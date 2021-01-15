CC = gcc
CFLAGS = -Wall -Wfatal-errors 
LDFLAGS = -lm -lMLV
OBJFILES = src/token.o src/moteur.o src/graphique.o src/threetogo.o src/main.o
TARGET = threetogo

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~