import smbus
import time

I2C_ADDR = 0x27
LCD_WIDTH = 16

LCD_CHR = 1 #Mode sending data
LCD_CMD = 0 #Mode sending command

LCD_LINE_1 = 0x80
LCD_LINE_2 = 0xC0

LCD_BACKLIGHT = 0x08 # On

ENABLE = 0b00000100

E_PULSE = 0.0005
E_DELAY = 0.0005

bus = smbus.SMBus(1)

class I2CScreen:
    def __init__(self):
        print("****** Init LCD ******")
        self.lcd_byte(0x33, LCD_CMD)
        self.lcd_byte(0x32, LCD_CMD)
        self.lcd_byte(0x06, LCD_CMD)
        self.lcd_byte(0x0C, LCD_CMD)
        self.lcd_byte(0x28, LCD_CMD)
        self.lcd_byte(0x01, LCD_CMD)
        time.sleep(E_DELAY)
        
    def lcd_byte(self,bits, mode):
        bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT
        bits_low = mode | ((bits<<4) & 0xF0) | LCD_BACKLIGHT
        
        bus.write_byte(I2C_ADDR, bits_high)
        self.lcd_toggle_enable(bits_high)
        
        bus.write_byte(I2C_ADDR, bits_low)
        self.lcd_toggle_enable(bits_low)
        
    def lcd_toggle_enable(self,bits):
        time.sleep(E_DELAY)
        bus.write_byte(I2C_ADDR, (bits | ENABLE))
        time.sleep(E_PULSE)
        bus.write_byte(I2C_ADDR,(bits & ~ENABLE))
        time.sleep(E_DELAY)
        
    def lcd_string(self,message,line):
        print("****** Write message ******")
        message = message.ljust(LCD_WIDTH," ")
        self.lcd_byte(line, LCD_CMD)
        for i in range(LCD_WIDTH):
            self.lcd_byte(ord(message[i]),LCD_CHR)
            
    def write(self,message1,message2):
        self.lcd_string(message1,LCD_LINE_1)
        self.lcd_string(message2,LCD_LINE_2)
          
          
