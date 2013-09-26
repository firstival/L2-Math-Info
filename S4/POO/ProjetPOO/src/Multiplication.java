import java.util.Vector;

public class Multiplication extends FonctionBinaire
{
	
	public Multiplication(){}
	public Multiplication(Expression gauche,Expression droite)
	{
		arg1=gauche;
		arg2=droite;
	}
	public Multiplication(double i,Expression e)
	{
		arg1=new Constante(i);
		arg2=e;
	}
	public Multiplication(Expression e,double i)
	{
		arg2=new Constante(i);
		arg1=e;
	}
	public Multiplication(double a,double b)
	{
		arg1=new Constante(a);
		arg2=new Constante(b);
	}
	public double evaluation(InconnuValeur[] inconnu)
	{
		return arg1.evaluation(inconnu)*arg2.evaluation(inconnu);
	}
	public String toString()
	{
		String tmp1;
		String tmp2;
		if(((arg1 instanceof Constante)&&(((Constante)arg1).getVal()>=0))||(arg1 instanceof Inconnue)||(arg1 instanceof FonctionUnaire)||(arg1 instanceof Multiplication)) tmp1=arg1.toString();
		else tmp1="("+arg1.toString()+")";
		if(((arg2 instanceof Constante)&&(((Constante)arg2).getVal()>=0))||(arg2 instanceof Inconnue)||(arg2 instanceof FonctionUnaire)||(arg2 instanceof Multiplication)) tmp2=arg2.toString();
		else tmp2="("+arg2.toString()+")";
		return tmp1+"*"+tmp2;
	}
	/*
	 * Fonction qui simplifie localement (au niveau de l'opération)
	 */
	public Expression simplifierLocalement(Expression e1,Expression e2)
	{
		return Multiplication.regleSimplification(e1,e2);
	}
	public Expression deriverLocalement(Expression e1, Expression e2)
	{
		Expression tmp1=Multiplication.regleSimplification(e1,arg2);//u'*v
		Expression tmp2=Multiplication.regleSimplification(arg1,e2);//u*v'
		return Addition.regleSimplification(tmp1,tmp2);//u'v + uv', que l'on simplifie selon les règles de l'addition
	}
	
