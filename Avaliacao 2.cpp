// Avaliacao 2.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
//2. Elabore um programa que permita simular o funcionamento de uma máquina de
//venda de vários tipos de bebidas quentes.O custo de cada produto é o seguinte :
//café - 0, 25€
//cappuccino – 0, 30€
//Chocolate – 0, 35€
//Chá – 0, 20€
//• Deverá ser apresentado um menu de opções para que o utilizador possa
//escolher a sua bebida.
//• A máquina aceita moedas de 0.05€, 0.10€, 0.20€, 0.50€, 1€ e 2€.
//• O cliente tem a possibilidade de comprar várias bebidas com o dinheiro
//introduzido.
//• O troco devolvido deve conter o menor número possível de moedas e
//explicitar quais as moedas devolvidas.

#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Definição dos preços das bebidas
#define CAFE 0.25
#define CAPPUCCINO 0.30
#define CHOCOLATE 0.35
#define CHA 0.20

// Declaração dos prótotipos das funções
void exibirMenu();
void introduzirMoedas(float& montanteIntroduzido);

void exibirMenu();
void escolherBebidas(float& montanteIntroduzido);
void calcularMoedasTroco(float& montanteIntroduzido, int quantidadeMoedas[], float valoresMoedas[]);
void imprimirMoedasTroco(int quantidadeMoedas[], float& montanteIntroduzido, float valoresMoedas[]);

int main()
{
	SetConsoleOutputCP(CP_UTF8); // Por algum motivo o código 1252 não estava a mostrar a acentuação e simbolo do €

	float montanteIntroduzido = 0; // Montante total inserido pelo cliente
	float valoresMoedas[6] = { 2, 1, 0.50, 0.20, 0.10, 0.05 }; // Valores das moedas aceitas
	int quantidadeMoedas[6] = { 0 }; // Quantidade de moedas de cada tipo para o troco

	exibirMenu();
	introduzirMoedas(montanteIntroduzido);
	system("cls"); // Limpa o terminal
	exibirMenu();
	escolherBebidas(montanteIntroduzido);
	system("cls"); // Limpa o terminal
	calcularMoedasTroco(montanteIntroduzido, quantidadeMoedas, valoresMoedas);
	imprimirMoedasTroco(quantidadeMoedas, montanteIntroduzido, valoresMoedas);

	cout << endl;
	return 0;
}

// Função para exibir o menu de bebidas
void exibirMenu()
{
	cout << "\n\n\tBebidas Quentes\t\tPreço";
	cout << endl;
	cout << "\n\t1 - Café:\t\t" << CAFE << "€";
	cout << "\n\t2 - Cappuccino:\t\t" << CAPPUCCINO << "€";
	cout << "\n\t3 - Chocolate:\t\t" << CHOCOLATE << "€";
	cout << "\n\t4 - Chá:\t\t" << CHA << "€";
	cout << endl;
}

// Função para permitir a introdução de moedas
void introduzirMoedas(float& montanteIntroduzido)
{
	char continuar = 'S'; // Variável para controlar se o cliente quer continuar a meter moedas
	float moeda; // Armazena o valor da moeda metida

	do
	{
		while (true)
		{
			cout << "\n\tA máquina aceita moedas de 0.05€, 0.10€, 0.20€, 0.50€, 1€ e 2€.\n\t\tIntroduza uma moeda:    ";
			if (cin >> moeda) // Verifica se o valor foi introduzido corretamente
			{
				// Define uma margem de tolerância para comparação, se não utilizar esta margem de tolerância não funciona como o esperado
				const double epsilon = 0.0001;

				if (fabs(moeda - 0.05) < epsilon ||
					fabs(moeda - 0.10) < epsilon ||
					fabs(moeda - 0.20) < epsilon ||
					fabs(moeda - 0.50) < epsilon ||
					fabs(moeda - 1.00) < epsilon ||
					fabs(moeda - 2.00) < epsilon)
				{
					montanteIntroduzido += moeda; // Soma o valor da moeda ao montante total
					break;
				}
				else
					cout << "\n\tValor introduzido não aceite pela máquina..." << endl;
			}
			else
			{
				cout << "\n\tEntrada inválida. Por favor, insira um valor numérico." << endl;
				cin.clear();
			}
			cin.ignore(1000, '\n');
		}

			while (true)
			{
				cout << "\n\tDeseja introduzir mais moedas (S/N)?    ";
				cin >> continuar;
				continuar = toupper(continuar);
				cin.ignore(1000, '\n');
				if (continuar == 'S' || continuar == 'N')
					break;  // Sai do loop se a entrada for válida
				else
					cout << "\n\tEntrada inválida. Por favor, insira 'S' para Sim ou 'N' para Não." << endl;
			}
		} while (continuar == 'S'); // Continua enquanto o cliente quiser inserir mais moedas
	}

