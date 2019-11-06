//
// Created by Scordragours on 17/06/2019.
//
#ifndef PATHFINDING_LIBRARY_H
#define PATHFINDING_LIBRARY_H

#include <vector>
#include <limits.h>
#include <math.h>

#include "Point_T.h"

using namespace std;

vector<int> CalculeDistance(vector<Point_T> Tableau_Point, Point_T S);
Point_T ComparerDistance(vector<Point_T> Tableau_Point, Point_T S);
vector<Point_T> RecuperationPositionPoint(Point_T S);
int CalculeDistanceTowPoint(Point_T S1, Point_T S2);
void Trajet(Point_T X);

enum Position_Voiture_Map{
    LEFT,
    RIGHT,
    TOP,
    DOWN,
    GOD
};

#endif