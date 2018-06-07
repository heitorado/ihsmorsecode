#
#  Configure:
#  source /opt/yocto/poky/1.3.2/environment-setup-core2-poky-linux
#

app: app.c
	$(CC) app.c -o app -fopenmp
	# cp app /opt/tftp

clean:
	rm -rf *.o *~ core app
