import Adafruit_BBIO.GPIO as GPIO
import time

lights=[["P8_1","P8_2","P8_3"],["P8_4","P8_5","P8_6"],["P9_1","P9_2","P9_3"],["P9_4","P9_5","P9_6"]]
for i in range(4):
	for j in range(3):
		GPIO.setup(lights[i][j],GPIO.out)

def signal_stop(a):
	GPIO.output(a[0],GPIO.HIGH)
	GPIO.output(a[0],GPIO.LOW)
	GPIO.output(a[0],GPIO.LOW)

def signal_look(a):
	GPIO.output(a[0],GPIO.LOW)
	GPIO.output(a[0],GPIO.HIGH)
	GPIO.output(a[0],GPIO.LOW)

def signal_go(a):
	GPIO.output(a[0],GPIO.LOW)
	GPIO.output(a[0],GPIO.LOW)
	GPIO.output(a[0],GPIO.HIGH)

while(True):
	for i in range(4):
		signal_stop(lights[i%4])
		signal_stop(lights[(i+1)%4])
		signal_stop(lights[(i+2)%4])
		signal_stop(lights[(i+3)%4])
		time.sleep(5)

		signal_look(lights[i%4])
		signal_stop(lights[(i+1)%4])
		signal_stop(lights[(i+2)%4])
		signal_stop(lights[(i+3)%4])
		time.sleep(2)

		signal_go(lights[i%4])
		signal_stop(lights[(i+1)%4])
		signal_stop(lights[(i+2)%4])
		signal_stop(lights[(i+3)%4])
		time.sleep(5)
		
		signal_look(lights[i%4])
		signal_stop(lights[(i+1)%4])
		signal_stop(lights[(i+2)%4])
		signal_stop(lights[(i+3)%4])
		time.sleep(2)
