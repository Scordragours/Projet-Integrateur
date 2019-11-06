package main;

import model.Arduino_Communication;
import model.Model;
import view.View;

public abstract class Main{
    public static void main(String args[]){
        Model Model = new Model();
        Arduino_Communication Arduino = new Arduino_Communication(Model);
        Arduino.start();
        View View = new View(Model);
    }
}