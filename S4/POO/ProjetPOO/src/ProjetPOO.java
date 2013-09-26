import java.util.Scanner;

public class ProjetPOO {

	public static void main(String[] args)
	{
		boolean finProgramme=false;
		int choix=0;
		double eval=0;
		String dx;
		
		String line=null;
		Scanner sc=new Scanner(System.in);
		System.out.println("Veuillez rentrer l'expression arithmétique désirée : ");
		line=sc.nextLine();
		line=line.replaceAll(" ","");
		Equation equ=new Equation(line);
		
		do
		{
			/*
			 * Menu
			 */
			System.out.println();
			System.out.println("Que voulez vous faire?");
			System.out.println("1 : Taper une nouvelle expression");
			System.out.println("2 : Afficher l'expression");
			System.out.println("3 : Evaluer l'expression étant donnée une valeur par inconnu");
			System.out.println("4 : Afficher la derivée partielle l'expression");
			System.out.println("5 : Afficher la simplification de l'expression");
			System.out.println("6 : Quitter le programme");
			System.out.print("Que voulez vous faire? : ");
			choix=sc.nextInt();
			System.out.println();
			switch(choix)
			{
				case 1:
					System.out.println("Veuillez rentrer l'expression arithmétique désirée : ");
					sc.nextLine();
					line=sc.nextLine();
					line=line.replaceAll(" ","");
					equ=new Equation(line);
					break;
				case 2:
					System.out.println(equ);
					break;
				case 3:
					eval=equ.getEvaluation();
					System.out.println("L'expression "+equ+"   vaut "+eval);
					break;
				case 4:
					sc.nextLine();
					do
					{
						System.out.print("Dériver selon quelle variable? : ");
						dx=sc.nextLine();	
					}
					while(!equ.estDedans(dx));//Tant qu'on donne de mauvaise inconnu
					System.out.println("d("+equ+")/d"+dx+" = "+equ.getDerivation(dx));
					break;
				case 5:
					System.out.println(equ+" --> "+equ.getSimplification());
					break;
				case 6:
					finProgramme=true;
					break;
				default:
					System.out.println("Choix incorrecte, Veuillez taper le numéro associé à l'un des choix proposés");
					break;
			}
		}
		while(!finProgramme);
		
	}

}
