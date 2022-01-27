#include <iostream>
#include <vector>


using namespace std;





int main(void)
{
    vector <int> a = {1,2,3,4,5, 9, 6,1};
    //1 6 5 4 3 2 1

    int  k = 1;
    int j = 5;
    while(k < j)
    {
        swap(a[j], a[k]);
        j--;
        k++;
        
    }

    for(int i = 0; i < 8; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    

}