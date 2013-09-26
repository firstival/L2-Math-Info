public class PileParTableau
{
	private Integer tab[];
	private int indice;
	
	public PileParTableau()
	{
		tab=new Integer[10];
		indice=0;
	}
	public PileParTableau(int n)
	{
		tab=new Integer[n];
		indice=0;
	}
	public boolean PileVide()
	{
		return indice==0;
	}
	public boolean PilePleine()
	{
		return indice==tab.length;
	}
	public Integer depiler()
	{
		Integer tmp=null;
		if(!this.PileVide())
		{
			tmp=tab[indice-1];
			indice--;
		}
		return tmp;
	}
	public void empiler(Integer i)
	{
		if(!this.PilePleine())
		{
			tab[indice]=i;
			indice++;
		}
	}
	

}
