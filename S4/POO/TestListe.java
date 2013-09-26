public class TestListe
{
	public static void main(String[] argv)
	{
		Liste<Integer> l=new Liste<Integer>();
		l.insererDebut(5);
		l.insererDebut(4);
		l.insererDebut(3);
		l.insererDebut(2);
		l.insererDebut(1);
		
		System.out.println(l);
		l.insererPositionDonnee(10,3);
		System.out.println(l);
		System.out.println(l.getTaille());
	}
}
