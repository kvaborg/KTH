import java.net.*;
import java.io.*;

public class HTTPEcho {
    public static void main(String[] args) throws IOException{
        int port = Integer.parseInt(args[0]);
        ServerSocket welcomeSocket = new ServerSocket(port);

        while(true) {
          StringBuilder serverResponse = new StringBuilder();
          Socket connectionSocket = welcomeSocket.accept();
          BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
          DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());

          outToClient.writeBytes("HTTP/1.1 200 OK\r\n\r\n");

          String st;
          while(!(st = inFromClient.readLine()).isEmpty()) {
            serverResponse.append(st + "\r\n");
          }

          outToClient.writeBytes(serverResponse.toString());
          connectionSocket.close();
        }
    }
}
