#include <iostream>
#include <algorithm>

using namespace std;

#define NOTINIT 5000025


int first_row[505];
int second_row[505];

int cols;
int pieces1;
int pieces2;

int memo[500][500][500];


int dp(int piece1_i, int piece2_j, int coluna);
int main()
{
	
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			for (int z = 0; z < 500; z++) {
				// marcar como não inicializado os estados
				memo[i][j][z] = NOTINIT;
			}
		}
	}

	cin >> cols;
	cin >> pieces1;
	for (int i = 0; i < pieces1; i++) {
		cin >> first_row[i];
	}

	cin >> pieces2;
	for (int i = 0; i < pieces2; i++) {
		cin >> second_row[i];
	}

	int a = dp(0, 0, 0);
	cout << a << endl;

	return 0;
}

int dp(int piece1_i, int piece2_j, int coluna)
{
	if (memo[piece1_i][piece2_j][coluna] == NOTINIT) {
		// estado inválido
		if (coluna > piece1_i + cols - pieces1 or coluna > piece2_j + cols - pieces2) {
			// -inf
			memo[piece1_i][piece2_j][coluna] = -(1e9);
			return memo[piece1_i][piece2_j][coluna];
		}

		// acabaram as peças
		if (piece2_j >= pieces2 or piece1_i >= pieces1) {
			// parar de jogar
			memo[piece1_i][piece2_j][coluna] = 0;
			return memo[piece1_i][piece2_j][coluna];
		}

		// transição base
		return memo[piece1_i][piece2_j][coluna] = max(dp(piece1_i + 1, piece2_j + 1, coluna + 1) + first_row[piece1_i] * second_row[piece2_j], 
				max(dp(piece1_i + 1, piece2_j, coluna + 1) + 0, dp(piece1_i, piece2_j + 1, coluna + 1) + 0));
	} else {
		return memo[piece1_i][piece2_j][coluna];
	}

}