	public static Expression regleSimplification(Expression e1, Expression e2)
	{
		if(e1 instanceof Constante)
		{
			Constante tmp1=(Constante)e1;
			if(tmp1.getVal()==0.) return new Constante(0);//0*a=0
			else if(tmp1.getVal()==1.) return e2;//a*1=a
			else if(tmp1.getVal()<0) return Oppose.regleSimplification(Multiplication.regleSimplification(new Constante(-tmp1.getVal()),e2));//(-5)*X=-(5*X)
			else if(e2 instanceof Constante) return new Constante(tmp1.getVal()*((Constante)e2).getVal());//2*3=6
			else if(e2 instanceof Multiplication)
			{
				Multiplication tmp2=(Multiplication)e2;
				if(tmp2.getArgGauche() instanceof Constante) return regleSimplification(new Constante(tmp1.getVal()*((Constante)tmp2.getArgGauche()).getVal()), tmp2.getArgDroite());//2*3*a=6*a
				else if(tmp2.getArgDroite() instanceof Constante) return regleSimplification(new Constante(tmp1.getVal()*((Constante)tmp2.getArgDroite()).getVal()), tmp2.getArgGauche());//2*a*3=6*a
			}
			else if(e2 instanceof Exponentielle)
			{
				Exponentielle tmp2=(Exponentielle)e2;
				if(tmp2.getBase()==tmp1.getVal())
				{
					return new Exponentielle(tmp2.getBase(),Addition.regleSimplification(tmp2.getArg(),new Constante(1)));//a*a^X=a^(X+1)
				}
			}
			else if(e2 instanceof Puissance)
			{
				Puissance tmp2=(Puissance)e2;
				if(tmp2.getArg().toString().equals(tmp1.toString()))
				{
					return new Puissance(tmp2.getArg(),tmp2.getPuissance()+1);//X*X^n=X^(n+1)
				}
			}
			else if(e2 instanceof Oppose)
			{
				Oppose tmp2=(Oppose)e2;
				if(tmp1.getVal()<0) return regleSimplification(new Constante((-1)*tmp1.getVal()),tmp2.getArg());//(-a)*(-X)=a*X
				else return new Oppose(regleSimplification(e1,tmp2.getArg()));//a*(-X)=-(a*X)
			}
		}
		else if(e1 instanceof Puissance)
		{
			Puissance tmp1=(Puissance)e1;
			if(e2.toString().equals(tmp1.getArg().toString())) return new Puissance(tmp1.getArg(),tmp1.getPuissance()+1);//X^n*X=X^(n+1)
			else if(e2 instanceof Puissance)
			{
				Puissance tmp2=(Puissance)e2;
				if(tmp2.getArg().toString().equals(tmp1.getArg().toString())) return new Puissance(tmp1.getArg(),tmp1.getPuissance()+tmp2.getPuissance());//X^n * X^m = X^(n+m)
			}
		}
		else if(e1 instanceof Exponentielle)
		{
			Exponentielle tmp1=(Exponentielle)e1;
			if(e2.toString().equals(tmp1.getArg().toString())) return new Exponentielle(tmp1.getBase(),Addition.regleSimplification(tmp1.getArg(),new Constante(1)));//a*a^X=a^(X+1)
			else if(e2 instanceof Exponentielle)
			{
				Exponentielle tmp2=(Exponentielle)e2;
				if(tmp2.getBase()==tmp1.getBase()) return new Exponentielle(tmp1.getBase(),Addition.regleSimplification(tmp1.getArg(), tmp2.getArg()));//a^X * a^Y = a^(X+Y)
			}
		}
		else if((e2 instanceof Division)&&((Division)e2).getArgDroite().toString().equals(e1.toString())) return ((Division)e2).getArgGauche();//X*(Y/X)=Y
		/*
		 * Ce qui marche comme simplification pour X*Y marche aussi pour Y*X (assiociativité de la multiplication).
		 * A partir d'ici, c'est donc comme en haut, sauf que à la place de e1 on a e2 et e2 on a e1
		 */
		else if(e2 instanceof Constante)
		{
			Constante tmp2=(Constante)e2;
			if(((Constante)e2).getVal()==0.) return new Constante(0);//0*a=0
			else if(((Constante)e2).getVal()==1.) return e1;//a*1=a
			else if(tmp2.getVal()<0) return Oppose.regleSimplification(Multiplication.regleSimplification(new Constante(-tmp2.getVal()),e1));
			else if(e1 instanceof Multiplication)
			{
				Multiplication tmp1=(Multiplication)e1;
				if(tmp1.getArgGauche() instanceof Constante) return regleSimplification(new Constante(tmp2.getVal()*((Constante)tmp1.getArgGauche()).getVal()), tmp1.getArgDroite());//1*3*a=6*a
				else if(tmp1.getArgDroite() instanceof Constante) return regleSimplification(new Constante(tmp2.getVal()*((Constante)tmp1.getArgDroite()).getVal()), tmp1.getArgGauche());//1*a*3=6*a
			}
			else if(e1 instanceof Exponentielle)
			{
				Exponentielle tmp1=(Exponentielle)e1;
				if(tmp1.getBase()==tmp2.getVal())
				{
					return new Exponentielle(tmp1.getBase(),Addition.regleSimplification(tmp1.getArg(),new Constante(1)));//1*1^(x+3)=1^(x+4)
				}
			}
			else if(e1 instanceof Puissance)
			{
				Puissance tmp1=(Puissance)e1;
				if(tmp1.getArg().toString().equals(tmp2.toString()))
				{
					return new Puissance(tmp1.getArg(),tmp1.getPuissance()+1);//1*1^n=1^(n+1)
				}
			}
			else if(e1 instanceof Oppose)
			{
				Oppose tmp1=(Oppose)e1;
				if(tmp2.getVal()<0) return regleSimplification(new Constante((-1)*tmp2.getVal()),tmp1.getArg());//(-a)*(-X)=a*X
				else return new Oppose(regleSimplification(e2,tmp1.getArg()));//a*(-X)=-(a*X)
			}
		}
		else if(e2 instanceof Puissance)
		{
			Puissance tmp2=(Puissance)e2;
			if(e1.toString().equals(tmp2.getArg().toString())) return new Puissance(tmp2.getArg(),tmp2.getPuissance()+1);//X^n*X=X^(n+1)
		}
		else if(e2 instanceof Exponentielle)
		{
			Exponentielle tmp2=(Exponentielle)e2;
			if(e1.toString().equals(tmp2.getArg().toString())) return new Exponentielle(tmp2.getBase(),Addition.regleSimplification(tmp2.getArg(),new Constante(1)));//a*a^X=a^(X+1)
		}
		else if((e1 instanceof Division)&&((Division)e1).getArgDroite().toString().equals(e2.toString())) return ((Division)e1).getArgGauche();
		
		else if(e1.toString().equals(e2.toString())) return new Puissance(null,2).simplifierLocalement(e1);//X*X=X²
		return new Multiplication(e1,e2);
	}
	
	
	
