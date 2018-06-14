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
	file_obj = open(FILENAME, "a+")

	ser = serial.Serial(PORT, RATE)
	val = ser.readline()
	file_obj.write(val)
	ser.close()

	file_obj.close()

	print(val)