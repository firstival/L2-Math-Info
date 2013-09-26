/*
public class Cercle
{
	protected Point p;
	protected double r;
	public Cercle(){}
	public Cercle(double x,double y,double r)
	{
		p=new Point(x,y);
		this.r=r;
	}
	
	public void deplaceCentre(double x,double y)
	{
		p=new Point(x,y);
	}
	public void deplaceCentre(Point p0)
	{
		p=p0;
	}
	public void changeRayon(double a)
	{
		r=a;
	}
	public Point getCentre()
	{
		return p;
	}
	public String toString()
	{
		return p.toString()+"\nRayon : "+r;
	}
}
*/

public class Cercle extends Point
{
	protected double r;
	public Cercle(){}
	public Cercle(double x,double y,double r)
	{
		super(x,y);
		this.r=r;
	}
	public void deplaceCentre(double x,double y)
	{
		super.x=x;
		super.y=y;
	}
	public void changeRayon(double a)
	{
		r=a;
	}
	public Point getCentre()
	{
		return new Point(x,y);
	}
	public String toString()
	{
		return super.toString()+"\nRayon : "+r;
	}
}
