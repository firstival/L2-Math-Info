public class Noeud<S>{
	private S etiquette=null;
	private Noeud<S> suivant=null;
	private Noeud<S> precedent=null;
	
	public Noeud(S n)
	{
		etiquette=n;
	}
	public Noeud(S n,Noeud<S> suiv)
	{
		etiquette=n;
		suivant=suiv;
	}
	public Noeud(S n,Noeud<S> prec,Noeud<S> suiv)
	{
		etiquette=n;
		suivant=suiv;
		precedent=prec;
	}
	public S getEtiquette()
	{
		return etiquette;
	}
	public Noeud<S> getSuivant()
	{
		return suivant;
	}
	public Noeud<S> getPrecedent()
	{
		return precedent;
	}
	public void setEtiquette(S n)
	{
		etiquette=n;
	}
	public void setSuivant(Noeud<S> suiv)
	{
		suivant=suiv;
	}
	public void setPrecedent(Noeud<S> prec)
	{
		precedent=prec;
	}
	public String toString()
	{
		return ""+etiquette;
	}
}
