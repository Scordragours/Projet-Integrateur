#include <ArduinoSTL.h>

#include <math.h>
#include "Point_T.h"

using namespace std;

// Définie la direction de la voiture sur la map.
enum Position_Voiture_Map{
    LEFT,
    RIGHT,
    TOP,
    DOWN,
    GOD
};

// Définien les commandes de direction pour le robot.
vector<char> State_Vehicule;

//Rentre les coordonées des différents points sur la map. 
Point_T A('A', 1, 0), B('B', 0, 0), C('C', 0, 2), D('D', 0, 4), E('E', 0, 5), Y('Y', 1, 5), G('G', 3, 5), H('H', 4, 5), I('I', 5, 5), J('J', 5, 2), K('K', 5, 0), L('L', 1, 1), M('M', 4, 1), N('N', 4, 2), O('O', 1, 4), P('P', 3, 4), Z('Z', 0, 0), Zo('Q', 0, 0);

//Initialise un point de départ et un point de fin. 
Point_T Depart = A, Fin = C;

//Initialise le sens de départ de la voiture
Position_Voiture_Map Voiture = TOP;

// Le tableau va contenir le chemin de point le plus court.
vector<Point_T> Tableau_Point_Final;

//Tableau dynamique représentant la carte les Z sont des points qui ne sont pas important. 
Point_T Map[6][6] = {
        {B, A, Z, Z, Z, K},
        {Z, L, Z, Z, M, Z},
        {C, Z, Z, Z, N, J},
        {Z, Zo, Zo, Zo, Z, Z},
        {D, O, Z, P, Z, Z},
        {E, Y, Z, G, H, I}
};


vector<int> CalculeDistance(vector<Point_T> Tableau_Point, Point_T S);
Point_T ComparerDistance(vector<Point_T> Tableau_Point, Point_T S);
vector<Point_T> RecuperationPositionPoint(Point_T S);
int CalculeDistanceTowPoint(Point_T S1, Point_T S2);
void Trajet(Point_T X);

//Fonction vectorielle qui va retourner un tableau de Distance
vector<int> CalculeDistance(vector<Point_T> Tableau_Point, Point_T S){
    vector<int> Distance;
    for(int i = 0; i < Tableau_Point.size(); i++){
        Distance.push_back(CalculeDistanceTowPoint(Tableau_Point[i], S));
    }
    return Distance;
}

//Fonction qui va comparer la distance entre chaques point. 
Point_T ComparerDistance(vector<Point_T> Tableau_Point, Point_T S){
    vector<int> Tableau_Distance = CalculeDistance(Tableau_Point, S);
    Point_T Temporaire = Tableau_Point.at(0);
    Point_T Buffered;
    int Min = Tableau_Distance.at(0);
    int Calcule_Vect_Point_1_To_Fin, Calcule_Vect_Point_2_To_Fin, Calcule_Vect_Point_3_To_Fin;
    for(int i = 0; i < Tableau_Distance.size(); i++){
        Buffered = Temporaire;
        if(i == Tableau_Distance.size() - 1){
            Calcule_Vect_Point_1_To_Fin = CalculeDistanceTowPoint(Tableau_Point.at(i), Fin),
                    Calcule_Vect_Point_2_To_Fin = CalculeDistanceTowPoint(Tableau_Point.at(0) , Fin);
            Calcule_Vect_Point_3_To_Fin = CalculeDistanceTowPoint(Temporaire, Fin);
            if(Calcule_Vect_Point_1_To_Fin < Calcule_Vect_Point_2_To_Fin){
                Temporaire = Tableau_Point.at(i);
            }else{
                Temporaire = Tableau_Point.at(0);
            }
            if((Calcule_Vect_Point_1_To_Fin > Calcule_Vect_Point_3_To_Fin)||(Calcule_Vect_Point_2_To_Fin > Calcule_Vect_Point_3_To_Fin)){
                Temporaire = Buffered;
            }
        }else{
            Calcule_Vect_Point_1_To_Fin = CalculeDistanceTowPoint(Tableau_Point[i], Fin),
            Calcule_Vect_Point_2_To_Fin = CalculeDistanceTowPoint(Tableau_Point[i + 1] , Fin),
            Calcule_Vect_Point_3_To_Fin = CalculeDistanceTowPoint(Temporaire, Fin);
            if(Calcule_Vect_Point_1_To_Fin < Calcule_Vect_Point_2_To_Fin){
                Temporaire = Tableau_Point.at(i);
            }else{
                Temporaire = Tableau_Point.at(i + 1);
            }
            if((Calcule_Vect_Point_1_To_Fin > Calcule_Vect_Point_3_To_Fin)||(Calcule_Vect_Point_2_To_Fin > Calcule_Vect_Point_3_To_Fin)){
                Temporaire = Buffered;
            }
        }
    }
    Tableau_Point_Final.push_back(Temporaire);
    return Temporaire;
}

