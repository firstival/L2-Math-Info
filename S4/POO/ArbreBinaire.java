public class ArbreBinaire
{
	private ArbreBinaire g=null;
	private ArbreBinaire d=null;
	private int v;
	public ArbreBinaire() {}
	public ArbreBinaire(int x)
	{
		v=x;
	}
	public ArbreBinaire(ArbreBinaire a1,int x,ArbreBinaire a2)
	{
		v=x;
		g=a1;
		d=a2;
	}
	public ArbreBinaire getag()
	{
		return g;
	}
	public ArbreBinaire getad()
	{
		return d;
	}
	public int getv()
	{
		return v;
	}
	public void setag(ArbreBinaire a)
	{
		g=a;
	}
	public void setad(ArbreBinaire a)
	{
		d=a;
	}
	public int setv(int x)
	{
		v=x;
	}
	
	static ArbreBinaire add(int x,ArbreBinaire a)
	{
		boolean stop=true;
		if(a != null)
		{
			if(x!=a.getv())
			{
				ArbreBinaire tmp=a;
				while(stop)
				{
					if(x<tmp.getv())
					{
						if(tmp.getag() == null)
						{
							tmp.setag(new ArbreBinaire(x));
							stop=false;
						}
						else tmp=tmp.getag();

					}
					else
					{
						if(tmp.getad() == null)
						{
							tmp.setad(new ArbreBinaire(x));
							stop=false;
						}
						else tmp=tmp.getad();
					}
				}
			}
		}
		else
		{
			a=new ArbreBinaire(x);
		}
		return a;
	}
	static public void afficher(ArbreBinaire a)
	{
		if(a==null) return;
		else
		{
			System.out.println(v);
			afficher(g);
			afficher(d);
		}
	}
	
		
}
