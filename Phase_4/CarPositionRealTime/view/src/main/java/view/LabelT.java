package view;

import javax.swing.*;

public class LabelT extends JLabel{
    private int Width, Height, X, Y;

    public LabelT(String Text, int X, int Y, int Width, int Height){
        super(Text, SwingConstants.CENTER);
        this.setWidth(Width);
        this.setHeight(Height);
        this.setX(X);
        this.setY(Y);
        this.setText(Text);
        setOpaque(false);
    }
    public int getWidth(){
        return this.Width;
    }
    public int getHeight(){
        return this.Height;
    }
    public int getX(){
        return this.X;
    }
    public int getY(){
        return this.Y;
    }
    protected void setWidth(int Width){
        this.Width = Width;
    }
    protected void setHeight(int Height){
        this.Height = Height;
    }
    protected void setX(int X){
        this.X = X;
    }
    protected void setY(int Y){
        this.Y = Y;
    }
}