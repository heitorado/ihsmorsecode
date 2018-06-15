import serial

FILENAME = "py-c"
PORT = "/dev/ttyUSB0" 
RATE = 9600

print("WARNING!")
print("Using as PORT COM: " + PORT)

open(FILENAME, 'w').close() # wipe file

ser = serial.Serial(PORT, RATE)
print("SERIAL NAME: " + ser.name)
ser.close()

while (True):

	ser = serial.Serial(PORT, RATE)
	val = str( ser.readline().strip() )
	ser.close()

	if (val != ''):
		file_obj = open(FILENAME, "w")
		file_obj.write(val)
		file_obj.close()

	print(val)