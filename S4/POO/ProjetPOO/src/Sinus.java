public class Sinus extends FonctionUnaire
{
	public Sinus(){}
	public Sinus(double d)
	{
		arg=new Constante(d);
	}
	public Sinus (Expression e)
	{
		arg=e;
	}
	
	
	public double evaluation(InconnuValeur[] inconnu) {
		
		return Math.sin(arg.evaluation(inconnu));
	}
	public String toString()
	{
		return "sin("+arg.toString()+")";
	}
	public Expression simplifierLocalement(Expression e)
	{
		if(e instanceof Constante)return new Constante(Math.sin(((Constante)e).getVal()));//On remplace par la valeur de sin(arg) si arg est une constante
		else return new Sinus(e);
	}
	public Expression deriverLocalement()
	{
		return new Cosinus(arg);//sin(x)'=cos(x)
	}
}
