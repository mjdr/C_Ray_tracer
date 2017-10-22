FRAME_RATE=30
FRAME_WIDTH=1280
FRAME_HEIGHT=720
TIME=30


flags=-D FRAME_RATE=$(FRAME_RATE) -D FRAME_WIDTH=$(FRAME_WIDTH) -D FRAME_HEIGHT=$(FRAME_HEIGHT)\
	-D TIME=$(TIME)
CC= gcc -Werror $(flags)
FF_PARAMS=-f rawvideo -pixel_format rgb0 -video_size $(FRAME_WIDTH)x$(FRAME_HEIGHT) -framerate $(FRAME_RATE) -i pipe:0

all: play


make: clear compile
	
compile:
	$(CC) -c *.c
	
	$(CC) -o main main.o video.o util.o geometry.o -lm
run:
	./main

clear:
	rm -f main
	rm -f *.o

play: make
	./main | ffplay $(FF_PARAMS)

store: make
	rm -f out.mp4
	./main | ffmpeg $(FF_PARAMS) out.mp4
