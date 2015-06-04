import java.io.*;
import java.net.*;

public class echoserver implements Runnable{

	public static ServerSocket my_socket;
	public static Socket server;
	public Thread t;
	
	public static void main(String[] args) throws Exception {
		my_socket = new ServerSocket(1234);
		new echoserver().start();
	}
	
	public void run(){
		
		try {
			DataInputStream inp = new DataInputStream(server.getInputStream());
			String msg=inp.readUTF();
			System.out.println("Thread id :"+t.getName());
			System.out.println("Message :"+msg+"\n");
			DataOutputStream op=new DataOutputStream(server.getOutputStream());
			op.writeUTF(msg);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void start(){
		int i = 0;
		
		while(true){
			try {
				server = my_socket.accept();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			String name = "thread_"+i;
			t=new Thread(this, name);
			t.start();
			i++;
			System.out.println("Number of threads :"+i);
		}
	}
}

