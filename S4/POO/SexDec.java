import java.io.*;

public class SexDec
{
	private int heure;
	private int min;
	private int sec;
	public SexDec(int h,int m,int s)
	{
		heure=h;
		min=m;
		sec=s;
	}
	public SexDec(double h)
	{
		heure=(int)h;
		min=(int)((h-heure)*60);
		sec=(int)((h-heure-min/60)*3600);
	}
	public double getDec()
	{
		return heure+min/60+sec/3600
	}
	public int getH()
	{
		return heure;
	}
	public int getM()
	{
		return min;
	}
	public int getS()
	{
		return sec;
	}
	
	public static void main(String[] args)
	{
		SexDec h=new SexDec(1.25);
		System.out.println(h.getH());
		System.out.println(h.getM());
		System.out.println(h.getS());
	}
}
