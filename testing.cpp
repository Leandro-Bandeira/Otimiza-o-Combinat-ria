#include <iostream>
#include <math.h>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;





int main(void)
{
    vector <int> a = {1,2,3,4,5, 9, 6,1, 1 , 1 , 2, 2, 5, 6};
    int limiteInferior = 2;
    int limiteSuperior = ceil((double) a.size() / 10);

    int tamanho1, tamanho2;


    unsigned seed = time(0);
    srand(seed);

    tamanho1 = rand() % limiteSuperior + limiteInferior;
    tamanho2 = rand() % limiteSuperior + limiteInferior;

    cout << tamanho1 << " " << tamanho2;

    

}