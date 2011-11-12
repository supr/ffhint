CC= clang

LDFLAGS+= -L/usr/lib -lavutil -lavformat -lavcodec -lz -lm 
CFLAGS+=  -g -std=c99 -I/usr/include/libavutil -I/usr/include/libavformat -I/usr/include/libavcodec -I.

SRC=\
	util.c\
	main.c\

OBJ= $(SRC:%.c=%.o)

TARG=	fft

.PHONY: all clean

all: $(TARG)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<

$(TARG): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) 

clean:
	rm -fr $(OBJ) $(TARG)
