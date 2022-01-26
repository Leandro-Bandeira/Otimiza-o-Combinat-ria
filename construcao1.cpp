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
/****
 * RemoveValor(): Função responsável pro remover os valores presentes no conjunto CL.
 * 
 * 
 * Parâmetros:
 *                  CL(entrada e saída): Conjunto que será modificado
 *                  k(entrada): valor que será retirado do conjunto
 * 
 * Retorno:
 *                  Nenhum
 ****/
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


/****
 * CalculaCustoTotal(): Função responsável por calcular o custo total do tour
 * 
 * 
 * Parâmetros:
 *                      s1(entrada): tour que será consultado
 *                      matriz[](entrada): valores dos custos
 * 
 * Retorno:
 *                      nenhum
 ****/
void CalculaCustoTotal( tSolucao& s1, tVertice matriz[])
{   
    int vertice_i;  /*  Primeiro vértice    */
    int vertice_j;  /*  Vértice imeditamente posterior  */


    for(int i = 0; i < s1.sequencia.size() - 1; i++)
    {
        vertice_i = s1.sequencia[i];
        vertice_i--;

        vertice_j = s1.sequencia[i + 1];
        vertice_j--;

        s1.custo += matriz[vertice_i].verticeB[vertice_j];
        

    }



}

/****
 * CalculateSwapCost(): Função responsável por calcular o custo de troca pelo método swap
 * 
 * 
 * Parâmetros:
 *                      s1(entrada): tour no qual será consultado os vértices
 *                      i: primeiro índice que aponta para um vértice
 *                      j: segundo índice que aponta para o segundo vértice de troca
 *                      matriz(entrada): valor onde será consultado o custo das arestas
 * 
 * Retorno:
 *                      Valor do custo de troca
 * 
 ****/
double CalculateSwapCost(tSolucao &s1, int i, int j, tVertice matriz[])
{
    double custoTroca = 0;
    /*  Deve-se fazer a regulação com a retirada de 1, pois o índice da matriz inicia em 0  */
    /*  Logo, a matriz vai de 0 a 13, o qual o índice 0 representa a cidade 1   */
    int vertice_i = s1.sequencia[i];
    int vertice_j = s1.sequencia[j];
    vertice_i--;
    vertice_j--;

    /*  Pegamos o valor do vértice anterior de i    */
    int vertice_i_anterior = s1.sequencia[i - 1];
    vertice_i_anterior--;

    /*  Pegamos o vértice posterior de j    */
    int vertice_j_posterior = s1.sequencia[j + 1];
    vertice_j_posterior--;

    
    /*  Fazemos o cáculo do custo, pegamos as novas arestas criadas e retiramos o valor das arestas antiga, para ver qual o valor do custo  */
    custoTroca = (matriz[vertice_i_anterior].verticeB[vertice_j] + matriz[vertice_i].verticeB[vertice_j_posterior]) - (matriz[vertice_i_anterior].verticeB[vertice_i] + matriz[vertice_j_posterior].verticeB[vertice_j]);
    return custoTroca;

}









/****
 * BestImprovementSwap(): Função responsável por fazer as trocas entre os vértices, a partir do método swap
 * 
 * 
 * Parâmetros:
 *                          s1(entrada e saída): tour que provavelmente será modificado
 *                          matriz[]: matriz que possui os custos de cada aresta
 * 
 * Retorno:
 *                          true:  se de fato houve o método swap, ou seja, uma provável melhora
 *                          false: se não houve troca por meio do swap
 ****/
