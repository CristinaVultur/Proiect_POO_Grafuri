#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;
class Graf
{
     int nrnoduri,nrmuchii;
     int **matrice;
     public:
        Graf(){nrnoduri=nrmuchii=0;}//constructor fara parametri
        Graf(int);
        Graf(const Graf &g);
        ~Graf(){
            for(int i=0;i<=nrnoduri;i++)//stregem fiecare linie a matricei
                delete []matrice[i];
            delete []matrice;//stregem vectorul de pinteri si cel de vecini
            nrnoduri=nrmuchii=0;
            cout<<"Distrugerea obiectului";
            }
        friend ostream& operator<<(ostream &,const Graf &);
        friend istream& operator>>(istream&,Graf &);
        Graf &operator=(const Graf &);
        int* BFS(int);
        void DFSUtil(int,bool*,int**,int);
        int *DFS(int);
        int distanta(int, int);
        int& operator[](int);
        friend bool operator<(const Graf&,const Graf&);
        friend bool operator>(const Graf&,const Graf&);
        bool arbore();
        int conexe();
        void adaugare_muchie(int x,int y);
        void resize_matrice(int);
        void resize_lista(int);
        int get_noduri(){return nrnoduri;}
        int get_muchii(){return nrmuchii;}
 };


#endif // GRAF_H_INCLUDED
