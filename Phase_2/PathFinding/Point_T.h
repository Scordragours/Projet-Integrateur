//
// Created by Scordragours on 17/06/2019.
//
#ifndef PATHFINDING_POINT_T_H
#define PATHFINDING_POINT_T_H


class Point_T{
    public:
        Point_T();
        Point_T(char Nom, int X, int Y);

        char Nom;
        int X, Y;
        bool Flag = false;
};

#endif