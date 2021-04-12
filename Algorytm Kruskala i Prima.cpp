#include<iostream>
#include<vector>
#include<algorithm>
#include <fstream>
#include<queue>
#include <chrono>
#include <ctime>
#include "windows.h"
using namespace std;
ifstream fin ("prim2.txt");
ifstream fin2 ("prim2.txt");

class Timer{
public:
    Timer()
    {
        chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        Stop();
    }
    void Stop()
    {
        auto endTimepoint = chrono::high_resolution_clock::now();

        auto start = chrono::time_point_cast<chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = chrono::time_point_cast<chrono::microseconds>(endTimepoint).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * 0.001;
        double s = ms * 0.001;

        cout<< ms <<"ms"<<"= " <<s<< "sec"<<endl;
    }
private:
    chrono::time_point<chrono::high_resolution_clock> m_StartTimepoint;
};

class algorytm_kruskala{
public:
    LARGE_INTEGER fr,K1,K2;
    int tab1[1000];
    int a,b,t1,t2,wierzcholek,krawedz,c;

    int find(int t1){
    if(tab1[t1] == t1){
        return t1;
    }
    return find(tab1[t1]);
}

void connector(int t1, int t2){
    int ft1 = find(t1);
    int ft2 = find(t2);
    tab1[ft1] = ft2;
}
void initialize(){

    for(int i=0;i<1000;i++){
        tab1[i]=i;
    }

    vector < pair < int , pair < int , int > > > edges;

    cout << "W: "<< "K: " <<"Koszt: \n";
    fin>>wierzcholek;
    fin>>krawedz;
    int z=krawedz;
    for(int i=0;i<krawedz;i++){
        fin>>a>>b>>c;
        edges.push_back(make_pair( c,make_pair(a,b) ) );
        cout<<a<<" "<<b<<" "<<c<<endl;
    }
    cout<<endl;
    cout<<endl;
    QueryPerformanceCounter(&K1);
    {
     Timer timer;
    int koszt = 0, mst_edges = 0;
    int index = 0;
    sort(edges.begin(),edges.end());
    while( ( mst_edges < wierzcholek-1) || (index < krawedz) ){
        a = edges[index].second.first;
        b = edges[index].second.second;
        c = edges[index].first;
        if( find(a) != find(b) ) {
            connector(a,b);
            koszt += c;
            cout<<a<<" "<<b<<" "<<c<<endl;
            mst_edges++;
        }
        index++;
    }
    cout<<"\nKoszt: "<<koszt<<endl;
    }
    QueryPerformanceCounter(&K2);
    QueryPerformanceFrequency(&fr);
    double diff_sec = (K2.QuadPart-K1.QuadPart)/(double)fr.QuadPart;
    cout<<diff_sec<<endl;
    cout<<endl;
    cout<<endl;
    fin.close();
}

};

class algorytm_prima{
    public:
    LARGE_INTEGER fr,P1,P2;
    int a,b,w;
void load(){
priority_queue < pair< int, int>, vector<pair <int, int> >,greater< pair <int, int > > >edges;

int n,m;
vector < pair< int,int> > sample;
vector < vector < pair<int, int> > > ad(1000, sample);
int vis[1001];
int mst_w=0;
fin2>>n;
    fin2>>m;
    int z=m;
    int a,b,w;
    while(z--){
        fin2>>a>>b>>w;
        ad[a].push_back(make_pair(w,b));
        ad[b].push_back(make_pair(w,a));

    }
 
QueryPerformanceCounter(&P1);
{
Timer timer;

int cnode =2,visn=0;
while(visn<n-1){
    vis[cnode]=1;
    visn++;
    for(int i=0;i<ad[cnode].size();i++){
        edges.push(ad[cnode][i]);
    }
    while (vis[edges.top().second]==1){
        edges.pop();
    }
    mst_w=mst_w+edges.top().first;
    cnode=edges.top().second;
    edges.pop();
}

cout<<"Koszt P: "<<mst_w<<endl;
}
    QueryPerformanceCounter(&P2);
    QueryPerformanceFrequency(&fr);
    double diff_sec = (P2.QuadPart-P1.QuadPart)/(double)fr.QuadPart;
    cout<<diff_sec<<endl;
}
};
int main(){
    algorytm_kruskala a;
    a.initialize();
	algorytm_prima b;
    b.load();
}
