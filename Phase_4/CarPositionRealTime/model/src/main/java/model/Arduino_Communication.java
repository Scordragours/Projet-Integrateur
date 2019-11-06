package model;

import contract.DirectionRobot;
import contract.IModel;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortEvent;
import com.fazecast.jSerialComm.SerialPortMessageListener;

final class MessageListener implements SerialPortMessageListener{
    private IModel Modele;
    public MessageListener(IModel Modele){
        this.setModele(Modele);
    }
    public IModel getModele(){
        return this.Modele;
    }
    private void setModele(IModel Modele){
        this.Modele = Modele;
    }
    public int getListeningEvents(){
        return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
    }

    public byte[] getMessageDelimiter(){
        return new byte[] { (byte) 0x45, (byte) 0x4F, (byte) 0x54 };
    }
    public boolean delimiterIndicatesEndOfMessage(){
        return true;
    }
    public void serialEvent(SerialPortEvent event){
        byte[] Message = event.getReceivedData();

        /*for(int i = 0; i < Message.length; i++){
            System.out.print((char) Message[i]);
        }*/

        for(int j = 0; j <= (Message.length - 27); j++){
            StringBuilder Temp = new StringBuilder();

            Temp.append((char) Message[j]);
            Temp.append((char) Message[j + 1]);
            Temp.append((char) Message[j + 2]);

            if(Temp.toString().equals("G4>")){
                StringBuilder Buffered = new StringBuilder();
                for(int i = 3 + j; i < 27 + j; i++){
                    Buffered.append((char) Message[i]);
                }

                if(Buffered.toString().substring(Buffered.length() - 3, Buffered.length()).equals("EOT")){
                    String Reponce = Buffered.toString().substring(0, Buffered.length() - 3);
                    int X = Integer.parseInt(Reponce.substring(1, 2)), Y = Integer.parseInt(Reponce.substring(4, 5));
                    float Distance = Float.parseFloat(Reponce.substring(7, 11)), Vitesse = Float.parseFloat(Reponce.substring(13, 17));
                    DirectionRobot Direction_Robot = DirectionRobot.LEFT;
                    switch(Reponce.substring(18, 21)){
                        case "[1]":
                            Direction_Robot = Direction_Robot.LEFT;
                            break;
                        case "[2]":
                            Direction_Robot = Direction_Robot.RIGHT;
                            break;
                        case "[3]":
                            Direction_Robot = Direction_Robot.TOP;
                            break;
                        case "[4]":
                            Direction_Robot = Direction_Robot.DOWN;
                            break;
                    }
                    //System.out.println("X = " + X + ", Y = " + Y + ", D = " + Distance + ", V = " + Vitesse + ", Direction = " + Direction_Robot);
                    this.getModele().CalculePositionRobot(X, Y, Distance, Vitesse, Direction_Robot);
                }
            }
            System.out.println();
        }
    }
}

public class Arduino_Communication extends Thread{
    private SerialPort CommunicationPort;
    private IModel Modele;
    public Arduino_Communication(IModel Modele){
        this.setModele(Modele);
        this.setCommunicationPort(SerialPort.getCommPorts()[0]);
        this.getCommunicationPort().setBaudRate(9600);
    }
    public void OpenConnection(){
        if(this.getCommunicationPort().openPort()){
            System.out.println("Connection accepted.");
        }else{
            System.out.println("Connection denied.");
        }
    }
    public void CloseConnection(){
        System.out.println("Disconnects port.");
        this.getCommunicationPort().closePort();
    }
    public SerialPort getCommunicationPort(){
        return this.CommunicationPort;
    }
    public IModel getModele() {
        return this.Modele;
    }
    private void setCommunicationPort(SerialPort CommunicationPort){
        this.CommunicationPort = CommunicationPort;
    }
    private void setModele(IModel Modele){
        this.Modele = Modele;
    }
    public void run(){
        this.OpenConnection();
        MessageListener ReadSerialPort = new MessageListener(this.getModele());
        this.getCommunicationPort().addDataListener(ReadSerialPort);
    }
}