#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <locale.h>
#include <cstdlib>

using namespace std;

// Cabe�alhos de fun��es
void menuInicial();

static void limpaTela() {
	system("CLS");
}

static void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]) {
	// Popula o tabuleiro com �gua
	int linha, coluna;
	for (linha = 0; linha < 10; linha++) {
		for (coluna = 0; coluna < 10; coluna++) {
			tabuleiro[linha][coluna] = 'A';
			mascara[linha][coluna] = '*';
		}
	}
}

static void exibeMapa() {
	// Mapa indicador de colunas
	int cont;
	for (cont = 0; cont < 10; cont++) {
		if (cont == 0) {
			cout << "     ";
		}
		cout << cont << " ";
	}
	cout << "\n";

	for (cont = 0; cont < 10; cont++) {
		if (cont == 0) {
			cout << "     ";
		}
		cout << "| ";
	}
	cout << "\n";
}

static void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraGabarito) {
	char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
	char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
	char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

	// Exibe o tabuleiro
	int linha, coluna;
	for (linha = 0; linha < 10; linha++) {
		cout << linha << " - ";
		for (coluna = 0; coluna < 10; coluna++) {
			switch (mascara[linha][coluna]) {
			case 'A':
				cout << blue << " " << mascara[linha][coluna] << normal;
				break;
			case 'P':
				cout << green << " " << mascara[linha][coluna] << normal;
				break;
			default:
				cout << " " << mascara[linha][coluna];
				break;
			}
		}
		cout << "\n";
	}

	if (mostraGabarito == true) {
		for (linha = 0; linha < 10; linha++) {
			for (coluna = 0; coluna < 10; coluna++) {
				cout << " " << tabuleiro[linha][coluna];
			}
			cout << "\n";
		}
	}
}

static void posicionaBarcos(char tabuleiro[10][10]) {
	// Coloca 10 barcos no tabuleiro
	int cont, quantidade = 10, quantidadePosicionada = 0;

	// Verifica se j� posicionou todos os barcos
	while (quantidadePosicionada < quantidade) {
		int linhaAleatoria = rand() % 10;						// Gera n�mero aleat�rio de 0 a 9
		int colunaAleatoria = rand() % 10;						// Gera n�mero aleat�rio de 0 a 9

		if (tabuleiro[linhaAleatoria][colunaAleatoria] == 'A') {
			// Posiciona 10 Barcos aleatoriamente
			tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';

			// Aumenta o contador de barcos posicionados
			quantidadePosicionada++;
		}
	}	
}

static void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem) {
	// Verifica quantos pontos adicionar
	switch (tabuleiro[linhaJogada][colunaJogada]) {
	case 'P':
		*pontos = *pontos + 10;								// (*) - Posi��o na mem�ria apontada por 
		*mensagem = "Voc� acertou um barco pequeno! (10 pts)";
		break;
	case 'A':
		*mensagem = "Voc� acertou a �gua";
		break;
	}
}

static void jogo(string nomeDoJogador) {
	/// Vari�veis Gerais
	char tabuleiro[10][10], mascara[10][10];				// Tabuleiro do Jogo
	int linha, coluna;										// Auxiliares de navega��o
	int linhaJogada, colunaJogada;							// Posi��o escolhida pelo jogador
	int estadoDeJogo = 1;									// 1 = Jogo Acontecendo, 0 = Fim de Jogo
	int pontos = 0;											// Pontua��o do jogador
	int tentativas = 0, maximoDeTentativas = 5;				// Tentativas do jogador
	int opcao;												// Op��es de fim de jogo
	string mensagem = "Bem-vindo ao jogo!";					// Mensagem de Feedback para o jogador
	
	// Inicia o tabuleiro com �gua
	iniciaTabuleiro(tabuleiro, mascara);

	// Posiciona os barcos aleatoriamente
	posicionaBarcos(tabuleiro);

	while (tentativas < maximoDeTentativas) {
		limpaTela();

		// Exibe o mapa de indica��es
		exibeMapa();

		// Exibe tabuleiro
		exibeTabuleiro(tabuleiro, mascara, true);

		cout << "\nPontos: " << pontos << ", Tentativas Restantes: " << maximoDeTentativas - tentativas;
		cout << "\n" << mensagem;

		// Verifica��o de dados
		linhaJogada = -1;
		colunaJogada = -1;

		while ( (linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9) ) {
			cout << "\n" << nomeDoJogador << ", digite uma linha: ";
			cin >> linhaJogada;
			cout << "\n" << nomeDoJogador << ", digite uma coluna: ";
			cin >> colunaJogada;
		}

		// Verifica o que aconteceu
		verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);

		// Revela o que est� no tabuleiro
		mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

		tentativas++;
	}

	cout << "\nFim de jogo, o que deseja fazer?";
	cout << "\n1 - Jogar Novamente";
	cout << "\n2 - Ir para o Menu";
	cout << "\n3 - Sair\n";
	cin >> opcao;

	switch (opcao) {
	case 1:
		jogo(nomeDoJogador);
		break;
	case 2:
		menuInicial();
		break;
	}
}

static void menuInicial() {
	// Op��o escolhida pelo usu�rio
	int opcao = 0;

	// Nome do usu�rio
	string nomeDoJogador;									

	// Enquanto o jogador n�o digita uma op��o valida, mostra o menu novamente
	while (opcao < 1 || opcao > 3) {

		limpaTela();

		cout << "Bem-vindo ao Jogo de Batalha Naval";
		cout << "\n1 - Jogar";
		cout << "\n2 - Sobre";
		cout << "\n3 - Sair";
		cout << "\nEscolha uma op��o e pressione ENTER: ";

		cin >> opcao;

		// Faz algo de acordo com a op��o escolhida
		switch (opcao)
		{
		case 1:
			cout << "Qual seu nome? ";
			cin >> nomeDoJogador;

			// Inicia o jogo
			jogo(nomeDoJogador);

			break;

		case 2:

			// Mostra informa��es do jogo
			cout << "Informa��es do jogo";

			break;

		case 3:

			cout << "At� mais!";

			break;
		}
	}
}

int main() {
	setlocale(LC_ALL, "");

	// Para gerar n�meros realmente aleat�rios
	srand((unsigned)time(NULL));

	menuInicial();

	return 0;
}