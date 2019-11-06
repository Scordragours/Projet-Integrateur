//
// Created by lecra on 17/06/2019.
//
class Point_T {
    public:
        Point_T(){}
        Point_T(char Nom, int X, int Y) : Nom(Nom), X(X), Y(Y){}

        char Nom;
        int X, Y;
        bool Flag = false;
};
