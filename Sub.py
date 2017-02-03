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

print("Initializing...");

pygame.init()
print("Initialized. Finding joystick...")
joystick = pygame.joystick.Joystick(0)
joystick.init()

print("Started");

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
        '''
            f = front
            forward
            b = front
            backward
            s = front
            stop

            r = right
            forward
            e = right
            backward
            o = right
            stop

            l = left
            forward
            t = left
            backward
            a = left
            stop

            u = top
            forward
            d = top
            backward
            n = top
            stop
            '''

        forward = -joystick.get_axis(1)
        if forward < 0.5 and forward > -0.5:
            forward = 0;

        side = joystick.get_axis(0)
        if side < 0.5 and side > -0.5:
            side = 0;

        twist = joystick.get_axis(3);
        if twist < 0.5 and twist > -0.5:
            twist = 0;

        print(forward)

        if forward == 0 and side == 0 and twist != 0:
            if twist < -0.5:
                ser.write(b"srt");
            elif twist > 0.5:
                ser.write(b"sle");
        elif forward != 0 and side == 0:
            if forward > 0.5:
                ser.write(b"frl");
            elif forward < -0.5:
                ser.write(b"bet");
        elif forward != 0 and side != 0:
            if forward > 0.5:
                ser.write(b"f")
            elif forward < -0.5:
                ser.write(b"b")
            if side < -0.5:
                ser.write(b"ar")
            elif side > 0.5:
                ser.write(b"ol")
        else:
            ser.write(b"sao");


    elif event.type == pygame.JOYHATMOTION:
        val = joystick.get_hat(0)
        if val[1] == 1:
            ser.write(b"d")
        elif val[1] == -1:
            ser.write(b"u")
        else:

            ser.write(b"n")