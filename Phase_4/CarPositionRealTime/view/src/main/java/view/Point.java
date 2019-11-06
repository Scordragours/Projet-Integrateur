package view;

public class Point{
    private int X, Y;
    public Point(int X, int Y){
        this.setX(X);
        this.setY(Y);
    }
    public Point(Point Point){
        this.setX(Point.getX());
        this.setY(Point.getY());
    }
    public int getX(){
        return this.X;
    }
    public int getY(){
        return this.Y;
    }
    private void setX(int X){
        this.X = X;
    }
    private void setY(int Y){
        this.Y = Y;
    }
}