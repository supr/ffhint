CC= clang

LDFLAGS+= -L/usr/lib -lavutil -lavformat -lavcodec -lz -lm 
CFLAGS+=  -g -std=c99 -I/usr/include/libavutil -I/usr/include/libavformat -I/usr/include/libavcodec -I. \
	-pedantic -fPIC -Wall -Werror -Wextra

SRC=\
	util.c\
	main.c\

HEADERS= $(shell ls *.h)

OBJ= $(SRC:%.c=%.o)

TARG=	ffhint

.PHONY: all clean

all: $(TARG)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $(CFLAGS) $<

$(TARG): $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) 

clean:
	rm -fr $(OBJ) $(TARG)
