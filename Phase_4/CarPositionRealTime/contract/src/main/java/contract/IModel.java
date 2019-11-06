package contract;

import java.util.Observable;

public interface IModel {
    Observable getObservable();
    float[] getRobotPosition();
    float getVitesse();
    DirectionRobot getDirectionRobot();
    void CalculePositionRobot(int X, int Y, float Distance, float Vitesse, DirectionRobot DirectionRobot);
    float[] getDistance();
}