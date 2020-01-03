# general imports
import Jetson.GPIO as GPIO
import time
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
    GPIO.setup(32, GPIO.OUT)

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
    GPIO.output(31, GPIO.HIGH)
    GPIO.output(31, GPIO.LOW)

def PWM_Test():
    pwm = GPIO.PWM(32, 100)
    print("\nPress Ctl C to quit \n")  # Print blank line before and after message.
    dc=0                               # set dc variable to 0 for 0%
    pwm.start(dc)                      # Start PWM with 0% duty cycle

    try:
        while True:                      # Loop until Ctl C is pressed to stop.
            for dc in range(0, 101, 5):    # Loop 0 to 100 stepping dc by 5 each loop
                pwm.ChangeDutyCycle(dc)
                time.sleep(0.05)             # wait .05 seconds at current LED brightness
                print(dc)
            for dc in range(95, 0, -5):    # Loop 95 to 5 stepping dc down by 5 each loop
                pwm.ChangeDutyCycle(dc)
                time.sleep(0.05)             # wait .05 seconds at current LED brightness
                print(dc)
    except KeyboardInterrupt:
        print("Ctl C pressed - ending program")

    pwm.stop()                         # stop PWM
    GPIO.cleanup()                     # resets GPIO ports used back to input mode

if __name__ == "__main__":
    GPIOInit()
    while(1):
         PortLEDs() # uncomment this to cycle through green status LEDs
        # ToggleLEDs() # uncomment this to toggle LEDs rapidly
        # PWM_Test() # uncomment to test PWM on pin 32
