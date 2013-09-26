import java.io.*;

public class TestChaine 
{
	public static void num1() throws IOException
	{
		String line;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		line=br.readLine();
		System.out.println(line.length());
	}
	
	public static void num2() throws IOException
	{
		String s1,s2;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		s2=br.readLine();
		
		System.out.println("S1==S2: "+(s1==s2));
		System.out.println("s1.equals(s2): "+s1.equals(s2));
		System.out.println("s1.compareTo(s2): "+s1.compareTo(s2));
		System.out.println("s1.compareToIgnoreCase(s2): "+s1.compareToIgnoreCase(s2));
	}
	
	public static void num3() throws IOException
	{
		String s1,s2;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		s2=br.readLine();
		
		System.out.println("Ces deyx chaînes commencent-elles par le même caractère ? : "+(s1.charAt(0)==s2.charAt(0)));
		
		
	}
	
	public static void num4() throws IOException
	{
		String s1,s2;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		s2=br.readLine();
		System.out.println("s1 commence par s2 ? : "+s1.startsWith(s2));
		System.out.println("s2 se finit par s2 ? : "+s1.endsWith(s2));
		System.out.println("s1 contient-elle s2 ? : "+s1.contains(s2));
	}
	
	public static void num5() throws IOException
	{
		String s1,s2,s3;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		s2=br.readLine();
		s3=s1+s2;
		System.out.println(s3);
	}
	
	public static void num6() throws IOException
	{
		String s1;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		System.out.println(s1.replace('o','O'));
	}
	
	public static void num() throws IOException
	{
		String s1,s2;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		s2=br.readLine();
	}
	
		public static void num7() throws IOException
	{
		String s1,s2;
		int i=0;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		s2=br.readLine();
		while(s1.contains(s2))
		{
			i=s1.indexOf(s2);
			s1=s1.substring(0,i)+s1.substring(i+s2.length(),s1.length());
		}
		
		System.out.println(s1);
	}

	public static void num8() throws IOException
	{
		String s1;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		System.out.println(s1.toUpperCase());
	}
	
	public static void num9() throws IOException
	{
		String s1;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		System.out.println(s1.trim());
	}
	
	public static void num10() throws IOException
	{
		String s1;
		String[] t;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		t=s1.split(" ");
		for(String s : t)
		{
			System.out.println(s);
		}
	}
	
		public static void test() throws IOException
	{
		String s1;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		System.out.println(s1+'A');
		System.out.println(s1);
	}
	
		public static void num11() throws IOException
	{
		String s1;
		StringBuffer s;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		s1=br.readLine();
		s=new StringBuffer(s1);
		System.out.println(s.toString());
	}
	
	public static void main(String[] args) throws IOException
	{
		num11();
	}
}
