package view;

import contract.DirectionRobot;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Panel extends JPanel{
    private float[] Position = new float[] {(float) 30, (float) 30};
    private DirectionRobot DirectionRobot = contract.DirectionRobot.TOP;
    public Label D1, D2, D3, D4, D5, D6, V;
    private final Point A = new Point(210, 440),
            B = new Point(98, 440),
            C = new Point(98, 305),
            D = new Point(98, 194),
            E = new Point(98, 108),
            F = new Point(210, 108),
            G = new Point(452, 108),
            H = new Point(560, 108),
            I = new Point(630, 108),
            J = new Point(630, 305),
            K = new Point(630, 440),
            L = new Point(210, 365),
            M = new Point(560, 365),
            N = new Point(560, 305),
            O = new Point(210, 194),
            P = new Point(452, 194),
            Z = new Point(15, 15),
            U = new Point(15, 15);

    private Point[][] Map = {
        {B, A, Z, Z, Z, K},
        {Z, L, Z, Z, M, Z},
        {C, Z, Z, Z, N, J},
        {Z, U, U, U, Z, Z},
        {D, O, Z, P, Z, Z},
        {E, F, Z, G, H, I}
    };

    private static String Path = System.getProperty("user.dir") +"\\model\\src\\main\\resources\\Assets\\";

    public Panel(){
        Font FontLabel = new Font("TimesRoman", Font.BOLD, 25);

        this.D1 = new Label("0 m", 118, 36);
        this.D1.setBounds(231, 483, 118, 36);
        this.D1.setFont(FontLabel);
        this.D1.setForeground(Color.BLACK);

        this.D2 = new Label("0 m", 73, 36);
        this.D2.setBounds(470, 483, 73, 36);
        this.D2.setFont(FontLabel);
        this.D2.setForeground(Color.BLACK);

        this.D3 = new Label("0 m", 125, 93);
        this.D3.setBounds(675, 334, 125, 93);
        this.D3.setFont(FontLabel);
        this.D3.setForeground(Color.BLACK);

        this.D4 = new Label("0 m", 127, 77);
        this.D4.setBounds(673, 194, 127, 77);
        this.D4.setFont(FontLabel);
        this.D4.setForeground(Color.BLACK);

        this.D5 = new Label("0 m", 105, 36);
        this.D5.setBounds(431, 28, 105, 36);
        this.D5.setFont(FontLabel);
        this.D5.setForeground(Color.BLACK);

        this.D6 = new Label("0 m", 114, 36);
        this.D6.setBounds(254, 28, 114, 36);
        this.D6.setFont(FontLabel);
        this.D6.setForeground(Color.BLACK);

        this.V = new Label("0 m/s", 800, 56);
        this.V.setBounds(0, 544, 800, 56);
        this.V.setFont(FontLabel);
        this.V.setForeground(Color.BLACK);

    }

    public float[] getPosition(){
        return this.Position;
    }
    public contract.DirectionRobot getDirectionRobot(){
        return this.DirectionRobot;
    }
    protected void setPosition(float[] Position){
        this.Position = Position;
    }
    protected void setDirectionRobot(contract.DirectionRobot DirectionRobot){
        this.DirectionRobot = DirectionRobot;
    }

    protected void paintComponent(Graphics Graphic){
        try{
            if((this.Position[0] == 30)&&(this.Position[1] == 30)){
                Graphic.drawImage((new ImageIcon(Path +"Laoding.gif")).getImage(), 0, 0, 800, 600, this);
            }else{
                Graphic.drawImage(ImageIO.read(new File(Path +"Background_White.png")), 0, 0, 800, 600, this);
                Graphic.drawImage(ImageIO.read(new File(Path +"Background.png")), 0, 0, 732, 544, this);
                //this.setPosition(new float[]{(float) 0, (float) 0.5});3

                this.add(this.D1);
                this.add(this.D2);
                this.add(this.D3);
                this.add(this.D4);
                this.add(this.D5);
                this.add(this.D6);
                this.add(this.V);

                int[] PositionImage = Calculer_Coordonne(this.getPosition());
                Graphic.drawImage(ImageIO.read(new File(Path +"Voiture\\"+ this.getDirectionRobot() +".png")), PositionImage[0] - 16, PositionImage[1] - 16, 33, 33, this);
            }
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    private int[] Calculer_Coordonne(float[] Position){
        int[][] PositionMapPoints = {
            {(int) Math.floor((double) Position[0]), (int) Math.floor((double) Position[1])},
            {(int) Math.ceil((double) Position[0]), (int) Math.ceil((double) Position[1])}
        };

        float[] PositionRelativeToPoint = {(float) Math.ceil((PositionMapPoints[1][0] - (float) Math.floor(Position[0]*100)/100)*100)/100, (float) Math.ceil((PositionMapPoints[1][1] - (float) Math.floor(Position[1]*100)/100)*100)/100};

        int i = PositionMapPoints[1][0], j = PositionMapPoints[1][1];

        if((Map[j][i].getX() == 15)&&(Map[j][i].getY() == 15)){
            do{
                if((PositionMapPoints[0][0] < PositionMapPoints[1][0])&&(i <= 5)){
                    i++;
                }
                if((PositionMapPoints[0][1] < PositionMapPoints[1][1])&&(i <= 5)){
                    j++;
                }
            }while((Map[j][i].getX() == 15)&&(Map[j][i].getY() == 15));
        }

        Point A_R = Map[PositionMapPoints[0][1]][PositionMapPoints[0][0]], B_R = Map[j][i];
        float PointAffichagerX = PositionRelativeToPoint[0] * Math.abs(A_R.getX() - B_R.getX()), PointAfficherY = PositionRelativeToPoint[1] * Math.abs(A_R.getY() - B_R.getY());
        int[] Resultat = {(int) Math.ceil(B_R.getX() - PointAffichagerX), (int) Math.ceil(PointAfficherY + B_R.getY())};

        /*System.out.println("X = "+PositionMapPoints[1][0] +" Y = "+ PositionMapPoints[1][1]);
        System.out.println("X = "+PositionMapPoints[0][0] +" Y = "+ PositionMapPoints[0][1]);
        System.out.println("X = "+ Position[0] +" Y = "+ Position[1]);
        System.out.println("===");
        System.out.println(PositionRelativeToPoint[1]);
        System.out.println((float) Math.floor(Position[1]*100)/100);
        System.out.println("===");
        System.out.println(PointAffichagerX);
        System.out.println(Math.abs(A_R.getX() - B_R.getX()));
        System.out.println("==="+ Resultat[0]);
        System.out.println(" ");*/
        return Resultat;
    }
}