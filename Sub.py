import pygame
import serial
from time import sleep

try:
    ser = serial.Serial('/dev/ttyUSB0', timeout=None, baudrate=9600, rtscts=False, dsrdtr=False);
except serial.SerialException:
    try:
        ser = serial.Serial('/dev/ttyUSB1', timeout=None, baudrate=9600, rtscts=False, dsrdtr=False);
    except serial.SerialException:
        try:
            ser = serial.Serial('/dev/ttyUSB2', timeout=None, baudrate=9600, rtscts=False, dsrdtr=False);
        except serial.SerialException:
            try:
                ser = serial.Serial('/dev/ttyUSB3', timeout=None, baudrate=9600, rtscts=False, dsrdtr=False);
            except serial.SerialException:
                try:
                    ser = serial.Serial('/dev/ttyUSB5', timeout=None, baudrate=9600, rtscts=False, dsrdtr=False);
                except serial.SerialException:
                    try:
                        ser = serial.Serial('COM0', timeout=None, baudrate=9600, rtscts=False, dsrdtr=False);
                    except serial.SerialException:
                        try:
                            ser = serial.Serial('COM1', timeout=None, baudrate=9600, rtscts=False,
                                                dsrdtr=False);
                        except serial.SerialException:
                            try:
                                ser = serial.Serial('COM2', timeout=None, baudrate=9600, rtscts=False,
                                                    dsrdtr=False);
                            except serial.SerialException:
                                try:
                                    ser = serial.Serial('COM3', timeout=None, baudrate=9600, rtscts=False,
                                                        dsrdtr=False);
                                except serial.SerialException:
                                    try:
                                        ser = serial.Serial('COM4', timeout=None, baudrate=9600, rtscts=False,
                                                            dsrdtr=False);
                                    except serial.SerialException:
                                        ser = serial.Serial('COM5', timeout=None, baudrate=9600, rtscts=False,
                                                            dsrdtr=False);


pygame.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

keepAlive = True

while keepAlive:
    event = pygame.event.wait()

    inSerial = ''
    if ser.inWaiting() > 0:
        inSerial = ser.readline();

    print("Received input: " + str(inSerial))

    if event.type == pygame.QUIT:
        keepAlive = False
    elif event.type == pygame.JOYAXISMOTION:
        val = joystick.get_axis(0)
        if val < 0.05 and val > -0.05:
            val = 0;

        if val > 0.5:
            val = b"r";
        elif val < -0.5:
            val = b"l"
        else:
            val = b"c"

        print("Sending: "+str(val));

        ser.write(val)

        val = joystick.get_axis(1)
        if val < 0.05 and val > -0.05:
            val = 0;

        if val > 0.5:
            val = b"f";
        elif val < -0.5:
            val = b"b"
        else:
            val = b"s"

        print("Sending: " + str(val));

        ser.write(val)
    elif event.type == pygame.JOYHATMOTION:
        val = joystick.get_hat(0)
        if val[1] == 1:
            ser.write(b"u")
        elif val[1] == -1:
            ser.write(b"d")
        else:
            ser.write(b"n")