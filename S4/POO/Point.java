class Point
{
	protected double x;
	protected double y;
	
	public Point(){}
	public Point(double x0,double y0)
	{
		x=x0;
		y=y0;
	}
	public double getX()
	{
		return x;
	}
	public double getY()
	{
		return y;
	}
	public void setX(double x0)
	{
		x=x0;
	}
	public void setY(double y0)
	{
		y=y0;
	}
	public void deplace(double dx, double dy) {
        x += dx;
        y += dy;
    }
    public String toString() {
        return "Point de coordonnees : " + x + ", " + y;
    }
	
}
