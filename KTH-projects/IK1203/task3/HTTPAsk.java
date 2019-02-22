import java.net.*;
import java.io.*;

public class HTTPAsk {
    public static void main( String[] args) throws IOException {
      String serverResponse;

      int port = Integer.parseInt(args[0]);
      ServerSocket welcomeSocket = new ServerSocket(port);

      while(true) {
        Socket connectionSocket = welcomeSocket.accept();
        BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
        DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());

        try {
          String url = getUrl(inFromClient);
          String tcpHost = getHost(url);
          int tcpPort = Integer.parseInt(getPort(url));
          String tcpString = getString(url);

          try {
            serverResponse = ask(tcpHost, tcpPort, tcpString);
            outToClient.writeBytes("HTTP/1.1 200 OK\r\n\r\n");
            outToClient.writeBytes(serverResponse);
          } catch (Exception e) {
            outToClient.writeBytes("HTTP/1.1 404 Not Found\r\n\r\n");
            outToClient.writeBytes(e.toString());
            connectionSocket.close();
          }

        } catch(Exception e) {
          outToClient.writeBytes("HTTP/1.1 400 Bad Request\r\n\r\n");
          outToClient.writeBytes(e.toString());
          connectionSocket.close();
        }

        connectionSocket.close();

      }
    }

    private static String ask(String host, int port, String str) throws IOException {
      TCPClient client = new TCPClient();
      String response;

      if (str.equals("")) {
        response = client.askServer(host, port);
        return response;
      } else {
        response = client.askServer(host, port, str);
        return response;
      }
    }

    private static boolean checkAsk(String url) {
      String[] seq = url.split("[/?]");
      boolean ask = false;

      if (seq[1].equals("ask")) {
        ask = true;
      }

      return ask;
    }

    private static String getUrl(BufferedReader br) throws IOException {
      String httpReq = br.readLine();
      String[] seq = httpReq.split(" ");
      String url = seq[1];

      if (!(checkAsk(url))) {
        return null;
      }

      return url;
    }

    private static String getHost(String url) {
      String[] arr = url.split("[=&]");
      String host = arr[1];
      return host;
    }

    private static String getPort(String url) {
      String[] arr = url.split("[=&]");
      return arr[3];
    }

    private static String getString(String url) {
      String[] arr = url.split("string=");
      if (arr.length > 1) {
        return arr[1];
      } else {
        return "";
      }
    }


}
