#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define map unordered_map

int n;
vector<int> posts;

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a; 
		cin >> a;
		posts.push_back(a);
	}

	sort(posts.begin(), posts.end());

	int max_indice = 0;	
	// PERGUNTA: porque iterar o indice sobre o número de postagens se pode, por exemplo, existir postagens com índice maior que o número de postagens 
	// (exemplo 10ˆ6 o índice de repostagem de uma das postagens e apenas 5 * 10ˆ5 postagens); Ou seja, porque não procurar mais do que n?
	//
	// RESPOSTA: 
	//
	// Não é imediatamente óbvio porque eu itero sobre o número de postagem para ver meus índices.
	//
	// teoricamente, eu poderia fazer uma compressão de coordenadas aqui (ver link do editorial caso não saiba o que é compressão de coordenadas)
	// e iterar apenas sobre os valores que existem na lista de postagens. De fato, seria mais simples explicar o porque que isso estaria teoricamente correto
	// (eu estaria checando todos os valores possíveis e necessários)
	//
	// O que me permite simplesmente iterar os indices que eu quero procurar para achar o maior fator de influência pelo tamanho da minha lista
	// é que para um índice poder ser fator de influência é necessário que existam pelo menos o mesmo número de postagens que o número do indice
	// de repostagem, então isso coloca um teto máximo para o fator de influência de um usuário. Exemplo: não pode existir um fator de influência
	// que seja 10ˆ6 porque nao há como existir as mínimas 10ˆ6 postagens com esse índice de repostagem. Então o máximo que pode existir de fator 
	// de influência é 5 * 10ˆ5 pois podem existir 5 * 10ˆ5 postagens com esse índice de repostagem.
	//
	// Ou seja, eu posso só procurar indices que sejam menores do que n, já que no pior caso (5 * 10ˆ5 postagens) esse é o teto limite para o fator
	// de influência.
	for (int indice = 1; indice <= n; indice++) {
		// fazer binary search para encontrar index do primeiro número 
		// com indice de repostagem "indice"
		auto it = lower_bound(posts.begin(), posts.end(), indice);
		if (it != posts.end()) {
			// após achar index, calcular quantas postagens existem com
			// indice maior ou igual ao indice que eu estou buscando
			// n é o número de postagens e (it - posts.begin()) é o index do número 
			int amount = n - (it - posts.begin());
			// se a quantidade de mensagens que têm indice de repostagem que se encaixa nas regras
			// é maior ou igual ao próprio indice de repostagem (meio confuso, mas é da regra do enunciado mesmo)
			if (amount >= indice) {
				// guardar indice de repostagem
				max_indice = indice;
			}
		}
	}

	// complexidade O(n log n)
	cout << max_indice << endl;
	return 0;
}
