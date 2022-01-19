#include <iostream>
#include <vector>
#include <cstdlib> //funcao rand
#include <ctime>
#include <string>
#include <algorithm>
#include <math.h>
#include <tgmath.h>
#include <random>

using namespace std;


#define MAX 100
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

/* struct responsável por armazenar os dados de distância entre as cidades  */
typedef struct
{
    vector <int> verticeB;
}tVertice;




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

/****
 * CalcularCUstoInsercao(): Função responsável por calcular o custo insercao, de cada vértice pertecente a CL no primeiro tour
 * 
 * 
 * Parâemtros:
 *                          s1(entrada): Primeiro tour
 *                          CL(entrada): vértices que faltam serem inseridos no tour
 *                          matriz(entrada): Dados responsáveis pela distancia entre as cidades
 * 
 * 
 * Retorno:
 *                          vector que possui todos os dados de inserção
 * 
 ****/
vector <InsertionInfo>  CalcularCustoInsercao(tSolucao& s1, vector <int>& CL, tVertice matriz[])
{
    int i = 0;  /*  Primeiro Vértice    */
    int j;      /*  Segundo vértice */
    /*  Criação da lista de cada k de CL associado a um par de arestas  */
    vector <InsertionInfo> custoInsercao((s1.sequencia.size() - 1) * CL.size());
    int l = 0;  /*  Variávelr responsável pelo índice de custoInsercao  */
    
    /*  Primeiro vamos selecionar os dois primeiros vértices do tour inicial    */
    /*  Depois criamos um loop para cada CL, onde será calculado o custo de inseri-lo entre os valores de i e j, depois será armazenado qual vértice foi inserido e a aresta removida   */
    for(int a = 0, b = 1; a < s1.sequencia.size() - 1; a++, b++) 
    {
        /*  EX: s' = {1,2,3,4,1}    */
        /*  CL = {5,6,7,8,9}
        /*  i = 1 e j = 2   */
        i = s1.sequencia[a];  /*  a e b são os índices dos vértices  {i,j}    */
        /*  Foi retirado um de i e de j, pois a matriz está organizada a partir do índice 0, então a cidade 1 equivale a cidade 0 e assim sucessivamente    */
        i--;
        j = s1.sequencia[b];
        j--;
        /*  K é do tipo inteiro */
        /*  Estamos aqui acessando todos os vértices que faltam adicionar no tour   */
        for (auto k : CL) 
        {
            /* O que aconteceu com i e j, também deve ser feito para k, pois a cidade 14, por exemplo, equivale a cidade 13 */
            k--;
            custoInsercao[l].custo = matriz[i].verticeB[k] + matriz[j].verticeB[k] - matriz[i].verticeB[j];   /*  Calculo do custo    */
            custoInsercao[l].noInserido = k;                        /*  Valor inserido  */
            custoInsercao[l].arestaRemovida = i;                    /*  Aresta removida */
            l++;
        }
    }
    return custoInsercao;
    
}

/****
 * OrdenaremOrdemCrescente(): Função responsável por colocar os custos em ordem crescente
 * 
 * 
 * Parâmetros:
 *          
 * 
 *                          CustoInsercao(entrada e saída): Variável no qual haverá o ordenamento
 * 
 * Observações:
 *                          Só ordena o custo
 * 
 * Retorno:
 *                          nenhum
 * 
 ****/
void OrdenarEmOrdemCrescente(vector <InsertionInfo>& custoInsercao)
{
    /*  Utilizacao do metodo sort, define o inicio e o fim, como sendo todo o vector de CustoInsercao  */
    /*  Define duas variáveis do tipo InsertionInfo */
    /*  No qual, essas variáveis vão acessar somente o custo e ordená-los   */
    sort(custoInsercao.begin(), custoInsercao.end(), [](InsertionInfo a, InsertionInfo b)
    {

        return a.custo < b.custo;

    });
    
    

}

/****
 * InserirNaSolucao():  Função responsável por inserir na solução o vértice dado
 * 
 * 
 * Parãmetros:
 *                      s1(entrada e saída): tour que será modificado
 *                      selecionado(entrada): vértice escolhido
 *                      k(entrada): vertíce que será colocado na solução
 * 
 * Retorno: Nenhum
 ****/
