public class Liste<S>
{
	private Noeud<S> debut=null;
	private Noeud<S> fin=null;
	private int taille=0;
	
	public Liste()
	{}
	public Liste(S n)
	{
		debut=new Noeud<S>(n);
		taille++;
	}
	
	public void insererDebut(S n)
	{
		Noeud<S> nouveauNoeud=new Noeud<S>(n,debut);
		if(debut!=null) debut.setPrecedent(nouveauNoeud);
		debut=nouveauNoeud;
		if(taille==0) fin=nouveauNoeud;
		taille++;
	}
	
	public void insererFin(S n)
	{
		Noeud<S> nouveauNoeud=new Noeud<S>(n,fin,null);
		if(fin!=null)fin.setSuivant(nouveauNoeud);
		fin=nouveauNoeud;
		if(taille==0) debut=nouveauNoeud;
		taille++;
	}
	
	public void insererPositionDonnee(S n,int i)
	{
		Noeud<S> tmp=debut;
		if(i==0) this.insererDebut(n);
		else if(i>=taille) this.insererFin(n);
		else
		{
			while(i>0)
			{
				tmp=tmp.getSuivant();
				i--;
			}
			Noeud<S> nouveauNoeud=new Noeud<S>(n,tmp.getPrecedent(),tmp);
			tmp.getPrecedent().setSuivant(nouveauNoeud);
			tmp.setPrecedent(nouveauNoeud);
			taille++;
		}
	}
	
	public int getTaille()
	{
		return taille;
	}
	
	public String toString()
	{
		Noeud<S> tmp=debut;
		String liste=debut.toString();
		tmp=tmp.getSuivant();
		while(tmp != null)
		{
			liste=liste+" | "+tmp.toString();
			tmp=tmp.getSuivant();
		}
		return liste;
	}
}
