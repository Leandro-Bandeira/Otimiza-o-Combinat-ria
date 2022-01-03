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


void Escolher3NumerosAleatorios(tSolucao& s1)
{
    int aleatorio;  /*  Número aleatório determinado    */
    int presente;   /*  Variável que diz, se o número aleatório já foi escolhido ou não */
    //V = {1,2,3,4,5,6,7,8,9, 10}   Vértices totais
    unsigned seed = time(0);
    srand(seed);

    /*  Gerando o valor aleatorio, e colocando-o logo depois do seu antecessor a partir do inicio   */
    /*  Inicialmente, gera-se um número aleatório entre 1 e 10, após isso verifica se ele já se encontra no primeiro tour   */
    /*  Caso sim, mudamos o valor de presente para 1 e voltamos uma casa no loop, para que seja colocado de fato 3 valores aleatórios   */
    for(int i = 1; i <= 3; i++)
    {
        presente = 0;

        /*  Determinação do número aleatório    */
        aleatorio = (rand() % 10) + 1;
        
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
void ExibirSolucao(tSolucao *s)
{
    for(int i = 0; i < s->sequencia.size(); i++)
    {
        cout << s->sequencia[i] << "-> ";
        
    }

}

vector <int> Restantes(tSolucao& s1)
{
    /*  Criação de todos os vertices    */
    vector <int> v;
    for(int i = 2; i <= 10; i++)
    {
        v.push_back(i);

    }
    //2,3,4,5,6,7,8,9,10

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
vector <InsertionInfo>  CalcularCustoInsercao(tSolucao& s, vector <int>& CL)
{
    int c[1000][1000];
    int i = 0;
    int j;
    /*  Criação da lista de cada k de CL associado a um par de arestas  */
    vector <InsertionInfo> custoInsercao((s.sequencia.size() - 1) * CL.size());
    int l = 0;
    
    for(int a = 0, b = 1; a < s.sequencia.size() - 1; a++, b++) 
    {
        /*  EX: s' = {1,2,3,4,1}    */
        /*  CL = {5,6,7,8,9}
        /*  i = 1 e j = 2   */
        i = s.sequencia[a];  /*  a e b são os índices dos vértices  {i,j}    */
        j = s.sequencia[b];
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


double CalculaSwapCost(int i, int j)
{
    /*  Vamos supor que temos as vértices 3,5,2 */
    /*  A distância de 3-5 é 20km e de 5-2 é 10km e de 3-2 é 5 km   */
    /*  supondo que troquemos 3-5, o custo adicional é (3-2) - (5-2)    */
    return  c[i][j+1] - c[j][j+1]
}

/*  Função para o método swap, que irá fazer a troca de dois vértices vizinhos  */
/*  E procurar aqueles dois vértices, que oferecem a melhor troca, logo o menor custo   */
bool BestImprovemmentSwap(tSolucao *s)
{
    double bestDelta = 0; /*    Variável do melhor custo    */
    int best_i, best_j; /*      Variáveis referentes aos melhores vértices do custo */

    for(int i = 1; i < s->sequencia.size() - 1; i++)
    {
        for(int j = i + 1; j < s->sequencia.size() - 1; j++)
        {
            double delta = CalculaSwapCost(i, j);   /*  Foi retornado da função CalculaSwapCost o custo da troca de i e j   */
            /*  Se esse custo,for menor que o custo de bestDelta, ele é o melhor e menor custo  */
            if(delta < bestDelta)
            {
                /*  Logo, ele virá o melhor custo   */
                bestDelta = delta;
                /*  E os vértices devem ser trocados    */
                best_i = i;
                best_j = j;
            }
        }
    }
    
    /*  Se o melhor custo foi encontrado, então faça a troca dos vertices e mude o custo    */
    /*  Retorne true    */
    if(bestDelta < 0)
    {
        swap(s->sequencia[best_i], s->sequencia[best_j])
        s->custo = s->custo - delta;
        return true;
    }
    return false;
}

int main(void)
{
    /*  Iniciamos o primeiro tour com, 1 e 1, e depois vamos vamos colocar 3 vértices aleatórias    */
    tSolucao s1 = {{1,1}, 0}; /* Sempre iniciar o primeiro tour com 1 e 1    */
   
   
    Escolher3NumerosAleatorios(s1);    /*  Chamada da função para escolha de três números aleatórios   */
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
    vector <int> CL = Restantes(s1);     /* Criação do CL */
    
    /*
    cout << "CL: " << CL.size() << endl;
    for(int i = 0; i < CL.size(); i++)
    {
        cout << CL[i] << " "; 
    }
    
    
    cout << CL.size() << endl;
    */
    
    vector <InsertionInfo>  custoInsercao;
 
    /*  Enquanto CL não estiver vazio, nós vamos fazer o teste de cada vértice que pertence a CL na entrada de uma aresta {i, j}    */
    /*  Vamos calcular seu custo de inserção e após isso, ordenar todos em ordem crescente  */
    while(!CL.empty())
    {
        
        vector <InsertionInfo>  custoInsercao = CalcularCustoInsercao(s1, CL);
        // ordenação em forma crescente de custo, em Ω
        OrdenarEmOrdemCrescente(custoInsercao);
        // criação do alpha
        double alpha = (double) rand() / RAND_MAX;
        /*  Selecionando o numero aleatoriamente em função de alfa  */
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        InserirNaSolucao(s1, selecionado);
        
    }
    
    
    
    
    
    
  
    


}