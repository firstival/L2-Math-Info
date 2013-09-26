/*
public class TestCercle {
    public static void main(String[] args) {
        Cercle c = new Cercle(3, 8, 2.5);
        System.out.println(c);
        c.deplaceCentre(1, 0.5);
        c.changeRayon(5.25);
        System.out.println(c);
        Point pt = c.getCentre();
        System.out.println(pt);
    }
}
*/


public class TestCercle {
    public static void main(String[] args) {
        Point pt1, pt2;
        Cercle c1, c2;
        pt1 = new Point(4.2, 7.3);
        pt2 = new Cercle(14.7, 62, 5.2);
        c1 = new Cercle(3.56, 7.84, 2.25);
        //c2 = new Point(56.1, 76.9);

        pt1.deplace(0.5, 0.5);
        pt2.deplace(0.3, 0.8);
        ((Cercle)pt2).changeRayon(6.21);
        c1.deplace(0.4, 0.5);
        c1.changeRayon(2.52);
        c1.x = 4.78;
    }
}