	public Expression developper()
	{
		Expression tmp1=arg1.developper();
		Expression tmp2=arg2.developper();
		if((tmp1 instanceof Constante)&&(((Constante)tmp1).getVal()>0))//nX=X+X+X....+X (n fois)
		{
			return Addition.nFoisExpressionPositive(tmp2,((Constante)tmp1).getVal());
		}
		else if((tmp2 instanceof Constante)&&(((Constante)tmp2).getVal()>0))//Xn=X+X+X....+X (n fois)
		{
			return Addition.nFoisExpressionPositive(tmp1,((Constante)tmp2).getVal());
		}
		else if((tmp1 instanceof Constante)&&(((Constante)tmp1).getVal()<0))//(-n)X=-X-X-X....-X (n fois)
		{
			return Addition.nFoisExpressionNegative(tmp2,((Constante)tmp1).getVal());
		}
		else if((tmp2 instanceof Constante)&&(((Constante)tmp2).getVal()<0))//X(-n)=-X-X-X....-X (n fois)
		{
			return Addition.nFoisExpressionNegative(tmp1,((Constante)tmp2).getVal());
		}
		else
		{
			Vector<Expression> liste1= new Vector<Expression>();
			Vector<Expression> liste2= new Vector<Expression>();
			Addition.ListeAddition(tmp1,liste1);
			Addition.ListeAddition(tmp2,liste2);
			
			Expression[] tab1=(Expression[])liste1.toArray(new Expression[0]);//Ce tableau contient toute les expressions séparé par un "+" ou "-" contenu dans l'argument de gauche de la multiplication
			Expression[] tab2=(Expression[])liste2.toArray(new Expression[0]);//Ce tableau contient toute les expressions séparé par un "+" ou "-" contenu dans l'argument de droite de la multiplication
			return developperAux(tab1,tab2,0,0);//On développe tout les éléments de tab1 par ceux de tab2 l'un après l'autre (on développe quoi...)
		}
	}
	/*
	 * La factorisation d'un multiplication ici revient à rassembler les mêmes termes au sain d'une multiplication, de les mettres dans une puissance, et de les liés par la multiplication : X*U*X=X²*U
	 */
	public Expression factoriser()
	{
		Vector<Expression> liste=new Vector<Expression>();
		ListeMultiplication(this,liste);//On liste les éléments de la multiplication
		Expression[] tab=(Expression[])liste.toArray(new Expression[0]);
		return factoriserAux(tab,1);//On les factorises
	}
	/*
	 * Créer un arbre d'addition de multiplication en fonction de tab1 et tab2
	 * (tab1 correspond a l'argument a gauche de la multiplication a l'origine du developpement, tab2 a l'argument de droite
	 * 0<=i<tab1.length et 0<=j<tab2.length
	 */
	private static Expression developperAux(Expression[] tab1,Expression[] tab2,int i,int j)
	{
		if((i<tab1.length-1)||(j<tab2.length-1))
		{
			if(i==tab1.length-1) return new Addition(Multiplication.regleSimplification(tab1[i], tab2[j]),developperAux(tab1,tab2,0,j+1));
			else return new Addition(Multiplication.regleSimplification(tab1[i], tab2[j]),developperAux(tab1,tab2,i+1,j));
		}
		else return Multiplication.regleSimplification(tab1[tab1.length-1], tab2[tab2.length-1]);//Cas d'arrêt
	}
	//Liste les éléments d'une multiplication (tout les éléments qui sont séparé par une multiplication)
	public static void ListeMultiplication(Expression e,Vector<Expression> liste)
	{
		if(e instanceof Multiplication)// Si e est une multiplication, on ajoute les éléments de gauche, puis de droite
		{
			Multiplication tmp=(Multiplication)e;
			ListeMultiplication(tmp.getArgGauche(),liste);
			ListeMultiplication(tmp.getArgDroite(),liste);
		}
		else liste.add(e);//Sinon ce n'est pas une multiplication, et on ajoute l'élément
	}
	
