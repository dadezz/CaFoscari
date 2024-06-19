package ProveEsami;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.util.function.Function;

/*Definiamo in Java 8+ un sistema di classi ed interfacce che rappresentano punti e solidi nello spazio R3. Per
semplificare i calcoli legati alle coordinate assumiamo che tali solidi siano sempre orientati ortogonalmente rispetto
agli assi cartesiani. */
public class Esame200131 {
    
}


class Point {
    double x, y, z;
    Point(double x_, double y_, double z_){
        x = x_;
        y = y_;
        z = z_;
    }
    Point move(double dx, double dy, double dz) {
        return new Point(x+dx, y+dy, z+dz);
    }
}


interface Solid extends Comparable<Solid> {
    double area();
    double volume();
    
    PositionedSolid at(Point origin);
    
    static <S extends Solid> int compareBy(Function<S, Double> f, S s1, S s2) {
        return Double.compare(f.apply(s1), f.apply(s2));
    }
    
    static <S extends Solid> Comparator<S> comparatorBy(Function<S, Double> f) {
        return (s1, s2) -> compareBy(f, s1, s2);
    }
    
    default int compareTo(Solid s) {
        return compareBy((x) -> x.volume(), this, s);
    }
}
    
interface Polyhedron extends Solid {
    double perimeter();
    
    @Override
    PositionedPolyhedron at(Point origin);
}
    
interface PositionedSolid {
    Point origin();
}

interface PositionedPolyhedron extends PositionedSolid, Iterable<Point> {}

/*Si implementi la classe Cube, con il suo costruttore parametrico sulla lunghezza del lato ed i metodi
richiesti dalle interfacce implementate */

class Cube implements Polyhedron {
    private double side; // lato del cubo
    /* implementare il resto */

    Cube(double l){
        side = l;
    }

    public double perimeter() {
        return side * 12;
    }

    public PositionedPolyhedron at(Point Origin){
        return new PositionedPolyhedron() {

            Point o = Origin;
            @Override
            public Point origin() {
                return o;
            }

            @Override
            public Iterator<Point> iterator() {
                    final Point u = o.move(side, side, side);
                    final Point[] ps = new Point[]{
                            o, o.move(side, 0., 0.), o.move(0., side, 0.), o.move(0., 0., side),
                            u, u.move(side, 0., 0.), u.move(0., side, 0.), u.move(0., 0., side)
                    };                    
                    return Arrays.asList(ps).iterator();
                };
            }
            
        ;
    }

    public double area() {
        return 6 * side * side;
    }

    public double volume() {
        return side * side * side;
    }


}