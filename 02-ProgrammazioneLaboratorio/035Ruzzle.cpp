#include <vector>
#include <string>
using namespace std;
/**RUZZLE
 * in una matrice di lettere, possiamo muoverci in oriz, vert e diag. non si può usare la stessa lettera 2 volte
 * (saria paroliere).
 * 
 * 
 * gioco: è possibile fare la parola "..." nel tabellone? se sì, darne una codifica, 
 * ovvero dicendo come si fa.
 * 
 * 
 * faccio ricorsione su lunghezza stringa
 * 
 * 
 * è possibile trovare la soluzione a partire dalla posizione (i,j)?
*/

bool trova_parola(const vector<vector<char>>& t, vector<vector<bool>>& u, string s, int i, int j){
    if (i<0 or i>=4 or j<0 or j>=4) return false;
    if (s.length() == 0) return true;
    if (s.at(0) != t.at(i).at(j) or u.at(i).at(j)) return true;
    bool found = false;
    u.at(i).at(j) = true;
    s.erase(s.begin(), s.begin());
    for (int r = i-1; r<=i+1;r++){
        for (int c=j-1; c<=j+1; c++){
            if (!found) found = trova_parola(t, u, s, r, c);
        }
    }
    if (!found) u.at(i).at(j) = false;
    return found;   
}

bool trova_totale(const vector<vector<char>>& t, vector<vector<bool>>& u, string s){
    bool found = false;
    for (int r = 0; r<=4;r++)
        for (int c=0; c<=4; c++)
            if (!found) 
                found = trova_parola(t, u, s, r, c);
    return found;
}

/**
 * prato fiorito:
*/