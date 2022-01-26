#include <iostream>
#include <vector>


using namespace std;


typedef struct
{
    vector <int> a;

}tInteiro;



void Mostra(tInteiro lea[], int dimensao)
{
    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < dimensao ; j++)
        {
            cout << lea[i].a[j] << " ";
        }
        cout << endl;
    }
}
int main(void)
{
    int dimensao;
    int numero;

    cin >> dimensao;
    tInteiro lea[dimensao];

    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            cin >> numero;
            lea[i].a.push_back(numero);
        }
    }
    Mostra(lea, dimensao);

    

}