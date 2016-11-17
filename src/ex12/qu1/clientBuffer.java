//
// **********************************************************
// *
// *  Programme : clientBuffeur.java
// *
// *  ecrit par : LP.
// *
// *  resume :    envoie une chaine de caractere au serveur, 
//                recoit la taille
// *
// *  date :      25 / 01 / 06
// *
// ***********************************************************
//

import java.net.* ;
import java.io.* ;

public class clientBuffer {

    public static void main(String [] args) {

	Socket s ;

	// References de la socket
	String hote = "localhost" ;
	int port = 5555;

	// Message envoye
	String message = new String("Master Informatique");
	
	try {

	    // Creation de la socket
	    s = new Socket (hote, port) ;

	    // On a besoin d'un flux de sortie pour
	    // envoyer et un d'entree pour recevoir
	    OutputStream os = s.getOutputStream();
	    InputStream is = s.getInputStream();

	    // Extraire le buffeur de caracteres de la
	    // chaine. Il serait aussi possible de creer
	    // un tableau et de l'initialiser directement 
	    // caractere par caractere
	    byte[] tablo = message.getBytes();

	    // Envoi
	    os.write(tablo);

	    // Reception
            int recu = is.read();

	    System.out.println("La taille de la chaine est : " + recu);
	    
	    is.close();
	    os.close();

	} 
	// Traitement des exceptions comme leur nom l'indique
	catch ( UnknownHostException e ) { 

	    System.out.println("Unknown host" + e);
	}
	catch ( IOException e) { 
	    
	    System.out.println("IO exception" + e);
	}
	
    }
    
}
