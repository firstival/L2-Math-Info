public class Ville{
	protected final String nom;
	protected int nbHabitant=0;
	
	public Ville(String n)
	{
		nom=n.toUpperCase();
	}
	public Ville(String n,int nb)
	{
		nom=n.toUpperCase();
		nbHabitant=nb;
	}
	public String getNom()
	{
		return nom;
	}
	public int getNbHabitant()
	{
		return nbHabitant;
	}
	public void setNbHabitants(int n)
	{
		if(n<0)n=0;
		nbHabitant=n;
	}
	public boolean nbHabitantConnu()
	{
		return (nbHabitant!=0);
	}
	public String toString()
	{
		if(nbHabitant==0) return "Ville de "+nom+".";
		else return "Ville de "+nom+" ; "+nbHabitant+" habitants.";
	}
	public String categorie()
	{
		if(nbHabitant<500000 && nbHabitant!=0)return "A";
		else if(nbHabitant>5000000) return "B";
		else return "?";
	}
}
