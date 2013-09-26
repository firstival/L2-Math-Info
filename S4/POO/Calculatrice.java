import java.io.*;

public class Calculatrice
{
	public static void main(String[] args) throws IOException
	{
		String line;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		
		System.out.print("1er nombre : ");
		line=br.readLine();
		int op1=Integer.parseInt(line);
		
		System.out.print("Opérateur : ");
		String str=br.readLine();
		
		System.out.print ("2eme nombre : ");
		line=br.readLine();
		int op2=Integer.parseInt(line);
		
		switch(str.charAt(0))
		{
			case '+' : System.out.println(op1+"+"+op2+"="+(op1+op2));
			break;
			case '-' : System.out.println(op1+"-"+op2+"="+(op1-op2));
			break;
			case '/' : System.out.println(op1+"/"+op2+"="+(op1/op2));
			break;
			case '*' : System.out.println(op1+"*"+op2+"="+(op1*op2));
			break;
			case '^' : System.out.println(op1+"^"+op2+"="+((int)Math.pow(op1,op2)));
			break;
			case '%' : System.out.println(op1+"%"+op2+"="+(op1%op2));
			break;
			default  : System.out.println("Opérateur inconu...");
		}
	}
}
