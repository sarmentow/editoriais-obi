#include <iostream>

using namespace std;

int amigos, reunioes;
int pzero, reunizero;
bool infectado[1001];
bool presente[1001];

int main() {
	cin >> amigos >> reunioes;
	cin >> pzero >> reunizero;

	infectado[pzero] = true;

	for (int r = 1; r <= reunioes; r++) {
		for (int a = 1; a <= amigos; a++) {
			presente[a] = false;
		}
		
		int participantes;
		cin >> participantes;

		for (int p = 0; p < participantes; p++) {
			int amigo_participante;
			cin >> amigo_participante;
			presente[amigo_participante] = true;
		}

		if (r < reunizero) {
			continue;
		}

		bool reuniao_contaminada = false;
		for (int a = 1; a <= amigos; a++) {
			if (infectado[a] && presente[a]) {
				reuniao_contaminada = true;	
				break;
			}
		}

		if (reuniao_contaminada) {
			for (int a= 1; a <= amigos; a++) {
				if (presente[a]) infectado[a] = true;
			}
		}
	}

	int ans = 0;
	for (int a = 1; a <= amigos; a++) {
		if (infectado[a]) ans++;	
	}

	cout << ans << endl;

	return 0;
}
