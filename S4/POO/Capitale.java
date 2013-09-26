public class Capitale extends Ville
{
	String pays;
	
	public Capitale(String v,String p)
	{
		super(v);
		pays=p.toUpperCase();
	}
	public Capitale(String v,String p,int n)
	{
		super(v,n);
		pays=p.toUpperCase();
	}
	public String toString()
	{
		return super.toString()+" Capitale de "+pays;
	}
	public String categorie()
	{
		return "C";
	}
}
