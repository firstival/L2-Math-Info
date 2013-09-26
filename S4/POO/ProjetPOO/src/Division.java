public class Division extends FonctionBinaire
{
	public Division(){}
	public Division(Expression arg1auche,Expression arg2roite)
	{
		arg1=arg1auche;
		arg2=arg2roite;
	}
	public Division(double i,Expression e)
	{
		arg1=new Constante(i);
		arg2=e;
	}
	public Division(Expression e,double i)
	{
		arg2=new Constante(i);
		arg1=e;
	}

	public double evaluation(InconnuValeur[] inconnu)
	{
		return arg1.evaluation(inconnu)/arg2.evaluation(inconnu);
	}
	public String toString()
	{
		if(((arg1 instanceof Constante)||(arg1 instanceof Inconnue))&&((arg2 instanceof Constante)||(arg2 instanceof Inconnue))) return "("+arg1.toString()+"/"+arg2.toString()+")";
		else if(((arg1 instanceof Constante)||(arg1 instanceof Inconnue))) return arg1.toString()+"/("+arg2.toString()+")";
		else if(((arg2 instanceof Constante)||(arg2 instanceof Inconnue))) return "("+arg1.toString()+")/"+arg2.toString();
		else return arg1.toString()+")/("+arg2.toString();
	}
	/*
	 * Fonction qui simplifie localement (au niveau de l'opération)
	 */
	public Expression simplifierLocalement(Expression e1,Expression e2)
	{
		return Division.regleSimplification(e1,e2);
	}
	/*
	 * Règle de simplification(juste en fonction des arguments de gauche et droite directement) de la division
	 */
	public static Expression regleSimplification(Expression e1,Expression e2)
	{
		if((e1 instanceof Constante)&&(((Constante)e1).getVal()==0)) return new Constante(0);//0/X=0
		else if(e1.toString().equals(e2.toString())) return new Constante(1);//X/X=1
		else if(e1 instanceof Puissance)//X^n/Y
		{
			Puissance tmp1=(Puissance)e1;
			if(e2 instanceof Puissance)//si Y est une puissance, D^m
			{
				Puissance tmp2=(Puissance)e2;
				if(tmp1.getArg().toString().equals(tmp2.getArg().toString())) return new Puissance(tmp1.getArg(),tmp1.getPuissance()-tmp2.getPuissance());//X^n/X^m=X^(n-m)
			}
			else if(tmp1.getArg().toString().equals(e2.toString()))//Si Y==X alors X^n/X=X^(n-1)
			{
				Puissance op=new Puissance(null,tmp1.getPuissance()-1);
				return op.simplifierLocalement(e2);
			}
		}
		else if(e2 instanceof Puissance)//N/D^n
		{
			Puissance tmp2=(Puissance)e2;
			if(e1.toString().equals(tmp2.getArg().toString()))//Si N==D, alors D/D^n=D^(1-X)
			{
				Puissance op=new Puissance(null,1-tmp2.getPuissance());
				return op.simplifierLocalement(e1);
			}
		}
		else if(e1 instanceof Exponentielle)//a^X/Y
		{
			Exponentielle tmp1=(Exponentielle)e1;
			if(e2 instanceof Exponentielle)//Si Y=b^Z
			{
				Exponentielle tmp2=(Exponentielle)e2;
				if(tmp1.getBase()==tmp2.getBase()) return new Exponentielle(tmp1.getBase(),(new Soustraction(tmp1.getArg(), tmp2.getArg())).simplifier());//Si a==b, alors la division donne a^(X-Z)
			}
			else if((e2 instanceof Constante)&&(((Constante)e2).getVal()==tmp1.getBase()))//Si Y==a, alors a^(X-1)
			{
				return new Exponentielle(tmp1.getBase(),Addition.regleSimplification(tmp1.getArg(),new Constante(-1)));
			}
		}
		else if(e2 instanceof Exponentielle)//Y/a^X
		{
			Exponentielle tmp2=(Exponentielle)e2;
			if((e1 instanceof Constante)&&(((Constante)e1).getVal()==tmp2.getBase()))//Si Y==a, alors a^(1-X)
			{
				return new Exponentielle(tmp2.getBase(),Soustraction.regleSimplification(new Constante(1),tmp2.getArg()));
			}
		}
		else if((e1 instanceof Division)&&(e2 instanceof Division))//(a/b)/(c/d)=(a*d)/(b*c)
		{
			Division tmp1=(Division)e1;
			Division tmp2=(Division)e2;
			return Division.regleSimplification(Multiplication.regleSimplification(tmp1.getArgGauche(),tmp2.getArgDroite()),Multiplication.regleSimplification(tmp1.getArgDroite(),tmp2.getArgGauche()));
		}
		return new Division(e1,e2);
	}
	public Expression deriverLocalement(Expression e1, Expression e2)//(U/V)'=(U'V-UV')/V²
	{
		Expression tmp1=Multiplication.regleSimplification(e1,arg2);//U'V
		Expression tmp2=Multiplication.regleSimplification(arg1,e2);//UV'
		Expression tmp3=Soustraction.regleSimplification(tmp1, tmp2);//(U'V-UV')
		Puissance tmp4=new Puissance(null,2);
		tmp4=(Puissance)tmp4.simplifierLocalement(arg2);//V²
		return regleSimplification(tmp3,tmp4);//(U'V-UV')/V²
	}
	public Expression developper()
	{
		return Division.regleSimplification(arg1.developper(), arg2.developper());
	}
	public Expression factoriser()
	{
		return Division.regleSimplification(arg1.factoriser(), arg2.factoriser());
	}
}
