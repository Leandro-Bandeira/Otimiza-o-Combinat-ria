#include <iostream>
#include <vector>


using namespace std;





int main(void)
{
    vector <int> a = {1,2,3,4,5, 9, 6,1};
    //1 6 5 4 3 2 1

    int  k = 3;
    int l = 4;

    int contador = 0;
    while(contador < 3)
    {
        swap(a[k], a[l]);
        k--;
        l--;
        contador++;
        
    }

    for(int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    

}