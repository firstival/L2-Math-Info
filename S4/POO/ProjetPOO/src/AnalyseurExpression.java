import java.util.Vector;


public class AnalyseurExpression {
	public static Expression analyser(String line,Vector<InconnuValeur> tabInconnu)
	{
		char[] chaine=line.toCharArray();
		int i=0;
		int j=1;
		/*
		 * Cas ou on a une parenthèse ouvrante en 1er caractère, soit on a une formule du type (...)+(...) et la les parenthèses sont utiles,mais si on a (...(..)+(..)), le 1er set de parenthèse est inutile
		 * On rappelle donc la fonction, sans ces parenthèses
		 */
		if(chaine[0]=='(')
		{
			boolean parenthese_inutile=true;
			for(i=1;i<chaine.length;i++)
			{
				if(j==0)
				{
					parenthese_inutile=false;
					break;
				}
				
				if(chaine[i]=='(') j++;
				else if(chaine[i]==')') j--;
			}
			if(parenthese_inutile) return AnalyseurExpression.analyser(line.substring(1, line.length()-1),tabInconnu);
		}
		j=0;
		int position_add=0;
		int position_moins=0;
		int position_mult=0;
		int position_div=0;
		int position_accent_circon=0;
		
		
		for(i=0;i<chaine.length;i++)
		{
			if(chaine[i]=='(') j++;
			else if(chaine[i]==')') j--;
			else if((j==0)&&(chaine[i]=='+'))
			{
				position_add=i;
				break;
			}
			else if((j==0)&&(chaine[i]=='*')&&(position_mult==0)) position_mult=i;
			else if((j==0)&&(chaine[i]=='/')&&(position_div==0)) position_div=i;
			else if((j==0)&&(chaine[i]=='^')&&(position_accent_circon==0)) position_accent_circon=i;
			else if((j==0)&&(chaine[i]=='-')) position_moins=i;
		}
		
		if((position_add==0)&&(position_moins==0)&&(position_div==0)&&(position_mult==0))//Si aucun des symboles de fonctions binaires n'ont été trouvé, alors c'est qu'il y a forcément une fonction unaire a traiter
		{
			if(chaine[0]=='-') return new Oppose(AnalyseurExpression.analyser(line.substring(1,line.length()),tabInconnu));//Si le 1er symbole est un '-', alors ce n'est pas le symbole de la soustraction mais de l'opposé(qui est une fonction unaire)
			else if(line.matches("^cos.*")) return new Cosinus(AnalyseurExpression.analyser(line.substring(4, line.length()-1), tabInconnu));
			else if(line.matches("^sin.*")) return new Sinus(AnalyseurExpression.analyser(line.substring(4, line.length()-1), tabInconnu));
			else if(line.matches("^tan.*")) return new Tangente(AnalyseurExpression.analyser(line.substring(4, line.length()-1), tabInconnu));
			else if(line.matches("^ln.*")) return new Logarithme(AnalyseurExpression.analyser(line.substring(3, line.length()-1), tabInconnu));
			else if(line.matches("^sqrt.*")) return new RacineCarre(AnalyseurExpression.analyser(line.substring(5, line.length()-1), tabInconnu));
			else if(line.matches("^e\\^\\(.*")) return new Exponentielle(Math.E,AnalyseurExpression.analyser(line.substring(3, line.length()-1), tabInconnu));//exponentielle naturel
			else if(line.matches("^e\\^.*")) return new Exponentielle(Math.E,AnalyseurExpression.analyser(line.substring(2, line.length()), tabInconnu));//exponentielle naturel sans parenthèse
			else if(line.matches("^.+\\^\\([0-9]+")) return new Puissance(AnalyseurExpression.analyser(line.substring(0, position_accent_circon), tabInconnu),Integer.parseInt(line.substring(position_accent_circon+2, line.length()-1)));//Puissance avec puissance sous parenthèse (par exemple négatif)
			else if(line.matches("^.+\\^[0-9]+")) return new Puissance(AnalyseurExpression.analyser(line.substring(0, position_accent_circon), tabInconnu),Integer.parseInt(line.substring(position_accent_circon+1, line.length())));//Puissance
			else if(line.matches("^[0-9]+\\^.+"))return new Exponentielle(Integer.parseInt(line.substring(0, position_accent_circon)),AnalyseurExpression.analyser(line.substring(position_accent_circon+1, line.length()), tabInconnu));//exponentielle avec base précisé
			else if(line.matches("^\\([0-9]+\\)\\^.+"))return new Exponentielle(Integer.parseInt(line.substring(1, position_accent_circon-1)),AnalyseurExpression.analyser(line.substring(position_accent_circon+1, line.length()-1), tabInconnu));//exponentielle avec base précisé (base entre parenthèses)
			else if((line.matches("[0-9]+"))||(line.matches("\\-[0-9]+"))) return new Constante(Integer.parseInt(line));//Cas de la constante
			//Sinon après tout, ça veut dire qu'on est tombé sur une inconnu
			else
			{
				InconnuValeur x=new InconnuValeur(line);
				if(!(tabInconnu.contains(x))) tabInconnu.add(x);//Si le Vector ne contient pas encore d'inconnu avec ce nom là, on l'ajoute au Vector
				return new Inconnue(line);
			}
		}
		else//Sinon, on est bien tombé sur une fonction binaire, reste à savoir laquelle
		{
			if(position_add!=0) return new Addition(AnalyseurExpression.analyser(line.substring(0, position_add), tabInconnu),AnalyseurExpression.analyser(line.substring(position_add+1,line.length()), tabInconnu));
			else if(position_moins!=0) return new Soustraction(AnalyseurExpression.analyser(line.substring(0, position_moins), tabInconnu),AnalyseurExpression.analyser(line.substring(position_moins+1,line.length()), tabInconnu));
			else if(position_mult!=0) return new Multiplication(AnalyseurExpression.analyser(line.substring(0, position_mult), tabInconnu),AnalyseurExpression.analyser(line.substring(position_mult+1,line.length()), tabInconnu));
			else return new Division(AnalyseurExpression.analyser(line.substring(0, position_div), tabInconnu),AnalyseurExpression.analyser(line.substring(position_div+1,line.length()), tabInconnu));
		}
	}
}
