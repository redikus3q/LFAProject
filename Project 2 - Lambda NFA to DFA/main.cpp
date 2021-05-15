#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

ifstream in("a.in");

typedef unordered_map<int, unordered_map<char, unordered_set<int>>> automat;
int n, m, stareInitiala;
automat automatInitial;
unordered_set<int> stariFinale;
vector<char> alphabet;
vector<unordered_set<int>> lambdaInchideri;

void parseazaStare(string stareString) {
    int j = 0, stareInt = 0;
    while (j < stareString.length()) {
        if (stareString[j] == '.') {
            cout << stareInt;
            stareInt = 0;
        }
        else {
            stareInt = stareInt * 10 + (int)stareString[j];
        }
        j++;
    }
}

unordered_set<int> decodeazaStare(string stareString){
    int j = 0, stareInt = 0;
    unordered_set<int> stare;
    while (j < stareString.length()) {
        if (stareString[j] == '.') {
            stare.insert(stareInt);
            stareInt = 0;
        }
        else {
            stareInt = stareInt * 10 + (int)stareString[j];
        }
        j++;
    }
    return stare;
}

void read() {
    alphabet.push_back('a');
    alphabet.push_back('b');
    in >> n >> m;
    int a, b;
    char c;
    for (int i = 0; i < m; i++) {
        in >> a >> b >> c;
        automatInitial[a][c].insert(b);
    }
    in >> stareInitiala;
    in >> a;
    for (int i = 0; i < a; i++) {
        in >> b;
        stariFinale.insert(b);
    }
}

void lambda() {
    queue<int> q;
    unordered_set<int> inchidere;
    lambdaInchideri.assign(n, inchidere);
    for (int i = 0; i < n; i++) {
        q.push(i);
        lambdaInchideri[i].insert(i);
        while (q.empty() == 0) {
            int x = q.front();
            q.pop();
            for (auto j : automatInitial[x]['l']) { /// parcurgere pt lambda tranzitii
                if (lambdaInchideri[i].find(j) == lambdaInchideri[i].end()) {
                    q.push(j);
                    lambdaInchideri[i].insert(j);
                }
            }
        }
        for (int j : stariFinale) { /// baga starile finale noi
            if (lambdaInchideri[i].find(j) != lambdaInchideri[i].end()) {
                stariFinale.insert(i);
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
            unordered_set<int> stareNesortata;
            set<int> stareSortata;
            for (int k : lambdaInchideri[i]) {
                if (automatInitial[k][j].empty() == 0) {
                    for (int l : automatInitial[k][j]) {
                        stareNesortata.insert(l);
                    }
                }
            }
            for (int k : stareNesortata) {
                if (lambdaInchideri[k].empty() == 0) {
                    for (int l : lambdaInchideri[k]) {
                        stareSortata.insert(l);
                    }
                }
            }
//            cout << i << ' ' << j << endl;
//            for(auto k: stareSortata){
//                cout << k << " ";
//            }
//            cout << endl;
            for (auto k : stareSortata) {
                nou[i][j].insert(k);
            }
        }
    }
/// nfa to dfa
    unordered_set<string> stari;
    queue<string> qu;
    string stareString, initialaDfa;
    unordered_map<string, unordered_map<char, string>> dfa;
    set<int> stareSortata;
    for (int i : lambdaInchideri[stareInitiala]) {
        stareSortata.insert(i);
    }
    for (int i : stareSortata) {
        stareString += i;
        stareString += '.';
    }
    initialaDfa = stareString;
    stari.insert(stareString);
    qu.push(stareString);
    while (qu.empty()==0) {
        string actual=qu.front();
        for (char j : alphabet) {
            set<int> stareSortata;
            for (int i : decodeazaStare(actual)) {
                for (int k : nou[i][j]) {
                    stareSortata.insert(k);
                }
            }
            string stareStringFin;
            for (int i : stareSortata) {
                stareStringFin += i;
                stareStringFin += '.';
            }
            if (stari.find(stareStringFin) == stari.end()) {
                stari.insert(stareStringFin);
                qu.push(stareStringFin);
            }
            dfa[actual][j] = stareStringFin;
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
    parseazaStare(initialaDfa);
    cout << '\n';
    cout << "Stari finale: ";
    for (auto i : stari) {
        for (int j : i) {
            if (stariFinale.find(j) != stariFinale.end()) {
                parseazaStare(i);
                cout << " ";
                break;
            }
        }
    }
    cout << '\n' << "Muchii:" << '\n';
    for (auto i : dfa) {
        for (auto j : i.second) {
            parseazaStare(i.first);
            cout << " " << j.first << " ";
            parseazaStare(j.second);
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
