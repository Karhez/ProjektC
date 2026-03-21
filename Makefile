CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm
 
TARGET = graph
 
SRCS = main.c algorytmy.c danePob.c graf.c
 
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)
 
clean:
	rm -f $(TARGET)