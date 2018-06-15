#
#  Configure:
#  source /opt/yocto/poky/1.3.2/environment-setup-core2-poky-linux
#

LDLIB := -fopenmp -lm -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf

app: app.c
	nasm -f elf bzz.asm
	$(CC) -m32 app.c -o app bzz.o $(LDLIB)
	# cp app /opt/tftp

clean:
	rm -rf *.o *~ core app
