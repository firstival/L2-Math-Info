import java.util.Scanner;
import java.util.Vector;

public class Equation
{
		protected Expression e;
		protected InconnuValeur[] inconnu;
		Scanner sc = new Scanner(System.in);
		public Equation(String s)
		{
			Vector<InconnuValeur> v=new Vector<InconnuValeur>();
			Expression tmp=AnalyseurExpression.analyser( s , v );//On analyse le String, crée l'arbre, et le place dans tmp puis e
			e=tmp;
			inconnu=v.toArray(new InconnuValeur[0]);//On met dans inconnu le tableau d'InconnuValeur qui contienne un index de toute les inconnues
		}
		/*
		 * Dérive selon l'inconnu du nom contenu dans le string dx
		 */
		public String getDerivation(String dx)
		{
			return (e.deriver(dx)).toString();
		}
		/*
		 * Appelle la simplification de l'expression et renvoie le String associé
		 */
		public String getSimplification()
		{
			return (e.simplifier()).toString();
		}
		/*
		 * Renvoie le String associé à l'arbre d'Expression
		 */
		public String toString()
		{
			return e.toString();
		}
		/*
		 * Appelle l'évaluation de l'expression
		 */
		public double getEvaluation()
		{
			InconnuValeur[] tabValeur=this.createTabInconnuValeur();//Créer un tableau d'InconnuValeur contenant le string(nom) de l'inconnu ainsi que la valeur qu'on veut lui associer
			return e.evaluation(tabValeur);
		}
		/*
		 * Teste si une inconnue 's' est déjà dans 'inconnu'
		 */
		public boolean estDedans(String s)
		{
			if(inconnu.length==0) return true;
			int i=0;
			for(i=0;i<inconnu.length;i++)
			{
				if(inconnu[i].getNom().equals(s)) return true;
			}
			return false;
		}
		/*
		 * Créer un tableau contenant inconnue et leur valeur associé : la fonction demande a l'utilisiteur de rentrer ces valeurs
		 */
		private InconnuValeur[] createTabInconnuValeur()
		{
			int i=0;
			double tmp;
			InconnuValeur[] newtab=new InconnuValeur[inconnu.length];
			for(i=0;i<inconnu.length;i++)
			{
				System.out.print(inconnu[i].getNom()+" = ");
				tmp=sc.nextDouble();
				newtab[i]=new InconnuValeur(inconnu[i].getNom(),tmp);
			}
			return newtab;
		}
}
