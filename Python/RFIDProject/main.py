from I2C_LCD import I2CScreen
import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522
from time import sleep

if __name__ == '__main__':
    GPIO.setwarnings(False)    # Ignore warning for now
    reader = SimpleMFRC522()
    screen = I2CScreen()
    while True:
            try:
                id, text = reader.read()
                print(id)
                print(type(id))
                print(text)
                if(id==592495348106):
                    screen.write("Welcome home !",text)
                    reader.write("It's me !")
                
                sleep(5)
                screen.write(" "," ")
                
            except:
                screen.write("Error"," ")
