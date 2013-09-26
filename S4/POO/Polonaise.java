import java.io.*;

public class Polonaise
{
	public static void main(String[] argv) throws IOException
	{
		String line;
		BufferedReader br;
		br=new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Veuillez rentrer une équation sous forme polonaise inversée");
		line=br.readLine();
		
		Expression e=new Expression(line);
		System.out.println("Réponse : "+e.evalue());
	}
		

}
