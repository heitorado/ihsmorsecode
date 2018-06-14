#
#  Configure:
#  source /opt/yocto/poky/1.3.2/environment-setup-core2-poky-linux
#

app: app.c
	nasm -f elf bzz.asm
	$(CC) -m32 app.c -o app bzz.o -fopenmp -lm
	# cp app /opt/tftp

clean:
	rm -rf *.o *~ core app
