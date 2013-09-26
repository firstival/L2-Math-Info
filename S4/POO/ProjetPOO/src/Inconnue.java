
public class Inconnue implements Expression {
	String nom;
	public Inconnue(){}
	public Inconnue(String n)
	{
		nom=n;
	}
	public String getNom()
	{
		return nom;
	}
	public void setNom(String n)
	{
		nom=n;
	}
	public String toString()
	{
		return nom;
	}
	public Expression simplifierSimple()
	{
		return this.simplifier();
	}
	public Expression simplifier()
	{
		return this;
	}
	public Expression deriver(String dx)
	{
		if(nom.equals(dx)) return new Constante(1);
		else return new Constante(0);
	}
	/*
	 * inconnu doit obligatoirement contenir une InconnuValeur avec nom=this.nom
	 */
	public double evaluation(InconnuValeur[] inconnu)
	{
		int i=0;
		while( (i<inconnu.length) && (!(inconnu[i].equals(this.nom)))) i++;//On recherche l'InconnuValeur contenant le nom de l'inconnue, pour avoir ainsi la valeur associée
		return inconnu[i].getValeur();
	}
	public Expression developper()
	{
		return this;
	}
	public Expression factoriser()
	{
		return this;
	}
}
