import java.net.*;
import java.io.*;

public class ConcHTTPAsk {
    public static void main(String[] args) throws IOException {
      int port = Integer.parseInt(args[0]);
      ServerSocket welcomeSocket = new ServerSocket(port);

      while(true) {
        Socket connectionSocket = null;

        try {
        connectionSocket = welcomeSocket.accept();
        } catch(Exception e){
          return;
        }

        Thread th = new Thread(new MyRunnable(connectionSocket));
        th.start();
      }
    }
}
