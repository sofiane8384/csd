import java.net.* ;
import java.io.* ;

public class server {
    
    public static void main(String [] args) {

	ServerSocket srv ;
	int port = 5555 ;

	try {

	    srv = new ServerSocket(port) ;

	    while ( true ) {

		Socket s = srv.accept() ;
		
		OutputStream os =  s.getOutputStream();
		
		InputStream is = s.getInputStream();

		int recu = is.read();

		System.out.println("J'ai recu: " + recu);

		os.write(66);

		byte[] buf = new byte[5];
		buf[0]=1;
		buf[1]=2;
		buf[2]=3;
		buf[3]=4;
		buf[4]=5;

		os.write( buf );

		s.close() ;

		System.out.println("fin");
		System.exit(0);
	    } 

	} catch(IOException e) {
    e.printStackTrace();
  }
    }
}
