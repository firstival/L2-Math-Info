public class Exponentielle extends FonctionUnaire
{
	double base;
	public Exponentielle(){}
	public Exponentielle(double base,Expression e)
	{
		this.base=base;
		arg=e;
	}
	public Exponentielle(Expression e)
	{
		base=Math.E;
		arg=e;
	}
	public String toString()
	{
		if(base==Math.E) return "e^("+arg.toString()+")";
		else return base+"^("+arg.toString()+")";
	}
	public double getBase()
	{
		return base;
	}
	public double evaluation(InconnuValeur[] inconnu)
	{
		return Math.exp(Math.log(base)*arg.evaluation(inconnu));
	}
	public Expression simplifierLocalement(Expression e)
	{
		if((e instanceof Logarithme)&&(base==Math.E))//e^(ln(X))
		{
			return ((Logarithme)e).getArg();//X
		}
		else return this;
	}
	
	public Expression deriverLocalement()//a^(X)
	{
		if(base == Math.E) return new Exponentielle(base,arg);// Si a==e alors e^(X)
		else return new Multiplication(new Logarithme(new Constante(base)),this);// sinon ln(a)*a^(X)
	}
}