void InserirNaSolucao(tSolucao&s1, int selecionado, int k)
{
    /*  É necessário somar aqui pois foi retirado 1 anteriormente por conta do index 0 dos arrays   */
    /*  Para se tornar o vértice real   */
    selecionado++;
    k++;
    /*  Procuramos o valor do vértice no tour   */
    for(int i = 0; i < s1.sequencia.size(); i++)
    {
        /*  Quando achado o vértice, vamos inserir ele entre ele e o vértice após ele   */
        if(s1.sequencia[i] == selecionado)
        {
            s1.sequencia.insert(s1.sequencia.begin() + i + 1, k);
            break;

        }
    }

}

void RemoveValor(vector <int> &CL, int k)
{
    /*  Somamos um a k, pois foi necessário uma regulação por conta dos índices dos arrays  */
    k++;
    /*  Quando for achado o vértice inserido, ele será apagado  */
    for(int i = 0; i < CL.size(); i++)
    {
        if(CL[i] == k)
        {
            CL.erase(CL.begin() + i);
            break;
        }
    }
    
}



int main(void)
{
    /*  Iniciamos o primeiro tour com, 1 e 1, e depois vamos vamos colocar 3 vértices aleatórios    */
    tSolucao s1 = {{1,1}, 0, 0}; /* Sempre iniciar o primeiro tour com 1 e 1    */
    
    /*  Pegando dados das instancias    */
    char buffer[1000];  /*  Pega somente o nome "dimensao"  */
    int dimensao, numero;   /*  Variável dimensao pega o tamanho da matriz e o número por pegar os dados    */
    cin >> buffer >> dimensao;
    


    /*  Vamos primeiramente  inicializar uma matriz, do tipo tVertice o qual vai conter as distâncias entre todas as cidades    */
    /*  A struct contém um vector e estamos simulando uma matriz 2x2, no qual o índice do array corresponde a cidade A e o índice do vector a cidade B */
    /*  Logo, o valor armazenado em matriz[0].verticeB[1] é a distância entre a primeira e a segunda cidade */
    /*  Lembre-se, que a cidade 1 equivale a cidade 0, pois a matriz começa em 0    */
    tVertice matriz[dimensao];
    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < dimensao; j++)
        {
            cin >> numero;
            matriz[i].verticeB.push_back(numero);
        }
    }

    
   
    /*
    for(int i = 0; i < dimensao; i++)
    {
        for(int j = 0; j < dimensao; j++)
        {
            cout << matriz[i].verticeB[j] << " "; 
        }
        cout << endl;
    }
    */
    
    

    
    
    /*  Chamada da função para escolha de três números aleatórios   */
    /*  Enviamos dimensão porque é a quantidade de véritices    */
    Escolher3NumerosAleatorios(s1, dimensao);   
    /*  Exemplo: s1, agora vira tour para os vertices {1,2,3,4,1}   */

    
    /*
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
    cout << endl;
    */
    
    
    
    
    
    
    /*  Enquanto CL não estiver vazio, nós vamos fazer o teste de cada vértice que pertence a CL na entrada de uma aresta {i, j}    */
    /*  Vamos calcular seu custo de inserção e após isso, ordenar todos em ordem crescente  */
    
    while(!CL.empty())
    {

        vector <InsertionInfo>  custoInsercao = CalcularCustoInsercao(s1, CL, matriz);
        /*  Chama a função para ordenar em forma crescente  */
        OrdenarEmOrdemCrescente(custoInsercao);
        /*  Gerando numero aleatorio entre 0 e 1    */
        srand(time(NULL));
        double alpha = (rand() * 1.0) / RAND_MAX;
        /*  Selecionando um dos vértices aleatoriamente */
        /*  Função ceil utilizada para arrendondar o valor para cima    */
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        /*  Vamos inserir no tour o vértice escolhido, enviando o próprio tour, a aresta removida e o vértice inserido  */
        InserirNaSolucao(s1, custoInsercao[selecionado].arestaRemovida, custoInsercao[selecionado].noInserido);

        /*  Vamos remover o vértice inserido em CL, chamando a função RemoveValro   */
        RemoveValor(CL, custoInsercao[selecionado].noInserido);
    }

    
    
    
    




    
    /*
    cout << "Onde inserido: " << custoInsercao[selecionado].noInserido << endl << "Aresta removida " << custoInsercao[selecionado].arestaRemovida << endl << "Custo: "<< custoInsercao[selecionado].custo << endl<< "-------- "<< endl;
    */
    for(int i = 0; i < s1.sequencia.size(); i++)
    {
        cout << s1.sequencia[i] << " "; 
    }
    cout << endl;
    
    
    return 0;
    
    
    
}