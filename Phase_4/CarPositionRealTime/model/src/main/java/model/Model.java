package model;

import contract.DirectionRobot;
import contract.IModel;

import java.sql.Timestamp;
import java.util.Observable;

public class Model extends Observable implements IModel{
    private final int Hauteur = 58, Largeur = 43;
    private Robot Robot = new Robot(0, 0);
    private int[] PositionSuperieur;
    Timestamp LastTimeReader = new Timestamp(System.currentTimeMillis());
    protected static char[][] MapRempl = {
            {'B', 'A', 'Z', 'Z', 'Z', 'K'},
            {'Z', 'L', 'Z', 'Z', 'M', 'Z'},
            {'C', 'Z', 'Z', 'Z', 'N', 'J'},
            {'Z', 'z', 'z', 'z', 'Z', 'Z'},
            {'D', 'O', 'Z', 'P', 'Z', 'Z'},
            {'E', 'F', 'Z', 'G', 'H', 'I'}
    };
    public Model(){}
    public float getVitesse(){
        return this.getRobot().getVitesse();
    }
    public Robot getRobot(){
        return this.Robot;
    }
    private void setRobot(Robot Robot){
        this.Robot = Robot;
    }
    private void setRobotPosition(float X, float Y, float XPourcent, float YPourcent, DirectionRobot DirectionRobot){
        this.getRobot().Move(X, Y, XPourcent, YPourcent, DirectionRobot);
    }
    private void setDistance(float Distance){
        float[][] PositionDistance = new float[2][2];
        float Position = 0;
        int[] TableauPoint = new int[2];
        int D = 0;
        switch(this.getRobot().getDirectionRobot()){
            case RIGHT:
                PositionDistance = new float[][] {
                        {(float) 1.047, (float) 1.309},
                        {(float) 1.61, (float) 1.792}
                };
                Position = this.getRobot().getXPourcent();
                D = 0;
                break;
            case LEFT:
                PositionDistance = new float[][] {
                        {(float) 2.181, (float) 2.461},
                        {(float) 2.913, (float) 3.777}
                };
                TableauPoint = this.RecherchePoint(-1, new int[] {(int) this.getRobot().getXPourcent(), (int) this.getRobot().getYPourcent()},1);
                Position = this.getRobot().getXPourcent() - TableauPoint[0];
                D = 4;
                break;
            case TOP:
                PositionDistance = new float[][] {
                        {(float) 2.436, (float) 2.827},
                        {(float) 0.096, (float) 0.785}
                };
                Position = this.getRobot().getYPourcent();
                D = 2;
                break;
        }

        for(int i = 0; i < 2; i++){
            if(((PositionDistance[i][0] < Position)&&(PositionDistance[i][1] > Position))&&((this.getRobot().getY() == 5)||(this.getRobot().getY() == 0)||(this.getRobot().getX() == 5))){
                //System.out.println(this.getRobot().getXPourcent() +" "+ this.getRobot().getYPourcent() +"   "+ Distance);
                this.getRobot().Distance[D + i] = Distance;
            }
        }
    }
    public float[] getRobotPosition(){
        float[] RobotPosition = {
                this.Robot.getXPourcent(),
                this.Robot.getYPourcent()
        };
        return RobotPosition;
    }
    public Observable getObservable(){
        return this;
    }
    public DirectionRobot getDirectionRobot(){
        return this.getRobot().getDirectionRobot();
    }
    private int[] RecherchePoint(int Calcule, int[] PointDepart, int Direction){
        int[] TableauPointFin = {PointDepart[0], PointDepart[1]};

        do{
            if(Direction == 1){
                TableauPointFin[0] += Calcule;
            }else{
                TableauPointFin[1] += Calcule;

            }
        }while(MapRempl[TableauPointFin[1]][TableauPointFin[0]] == 'Z');

        //System.out.println(TableauPointFin[0] +"    "+ TableauPointFin[1]);

        this.PositionSuperieur = TableauPointFin;

        return TableauPointFin;
    }
    public float[] getDistance(){
        return this.getRobot().Distance;
    }
    public void CalculePositionRobot(int X, int Y, float Distance, float Vitesse, DirectionRobot DirectionRobot){
        Timestamp TimeActual = new Timestamp(System.currentTimeMillis());
        float XActual = this.getRobot().getXPourcent(), YActual = this.getRobot().getYPourcent();

        float XSend = X, YSend = Y;

        if(Vitesse == 0){
            XSend = this.getRobot().getXPourcent();
            YSend = this.getRobot().getYPourcent();
        }else if(((X == 5)||(Y == 5))&&((DirectionRobot == DirectionRobot.RIGHT)||(DirectionRobot == DirectionRobot.TOP))){
            XSend = X;
            YSend = Y;
        }else{
            float Distance_Parcourue =  (Vitesse)*(Math.abs(LastTimeReader.getTime() - TimeActual.getTime()) / 1000f) * 100f;
            System.out.println(Vitesse +" "+ (Math.abs(LastTimeReader.getTime() - TimeActual.getTime()) / 1000f));

            if(((Math.floor(XActual) != X)||(Math.floor(YActual) != Y))&&((DirectionRobot == DirectionRobot.RIGHT)||(DirectionRobot == DirectionRobot.TOP))){
                XSend = X;
                YSend = Y;
            }else if(((Math.ceil(XActual) != X)||(Math.ceil(YActual) != Y))&&((DirectionRobot == DirectionRobot.LEFT)||(DirectionRobot == DirectionRobot.DOWN))){
                XSend = X;
                YSend = Y;
            }else{
                    int[] TableauPoint = new int[2];
                    float[] Resultat = {(float) X, (float) Y};
                    switch(DirectionRobot){
                        case LEFT:
                            TableauPoint = RecherchePoint(-1, new int[] {X, Y}, 1);
                            //System.out.println(Math.abs(TableauPoint[0] - X) +"    "+ Math.abs(TableauPoint[0] - X) +" "+ Distance_Parcourue * Hauteur +" "+ Distance_Parcourue +" "+ Vitesse +" "+ (TimeActual.getTime() - LastTimeReader.getTime()));
                            //System.out.println(XActual +"    "+ X +"    "+ XActual +"    "+ Math.abs(TableauPoint[0] - X) +" "+ Distance_Parcourue * Largeur +" "+ Distance_Parcourue +" "+ Vitesse +" "+ (TimeActual.getTime() - LastTimeReader.getTime()));
                            Resultat[0] = XActual - ((Distance_Parcourue)/(Math.abs(TableauPoint[0] - X) * Largeur));
                            break;
                        case RIGHT:
                            TableauPoint = RecherchePoint(+1, new int[] {X, Y}, 1);
                            //System.out.println(Math.abs(TableauPoint[0] - X) +"    "+ Math.abs(TableauPoint[0] - X) +" "+ Distance_Parcourue * Hauteur +" "+ Distance_Parcourue +" "+ Vitesse +" "+ (TimeActual.getTime() - LastTimeReader.getTime()));
                            //System.out.println(Math.abs(TableauPoint[0] - X) +" "+ Distance_Parcourue);
                            Resultat[0] = XActual + ((Distance_Parcourue)/(Math.abs(TableauPoint[0] - X) * Largeur));
                            break;
                        case TOP:
                            TableauPoint = RecherchePoint(+1, new int[] {X, Y}, 0);
                            //System.out.println(YActual +"    "+ Y +"    "+ YActual +"    "+ Math.abs(TableauPoint[1] - Y) +" "+ Distance_Parcourue * Hauteur +" "+ Distance_Parcourue +" "+ Vitesse +" "+ (TimeActual.getTime() - LastTimeReader.getTime()));
                            Resultat[1] = YActual + (((Math.abs(TableauPoint[1] - Y) * Distance_Parcourue * Hauteur)/(Math.abs(TableauPoint[1] - Y) * Hauteur))/Hauteur);
                            break;
                        case DOWN:
                            TableauPoint = RecherchePoint(-1, new int[] {X, Y}, 0);
                            //System.out.println(Math.abs(TableauPoint[1] - Y) +"    "+ Math.abs(TableauPoint[1] - Y) +" "+ Distance_Parcourue * Hauteur +" "+ Distance_Parcourue +" "+ Vitesse +" "+ (TimeActual.getTime() - LastTimeReader.getTime()));
                            Resultat[1] = YActual - (((Math.abs(TableauPoint[1] - Y) * Distance_Parcourue * Hauteur)/(Math.abs(TableauPoint[1] - Y) * Hauteur))/Hauteur);
                            break;
                    }

                    System.out.print(Resultat[0] +" ");
                    System.out.print(X +" ");
                    System.out.print(TableauPoint[0] +" ");
                    System.out.println(XActual);

                    if((Resultat[0] >= (float) X)&&(Resultat[0] <= (float) TableauPoint[0])){
                        System.out.println("ok");
                        XSend = Resultat[0];
                    }else{
                        XSend = XActual;
                    }

                    if((Resultat[0] >= (float) Y)&&(Resultat[0] <= (float) TableauPoint[1])){
                        YSend = Resultat[1];
                    }else{
                        YSend = YActual;
                    }
                }
            }

        LastTimeReader = TimeActual;

        //System.out.println("X = "+ XSend +" & Y = "+ YSend);
        //System.out.println("X = "+ X +", Y = "+ Y +", Distance = "+ Distance +", Vitesse = "+ Vitesse);
        this.setRobotPosition(X, Y, XSend, YSend, DirectionRobot);
        this.getRobot().setVitesse(Vitesse);
        this.setDistance(Distance);

        setChanged();
        notifyObservers();

        //this.setDistance(Distance);
    }
}