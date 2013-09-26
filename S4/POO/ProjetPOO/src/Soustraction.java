public class Soustraction extends Addition
{
	public Soustraction(){}
	/*
	 * La soustraction n'est qu'une addition avec l'opposé de l'argument de droite
	 */
	public Soustraction(Expression gauche,Expression droite)
	{
		super(gauche,new Oppose(droite));
	}
	public Soustraction(double i,Expression e)
	{
		super(i,new Oppose(e));
	}
	public Expression getArgDroit()
	{
		return ((Oppose)arg2).getArg();
	}
	public Soustraction(Expression e,double i)
	{
		super(e,-i);
	}
	
	public static Expression regleSimplification(Expression e1, Expression e2)
	{
		return Addition.regleSimplification(e1, Oppose.regleSimplification(e2));
	}
}
