public abstract class FonctionBinaire implements Expression
{
	protected Expression arg1;
	protected Expression arg2;
	/*
	 * Accesseurs
	 */
	public Expression getArgGauche()
	{
		return arg1;
	}
	public Expression getArgDroite()
	{
		return arg2;
	}
	/*
	 * On simplifie à gauche et à droite, puis on simplifie localement en utilisant les règles propres à l'opération
	 */
	public Expression simplifierSimple()
	{
		Expression tmpg=arg1.simplifier();
		Expression tmpd=arg2.simplifier();
		return simplifierLocalement(tmpg,tmpd);
	}
	/*
	 * On simplifie simplement d'abord, puis on développe pour atomiser totalement l'expression, puis on la factorise.
	 * Ensuite on la resimplifie simplement (pour gerer les cas de factorisation comme 2x+2x=2*2*x où l'on a plusieurs multiplication de constante, on a alors 4x).
	 */
	public Expression simplifier()
	{
		Expression e=this.simplifierSimple();
		e=e.developper();
		e=e.factoriser();
		return e.simplifierSimple();
	}
	/*
	 * On dérive à droite, puis à gauche, et confie les dérivés à deriverLocalement qui se charche des différentes règles de dérivation pour les opérations. On simplifie ensuite l'expression obtenu.
	 */
	public Expression deriver(String dx)
	{
		Expression tmpg=arg1.deriver(dx);
		Expression tmpd=arg2.deriver(dx);
		Expression tmp=deriverLocalement(tmpg,tmpd);
		return tmp.simplifier();
	}
	
	
	abstract public Expression simplifierLocalement(Expression e1,Expression e2);
	abstract public Expression deriverLocalement(Expression e1,Expression e2);
}
