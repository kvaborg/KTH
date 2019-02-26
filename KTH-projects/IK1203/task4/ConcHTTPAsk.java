import java.net.*;
import java.io.*;

public class ConcHTTPAsk {
    public static void main(String[] args) throws IOException {
      int port = Integer.parseInt(args[0]);
      ServerSocket welcomeSocket = new ServerSocket(port);

      while(true) {
<<<<<<< HEAD
        Socket connectionSocket = welcomeSocket.accept();
        BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
        DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
=======
        Socket connectionSocket = null;

        try {
        connectionSocket = welcomeSocket.accept();
        } catch(Exception e){
          return;
        }

        Thread th = new Thread(new MyRunnable(connectionSocket));
        th.start();
>>>>>>> task4
      }
    }
}
