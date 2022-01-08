#include <iostream>
#include <vector>
#include <cstdlib> //funcao rand
#include <ctime>
#include <string>
#include <algorithm>
#include <math.h>
#include <tgmath.h>


using namespace std;

typedef struct Solucao
{
    vector <int> sequencia;
    double valorObj;
    double custo;


}tSolucao;


typedef struct
{
    int noInserido; // K que será inserido
    int arestaRemovida; // aresta {i, j} onde o k será inserido
    double custo; // delta ao inserir k na aresta {i, j}

}InsertionInfo;




/****
 * Escolher3NumerosAleatorios(): Função escolhe 3 números aleatórios para serem adicionados no tour
 * 
 * 
 * 
 * Parâmetros:
 *                  s1(entrada e saída): local que será armazenado os números aleatórios
 *                  quantidade(entrada): limite dos números aleatórios, que é a dimensão da matriz
 * 
 * 
 * Retorno:
 *                  nenhum
 * 
 ****/
void Escolher3NumerosAleatorios(tSolucao& s1, int quantidade)
{
    int aleatorio;  /*  Número aleatório determinado    */
    int presente;   /*  Variável que diz, se o número aleatório já foi escolhido ou não */
    //V = {1,2,3,4,5,6,7,8,9, 10}   Vértices totais


    unsigned seed = time(0);    /*  Criação de uma semente para gerar aleatoriedade */
    srand(seed);

    /*  Inicialmente, gera-se um número aleatório entre a quantidade relativa a dimensão, após isso verifica se ele já se encontra no primeiro tour   */
    /*  Caso sim, mudamos o valor de presente para 1 e voltamos uma casa no loop, para que seja colocado de fato 3 valores aleatórios   */
    for(int i = 1; i <= 3; i++)
    {
        presente = 0;

        /*  Determinação do número aleatório    */
        aleatorio = (rand() % quantidade) + 1;
        
        /*  Verifica se ele se encontra ou não no tour inicial  */
        for(int i = 0; i < s1.sequencia.size(); i++)
        {
            if(aleatorio == s1.sequencia[i])
            {
                presente = 1;

            }
        }
        /*  Se ele não estiver presente, colocamos ele em uma posição   */
        if(!presente)
        {

            s1.sequencia.insert(s1.sequencia.begin() + 1 , aleatorio);
        }
        /*  Se não tiver presente, voltamos uma casa no loop    */
        else
        {
            i--;
        }


    }

}

/****
 * Restantes(): Criação da quantidade de vértices que ainda faltam serem inseridos no tour
 * 
 * 
 * 
 * Parâmetros:
 *                  s1(entrada): vector onde será consultado os valores.
 *                  quantidade: quantidade de vértices ou posiçẽs
 * 
 * Retorno:
 *                  Um vector com os vértices restantes
 * 
 * 
 ****/
vector <int> Restantes(tSolucao& s1, int quantidade)
{
    /*  Criação de todos os vertices    */
    vector <int> v;
    for(int i = 2; i <= quantidade; i++)
    {
        v.push_back(i);

    }

    /*  Verificação de quais se encontram no primeiro tour, para fazer o CL, que são os que faltam para completar todos os vértices */
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 0; j < v.size(); j++)
        {
            /*  Quando for encontrado o vértice já no tour, devemos apagar ele do CL    */
            if(s1.sequencia[i] == v[j])
            {
                v.erase(v.begin() + j);
            }
        }
    }
    
    
    return v;
}

/*  &s é uma passagem por referencia, estamos de fato passando seu valor   */
vector <InsertionInfo>  CalcularCustoInsercao(tSolucao& s1, vector <int>& CL, int c[][14])
{
    int i = 0;
    int j;
    /*  Criação da lista de cada k de CL associado a um par de arestas  */
    vector <InsertionInfo> custoInsercao((s1.sequencia.size() - 1) * CL.size());
    int l = 0;
    
    for(int a = 0, b = 1; a < s1.sequencia.size() - 1; a++, b++) 
    {
        /*  EX: s' = {1,2,3,4,1}    */
        /*  CL = {5,6,7,8,9}
        /*  i = 1 e j = 2   */
        i = s1.sequencia[a];  /*  a e b são os índices dos vértices  {i,j}    */
        j = s1.sequencia[b];
        /*  K é do tipo inteiro */
        /*  Estamos aqui acessando todos os vértices que faltam adicionar no tour   */
        for (auto k : CL) 
        {
            custoInsercao[l].custo = c[i][k] + c[j][k] - c[i][j];   /*  Calculo do custo    */
            custoInsercao[l].noInserido = k;                        /*  Valor inserido  */
            custoInsercao[l].arestaRemovida = a;                    /*  Aresta removida */
            l++;
        }
    }
    return custoInsercao;
    
}

void OrdenarEmOrdemCrescente(vector <InsertionInfo>& custoInsercao)
{
    sort(custoInsercao.begin(), custoInsercao.end(), [](InsertionInfo a, InsertionInfo b)
    {

        return a.custo < b.custo;

    });
    
    

}

void InserirNaSolucao(tSolucao& s1, int& selecionado)
{
    s1.sequencia.insert(s1.sequencia.end(), selecionado);

}




int main(void)
{
    /*  Iniciamos o primeiro tour com, 1 e 1, e depois vamos vamos colocar 3 vértices aleatórios    */
    tSolucao s1 = {{1,1}, 0}; /* Sempre iniciar o primeiro tour com 1 e 1    */
    
    /*  Pegando dados das instancias    */
    char buffer[1000];
    int dimensao;
    scanf("%s %d", buffer, &dimensao);
    printf("%d\n", dimensao);

    /*  Testando com o bruma14  */
    int matriz[14][14];
    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < dimensao; j++)
        {
            scanf("%d ", &matriz[i][j]);
        }
    }

    
    /*  Verificação se está certo ou não
    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < dimensao; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    */
    
    /*  Chamada da função para escolha de três números aleatórios   */
    /*  Enviamos dimensão porque é a quantidade de véritices    */
    Escolher3NumerosAleatorios(s1, dimensao);   
    /*  Exemplo: s1, agora vira tour para os vertices {1,2,3,4,1}   */

    /*
    cout << "s1:" << s1.sequencia.size() << endl;

    for(int i = 0; i < s1.sequencia.size(); i++)
    {
        cout << s1.sequencia[i] << " "; 
    }
    cout << endl;
    */

    /*  Precisamos agora criar os vértices restantes que ainda faltam ser inseridos */
    vector <int> CL = Restantes(s1, dimensao);     /* Criação do CL */
    
    /*
    cout << "CL: " << CL.size() << endl;
    for(int i = 0; i < CL.size(); i++)
    {
        cout << CL[i] << " "; 
    }
    
    
    cout << CL[0];
    cout << CL.size() << endl;
    */
    
    
    
 
    /*  Enquanto CL não estiver vazio, nós vamos fazer o teste de cada vértice que pertence a CL na entrada de uma aresta {i, j}    */
    /*  Vamos calcular seu custo de inserção e após isso, ordenar todos em ordem crescente  */
    
    while(!CL.empty())
    {
        vector <InsertionInfo>  custoInsercao = CalcularCustoInsercao(s1, CL, matriz);
    }
    
    
    
}