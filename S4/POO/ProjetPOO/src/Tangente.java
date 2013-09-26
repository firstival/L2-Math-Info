public class Tangente extends FonctionUnaire
{
	public Tangente(){}
	public Tangente(double d)
	{
		arg=new Constante(d);
	}
	public Tangente(Expression e)
	{
		arg=e;
	}

	
	public double evaluation(InconnuValeur[] inconnu) {
		
		return Math.tan(arg.evaluation(inconnu));
	}
	public String toString()
	{
		return "tan("+arg.toString()+")";
	}
	public Expression simplifierLocalement(Expression e)
	{
		if(e instanceof Constante) return new Constante(Math.tan(((Constante)e).getVal()));
		else return new Tangente(e);
	}
	public Expression deriverLocalement()
	{
		return new Addition(1,new Puissance(this,2));// u'*(1+tan²(u))
	}
}
