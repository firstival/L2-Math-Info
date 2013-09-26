public class InconnuValeur
{
	/*
	 * Cette classe servira a indexer les inconnus, et à leur attribuer des valeurs pour l'évaluation
	 */
	String nom;
	double valeur;
	public InconnuValeur(){}
	public InconnuValeur(String n)
	{
		nom=n;
	}
	public InconnuValeur(String n,double d)
	{
		nom=n;
		valeur=d;
	}
	public InconnuValeur(double d,String n)
	{
		nom=n;
		valeur=d;
	}
	/*
	 * Accesseurs
	 */
	public String getNom()
	{
		return nom;
	}
	public double getValeur()
	{
		return valeur;
	}
	/*
	 * Mutateurs
	 */
	public void setNom(String n)
	{
		nom=n;
	}
	public void setValeur(double d)
	{
		valeur=d;
	}
	/*
	 * Fonction qui détermine si un object i est égal à l'instance de cet objet d'InconnuValeur
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	public boolean equals(Object i)
	{
		if(i instanceof InconnuValeur) return this.nom.equals(((InconnuValeur)i).getNom());
		else if(i instanceof String) return this.nom.equals((String)i);
		else return false;
	}

}
