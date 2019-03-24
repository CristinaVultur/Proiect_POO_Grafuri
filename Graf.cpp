#include "Graf.h"
using namespace std;
Graf::Graf(int n)//constructor cu parametri
{
    matrice=new int*[n+1];
    nrnoduri=n;
}
Graf::Graf(const Graf &g)//constructor de copiere
{
    int i,j;
    nrnoduri=g.nrnoduri;
    nrmuchii=g.nrmuchii;

    matrice=new int*[nrnoduri+1];//ALOCAM MEMORIE PT POINTERII CATRE LINII
    for(i=1;i<=g.nrnoduri;i++)//alocam memorie pt liniile matricei
        {
             matrice[i]=new int[g.matrice[i][0]+1];//pe coloana 0 a fiecariui nod salvam nr de vecini
        }
    for(i=1;i<=g.nrnoduri;i++)
        {
            for(j=0;j<=g.matrice[i][0];j++)
                matrice[i][j]=g.matrice[i][j];
        }
}

Graf& Graf::operator=(const Graf &g)
{
    if(this==&g)
        return *this;//evitare autoatribuire
     for(int i=0;i<=nrnoduri;i++)
        delete[] matrice[i];//daca exista deja un graf il stergem
    delete[] matrice;
    nrnoduri=g.nrnoduri;
    nrmuchii=g.nrmuchii;
    matrice=new int*[nrnoduri];
    for(int i=1;i<=nrnoduri;i++)
        matrice[i]=new int[g.matrice[i][0]];
    for(int i=1;i<=nrnoduri;i++)
        for(int j=0;j<=g.matrice[i][0];j++)
        matrice[i][j]=g.matrice[i][j];
    return *this;
}

ostream & operator<<(ostream &out,const Graf &g)
{
    out<<g.nrnoduri<<" "<<g.nrmuchii<<"\n";
     for(int i=1;i<=g.nrnoduri;i++)
        {
            out<<i<<" ";
            for(int j=1;j<=g.matrice[i][0];j++){
                out<<g.matrice[i][j]<<" ";}
            out<<"\n";
        }
    return out;
}
istream &operator>>(istream& in, Graf &graf)
{
   int n,m,i,x,y;
    int **temp;
    for(int i=0;i<graf.nrnoduri;i++)//stergem matricea daca exista
                delete []graf.matrice[i];
            delete []graf.matrice;

    in>>graf.nrnoduri>>graf.nrmuchii;//citim nr noduri si muchii
    n=graf.nrnoduri;
    m=graf.nrmuchii;
    temp=new int*[n+1];//alocam memorie pentru matricea temporara
    for(i=0;i<=n+1;i++)
        temp[i]=new int[n+1];//pe fiecare linie alocam memorie pt nr maxim de vecini
    for(i=1;i<=n;i++)
        temp[i][0]=0;//pe coloana 0 punem 0 pentru a o putea incrementa

    for(i=0;i<m;i++)
    {
        in>>x>>y;//citim muchiile
        temp[x][0]++;//crestem nr de vecini
        temp[y][0]++;
        temp[x][temp[x][0]]=y;//adaugam vecinii la lista de adiacenta
        temp[y][temp[y][0]]=x;
    }
    graf.matrice=new int*[n+1];
    for(i=1;i<=n;i++)
        graf.matrice[i]=new int[temp[i][0]+1];//acum stim nr de vecini ai fiecarui nod deci putem aloca exact cata memorie avem nevoie
    for(i=1;i<=n;i++)
        for(int j=0;j<=temp[i][0];j++)
            graf.matrice[i][j]=temp[i][j];//copiem datele citie in matricea grafului

    for(i=0;i<=n;i++)
        delete[] temp[i];//stergem matricea temporara
    delete[] temp;

        return in;
}

