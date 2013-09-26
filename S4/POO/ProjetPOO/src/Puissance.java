public class Puissance extends FonctionUnaire
{
	double puissance;
	public Puissance(){}
	public Puissance(Expression e)
	{
		puissance=2;
		arg=e;
	}
	public Puissance(double i,Expression e)
	{
		puissance=i;
		arg=e;
	}
	public Puissance(Expression e,double i)
	{
		arg=e;
		puissance=i;
	}
	public Puissance(double i,double p)
	{
		arg=new Constante(i);
		puissance=p;
	}
	public double getPuissance()
	{
		return puissance;
	}
	
	public double evaluation(InconnuValeur[] inconnu)
	{
		return Math.pow(arg.evaluation(inconnu),puissance);
	}
	public String toString()
	{
		if(puissance==0.5) return "√("+arg.toString()+")";//Si la puissance est 0.5, alors c'est une racine carré, on affiche donc le symbole √
		else if((arg instanceof Inconnue)||(arg instanceof Constante))//Si c'est une inconnue ou une constante, on ne met pas de parenthèse
		{
			if(puissance == 2) return arg.toString()+"²";// Si la puissance est 2, on affiche le symbole ²
			else return arg.toString()+"^"+puissance;// Sinon on met le symbole ^
		}
		else
		{
			if(puissance == 2) return "("+arg.toString()+")²";
			else return "("+arg.toString()+")^"+puissance;//Sinon on met des parenthèses
		}
	}
	/*
	 * Fonction qui simplifie localement (au niveau de l'opération)
	 */
	public Expression simplifierLocalement(Expression e)
	{
		if(e instanceof Puissance)
		{
			Puissance tmp=(Puissance)e;
			return new Puissance(puissance+tmp.getPuissance(),tmp.getArg());//X^(a^b)=X^(a*b)
		}
		else if(puissance==1)return e;//X^1=X
		else if(puissance==0.5) return new RacineCarre(arg);//X^0.5=sqrt(X)
		else if(puissance==0)return new Constante(1);//X^0=1
		else if(puissance < 0) return new Division(1,(new Puissance(arg,-puissance)).simplifierLocalement(e));//X^(-n)=1/(X^n)
		else return new Puissance(puissance,e);
	}
	public Expression deriverLocalement()
	{
		if(puissance==2) return Multiplication.regleSimplification(new Constante(2),arg);//X^2=2X
		else return Multiplication.regleSimplification(new Constante(puissance),(new Puissance(puissance-1,arg)).simplifierLocalement(arg));//X^n=n*X^(n-1)
	}
	public Expression simplifier()
	{
		Expression tmp=new Puissance(arg.simplifier(),puissance);
		return tmp.developper().factoriser();//On développe X^n, puis factorise
	}
	public Expression developper()
	{
		if(puissance>1)
		{
			Puissance tmp1=new Puissance(arg,puissance-1);
			Expression tmp2=tmp1.simplifierLocalement(arg);
			return new Multiplication(arg,tmp2.developper()).developper();//X^n=X*X^(n-1) puis on developpe X^(n-1) pour avoir X*X*X*....X, pour ensuite développer X*X, puis X*(le resultat d'avant) etc...
		}
		else return this;
	}
	
	public static Expression nFoisExpressionPositive(Expression e,double d)
	{
		if(d>1) return new Multiplication(e,nFoisExpressionPositive(e,d-1));//X^n=X*X^(n-1)...
		else return e;
	}
	/*
	 * X^(-n)=X^(-1) * X^(1-n).... pour avoir X^(-n)=X^(-1)*X^(-1)*X^(-1)*X^(-1)*X^(-1)*.... n fois
	 */
	public static Expression nFoisExpressionNegative(Expression e,double d)
	{
		if(d<-1) return new Multiplication(new Puissance(e,-1),Puissance.nFoisExpressionNegative(e,d+1));
		else return new Puissance(e,-1);
	}
}
