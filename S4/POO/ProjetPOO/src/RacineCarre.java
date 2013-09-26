
public class RacineCarre extends Puissance
{
	public RacineCarre(){}
	/*
	 * La racine carré n'est que la puissance 0.5
	 */
	public RacineCarre(Expression e)
	{
		super(e,0.5);
	}
	public String toString()
	{
		return "√("+arg.toString()+")";//toString spécial pour la racine carré pour afficher le symble '√'
	}

}