int* Graf::BFS(int start)
{
    bool *vizitat=new bool[nrnoduri+1];
    for(int i=0;i<=nrnoduri;i++)
        vizitat[i]=false;
    int *noduri=new int[nrnoduri];
    vizitat[start]=true;//marcam nodul de start ca vizitat
    int *coada=new int[nrnoduri];//alocam memorie pt coada
    int prim=0,ultim=0,n=0;
    //noduri[0]=start;
    coada[ultim]=start;//punem nodul de start in coada
    while(prim<=ultim)//cat timp "coada nu e vida"
    {
        noduri[n]=coada[prim];
        n++;
        for(int i=1;i<=matrice[coada[prim]][0];i++)//parcurgem lista de adiacenta a nodului curent
            if(vizitat[matrice[coada[prim]][i]]==false)//daca nodul nu a fost vizitat
                {
                    ultim++;
                    coada[ultim]=matrice[coada[prim]][i];//il punem in varful cozii
                    vizitat[matrice[coada[prim]][i]]=true;//il marcam ca vizitat
                }
        prim++;//dupa ce am terminat cu nodul curent trecem la urm din coada
    }
    noduri[n]=coada[prim];
    for(int i=0;i<nrnoduri;i++) cout<<noduri[i]<<" ";
    return noduri;//funtia returneaza un vector cu nodurile ordonare dupa parcurgerea in latime
}
void Graf::DFSUtil(int s,bool *vizitat,int **noduri,int n)
{
    (*noduri)[n]=s;
    vizitat[s]=true;
    for(int i=1;i<=nrnoduri;i++)
        if(vizitat[matrice[s][i]]==false)
                DFSUtil(matrice[s][i],vizitat,noduri,n++);
}
int *Graf::DFS(int start)
{
    int i,n=0;
    bool *vizitat=new bool[nrnoduri+1];
    for(i=0;i<=nrnoduri;i++)
        vizitat[i]=false;
    int *noduri=new int[nrnoduri];
    DFSUtil(start,vizitat,&noduri,n);
    return noduri;
}
int Graf::distanta(int x,int y)
{
    //ca la bfs
    int *distanta=new int [nrnoduri+1];
    for(int i=0;i<=nrnoduri;i++)
        distanta[i]=0;
    distanta[x]=0;
    bool *vizitat=new bool[nrnoduri+1];
    for(int i=0;i<=nrnoduri;i++)
        vizitat[i]=false;
    vizitat[x]=true;//marcam nodul de start ca vizitat
    int *coada=new int[nrnoduri];//alocam memorie pt coada
    int prim=0,ultim=0;
    //noduri[0]=start;
    coada[ultim]=x;//punem nodul de start in coada
    while(prim<=ultim)//cat timp "coada nu e vida"
    {
        for(int i=1;i<=matrice[coada[prim]][0];i++)//parcurgem lista de adiacenta a nodului curent
            if(vizitat[matrice[coada[prim]][i]]==false)//daca nodul nu a fost vizitat
                {
                    distanta[matrice[coada[prim]][i]]=distanta[coada[prim]]+1;
                    ultim++;
                    coada[ultim]=matrice[coada[prim]][i];//il punem in varful cozii
                    vizitat[matrice[coada[prim]][i]]=true;//il marcam ca vizitat
                }
        prim++;//dupa ce am terminat cu nodul curent trecem la urm din coada
    }
    return distanta[y];//funtia returneaza un vector cu nodurile ordonare dupa parcurgerea in latime

}
int& Graf::operator[](int i)
{
    if(i<0||i>=nrnoduri)
    {
        invalid_argument e("Index invalid");
        throw e;
    }
    return *matrice[i];//intoarce lista de adiacenta a nodului i sub forma de vector
}
bool operator<(const Graf &g1,const Graf &g2)
{
    if(g1.nrnoduri<g2.nrnoduri) return true;
    if(g1.nrnoduri==g2.nrnoduri&&g1.nrmuchii<g2.nrmuchii) return true;
    return false;
}
bool operator>(const Graf &g1,const Graf &g2)
{
    if(g1.nrnoduri>g2.nrnoduri) return true;
    if(g1.nrnoduri==g2.nrnoduri&&g1.nrmuchii>g2.nrmuchii) return true;
    return false;
}
int Graf::conexe()
{
    int nrcomp=0;
    int *vizitat=new int[nrnoduri+1];
    for(int i=0;i<=nrnoduri;i++)
        vizitat[i]=0;
    int *noduri;
    for(int i=1;i<=nrnoduri;i++)
    {
        if(vizitat[i]==false){
            noduri=BFS(i);//de cate ori gasim un nod nevizitat apelam bfs
            for(i=0;i<nrnoduri;i++)
             {
               vizitat[noduri[i]]=true;
             }
             nrcomp++;//si crestem nr de componente conexe
        }
    }
    return nrcomp;

}
bool Graf::arbore()
{
    int nr_comp_conexe;
    nr_comp_conexe=conexe();//daca graful are n-1 muchii si o sg comp conexa atunci este arbore
    if(nrmuchii==nrnoduri-1&&nr_comp_conexe==1) return true;
    else return false;
}
void Graf::resize_matrice(int n)
{
    Graf temp(n+1);
    temp.nrnoduri=n;//daca eticheta n este mai mare decat nr de noduri atunci vom avea n noduri de la 1 la n
    temp.nrmuchii=nrmuchii;
    for(int i=1;i<=nrnoduri;i++)
    {
        temp.matrice[i]=matrice[i];
    }
    matrice=temp.matrice;
}
void Graf::resize_lista(int x)
{
    matrice[x][0]++;
    int *temp=new int[matrice[x][0]+1];//daca adaugam o noua muchie atunci nr de elem din lista de adiacenta sigur va creste cu 1
    for(int i=0;i<matrice[x][0];i++)
        temp[i]=matrice[x][i];
    delete[] matrice[x];
    matrice[x]=temp;
    delete[] temp;
}
void Graf::adaugare_muchie(int x, int y)
{
    if(x>y)
        if(x>nrnoduri)//nodurile au etichete de la 1 la nr de noduri deci daca e are eticheta mai mare atunci este un nod nou
          resize_matrice(x);
    else
        if(y>nrnoduri) resize_matrice(y);
    resize_lista(x);
    resize_lista(y);
    matrice[x][matrice[x][0]]=y;//adaugam y la lista lui x
    matrice[y][matrice[y][0]]=x;//adaugam x la lista lui y
    nrmuchii++;
    //incrementam de muchii pentru a sti mereu valoarea
}
