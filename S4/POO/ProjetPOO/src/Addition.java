import java.util.Vector;

public class Addition extends FonctionBinaire
{
	public Addition(){}
	public Addition(Expression gauche,Expression droite)
	{
		arg1=gauche;
		arg2=droite;
	}
	public Addition(double i,Expression e)
	{
		arg1=new Constante(i);
		arg2=e;
	}
	public Addition(Expression e,double i)
	{
		arg1=e;
		arg2=new Constante(i);
	}
	public double evaluation(InconnuValeur[] inconnu)
	{
		return arg1.evaluation(inconnu)+arg2.evaluation(inconnu);
	}
	public String toString()
	{
		String tmp1=arg1.toString();
		String tmp2=arg2.toString();
		if(tmp2.charAt(0)=='-') return tmp1+tmp2;//Si l'affichage de tmp2 commence par un '-' alors on ne fait pas apparaitre de signe '+'
		else return tmp1+'+'+tmp2;
	}
	/*
	 * Fonction qui simplifie localement (au niveau de l'opération)
	 */
	public Expression simplifierLocalement(Expression e1, Expression e2)
	{
		return Addition.regleSimplification(e1,e2);
	}
	
	public static Expression regleSimplification(Expression e1,Expression e2)
	{
		if((e1 instanceof Constante)&&(e2 instanceof Constante)) return new Constante( (((Constante)e1).getVal()) + ((Constante)e2).getVal() );//Constante+Constante=Constante
		else if((e1 instanceof Constante)&&((((Constante)e1).getVal())==0)) return e2;//0+X=X
		else if((e2 instanceof Constante)&&((((Constante)e2).getVal())==0)) return e1;//X+0=X
		else if(e1.toString().equals(e2.toString())) return Multiplication.regleSimplification(new Constante(2),e1);//X+X=2*X
		else if( (e1.toString().equals("-"+e2.toString())) || (e1.toString().equals("-"+e2.toString()))) return new Constante(0);//X+(-X) ou (-X)+X  = 0
		else if(e1 instanceof Multiplication)
		{
			Multiplication tmp=(Multiplication)e1;
			if(tmp.getArgDroite().toString().equals(e2.toString())) return new Multiplication(Addition.regleSimplification(tmp.getArgGauche(), new Constante(1)),tmp.getArgDroite());//nX+X=(n+1)X
			else if(tmp.getArgGauche().toString().equals(e2.toString())) return new Multiplication(Addition.regleSimplification(tmp.getArgDroite(), new Constante(1)),tmp.getArgGauche());//Xn+X=(n+1)X
		}
		
		else if(e2 instanceof Multiplication)
		{
			if(!((e1 instanceof Constante)&&((((Constante)e1).getVal()!=1)||(((Constante)e1).getVal()!=1))))
			{
				Multiplication tmp=(Multiplication)e2;
				if(tmp.getArgDroite().toString().equals(e1.toString())) return new Multiplication(Addition.regleSimplification(tmp.getArgGauche(), new Constante(1)),tmp.getArgDroite());//X+nX=(n+1)X
				else if(tmp.getArgGauche().toString().equals(e1.toString())) return new Multiplication(Addition.regleSimplification(tmp.getArgDroite(), new Constante(1)),tmp.getArgGauche());//X+Xn=(n+1)X
		
			}
		}
		return new Addition(e1,e2);
	}
	
