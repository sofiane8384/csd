//
// **********************************************************
// *
// *  Programme : serveur.java
// *
// *  ecrit par : LP.
// *
// *  resume :    Recoit un objet de type donnes et en affiche le 
// *              contenu
// *
// *  date :      25 / 01 / 06
// *
// ***********************************************************
//

import java.net.* ;
import java.io.* ;
import java.util.Date ;

public class server {
    
    public static void main(String [] args) {

	ServerSocket srv ;
	int port = 5555 ;

	try {

	    srv = new ServerSocket(port) ;

	    //while ( true ) {

		Socket s = srv.accept() ;
		
		// Les InputStream servent a l'entree
		// mais ne peuvent prendre en parametre que
		// des byte ou des entiers
		OutputStream os =  s.getOutputStream();
		
		InputStream is = s.getInputStream();

		// Pour cette raison, on utilise des ObjectInputStream
		// qui permmettent de prendre des donnees quelconques
		ObjectInputStream ois = new ObjectInputStream(is);

		try {
		    Donnes maDon = null;
		    
		    // Reception de l'objet. Il faut caster car nous
		    // recevons un type d'objet generique
		    maDon = (Donnes) (ois.readObject());
		    
		    Date date = maDon.getDate();

		    System.out.println("J'ai recu un message de : " + 
				       maDon.getNom() + " envoye a " +
				       date.toString());
		    System.out.println("Texte : " + maDon.getTexte());

		} catch ( Exception e) {
		    System.out.println(e);
		}

		s.close() ;

		System.out.println("fin");
		System.exit(0);
		//} 

	} catch(IOException e) { }
    }
}
