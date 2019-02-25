import java.net.*;
import java.io.*;

public class TCPClient {

    public static String askServer(String hostname, int port, String ToServer) throws IOException {
        StringBuilder serverReply = new StringBuilder();
        String line;

        Socket clientSocket = new Socket(hostname, port);
        clientSocket.setSoTimeout(6000);

        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        outToServer.writeBytes(ToServer + '\n');

        try {
            while ((line = inFromServer.readLine()) != null) {
                serverReply.append(line + '\n');
            }
        } catch (SocketTimeoutException e) {
            System.out.println(e.toString());
        }


        clientSocket.close();
        return serverReply.toString();
    }

    public static String askServer(String hostname, int port) throws  IOException {
        StringBuilder serverReply = new StringBuilder();
        String line;

        Socket clientSocket = new Socket(hostname, port);
        clientSocket.setSoTimeout(6000);

        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        try {
            while ((line = inFromServer.readLine()) != null) {
                serverReply.append(line + '\n');
            }
        } catch (SocketTimeoutException e) {
            System.out.println(e.toString());
        }


        clientSocket.close();
        return serverReply.toString();
    }
}
