import time
import threading

floor_queue=[0,0,0,0,0,0,0,0,0,0]
request_queue=[]
my_lock=threading.Lock()

def request():
	while(True):
		i=int(input())
		if i in range(10):
			my_lock.acquire()
			if(floor_queue[i]==0):
				floor_queue[i]=1
				request_queue.append(i)
				print "request taken"
			my_lock.release()

def serve():
	initial=0;
	print "current floor :"+str(initial)
	while(True):
		if(len(request_queue)>0):
			if(request_queue[0]==initial):
				my_lock.acquire()
				floor_queue[initial]=0
				request_queue.pop(0)
				my_lock.release()
				print "open doors :"+str(initial)
				time.sleep(2)
				print "doors closed"
				continue
			if(request_queue[0]>initial):
				for i in range(initial+1,request_queue[0]+1):
					time.sleep(2)
					print "current floor :"+str(i)
					if(floor_queue[i]==1):
						my_lock.acquire()
						floor_queue[i]=0
						ind=request_queue.index(i)
						request_queue.pop(ind)
						my_lock.release()
						print "open doors :"+str(i)
						time.sleep(2)
						print "doors closed"
				initial=i
				continue
			if(request_queue[0]<initial):
				for i in range(initial-1,request_queue[0]-1,-1):
					time.sleep(2)
					print "current floor :"+str(i)
					if(floor_queue[i]==1):
						my_lock.acquire()
						floor_queue[i]=0
						ind=request_queue.index(i)
						request_queue.pop(ind)
						my_lock.release()
						print "open doors :"+str(i)
						time.sleep(2)
						print "doors closed"
				initial=i
				continue

t1=threading.Thread(target=request,args=())
t2=threading.Thread(target=serve,args=())
t1.start()
t2.start()
