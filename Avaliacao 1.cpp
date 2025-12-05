// Avaliacao 1.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
// Objectivo:
//Pretende - se com este trabalho que os formandos utilizem :
//• Estruturas de decisão e repetição condicional.
//• Tipos de dados compostos : array’s, strings, structs
//Os dados de entrada devem ser validados.
//1. Foi feita uma pesquisa de audiência de canal de TV em várias casas de uma certa
//cidade, num determinado dia.Para cada casa visitada, foi fornecido, o número do
//canal(1, 2, 3, 4) e o número de pessoas que o estavam a assistir naquela casa.
//Considere a possibilidade de existir mais do que uma televisão ligada na mesma
//casa.As casas onde não há TV’s ligadas não entram nas percentagens.Elabore
//um programa que :
//• Indique o número de casas pesquisadas.
//• Leia o número de pessoas a assistir cada canal em cada casa pesquisada.
//• Escreva o total de casas pesquisadas com TV ligada.
//• Calcule e escreva a percentagem de audiência para cada canal de TV.
//• Calcule e escreva a percentagem de sintonizações em cada canal.
//Nota : Deve repartir o código em várias funções(aquelas que achar
//    necessários) de modo a estruturar e organizar bem o programa.
//    Clareza no código, indentação e comentários no programa são de grande importância.

#include <iostream>
#include <Windows.h>
using namespace std;

#define MAXTVLIGADA 5 // Número máximo de TVs por casa
#define MAXCASAS 5 // Número máximo de casas a serem pesquisadas

// Estrutura que armazena informações relacionadas a cada TV
struct TV {
    int ligadas;                    // Número de TVs ligadas na casa
    int canal[4] = { 0 };           // Contagem de TVs sintonizadas em cada canal (1 a 4)
    int pessoasPorTv[MAXTVLIGADA];  // Número de pessoas a ver cada TV
};

// Estrutura que representa cada casa
struct CASA {
    struct TV tv;
};

// Prótotipos das funções
void inserirArmazenarDados(CASA casa[], int& totalTvsOn, int& casasTvOn, int& totalPessoas, int pessoasPorCanal[], int nCasas, int tvsPorCanal[]);
void calcularApresentarAudiencia(int pessoasPorCanal[], int totalPessoas);
void calcularApresentarSintonizacoes(int tvsPorCanal[], int totalTvsOn);

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    // Pede ao usuário o número de casas a serem pesquisadas e verifica se o valor é válido
    int nCasas;
    while (true)
    {
        cout << "\n\tQuantas casas deseja pesquisar (0 a 5):   ";
        if (cin >> nCasas && nCasas >= 0 && nCasas <= MAXCASAS)
        {
            cout << "\n\tEntrada lida com sucesso!";
            cin.ignore(1000, '\n');
            break;
        }
        cout << "\n\tErro na leitura..." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    CASA* casa = new CASA[nCasas];
    int casasTvOn = 0, totalTvsOn = 0, tvsPorCanal[4] = { 0 }, totalPessoas = 0, pessoasPorCanal[4] = { 0 };

    // Função para coletar e armazenar os dados das casas
    inserirArmazenarDados(casa, totalTvsOn, casasTvOn, totalPessoas, pessoasPorCanal, nCasas, tvsPorCanal);

    // Exibe o número total de casas pesquisadas e casas com TV ligada
    cout << "\n\tNúmero total de casas pesquisadas: " << nCasas;
    cout << "\n\tNúmero de casas com TV ligada: " << casasTvOn << endl;

    // Calcula e apresenta a audiência por canal
    calcularApresentarAudiencia(pessoasPorCanal, totalPessoas);

    // Calcula e apresenta as sintonizações por canal
    calcularApresentarSintonizacoes(tvsPorCanal, totalTvsOn);

    delete[] casa;
    return 0;
}

// Função para coletar e armazenar dados das TVs e canais de cada casa
void inserirArmazenarDados(CASA casa[], int& totalTvsOn, int& casasTvOn, int& totalPessoas, int pessoasPorCanal[], int nCasas, int tvsPorCanal[])
{
    for (int i = 0; i < nCasas; i++) {
        cout << "\n\tQuantas TVs estão ligadas na casa nº " << i + 1 << "? ";

        // Valida o número de TVs ligadas informado pelo usuário
        while (!(cin >> casa[i].tv.ligadas) || casa[i].tv.ligadas < 0 || casa[i].tv.ligadas > MAXTVLIGADA) {
            cout << "\n\tNúmero inválido. Insira um valor entre 0 e " << MAXTVLIGADA << ": ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        // Se há TVs ligadas na casa
        if (casa[i].tv.ligadas > 0) {
            casasTvOn++; // Incrementa a variável que guarda o número de casas com TV ligada
            totalTvsOn += casa[i].tv.ligadas; // Incrementa o total de TVs ligadas 

            for (int j = 0; j < casa[i].tv.ligadas; j++) {
                // Solicita o número de pessoas a ver a TV específica
                cout << "\n\tQuantas pessoas estão a ver a TV nº " << j + 1 << "? ";
                while (!(cin >> casa[i].tv.pessoasPorTv[j]) || casa[i].tv.pessoasPorTv[j] < 0) {
                    cout << "\n\tNúmero inválido. Insira um valor maior ou igual a 0: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                totalPessoas += casa[i].tv.pessoasPorTv[j]; // Soma ao total de pessoas a ver tv

                // Solicita o canal sintonizado na TV específica
                int nrCanal;
                cout << "\n\tQual canal (1, 2, 3, 4) está a dar na TV nº " << j + 1 << "? ";
                while (!(cin >> nrCanal) || nrCanal < 1 || nrCanal > 4) {
                    cout << "\n\tCanal inválido. Insira um valor entre 1 e 4: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                casa[i].tv.canal[nrCanal - 1]++; // Incrementa a contagem de TVs sintonizadas no canal
                tvsPorCanal[nrCanal - 1]++; // Soma as TVs em cada canal
                pessoasPorCanal[nrCanal - 1] += casa[i].tv.pessoasPorTv[j]; // Soma as pessoas a ver o canal
            }
        }
    }
}

// Função para calcular e exibir a audiência (percentagem de pessoas por canal)
void calcularApresentarAudiencia(int pessoasPorCanal[], int totalPessoas)
{
    cout << "\n\tPercentagens de audiência dos canais:";
    for (int i = 0; i < 4; i++) {
        // Calcula a percentagem de audiência para cada canal
        cout << "\n\tCanal " << i + 1 << ": " << (totalPessoas > 0 ? (float)pessoasPorCanal[i] / totalPessoas * 100 : 0) << "%";
    }
    cout << endl;
}

// Função para calcular e exibir as sintonizações (percentagem de TVs sintonizadas por canal)
void calcularApresentarSintonizacoes(int tvsPorCanal[], int totalTvsOn)
{
    cout << "\n\tPercentagens de sintonizações dos canais:";
    for (int i = 0; i < 4; i++)
    {
        // Calcula a percentagem de TVs ligadas em cada canal
        cout << "\n\tCanal " << i + 1 << ": " << (totalTvsOn > 0 ? (float)tvsPorCanal[i] / totalTvsOn * 100 : 0) << "%";
    }
    cout << endl;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
