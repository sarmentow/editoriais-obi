#include <iostream>

using namespace std;

#define VAZIA 0
#define PRETA 1
#define BRANCA 2

int rows, cols;
int pretas;

int max_pecas(int row, int col);
int tabuleiro[7][7];

// serve para testar todas as posições adjacentes da casa atual
int rmov[] = {0, 0, -1, 1};
int cmov[] = {1, -1, 0, 0};

int main()
{
	cin >> rows >> cols;
	cin >> pretas;

	for (int i = 0; i < pretas; i++) {
		int r, c;
		cin >> r >> c;
        // guardei as informação no array contando a partir do 0 ao invés do 1
		tabuleiro[r - 1][c - 1] = PRETA;
	}
	
    // mesma coisa que max_peças(1, 1) se eu estivesse contando a partir do 1
	int res = max_pecas(0, 0);

	cout << res << endl;

	return 0;
}


int max_pecas(int row, int col) 
{
	int res = 0;
	int next_row, next_col;
    // se estiver na ultima coluna, proxima chamada de função irá para a primeira coluna da fileira de baixo
	if (col == cols - 1) {
		next_row = row + 1;
		next_col = 0;
    // caso contrário, proxima chamada de função irá para a próxima coluna
	} else {
		next_row = row;
		next_col = col + 1;
	}

    // estado inválido
	if (row >= rows or col >= cols) return 0;
    // se no tabuleiro a peça atual é preta, simplesmente ir para a próxima casa
	if (tabuleiro[row][col] == PRETA) return max_pecas(next_row, next_col);


    // checa todas as posições adjacentes para ver se existem vizinhas brancas ou vizinhas pretas
	bool black_around = false;	
	bool white_around = false;
	for (int a = 0; a < 4; a++) {
		if (row + rmov[a] < rows and col + cmov[a] < cols and row + rmov[a] >= 0 and col + cmov[a] >= 0) {
			if (tabuleiro[row + rmov[a]][col + cmov[a]] == PRETA) black_around = true;
			if (tabuleiro[row + rmov[a]][col + cmov[a]] == BRANCA) white_around = true;
		}
	}

	// se apenas vizinhas pretas e nenhuma vizinha branca, podemos inserir a peça
	if (black_around and not white_around) {
        // marcar o tabuleiro
		tabuleiro[row][col] = BRANCA;
		res = max(res, 1 + max_pecas(next_row, next_col));	
        // restaurar o estado inicial de casa vazia
		tabuleiro[row][col] = VAZIA;
	}

    // não colocar peça na casa atual e ir para a próxima casa
	res = max(res, max_pecas(next_row, next_col));

	return res;
}