	public Expression deriverLocalement(Expression e1, Expression e2)
	{
		return Addition.regleSimplification(e1,e2);
	}
	/*
	 * Développer au niveau d'une addition revient à développer l'argument de gauche et de droite, et a addition tout ça
	 */
	public Expression developper()
	{
		return new Addition(arg1.developper(),arg2.developper());
	}
	/*
	 * Pour factoriser, on liste toutes les expressions de l'addition (en prenant soin de developper au maximum en addition en passant)
	 */
	public Expression factoriser()
	{
		Vector<Expression> liste=new Vector<Expression>();
		Addition.ListeAddition(this, liste);
		Expression[] tab=(Expression[])liste.toArray(new Expression[0]);
		return Addition.factoriserAux(tab, 1);//On envoie le tableau remplie des Expressions qui étaient les arguments des additions à factoriserAux qui va parser ces Expressions, et les factorisers
	}
	/*
	 * Créer une addition de n fois l'expression e (3x -> x+x+x), dans le cas où n est positive
	 */
	public static Expression nFoisExpressionPositive(Expression e,double d)
	{
		if(d>1) return new Addition(e,nFoisExpressionPositive(e,d-1));
		else return Multiplication.regleSimplification(new Constante(d),e);
	}
	/*
	 * Créer une addition de n fois l'expression e ((-3)x -> (-x)+(-x)+(-x)
	 */
	public static Expression nFoisExpressionNegative(Expression e,double d)
	{
		if(d<-1) return new Addition(nFoisExpressionNegative(e,d+1),Multiplication.propagerNegation(e));
		else if(d==-1) return Multiplication.propagerNegation(e);	
		else return Multiplication.regleSimplification(new Constante(d),e);
	}
	/*
	 * Remplie 'liste' de toute les expressions différentes de l'addition(bref créer une liste de tout les arguments des additions, dans le cas d'addition en cascade).
	 */
	public static void ListeAddition(Expression e,Vector<Expression> liste)
	{
		if(e instanceof Addition)
		{
			Addition tmp=(Addition)e;
			ListeAddition(tmp.getArgGauche(),liste);
			ListeAddition(tmp.getArgDroite(),liste);
		}
		else liste.add(e);	
	}
	
	private static Expression factoriserAux(Expression[] tab,int rechercheConstante)
	{
		double k=0;
		int i=0;
		int j=0;
		boolean dernier=true;
		Expression tmp=null;
		//Si cette variable vaut 1, alors on recherche toute les constantes, et les additionnes toutes entre elles dans k
		if(rechercheConstante==1)
		{
			for(i=0;i<tab.length;i++)
			{
				if(tab[i]!=null)
				{
					if(tab[i] instanceof Constante)
					{
						k+=((Constante)tab[i]).getVal();
						tab[i]=null;//En mettant à null, on élimine les Constantes du tableau pour pas retomber dessus plus tard
					}
					else dernier=false;
				}
			}
			//Si k est égal a 0, soit on a pas trouver de Constante, soit leur addition successive se sont simplifier en 0, dans tout les cas, ça ne sert a rien d'ajouter 0
			if(dernier) return new Constante(k);//Si dernier==true alors c'est qu'il n'y a que des Constantes, on renvoie donc une constante sans rappeler la fonction
			else if(k!=0) return new Addition(new Constante(k),factoriserAux(tab,0));//Sinon c'est qu'il reste d'autre expression à parser, et rappelle récursivement la fonction
		}
		dernier=true;
		for(i=0;i<tab.length;i++)
		{
			if(tab[i]!=null)
			{
				if(tmp==null)//Si tmp==null, c'est qu'on a pas encore trouvé une expression a factoriser
				{
					tmp=tab[i];//on met donc tab[i] dans tmp, et on incrémente j qui représente le nombre de fois que l'élément apparait dans la l'addition
					j++;
					tab[i]=null;//On met null dans le tableau pour pas le voir dans des passes ultérieures
				}
				else//sinon tmp n'est pas null, on est donc déjà à la recherche d'une expression
				{
					if(tab[i].toString().equals(tmp.toString()))//Si l'expression correspond, on incrémente j,et on met null dans le tableau
					{
						j++;
						tab[i]=null;
					}
					//Si l'expression correspond mais avec un '-', on décrémente j,et on met null dans le tableau, car on vient de trouver un opposé à l'expression
					else if((tab[i].toString().equals("-"+tmp.toString()))||(("-"+tab[i].toString()).equals(tmp.toString())))
					{
						j--;
						tab[i]=null;
					}
					else dernier=false;//Sinon, ca veut dire que l'expression est différente de tmp, donc tmp n'est pas la derniere expression du tableau
				}
			}
		}
		//Si on a pas rencontrer d'autre expression que tmp, dernier==true, donc on arrete la fonction vu qu'on vient de factoriser la derniere expression
		if(dernier) return Multiplication.regleSimplification(new Constante(j),tmp);
		//Si on ne trouve qu'une fois l'expression, on ne va pas la remplacer par 1*X, on revoit juste X+appelrecursif()
		else if(j==1) return new Addition(tmp,factoriserAux(tab,0));
		//Mais si on en trouve plusieurs, alors on factorise tmp par j, et on continue -> nX+appelrecursif()
		else return new Addition(Multiplication.regleSimplification(new Constante(j),tmp),factoriserAux(tab,0));
	}

}
