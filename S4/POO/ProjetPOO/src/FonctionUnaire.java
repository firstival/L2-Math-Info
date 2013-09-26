public abstract class FonctionUnaire implements Expression
{
	protected Expression arg;
	
	public Expression getArg()
	{
		return arg;
	}
	/*
	 * La simplification simple ne fait qu'appeler la simplification normal (on ne peut pas simplifier plus simplement que celle ci)
	 */
	public Expression simplifierSimple()
	{
		return this.simplifier();
	}
	/*
	 * On simplifie l'argument, et on le traite avec simplifierLocalement(simplification différente selon la fonction unaire)
	 */
	public Expression simplifier()
	{
		Expression tmp=arg.simplifier();
		return simplifierLocalement(tmp);
	}
	/*
	 * f(g(x))'=g'(x) * (f'(g(x))
	 * On appelle Multiplication.regleSimplification pour simplifier, si on le peut, immédiatement un peu 
	 */
	public Expression deriver(String dx)
	{
		return Multiplication.regleSimplification(arg.deriver(dx),this.deriverLocalement()).simplifier();
	}
	/*
	 * La plupart des fonction unaires ne sont pas développable, on revoie juste l'expression alors
	 */
	public Expression developper()
	{
		return this;
	}
	/*
	 * La plupart des fonction unaires ne sont pas factorisable, on revoie juste l'expression alors
	 */
	public Expression factoriser()
	{
		return this;
	}
	/*
	 * Fonction qui simplifie localement en fonction de la fonction unaire
	 */
	public abstract Expression simplifierLocalement(Expression e);
	/*
	 * Dérive selon les règles de dérivations de la fonction unaire
	 */
	public abstract Expression deriverLocalement();
}