	private static Expression factoriserAux(Expression[] tab,int rechercheConstante)
	{
		double k=1;
		int i=0;
		int j=0;
		Expression tmp=null;
		boolean dernier=true;
		//Si cette variable vaut 1, alors on recherche toute les constantes, et les multiplies tous entre elles dans k
		if(rechercheConstante==1)
		{
			for(i=0;i<tab.length;i++)
			{
				if(tab[i]!=null)
				{
					if(tab[i] instanceof Constante)
					{
						k*=((Constante)tab[i]).getVal();
						tab[i]=null;
					}
					else dernier=false;
				}
			}
			//Si k est égal a 1, soit on a pas trouver de Constante, soit leur multiplication successive se sont simplifier en 1, dans tout les cas, ça ne sert a rien de factoriser par 1
			if(dernier) return new Constante(k);//Si dernier=true, on a rien trouver d'autre que des Constantes, on s'arrete donc la
			else if(k!=1) return new Multiplication(new Constante(k),factoriserAux(tab,0));
		}
		dernier=true;
		for(i=0;i<tab.length;i++)
		{
			if(tab[i]!=null)
			{
				if(tmp==null)//Si tmp==null, c'est qu'on a pas encore trouvé une expression a factoriser
				{
					tmp=tab[i];//on met donc tab[i] dans tmp, et on incrémente j qui représente le nombre de fois que l'élément apparait dans la multiplication
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
					else dernier=false;//Sinon, ca veut dire que l'expression est différente de tmp, donc tmp n'est pas la derniere expression du tableau
				}
			}
		}
		//Si dernier=true, alors c'est qu'on rencontrer qu'une seul expression (meme plusieur fois) et qu'il faut s'arreter
		if(dernier) return new Puissance(tmp,j).simplifierLocalement(tmp);
		//Si on ne trouve qu'une fois l'expression, on ne va pas la remplacer par X^1, on revoit juste X*appelrecursif()
		if(j==1) return new Multiplication(tmp,factoriserAux(tab,0));
		//Mais si on en trouve plusieur, alors on transforme en puissance
		else return new Multiplication(new Puissance(tmp,j).simplifierLocalement(tmp),factoriserAux(tab,0));
	}
	
	/*
	 * Cette fonction sert a propager une négation a traver une expression : -1*(X)
	 */
	public static Expression propagerNegation(Expression e)
	{
		if(e instanceof Soustraction) return new Addition(propagerNegation(((Soustraction)e).getArgGauche()),((Soustraction)e).getArgDroite());//Si X=a-b, alors on propage sur a, et on l'additionne à b
		if(e instanceof Addition)     return new Addition(propagerNegation(((Addition)e).getArgGauche()),propagerNegation(((Addition)e).getArgDroite()));// Si X=a+b alors on progage sur a et b, et on les additionnes
		else if(e instanceof Oppose) return ((Oppose)e).getArg();//Si X=-Y alors on renvoue Y
		else return new Oppose(e);//Sinon on renvoie l'oppose de l'expression (vu qu'on ne peux pas la propager plus loin).
	}
}
