#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

ifstream in("a.in");

int n,m,init;
unordered_map<int, unordered_map<char, int>> mu;
unordered_set<int> fin;
vector<string> cuv;

void read(){

    in>>n>>m;
    int a,b;
    char c;
    for(int i=0;i<m;i++){
        in>>a>>b>>c;
        mu[a][c]=b;
    }
    in>>init;
    in>>a;
    for(int i=0;i<a;i++){
        in>>b;
        fin.insert(b);
    }
    in>>a;
    char aux[256];
    for(int i=0;i<a;i++){
        in.get();
        in.get(aux, 256);
        cuv.push_back(aux);
    }

}

vector<int> solve(string word){

    int a=init; //nod curent
    vector<int> res;
    res.push_back(a);
    for(auto i:word){
        if(mu.find(a)!=mu.end() && mu[a].find(i)!=mu[a].end()){
            a=mu[a][i];
            res.push_back(a);
        }
        else{
            return {-1};
        }
    }
    if(fin.find(a)!=fin.end()){
        return res;
    }
    return {-1};

}

int main(){

    read();
    for(auto i:cuv){
        vector<int> aux=solve(i);
        if(aux[0]==-1){
            cout<<"NU"<<endl;
        }
        else{
            cout<<"DA"<<endl<<"TRASEU: ";
            for(auto j:aux){
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }

}
