//
// **********************************************************
// *
// *  Programme : Donnes.java
// *
// *  ecrit par : LP.
// *
// *  resume :    definition d'une classe permettant l'echange de 
// *              plusieurs donnes entre le client et le serveur
// *
// *  date :      25 / 01 / 06
// *
// ***********************************************************
//

import java.io.*;
import java.util.Date;

// Pour que les donnees puissent etre transmises
// il faut que la classe soit serializable

public class Donnes implements Serializable
{

    String nom;
    Date date;
    String texte;

    // Constructeurs
    public Donnes ( String n, Date d, String t ) 
       { nom = n ; date = d ; texte = t ; }

    // Methodes
    public String getNom() { return nom; }
    public Date   getDate() { return date; }
    public String getTexte() { return texte; }
};
