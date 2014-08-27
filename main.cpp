#include <iostream>
#include <fstream>
#include "dice.hpp"

using namespace table;
using namespace std;

int mat[8][8]; // matrice de raspandire

ofstream g("dicerolltest.out");

int main(void) {
    //std::cout << "Primul commit la proiectul table";

    for (int i = 0; i < 10000000; ++i) // 1 milion de aruncari cu 2 zaruri, 23 secunde pe AMD PHENOM 2 X4 3.2 Ghz
    {
        pair<int, int> p;
        p = DoubleDiceRoll();

        mat[p.first][p.second]++;
        mat[p.second][p.first]++;
    }

    g << '\n';

    for (int i = 1; i <= 6; ++i) // afisare matrice raspandire
    {
        for (int j = 1; j <= 6; ++j)
            g << mat[i][j] << ' ';
        g << '\n';
    }

    g.close();
}
