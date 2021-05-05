#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ifstream in("b.in");

typedef unordered_map<int, unordered_map<char, unordered_set<int>>> automat;
int n, m, init;
automat mu;
unordered_set<int> fin;
vector<char> alphabet;
vector<unordered_set<int>> v;

void parsestare(string x) {
    int j = 0, aux = 0;
    while (j < x.length()) {
        if (x[j] == '.') {
            cout << aux;
            aux = 0;
        }
        else {
            aux = aux * 10 + (int)x[j];
        }
        j++;
    }
}
unordered_set<int> decodestare(string x){
    int j = 0, aux = 0;
    unordered_set<int> c;
    while (j < x.length()) {
        if (x[j] == '.') {
            c.insert(aux);
            aux = 0;
        }
        else {
            aux = aux * 10 + (int)x[j];
        }
        j++;
    }
    return c;
}

void read() {
    alphabet.push_back('a');
    alphabet.push_back('b');
    in >> n >> m;
    int a, b;
    char c;
    for (int i = 0; i < m; i++) {
        in >> a >> b >> c;
        mu[a][c].insert(b);
    }
    in >> init;
    in >> a;
    for (int i = 0; i < a; i++) {
        in >> b;
        fin.insert(b);
    }
}

void lambda() {
    queue<int> q;
    unordered_set<int> aux;
    v.assign(n, aux);
    for (int i = 0; i < n; i++) {
        q.push(i);
        v[i].insert(i);
        while (q.empty() == 0) {
            int x = q.front();
            q.pop();
            for (auto j : mu[x]['l']) { /// parcurgere pt lambda tranzitii
                if (v[i].find(j) == v[i].end()) {
                    q.push(j);
                    v[i].insert(j);
                }
            }
        }
        for (int j : fin) { /// baga starile finale noi
            if (v[i].find(j) != v[i].end()) {
                fin.insert(i);
            }
        }
    }
//    for(int i=0; i<n; i++){
//        for(int j: v[i]){
//            cout << j << " ";
//        }
//        cout << endl;
//    }
}

void dfa() {
/// lamdba nfa to nfa
    automat nou;
    for (int i = 0; i < n; i++) {
        for (char j : alphabet) {
            unordered_set<int> aux1;
            set<int> aux2;
            for (int k : v[i]) {
                if (mu[k][j].empty() == 0) {
                    for (int l : mu[k][j]) {
                        aux1.insert(l);
                    }
                }
            }
            for (int k : aux1) {
                if (v[k].empty() == 0) {
                    for (int l : v[k]) {
                        aux2.insert(l);
                    }
                }
            }
//            cout << i << ' ' << j << endl;
//            for(auto k: aux2){
//                cout << k << " ";
//            }
//            cout << endl;
            for (auto k : aux2) {
                nou[i][j].insert(k);
            }
        }
    }
/// nfa to dfa
    unordered_set<string> stari;
    queue<string> qu;
    string aux, initdfa;
    unordered_map<string, unordered_map<char, string>> dfa;
    set<int> aux1;
    for (int i : v[init]) {
        aux1.insert(i);
    }
    for (int i : aux1) {
        aux += i;
        aux += '.';
    }
    initdfa = aux;
    stari.insert(aux);
    qu.push(aux);
    while (qu.empty()==0) {
        string v=qu.front();
        for (char j : alphabet) {
            set<int> aux2;
            for (int i : decodestare(v)) {
                for (int k : nou[i][j]) {
                    aux2.insert(k);
                }
            }
            string aux3;
            for (int i : aux2) {
                aux3 += i;
                aux3 += '.';
            }
            if (stari.find(aux3) == stari.end()) {
                stari.insert(aux3);
                qu.push(aux3);
            }
            dfa[v][j] = aux3;
        }
        qu.pop();
    }
//    for(auto x: stari){
//        for(auto k: x){
//            cout << (int)k;
//        }
//        cout << endl;
//    }
/// afisare
    cout << "Stare initiala: ";
    parsestare(initdfa);
    cout << '\n';
    cout << "Stari finale: ";
    for (auto i : stari) {
        for (int j : i) {
            if (fin.find(j) != fin.end()) {
                parsestare(i);
                cout << " ";
                break;
            }
        }
    }
    cout << '\n' << "Muchii:" << '\n';
    for (auto i : dfa) {
        for (auto j : i.second) {
            parsestare(i.first);
            cout << " " << j.first << " ";
            parsestare(j.second);
            cout << '\n';
        }
    }
}

int main() {
    read();
    lambda();
    dfa();
    return 0;
}
