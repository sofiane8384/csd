import java.net.* ;
import java.io.* ;

public class client {

    public static void main(String [] args) {

	Socket s ;

	// References de la socket
	String hote = "localhost" ;
	int port = 5555;
	
	try {

	    s = new Socket (hote, port) ;

	    OutputStream os = s.getOutputStream();

	    InputStream is = s.getInputStream();

	    os.write(4);

            int recu = is.read();

	    System.out.println("J'ai recu " + recu);

	    byte[] buffer = new byte[20];
	    recu = is.read( buffer );

	    System.out.println("J'ai recu " + recu + 
			       " avec : " + (int)buffer[0] + 
			       " " + buffer[1] + 
			       " " + buffer[2] + 
			       " " + buffer[3] + 
			       " " + buffer[4] 
			       );


	} 
	catch ( UnknownHostException e ) { 

	    System.out.println("Unknown host" + e);
	}
	catch ( IOException e) { 
	    
	    System.out.println("IO exception" + e);
	}
	
    }
    
}
