package jun;



import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * Created by raojun on 10/8/16.
 */
public class ServerThread extends Thread {
    Socket socket;
    ServerThread(Socket socket){

        this.socket = socket;
    }
    public void run(){
        try {
            int c;
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(),true);
            while ((c =bufferedReader.read())!=-1){
                System.out.printf("%c", (char) c);
                out.printf("%c", (char) c);
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
