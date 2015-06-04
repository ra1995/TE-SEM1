import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class echoclient {
	
	private static Socket client;
	private static Scanner myScanner;
	
	public static void main(String[] args) throws Exception {
		
		client = new Socket("localhost",1234);
		while(true)
		{
		myScanner = new Scanner(System.in);
		String msg = myScanner.nextLine();
		
		DataOutputStream data = new DataOutputStream(client.getOutputStream());
		data.writeUTF(msg);
		DataInputStream in = new DataInputStream(client.getInputStream());
		System.out.println("Echo :"+in.readUTF());
		}
	}

}

