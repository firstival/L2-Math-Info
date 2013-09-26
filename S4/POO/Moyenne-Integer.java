public class Moyenne_Integer
{
	public static int min(int a,int b)
	{
		return (a>b)? b : a;
	}
	public static int max(int a,int b)
	{
		return (a>b)? a : b;
	}
	
	public static void main(String[] args)
	{
		if(args.length<2) System.out.println("Usage : nombre nombre ..... nombre");
		else
		{
			int i=0,somme=0,maximum=Integer.parseInt(args[0]),minimum=Integer.parseInt(args[0]);
			for(i=0;i<args.length;i++)
			{
				somme+=Integer.parseInt(args[i]);
				minimum=min(minimum,Integer.parseInt(args[i]));
				maximum=max(maximum,Integer.parseInt(args[i]));
			}
				
				
			System.out.println("Moyenne : "+((float)somme/(float)args.length));
			System.out.println("Maximum : "+maximum);
			System.out.println("Minimum : "+minimum);	
			
		}
	}
}
