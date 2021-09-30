# Trem da Mina
Assuntos: dijkstra e dfs 

[Problema](https://olimpiada.ic.unicamp.br/pratique/p2/2020/f3/trem/) 

Nesse problema, queremos a menor distância que torna possível retornar ao ponto de partida, dados o tamanho do trem e o vértice inicial. Dessa forma, deveremos partir do início até um ciclo, que obrigatoriamente deve ter comprimento maior que o do trem para que não haja sobreposição,  percorrer este e retornar de onde viemos, deslocando-se de forma a minimizar a distância. 

Uma informação que cabe ressaltar é que no enunciado é dito que cada vértice está em no máximo um ciclo, o que torna mais fácil achar o ciclo. 

É importante ressaltar que existem várias maneiras de resolver o problema apresentado. No editorial iremos tratar o problema utilizando [DFS Lowlink](https://codeforces.com/blog/entry/68138)  e [Dijkstra](https://noic.com.br/materiais-informatica/curso/graphs-03/).

Inicialmente, vamos tratar o grafo dado na questão para transformá-lo em uma árvore, guardando algumas informações sobre o ciclo, para isso utilizaremos a DFS Lowlink. Na imagem abaixo temos o grafo original dado na própria sample. 

![Grafo](https://github.com/sarmentow/editoriais-obi/blob/main/2020/imagens/trem-da-mina-grafo.png?raw=true)



Rodando a DFS Lowlink encontramos que as arestas (1, 2, 2) e (2, 3, 2) são pontes. Depois disso precisamos descobrir quais vértices estão numa mesma componente, para isso rodamos uma dfs para cada vértice não visitado, ignorando as pontes, pois dessa formas estamos isolando o ciclo e apenas percorrendo vértices que estão na mesma componente, ao fazer isso guardamos o tamanho de cada componente, a qual componente cada vértice pertence e a distância necessária para percorrer o ciclo por completo. 

Depois de termos salvo a informação de qual componente cada vértice faz parte torna mais fácil saber quais os vértices que podem ser usados como saída, ou seja, aqueles vértices que possuem alguma aresta que é ponte e podem ser usados para sair do ciclo sem passar por qualquer outro vértice deste. No grafo da imagem os vértices 2, 1 e 3 seriam vértices de saída. 

Para achar tais vértices basta iterar por cada vértice do grafo original e para cada aresta checar se ela está ligando vértices de componentes diferentes, caso isso seja verdade, achamos um vértice que pode ser usado como saída, daí guardamos para cada componente quais vértices podem ser usados para sair da ciclo. 

Agora, com todas as informações salvas, podemos responder as queries. A ideia final é que para cada vértice inicial dado, iremos realizar um dijkstra para achar a menor distância para todos os vértices. E iremos testar utilizar cada um dos ciclos, fixando usar cada um dos vértices de saída que achamos, existentes como forma de retorno, tentando minimizar a distância necessária. Nessa parte podemos ter dois casos:
 
1- o vértice não faz parte do ciclo que estamos utilizando para retornar, assim a distância necessária será duas vezes distância salva no dijkstra para ir até o ciclo, buscamos o vértice de saída mais próximo do nosso ciclo, somada a distância total do ciclo. 

2- caso o vértice faça parte do ciclo que estamos testando, a distância necessária será apenas a distância total para percorrer o ciclo 

É válido ressaltar que caso o ciclo tenha tamanho menor do que o do trem dado na query, utilizá-lo não nos dará um caminho válido, portanto devemos ignorá-lo.  

Segue o [código da solução comentada](../codigo/trem-da-mina.cpp) para melhor compreensão. 
 
 
## Agradecimentos
[Pijuma](https://github.com/pijuma) por ter escrito o editorial e o código

