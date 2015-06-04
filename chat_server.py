import socket
import os,sys
import threading

os.system("clear")
my_socket1=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
my_socket2=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
my_socket1.bind(('127.0.0.1',1234))
my_socket2.bind(('127.0.0.1',12345))
my_socket1.listen(1)
my_socket2.listen(1)
s1,addr1=my_socket1.accept()
s2,addr2=my_socket2.accept()

def send_msg():
	while(True):
		msg=raw_input()
		s1.sendall(msg)

def recv_msg():
	while(True):
		data=s2.recv(1024)
		if not data: continue
		print "message :",repr(data)

t1=threading.Thread(target=send_msg,args=())
t2=threading.Thread(target=recv_msg,args=())
t1.start()
t2.start()
