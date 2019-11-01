import java.net.*;
import java.io.*;

public class MyRunnable implements Runnable {

  String serverResponse = null;
  Socket connectionSocket = null;

  public MyRunnable(Socket s) throws IOException {
    this.connectionSocket = s;
  }

  public void run() {

    try {
      BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
      DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());

      try {
        String url = getUrl(inFromClient);
        String tcpHost = getHost(url);
        int tcpPort = Integer.parseInt(getPort(url));
        String tcpString = getString(url);

        try {
          this.serverResponse = ask(tcpHost, tcpPort, tcpString);
          outToClient.writeBytes("HTTP/1.1 200 OK\r\n\r\n");
          outToClient.writeBytes(serverResponse);
          connectionSocket.close();
        } catch (Exception e) {
          outToClient.writeBytes("HTTP/1.1 404 Not Found\r\n\r\n");
          e.printStackTrace();
          connectionSocket.close();
        }

      } catch(Exception e) {
        outToClient.writeBytes("HTTP/1.1 400 Bad Request\r\n\r\n");
        e.printStackTrace();
        connectionSocket.close();
      }

    }catch (Exception e) {
        e.printStackTrace();
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

  /*  CHECK IF HTTP-PARAMETERS STARTS WITH /ASK */
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
    String pattern = "(.+)(hostname=)([a-zA-Z0-9\\.]+)(&*.*)";
    String host = url.replaceAll(pattern, "$3");
    System.out.println(host);

    return host;
  }

  private static String getPort(String url) {
    String pattern = "(.+)(port=)([0-9]+)(&*.*)";
    String port = url.replaceAll(pattern, "$3");
    System.out.println(port);

    return port;
  }

  private static String getString(String url) {
    String pattern = "(.+)(string=)([^&]+)(&*.*)";
    String str = url.replaceAll(pattern, "$3");
    System.out.println(str);

    return str;
  }

}
