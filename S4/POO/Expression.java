public class Expression
{
	private String line;

	public Expression(String l)
	{
		line=l;
	}
	public Integer evalue()
	{
		String t[]=line.split(" ");
		PileParTableau p=new PileParTableau(t.length);
		int i=0;
		Integer a,b;
		for(i=0;i<t.length;i++)
		{
			if(t[i].equals("+"))
			{
				a=p.depiler();
				b=p.depiler();
				p.empiler(new Integer(b.intValue()+a.intValue()));
			}
			else if(t[i].equals("-"))
			{
				a=p.depiler();
				b=p.depiler();
				p.empiler(new Integer(b.intValue()-a.intValue()));
			}
			else if(t[i].equals("*"))
			{
				a=p.depiler();
				b=p.depiler();
				p.empiler(new Integer(b.intValue()*a.intValue()));
			}
			else if(t[i].equals("/"))
			{
				a=p.depiler();
				b=p.depiler();
				p.empiler(new Integer(b.intValue()/a.intValue()));
			}
			else p.empiler(new Integer(t[i]));
		}
		return p.depiler();
	}
	private boolean operateur(String s)
	{
		return (s.equals("+") || s.equals("-") || s.equals("/") || s.equals("*"));
	}
	private void calcul(PileParTableau p,char c)
	{
		Integer a=p.depiler(),b=p.depiler();
		switch(c)
		{
			case '+' :
			p.empiler(b+a);
			break;
			case '-' :
			p.empiler(b-a);
			break;
			case '*' :
			p.empiler(b*a);
			break;
			case '/' :
			p.empiler(b/a);
			break;
			default :
			break;
		}
	}
}
