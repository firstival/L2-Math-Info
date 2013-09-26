public class Logarithme extends FonctionUnaire
{
	public Logarithme(){}
	public Logarithme(Expression a)
	{
		arg=a;
	}
	public double evaluation(InconnuValeur[] inconnu) {
		
		return Math.log(arg.evaluation(inconnu));
	}
	public String toString()
	{
		return "ln("+arg.toString()+")";
	}
	public Expression simplifierLocalement(Expression e)
	{
		if(e instanceof Multiplication)//ln(M*N)
		{
			Multiplication tmp=(Multiplication)e;
			Expression tmp1=this.simplifierLocalement(tmp.getArgGauche());
			Expression tmp2=this.simplifierLocalement(tmp.getArgDroite());
			return Addition.regleSimplification(tmp1, tmp2);//ln(M)+ln(N)
		}
		else if(e instanceof Division)//ln(M/N)
		{
			Division tmp=(Division)e;
			Expression tmp1=this.simplifierLocalement(tmp.getArgGauche());
			Expression tmp2=this.simplifierLocalement(tmp.getArgDroite());
			return Soustraction.regleSimplification(tmp1, tmp2);//ln(M)-ln(N)
		}
		else if(e instanceof Puissance)//ln(X^n)
		{
			Puissance tmp=(Puissance)e;
			return new Multiplication(tmp.getPuissance(),new Logarithme(tmp.getArg()));//n*ln(X)
		}
		else if(e instanceof Exponentielle)//ln(a^X)
		{
			Exponentielle tmp=(Exponentielle)e;
			if(tmp.getBase()==Math.E) return tmp.getArg();//si a==e, alors X
			else return Multiplication.regleSimplification(new Constante(Math.log(tmp.getBase())), tmp.getArg());//sinon ln(a)*X
		}
		else return new Logarithme(e);
	}
	
	public Expression deriverLocalement()
	{
		return new Division(1,arg);//(ln(x))'=1/x
	}
}
