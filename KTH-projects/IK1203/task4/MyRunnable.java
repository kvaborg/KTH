import java.net.*;
import java.io.*;

<<<<<<< HEAD
  public void run() {
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

=======
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

>>>>>>> task4
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

<<<<<<< HEAD
=======
  /*  CHECK IF HTTP-PARAMETERS STARTS WITH /ASK */
>>>>>>> task4
  private static boolean checkAsk(String url) {
    String[] seq = url.split("[/?]");
    boolean ask = false;

    if (seq[1].equals("ask")) {
      ask = true;
    }
<<<<<<< HEAD

=======
>>>>>>> task4
    return ask;
  }

  private static String getUrl(BufferedReader br) throws IOException {
    String httpReq = br.readLine();
    String[] seq = httpReq.split(" ");
    String url = seq[1];

    if (!(checkAsk(url))) {
      return null;
    }
<<<<<<< HEAD

=======
>>>>>>> task4
    return url;
  }

  private static String getHost(String url) {
<<<<<<< HEAD
    String[] arr = url.split("[=&]");
    String host = arr[1];
=======
    String pattern = "(.+)(hostname=)([a-zA-Z0-9\\.]+)(&*.*)";
    String host = url.replaceAll(pattern, "$3");
    System.out.println(host);

>>>>>>> task4
    return host;
  }

  private static String getPort(String url) {
<<<<<<< HEAD
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
=======
    String pattern = "(.+)(port=)([0-9]+)(&*.*)";
    String port = url.replaceAll(pattern, "$3");
    System.out.println(port);

    return port;
  }

  private static String getString(String url) {
    String pattern = "(.+)(string=)([a-zA-z0-9\\.]+)(&*.*)";
    String str = url.replaceAll(pattern, "$3");
    System.out.println(str);

    return str;
>>>>>>> task4
  }

}
