#include <iostream>



using namespace std;



int main(void)
{
    char buffer[1000];
    int dimensao;
    scanf("%s %d", buffer, &dimensao);
    printf("%d\n", dimensao);

    int matriz[dimensao][dimensao];
    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < dimensao; j++)
        {
            scanf("%d ", &matriz[i][j]);
        }
    }
    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < dimensao; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    
}