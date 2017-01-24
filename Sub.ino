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

        val = (int(val * 255));

        print("Sending: "+str(val));

        ser.write(b"s")
        ser.write(b"%d" % val)
        ser.write(b'\n');

        val = joystick.get_axis(1)
        if val < 0.05 and val > -0.05:
            val = 0;

        val = -(int(val * 255));

        print("Sending: "+str(val));

        ser.write(b"f")
        ser.write(b"%d" % val)
        ser.write(b'\n');
    elif event.type == pygame.JOYHATMOTION:
        val = joystick.get_hat(0)
        ser.write(b"t")
        ser.write(b"%d" % int(val[1]))

        ser.write(b"b");
        ser.write(b"%d" % int(val[1]*-1))

    sleep(0.1)