bool bestImprovementSwap(tSolucao &s1, tVertice matriz[])
{
    double bestDelta = 0;
    double delta;
    int best_i, best_j;

    /*  Devemos inicializar com i == 1, pois vamos trocar entre os '1'  */
    /*  Estamos enviando o vértice posterior a 1 e o próximo a ele  , no nosso tour inicial */
    for(int i = 1; i < s1.sequencia.size() - 1; i++)
    {
        for(int j = i + 1; j < s1.sequencia.size() - 1; j++)
        {
            /*  Queremos receber o custo de troca entre esses vértices  */
            delta = CalculateSwapCost(s1,i,j, matriz);
            /*  Verificamos se o custo de troca é menor que o anterior  */
            /*  Porque se for, vale a pena a troca  */
            if (delta < bestDelta)
            {
                /*  Mudamos o valor de menor custo de troca */
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
        
    }
    
    /*  Se valer a pena a troca, fazemos a troca entre os valores e mudamos o custo */
    if(bestDelta < 0)
    {
        swap(s1.sequencia[best_i], s1.sequencia[best_j]);
        s1.custo = s1.custo - delta;
        return true;
    }

    return false;

}

/****
 * BestImprovemente2opt(): Função responsável por fazer as trocas entre vértices não adjacentes
 * 
 * 
 * Parâmetros:
 *                          s1(entrada e saída): tour que será modificado ou nao
 *                          matriz(entrada): matriz onde será consultada os dados de custo
 * 
 * 
 * Retorno:
 *                          True: se houve troca
 *                          false: senao houve troca
****/
bool bestImprovement2opt(tSolucao& s1, tVertice matriz[])
{
    double bestDelta = 0;
    double delta;
    int best_i, best_j;


    for(int i = 1; i < s1.sequencia.size() - 1; i++)
    {
        for(int j = i + 2; j < s1.sequencia.size() - 1; j++)
        {

            delta = CalculateSwapCost(s1, i, j, matriz);
            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

        }
    }

    if(bestDelta < 0)
    {
        swap(s1.sequencia[best_i], s1.sequencia[best_j]);
        s1.custo = s1.custo - delta;
        return true;
    }

    return false;


}



/****
 * CalculateOrCost(): Calcula o custo de troca da operação de reinsertion
 * 
 * 
 * Parâmetros:
 *                    s1(entrada): tour onde será consultado os vértices
 *                    i(entrada): índice do primeiro vértice da sequencia, que pode ser uma sequência de até 3 valores
 *                    j(entrada): índice do vértice que irá trocar de lugar com o vértice de índice i
 *                    matriz(entrada): valor onde será consutlado os custos de cada aresta
 *                    tamanho(entrada): valor do tamanho da sequeência
 * 
 * Retorno:
 *                    Custo de troca
 * 
 ****/
double CalculateOrCost(tSolucao& s1, int i, int j, tVertice matriz[], int tamanho)
{
    double custoTroca;  // variável que armazena o custo de troca

    int vertice_i = s1.sequencia[i];    // Primeiro vértice da sequência
    vertice_i--;    //  Devemos reduzir por conta da matriz que inicia em 0 e não em 1

    int vertice_i_anterior = s1.sequencia[i - 1];   // Vertice anterior ao primeiro vértice da sequência
    vertice_i_anterior--;


    int vertice_troca = s1.sequencia[j];    // vertice o qual será trocado pelo vértice de índice i
    vertice_troca--;


    int vertice_troca_posterior = s1.sequencia[j + 1];  // Vértice posterior ao vértice de troca
    vertice_troca_posterior--;

    //  Se o tamanho for igual 2 , quer dizer que será reinserido dois vértices em uma sequência
    if(tamanho == 2)
    {
        /*  Segundo vértice que será trocado    */
        int vertice_j = s1.sequencia[i + 1];
        vertice_j--;
        
        custoTroca = (matriz[vertice_i_anterior].verticeB[vertice_troca] + matriz[vertice_j].verticeB[vertice_troca_posterior]) - (matriz[vertice_i_anterior].verticeB[vertice_i] + matriz[vertice_troca].verticeB[vertice_troca_posterior]);
        return custoTroca;
    }

    // Se o tamanho for igual 3, quer dizer que será reinserido três vértices em uma sequência
    if(tamanho == 3)
    {
        /*  Segundo vértice que será trocado    */
        int vertice_j = s1.sequencia[i + 1];
        vertice_j--;

        /*  Terceiro vértice que será trocado   */
        int vertice_k = s1.sequencia[i + 2];
        vertice_k--;


        custoTroca = (matriz[vertice_i_anterior].verticeB[vertice_troca] + matriz[vertice_k].verticeB[vertice_troca_posterior]) - (matriz[vertice_i_anterior].verticeB[vertice_i] + matriz[vertice_troca].verticeB[vertice_troca_posterior]);
        return custoTroca;



    }
    if(tamanho == 1)
    {
        custoTroca = (matriz[vertice_i_anterior].verticeB[vertice_troca] + matriz[vertice_i].verticeB[vertice_troca_posterior]) - (matriz[vertice_i_anterior].verticeB[vertice_i] + matriz[vertice_troca].verticeB[vertice_troca_posterior]);
        return custoTroca;
    }

    
}


/****
 * BestImprovementOrOpt(): Função responsável por fazer o melhoramento pelo metodo de reisertion
 * 
 * 
 * Parâmetros:
 *                          s1(entrada e saída): tour que será modificado para melhoramento
 *                          matriz(entrada): valor onde será consultado os dados de custo
 *                          tamanho(entrada): variável responsável por indicar quantos valores irá fazer a reisertion
 * 
 * Retorno:
 *                          true: se houve melhoramento
 *                          false: se não houve melhoramento
 ****/
bool bestImprovementOrOpt(tSolucao& s1, tVertice matriz[], int tamanho)
{
    double bestDelta = 0;
    double delta;
    int best_i, best_j;


    for(int i = 1; i < s1.sequencia.size() - 1; i++)
    {
        
        /*  Fazemos j = i + tamanho, pois será o índice do vértice que será trocado     */
        /*  Se temos: 1 2 3 4 5 e tamanho == 1, ent devemos trocar o valor 2 com a posição 3 */
        /*  Se temos: 1 2 3 4 5 e tamanho == 2, ent devemos trocar o 2 e o 3 pela posicao do numero 4 que irá para a posição do numero 2    */
        for(int j = i + tamanho; j < s1.sequencia.size() - 1; j++)
        {
            delta = CalculateOrCost(s1, i, j, matriz, tamanho);
            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

        }
        
        
    }

    if(bestDelta < 0)
    {
        swap(s1.sequencia[best_i], s1.sequencia[best_j]);
        s1.custo = s1.custo - delta;
        return true;
    }

    return false;

}

/****
 * BuscaLocal(): Função responsável por chamar as outras funções de melhoramento de solução
 * 
 * 
 * Parâmetros:
 *               s1(entrada): Dados onde serão consultados os tour iniciais
 *               matriz(entrada): Dados de custo das arestas
 * 
 * 
 * Retorno: Nenhum
 * 
 ****/
void BuscaLocal(tSolucao& s1, tVertice matriz[])
{
    /*  Criamos um vector, para a retirada de um valor aleatório    */
    vector <int> NL = {1,2,3,4,5};
    bool improved = false;

    /*  Fazemos esse loop até que o vector esteja vazio */
    while(!NL.empty())
    {
        /*  Pegamos um valor aleatório, de 1 a 5 */
        /*  E fazemos um melhoramento   */
        /*  Caso de fato haja um melhoramento, não modifcamos o NL e continuamos até que   */
        /*  Não haja um melhoramento pelos métodos, se não houver, retiramos aquele método da seleção   */
        int n = rand() % NL.size();
        switch(NL[n])
        {
            case 1:
                improved = bestImprovementSwap(s1, matriz);

                break;

            case 2:
                improved = bestImprovement2opt(s1, matriz);

                break;
    
            case 3:
                improved = bestImprovementOrOpt(s1, matriz, 1); // Reinsertion

                break;
            case 4:
                improved = bestImprovementOrOpt(s1, matriz, 2); // Or-opt2

                break;
            
            case 5:
                improved = bestImprovementOrOpt(s1, matriz, 3); // Or-opt3
                
                break;
            
        }
        /*  Se houve de fato melhora, modificamos NL    */
        if(improved)
        {
            NL = {1,2,3,4,5};
        }
        /*  Se não houve melhora, apagamos aquele método    */
        else
        {
            NL.erase(NL.begin() + n);
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

    
   
    

    
    /*  Chamada da função para escolha de três números aleatórios   */
    /*  Enviamos dimensão porque é a quantidade de véritices    */
    Escolher3NumerosAleatorios(s1, dimensao);   
    /*  Exemplo: s1, agora vira tour para os vertices {1,2,3,4,1}   */

    
   
    
    

    /*  Precisamos agora criar os vértices restantes que ainda faltam ser inseridos */
    vector <int> CL = Restantes(s1, dimensao);     /* Criação do CL */
    
    
   
    
    
    
    
    
    
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

        /*  Vamos remover o vértice inserido em CL, chamando a função RemoveValor   */
        RemoveValor(CL, custoInsercao[selecionado].noInserido);
    }

    
    /*  Chamada da função para fazer o calculo do custo inicial */
    CalculaCustoTotal(s1, matriz);

    
    BuscaLocal(s1, matriz);
    
    cout << s1.custo << endl;
   


    

    
    return 0;
    
    
    
}