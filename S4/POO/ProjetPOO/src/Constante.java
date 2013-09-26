public class Constante implements Expression {
	private double val;
	public Constante(){}
	public Constante(double valeur)
	{
		val=valeur;
	}
	public double getVal()
	{
		return val;
	}
	public void setVal(double valeur)
	{
		val=valeur;
	}
	public String toString()
	{
		return val+"";
	}
	public Expression simplifierSimple()
	{
		return this.simplifier();
	}
	public Expression simplifier()
	{
		return this;
	}
	public Expression deriver(String dx)
	{
		return new Constante(0);
	}
	public double evaluation(InconnuValeur[] inconnu)
	{
		return val;
	}
	public Expression developper()
	{
		return this;
	}
	public Expression factoriser()
	{
		return this;
	}

}
