public class Oppose extends Multiplication
{
	public Oppose(){}
	/*
	 * L'opposé de X, c'est comme faire -1*X
	 */
	public Oppose(double d)
	{
		super(-1,d);
	}
	public Oppose(Expression e)
	{
		super(-1,e);
	}
	public Expression getArg()
	{
		return arg2;
	}
	
	public double evaluation(InconnuValeur[] inconnu)
	{
		return -arg2.evaluation(inconnu);
	}
	public String toString()
	{
		//Si l'argument est une constante/inconnu/multiplication/fonction unaire, pas la peine de mettre des parenthèses autour des arguments pour leur affichage
		if((arg2 instanceof Constante)||(arg2 instanceof Inconnue)||(arg2 instanceof Multiplication)||(arg2 instanceof FonctionUnaire)) return "-"+arg2.toString();
		else return "-("+arg2.toString()+")";
	}
	public Expression simplifierLocalement(Expression e1,Expression e2)
	{
		return Oppose.regleSimplification(e2);
	}
	public static Expression regleSimplification(Expression e)
	{
		if(e instanceof Oppose) return ((Oppose)e).getArg();//-(-X)=X
		else if(e instanceof Constante) return new Constante(-((Constante)e).getVal());//-(-5)=5
		else return new Oppose(e);//sinon -X
	}
}
