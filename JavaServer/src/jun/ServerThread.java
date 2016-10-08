package jun;



import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
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
            String message = null;
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            while((message = bufferedReader.readLine())!= null){
                System.out.println("incoming client message:" + message);
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
