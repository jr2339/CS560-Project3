package jun;

/**
 * Created by raojun on 10/8/16.
 */
import java.net.*;
import java.io.*;
import java.util.Scanner;

// the function of server is to accept some input from the client
//and process it and return it back to the client
public class SimpleServer {
    public static final int PORT = 23657;

    public static void main(String[] args) throws IOException {
        new SimpleServer().runServer();
    }

    public void runServer() throws IOException {
        ServerSocket serverSocket = new ServerSocket(PORT);
        System.out.println("Server up & ready for connections......");
        while (true) {
            Socket socket = serverSocket.accept();
            new ServerThread(socket).start();
        }
    }
}