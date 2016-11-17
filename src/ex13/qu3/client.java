//
// **********************************************************
// *
// *  Programme : client.java
// *
// *  ecrit par : LP.
// *
// *  resume :    Cree un ibjet de type donnes et l'envoie 
// *              au serveur
// *
// *  date :      25 / 01 / 06
// *
// ***********************************************************
//

import java.net.* ;
import java.io.* ;
import java.util.Date;

public class client {

    public static void main(String [] args) {

	Socket s ;
	Date date = new Date();

	Donnes d = new Donnes( "Philippe", date , "Bonjour a tous" );

	// References de la socket
	String hote = "localhost" ;
	int port = 5555;
	
	try {

	    s = new Socket (hote, port) ;

	    // Les OutputStream servent a la sortie
	    // mais ne peuvent prendre en parametre que
	    // des byte ou des entiers (et encore il 
	    // n'en prend que le premier octet !)
	    OutputStream os = s.getOutputStream();

	    InputStream is = s.getInputStream();

	    // Pour cette raison, on utilise des ObjectOutputStream
	    // qui permmettent de prendre des donnees quelconques
	    ObjectOutputStream oos = new ObjectOutputStream(os);

	    oos.writeObject(d);

	} 
	catch ( UnknownHostException e ) { 

	    System.out.println("Unknown host" + e);
	}
	catch ( IOException e) { 
	    
	    System.out.println("IO exception" + e);
	}
	
    }
    
}