// Cette fonction calcule tous les points autour.
vector<Point_T> RecuperationPositionPoint(Point_T S){
    vector<Point_T> Solution;
    int X_vers_moins, X_vers_plus, Y_vers_moins, Y_vers_plus;
    bool S1 = false, S2 = false, S3 = false, S4 = false;
    switch(Voiture){
        case LEFT:
            X_vers_moins = S.X - 1, X_vers_plus = 7, Y_vers_moins = S.Y - 1, Y_vers_plus = S.Y + 1;
            break;
        case RIGHT:
            X_vers_moins = -1, X_vers_plus = S.X + 1, Y_vers_moins = S.Y - 1, Y_vers_plus = S.Y + 1;
            break;
        case TOP:
            X_vers_moins = S.X - 1, X_vers_plus = S.X + 1, Y_vers_moins = -1, Y_vers_plus = S.Y + 1;
            break;
        case DOWN:
            X_vers_moins = S.X - 1, X_vers_plus = S.X + 1, Y_vers_moins = S.Y - 1, Y_vers_plus = 7;
            break;
        case GOD:
            X_vers_moins = S.X - 1, X_vers_plus = S.X + 1, Y_vers_moins = S.Y - 1, Y_vers_plus = S.Y + 1;
            break;
    }
    do{
        if((X_vers_moins < 0)||(Map[S.Y][X_vers_moins].Nom == 'Q')){
            S1 = true;
        }else if((Map[S.Y][X_vers_moins].Nom == 'Z')&&(!S1)){
            X_vers_moins--;
        }else if((Map[S.Y][X_vers_moins].Nom != 'Z')&&(X_vers_moins >= 0)&&(!S1)){
            Solution.push_back(Map[S.Y][X_vers_moins]);
            S1 = true;
        }

        if((X_vers_plus > 5)||(Map[S.Y][X_vers_plus].Nom == 'Q')){
            S2 = true;
        }else if((Map[S.Y][X_vers_plus].Nom == 'Z')&&(!S2)){
            X_vers_plus++;
        }else if((Map[S.Y][X_vers_plus].Nom != 'Z')&&(X_vers_plus <= 5)&&(!S2)){
            Solution.push_back(Map[S.Y][X_vers_plus]);
            S2 = true;
        }

        if((Y_vers_moins < 0)||(Map[Y_vers_moins][S.X].Nom == 'Q')){
            S3 = true;
        }else if((Map[Y_vers_moins][S.X].Nom == 'Z')&&(!S3)){
            Y_vers_moins--;
        }else if((Map[Y_vers_moins][S.X].Nom != 'Z')&&(Y_vers_moins >= 0)&&(!S3)){
            Solution.push_back(Map[Y_vers_moins][S.X]);
            S3 = true;
        }

        if((Y_vers_plus > 5)||(Map[Y_vers_plus][S.X].Nom == 'Q')){
            S4 = true;
        }else if((Map[Y_vers_plus][S.X].Nom == 'Z')&&(!S4)){
            Y_vers_plus++;
        }else if((Map[Y_vers_plus][S.X].Nom != 'Z')&&(Y_vers_plus <= 5)&&(!S4)){
            Solution.push_back(Map[Y_vers_plus][S.X]);
            S4 = true;
        }

        if((S1)&&(S2)&&(S3)&&(S4)){
            break;
        }
    }while(true);
    return Solution;
}

