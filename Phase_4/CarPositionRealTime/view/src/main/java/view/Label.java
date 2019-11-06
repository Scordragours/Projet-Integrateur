package view;

import javax.swing.*;

public class Label extends JLabel{
    private int Width, Height;

    public Label(String Text, int Width, int Height){
        super(Text, SwingConstants.CENTER);
        this.setWidth(Width);
        this.setHeight(Height);
        this.setText(Text);
        setOpaque(false);
    }
    protected void setWidth(int Width){
        this.Width = Width;
    }
    public int getWidth(){
        return this.Width;
    }
    protected void setHeight(int Height){
        this.Height = Height;
    }
    public int getHeight(){
        return this.Height;
    }
}
