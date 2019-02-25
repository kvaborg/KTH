import java.net.*;
import java.io.*;

public class ConcHTTPAsk {
    public static void main( String[] args) throws IOException {
      String serverResponse;

      int port = Integer.parseInt(args[0]);
      ServerSocket welcomeSocket = new ServerSocket(port);

      while(true) {
        Socket connectionSocket = welcomeSocket.accept();
        BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
        DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
      }
    }
}
