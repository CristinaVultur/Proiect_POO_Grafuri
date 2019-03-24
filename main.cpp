#include <iostream>
#include "Graf.h"
using namespace std;

int main()
{
    int n,m;
    Graf g,h,f;
    cin>>g;
    cout<<"Graful g:"<<g;
    n=g.get_noduri;
    m=g.get_muchii;
    h=g;
    cout<<"Graful h:"<<h;
    int *rezultat_BFS=BFS(1);
    int *rezultat_DFS=DFS(1);
    int d=g.distanta(1,4);
    int comp_conexe=g.conexe;
    bool Arbore=g.arbore;
    g.adaugare_muchie(3 ,5);
    cout<<"Graful g:"<<g;
    return 0;
}