// Calcule la distance directe entre deux points.
int CalculeDistanceTowPoint(Point_T S1, Point_T S2){
    int Distance_Total = (int) sqrt((S1.X - S2.X) * (S1.X - S2.X)) + (int) sqrt((S1.Y - S2.Y) * (S1.Y - S2.Y));
    return Distance_Total;
}

// Fonction qui regroupe toutes les fonctions jusqu'à atteindre le point final.
void Trajet(Point_T X){
    vector<Point_T> Point_Autour = RecuperationPositionPoint(X);
    Point_T Resultat = ComparerDistance(Point_Autour, X);

    Position_Voiture_Map Buffer = Voiture;

    if(Resultat.Y - X.Y < 0){
        Voiture = DOWN;
    }else if(Resultat.Y - X.Y > 0){
        Voiture = TOP;
    }else if(Resultat.X - X.X < 0){
        Voiture = LEFT;
    }else if(Resultat.X - X.X > 0){
        Voiture = RIGHT;
    }

    if(Buffer == Voiture){
        State_Vehicule.push_back('A');
    }else{
        if(Buffer == LEFT){
            if(Voiture == TOP){
                State_Vehicule.push_back('D');
            }else if(Voiture == DOWN){
                State_Vehicule.push_back('G');
            }
        }else if(Buffer == RIGHT){
            if(Voiture == DOWN){
                State_Vehicule.push_back('D');
            }else if(Voiture == TOP){
                State_Vehicule.push_back('G');
            }
        }else if(Buffer == TOP){
            if(Voiture == RIGHT){
                State_Vehicule.push_back('D');
            }else if(Voiture == LEFT){
                State_Vehicule.push_back('G');
            }
        }else if(Buffer == DOWN){
            if(Voiture == LEFT){
                State_Vehicule.push_back('D');
            }else if(Voiture == RIGHT){
                State_Vehicule.push_back('G');
            }
        }
    }

    Point_T Buffered_Image = Resultat;

    for(int i = 0; i < 10; ++i){
        if(Resultat.Nom ==  Fin.Nom){
            break;
        }
        Point_Autour = RecuperationPositionPoint(Resultat);
        Resultat = ComparerDistance(Point_Autour, Resultat);

        Buffer = Voiture;

        if(Resultat.Y - Buffered_Image.Y < 0){
            Voiture = DOWN;
        }else if(Resultat.Y - Buffered_Image.Y > 0){
            Voiture = TOP;
        }else if(Resultat.X - Buffered_Image.X < 0){
            Voiture = LEFT;
        }else if(Resultat.X - Buffered_Image.X > 0){
            Voiture = RIGHT;
        }

        if(Buffer == Voiture){
            State_Vehicule.push_back('A');
        }else{
            if(Buffer == LEFT){
                if(Voiture == TOP){
                    State_Vehicule.push_back('D');
                }else if(Voiture == DOWN){
                    State_Vehicule.push_back('G');
                }
            }else if(Buffer == RIGHT){
                if(Voiture == DOWN){
                    State_Vehicule.push_back('D');
                }else if(Voiture == TOP){
                    State_Vehicule.push_back('G');
                }
            }else if(Buffer == TOP){
                if(Voiture == RIGHT){
                    State_Vehicule.push_back('D');
                }else if(Voiture == LEFT){
                    State_Vehicule.push_back('G');
                }
            }else if(Buffer == DOWN){
                if(Voiture == LEFT){
                    State_Vehicule.push_back('D');
                }else if(Voiture == RIGHT){
                    State_Vehicule.push_back('G');
                }
            }
        }
        Buffered_Image = Resultat;
    }
}
