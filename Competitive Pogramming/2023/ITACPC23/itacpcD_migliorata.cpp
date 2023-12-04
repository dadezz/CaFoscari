#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/**
 * Non ho fatto submit di questa soluzione, mi è venuta in mente il giorno dopo, 
 * anche prendendo spunto da alcune risposte (sistematicamente sbagliate) di ChatGPT.
 * Presumo però sia corretta, per i limiti forniti alle variabili in input:
 * N<=10000, Lunghezza stringa<=600.
 * 
 * fare le varie combinazioni di 2 stringhe su N e verificare se sono palidrome, ha 
 * complessità O(N^2*L), con N in ingresso e L lunghezza stringa.
 * 
 * Questo algoritmo ha invece complessità O(N*L^2).
 * 
 * dal momento che 10000^2 >> 600^2, ha una complessità temporale decisamente migliorata.
 * In termini di spazio ne richiede molto di più, e ad ogni modo non so se la soluzione
 * sarebbe stata considerata giusta nel contest. ad ogni modo, la ritengo una valida
 * alternativa degna di essere lasciata
*/

long long countPalindromeCombinations(int N, const std::vector<std::string>& arr) {
    std::unordered_map<std::string, int> hashCounts;
    long long result = 0;

    // First pass: count substrings
    for (const auto& str : arr) {
        int len = str.length();
        for (int i = 0; i < len; ++i) {
            std::string substring = str.substr(0, i + 1);
            hashCounts[substring]++;
        }
    }

    // Second pass: check for palindrome combinations
    for (const auto& str : arr) {
        std::string reversed = str;
        std::reverse(reversed.begin(), reversed.end());

        if (hashCounts.find(reversed) != hashCounts.end()) {
            result += hashCounts[reversed];
        }
    }

    return result;
}

int main() {
    int N;
    std::cin >> N;

    std::vector<std::string> arr(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }

    long long result = countPalindromeCombinations(N, arr);
    std::cout << result;

    return 0;
}
