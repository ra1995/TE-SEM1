import matplotlib.pyplot as pl
import os, sys
import time

x=[0,1,2,3,4,5,6,7,8,9]
speed=[[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0]]

while(True):
	os.system("cat /proc/cpuinfo | grep -i Mhz > speed.txt")
	my_file=open("speed.txt",'r')
	for i in range(4):
		line=my_file.readline()
		speed_list=line.split(" ")
		speed_list=speed_list[len(speed_list)-1].strip()
		speed[i].pop(0)
		speed[i].append(float(speed_list))
	my_file.close()
	print speed
	time.sleep(1)
	pl.close()
	pl.ylabel("Speed - 'Mhz'")
	pl.plot(x,speed[0],color="r")
	pl.plot(x,speed[1],color="b")
	pl.plot(x,speed[2],color="g")
	pl.plot(x,speed[3],color="y")
	pl.savefig("speed.png")

my_file.close()
