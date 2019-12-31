# general imports
import Jetson.GPIO as GPIO

## import from user defined functions
import sys
sys.path.insert(0, '/home/rmcsqrd/programming/elvira/functions')
import delays

def GPIOInit():
    # initialize GPIO pins as output 
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(29, GPIO.OUT)
    GPIO.setup(31, GPIO.OUT)
    GPIO.setup(33, GPIO.OUT)

def GPIOClear():
    '''
    this function sets the status LED's to low
    '''
    GPIO.output(29, GPIO.LOW)
    GPIO.output(31, GPIO.LOW)
    GPIO.output(33, GPIO.LOW)

def PortLEDs():
    '''
    This function indefinitely cycles through the PORT 1-3 LED's 
    '''
    # cycle through LED's indefinitely
    GPIO_list = [29, 31, 33] 
    for pin in GPIO_list:
        GPIO.output(pin, GPIO.HIGH)
        delays.delay_ms(100)
        GPIOClear() 
def ToggleLEDs():
    GPIO.output(29, GPIO.HIGH)
    GPIO.output(29, GPIO.LOW)
if __name__ == "__main__":
    GPIOInit()
    while(1):
        # PortLEDs() # uncomment this to cycle through green status LEDs
        ToggleLEDs() # uncomment this to toggle LEDs rapidly
