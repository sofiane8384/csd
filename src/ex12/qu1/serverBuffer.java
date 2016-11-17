//
// **********************************************************
// *
// *  Programme : serveurBuffeur.java
// *
// *  ecrit par : LP.
// *
// *  resume :    recoit une chaine de caracteres du programme client
//                et retourne la longueur
// *
// *  date :      25 / 01 / 06
// *
// ***********************************************************
//

// Pour les commentaires, voir le client :-)

import java.net.* ;
import java.io.* ;

public class serverBuffer {
    
    public static void main(String [] args) {

	ServerSocket srv ;
	int port = 5555 ;

	try {

	    srv = new ServerSocket(port) ;

	    while ( true ) {

		Socket s = srv.accept() ;
		
		OutputStream os =  s.getOutputStream();
		
		InputStream is = s.getInputStream();

		byte[] tablo = new byte[20];

		int recu = is.read(tablo);

		// Creation de la chaine a partir du buffeur d'octets
		String message = new String( tablo );

		System.out.println("J'ai recu: " + message + ", de taille : " + recu );

		os.write( message.length() );

		s.close() ; 
	    } 

	} catch(IOException e) { }
    }
}
