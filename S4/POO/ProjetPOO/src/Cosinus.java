public class Cosinus extends FonctionUnaire
{

	public Cosinus(){}
	public Cosinus(double d)
	{
		arg=new Constante(d);
	}
	public Cosinus (Expression e)
	{
		arg=e;
	}
	
	
	public double evaluation(InconnuValeur[] inconnu)
	{
		return Math.cos(arg.evaluation(inconnu));
	}
	public String toString()
	{
		return "cos("+arg.toString()+")";
	}
	public Expression simplifierLocalement(Expression e)
	{
		if(e instanceof Constante) return new Constante(Math.cos(((Constante)e).getVal()));//Si l'argument est un constante, on simplifie en renvoyant la constante qui est le resultat de l'opération
		return new Cosinus(e);//Sinon on revoie cos(e)
	}
	public Expression deriverLocalement()
	{
		return new Oppose(new Sinus(arg));//cos'(u)=u'*(-sin(u)), içi on renvoie le -sin(u)
	}
}
