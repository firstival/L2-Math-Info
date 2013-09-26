public interface Expression
{
	public String toString();
	public Expression simplifierSimple();
	public Expression simplifier();
	public Expression deriver(String dx);
	public double evaluation(InconnuValeur[] inconnu);
	public Expression developper();
	public Expression factoriser();
}
