package model;

import contract.DirectionRobot;

public class Robot{
    private float X, Y, Vitesse, XPourcent, YPourcent;
    private char Sprite, Points;
    private DirectionRobot DirectionRobot;
    protected float[] Distance = new float[6];

    public Robot(float X, float Y){
        this.setX(X);
        this.setY(Y);
        this.setVitesse(0);
        this.setSprite('R');
    }
    public float getVitesse(){
        return this.Vitesse;
    }
    protected void setVitesse(float Vitesse){
        this.Vitesse = Vitesse;
    }
    protected void Move(float X, float Y,  float XPourcent, float YPourcent, DirectionRobot DirectionRobot){
        this.setX(X);
        this.setY(Y);
        this.setXPourcent(XPourcent);
        this.setYPourcent(YPourcent);
        this.setVitesse(Vitesse);
        this.setDirectionRobot(DirectionRobot);
    }
    public float getX(){
        return this.X;
    }
    public float getY(){
        return this.Y;
    }
    public float getXPourcent(){
        return this.XPourcent;
    }
    public float getYPourcent(){
        return this.YPourcent;
    }
    public char getSprite(){
        return this.Sprite;
    }
    public DirectionRobot getDirectionRobot(){
        return this.DirectionRobot;
    }
    private void setX(float X){
        this.X = X;
    }
    private void setY(float Y){
        this.Y = Y;
    }
    public void setXPourcent(float XPourcent){
        this.XPourcent = XPourcent;
    }
    public void setYPourcent(float YPourcent){
        this.YPourcent = YPourcent;
    }
    private void setSprite(char Sprite){
        this.Sprite = Sprite;
    }
    private void setDirectionRobot(DirectionRobot DirectionRobot){
        this.DirectionRobot = DirectionRobot;
    }
}