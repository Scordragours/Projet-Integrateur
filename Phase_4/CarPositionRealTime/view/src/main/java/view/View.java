package view;

import contract.DirectionRobot;
import contract.IModel;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.io.File;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;

public class View extends JFrame implements Observer{
    private IModel Model;
    private Panel Panel;
    private static String Path = System.getProperty("user.dir") +"\\model\\src\\main\\resources\\Assets\\";
    public View(IModel Model){
        this.setModel(Model);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("City Smart Road");
        this.setResizable(false);
        this.setSize(800/*738*/, 620);
        this.setLocationRelativeTo(null);
        try{
            this.setIconImage(ImageIO.read(new File(Path +"Icone.png")));
        }catch(IOException e){
            e.printStackTrace();
        }
        this.Panel = new Panel();
        this.setContentPane(this.Panel);
        this.setLayout(null);
        this.setVisible(true);
    }
    public IModel getModel(){
        return this.Model;
    }
    public void setModel(IModel Model){
        this.Model = Model;
        this.getModel().getObservable().addObserver(this);
    }
    public void update(Observable o, Object arg){
        float[] Position = this.getModel().getRobotPosition();

        //System.out.println(Position[1]);

        DirectionRobot DirectionRobot = this.getModel().getDirectionRobot();

        this.Panel.setPosition(Position);
        this.Panel.V.setText(this.getModel().getVitesse() +" m/s");
        this.Panel.setDirectionRobot(DirectionRobot);

        float[] distance = this.getModel().getDistance();
        this.Panel.D1.setText(Float.toString(distance[0]) +" m");
        this.Panel.D2.setText(Float.toString(distance[1]) +" m");
        this.Panel.D3.setText(Float.toString(distance[3]) +" m");
        this.Panel.D4.setText(Float.toString(distance[2]) +" m");
        this.Panel.D5.setText(Float.toString(distance[5]) +" m");
        this.Panel.D6.setText(Float.toString(distance[4]) +" m");

        this.Panel.repaint();
    }
}