// Função para permitir a escolha de bebidas
void escolherBebidas(float& montanteIntroduzido)
{
	char continuar = 'S'; // Variável para controlar se o cliente quer escolher mais bebidas
	int opcao; // Armazena a escolha do cliente (1-4)

	do
	{
		if (montanteIntroduzido >= 0.20) // Verifica se há dinheiro suficiente para pelo menos uma bebida
		{
			while (true)
			{
				cout << "\n\tVocê tem " << montanteIntroduzido << "€ restantes.";
				cout << "\n\tInsira a bebida que deseja (1 a 4):    ";
				if (cin >> opcao && opcao >= 1 && opcao <= 4)
				{
					cout << "\n\tOpção escolhida com sucesso!" << endl;
					cin.ignore(1000, '\n');
					break;
				}
				cout << "\n\tOpção inserida indisponivel..." << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}

			// Deduz o valor da bebida escolhida do montante disponível que foi inserido pelo cliente
			switch (opcao)
			{
			case 1: if (montanteIntroduzido - CAFE >= 0)
				montanteIntroduzido -= CAFE;
				  else
				cout << "\n\tDinheiro insuficiente para o produto escolhido." << endl;
				break;
			case 2: if (montanteIntroduzido - CAPPUCCINO >= 0)
				montanteIntroduzido -= CAPPUCCINO;
				  else
				cout << "\n\tDinheiro insuficiente para o produto escolhido." << endl;
				break;
			case 3: if (montanteIntroduzido - CHOCOLATE >= 0)
				montanteIntroduzido -= CHOCOLATE;
				  else
				cout << "\n\tDinheiro insuficiente para o produto escolhido." << endl;
				break;
			case 4: if (montanteIntroduzido - CHA >= 0)
				montanteIntroduzido -= CHA;
				  else
				cout << "\n\tDinheiro insuficiente para o produto escolhido." << endl;
				break;
			}

			while (true)
			{
				cout << "\n\tDeseja escolher mais bebidas (S/N)?    ";
				cin >> continuar;
				continuar = toupper(continuar);
				cin.ignore(1000, '\n');
				if (continuar == 'S' || continuar == 'N')
					break;  // Sai do loop se a entrada for válida
				else
					cout << "\n\tEntrada inválida. Por favor, insira 'S' para Sim ou 'N' para Não." << endl;
			}
		}
		else
			cout << "\n\tMontante insuficiente para comprar mais bebidas." << endl;
	} while (continuar == 'S' && montanteIntroduzido >= 0.20); // Continua enquanto houver dinheiro suficiente e o cliente desejar
}

// Função para calcular o troco
void calcularMoedasTroco(float& montanteIntroduzido, int quantidadeMoedas[], float valoresMoedas[])
{
	cout << "\n\tValor total do seu troco:	" << fixed << setprecision(2) << montanteIntroduzido << "€." << endl;

	for (int i = 0; i < 6; i++)
	{
		if (montanteIntroduzido >= valoresMoedas[i]) // Verifica se a moeda atual pode ser usada no troco
		{
			while (montanteIntroduzido >= valoresMoedas[i]) // Enquanto a moeda atual puder ser usada no troco
			{
				montanteIntroduzido -= valoresMoedas[i]; // Deduz o valor da moeda
				quantidadeMoedas[i]++; // Incrementa o contador de moedas com o mesmo indice
			}
		}
	}
}

// Função para imprimir o troco
void imprimirMoedasTroco(int quantidadeMoedas[], float& montanteIntroduzido, float valoresMoedas[])
{
	cout << "\n\tO seu troco será devolvido em:		";
	for (int i = 0; i < 6; i++)
	{
		if (quantidadeMoedas[i] > 0) // Imprime apenas os tipos de moedas que foram usadas no troco do cliente
			cout << "\n\t\t" << quantidadeMoedas[i] << " moeda(s) de " << valoresMoedas[i] << "€";
	}
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
