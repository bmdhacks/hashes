
#CC = gcc

CFLAGS = -Wall -O2
INCLUDES = -I/opt/twitter/Cellar/judy/1.0.5/include
LDFLAGS = -L/opt/twitter/Cellar/judy/1.0.5/lib
LIBS = -lJudy

SRCS = binarytree.c main.c hash.c
OBJS = $(SRCS:.c=.o)

benchmark:: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o benchmark $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ benchmark
