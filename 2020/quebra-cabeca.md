# Quebra-cabeças
Assuntos: DP
[Problema](https://olimpiada.ic.unicamp.br/pratique/p2/2020/f2/quebra/)


Esse problema é bastante similar ao [edit distance](https://cses.fi/problemset/task/1639) e retoma vários conceitos e transições de estado de DP presentes nesse problema, então é recomendado que você o resolva primeiro e entenda a solução antes de continuar a leitura.

Primeiramente, é importante reconhecer que esse é um problema de DP, então precisamos definir os estados e as transições possíveis para cada estado. Dito isso, a intuição para resolver o problema vem do fato de que existem 3 opções que podem ser tomadas para cada par de peças `i`e `j` existentes em cada fileira, sendo elas:

1. Deixar as peças `i` e `j` alinhadas
2. Mover a peça `i` para a direita
3. Move a peça `j` para a direita

Podemos pensar no estado como sendo definido então por 2 variáveis `i` e `j`, na qual `dp(i, j)` representa a maior pontuação possível para todas as escolhas que podemos tomar (as transições) a partir das peças `i` e `j`. 

Nesse caso dp(0, 0) seria a resposta para o problema pois corresponde à maior pontuação possível que pode ser conseguida considerando todas as possibilidades a partir das primeiras peças de cada fileira do tabuleiro.

Agora é preciso definir as transições de estado, ou seja, como cada escolha afeta a resposta de um estado. Então para um estado qualquer, a resposta será o máximo entre as 3 escolhas que foram explicadas acima. Transformando em código cada escolha e suas implicações na resposta do problema temos que dp(i, j) = máximo entre (supondo que as peças de cada fileira estão guardadas em um array `peças` no qual `peças[0][i]` corresponde à peça `i` da primeira fileira e `peças[1][j]` corresponde à peça j da segunda fileira):

1. Deixar as peças `i` e `j` alinhadas = `peças[0][i] * peças[1][j] + dp(i + 1, j + 1)`
2. Mover a peça `i` para a direita = `dp(i, j + 1)`
3. Mover a peça `j` para a direita = `dp(i + 1, j)`

Os casos óbvios são os casos em que já esgotamos o número de peças que podemos analisar, e nesse caso retornamos apenas 0, pois nesse caso o que ocorre é que só existe uma opção: deixar a peça numa coluna sozinha. Em código isso fica (assumindo que `a` seja o número de peças na primeira fileira e `b` seja o número de peças na segunda fileira):

```cpp
if (i >= a or j >= b) return 0;
``` 

Porém isso não é suficiente. Precisamos também levar em conta que o tabuleiro pode não permitir certas ações devido à quantidade limitada de colunas. Por exemplo, imagine o seguinte caso:
| 1 | 4 | 3 |    |   |
|---|---|---|----|---|
| 1 | 5 | 3 | -2 | 5 |

Eu não tenho espaço, na segunda fileira, para mover nenhuma das peças. Isso implica que, combinações como `peças[0][1]` com `peças[1][0]` são impossíveis. Como que podemos levar isso em conta na nossa DP?

O que é importante de se perceber é que o que vai determinar o, digamos, "alcance de deslize" (ou seja, quantas casas no máximo eu posso deslocar a peça de uma fileira para a direita) de uma peça é simplesmente a quantidade total de colunas do tabuleiro menos quantas peças têm em uma fileira. No caso que foi exemplificado, o grau de flexibilidade de qualquer peça da segunda coluna é 0 pois existem tantas peças quanto colunas, então não dá pra "deslizar" nenhuma peça.

Podemos incorporar essa ideia na nossa dp da seguinte forma: além de acompanhar as peças que eu estou comparando, eu também preciso acompanhar qual a casa fícticia do tabuleiro na qual essa comparação está acontecendo. Olhe atentamente o exemplo:

Vamos supor que eu comece com o seguinte tabuleiro:
| 1  | 4 | 3 |   |   |
|----|---|---|---|---|
| -3 | 5 | 2 |  3 | 2 |

Vamos supor que estamos dentro da função dp(0, 0). Então temos as 3 opções que já foram faladas acima:

No caso de deixar as peças 1 e -3 no lugar, teremos 1 * -3 + dp(i + 1, j + 1)

|   | ↓ |  |   |   |
|----|---|---|---|---|
| 1  | 4 | 3 |   |   |
| -3 | 5 | 2 | 3  | 2  |
|      | ↑ |   || |

Agora que você entendeu como que estamos visualizando, vou ignorar a possibilidade de mover o 1 para a direita e vou direto para a possibilidade de mover o -3 para a direita porque eu quero mostrar o caso que quero que você visualize:

| ?  | ↓ |  |   |   |
|----|---|---|---|---|
| 1  | 4 | 3 |   |   |
| -3 | 5 | 2 | 3  | 2  |
|  ↑    |  |   || |

Não podemos deslizar o -3 para essa coluna. Então a partir disso a sua intuição deveria dizer que podemos, a cada transição, além de acompanhar o i e o j das peças que estamos comparando, também podemos acompanhar a coluna do tabuleiro em que elas estão. Vamos chamar a coluna atual do tabuleiro de `k`. Se voltarmos às transições de estado que discutimos, ao invés de termos as definições iniciais, podemos pensar da seguinte maneira:

dp(i, j, k) é a máxima quantidade de pontos entre todas as opções de movimento possíveis entre as peças i e j quando elas estão na casa k.

1. Deixar como está = peças[0][i] * peças[1][j] + dp(i + 1, j + 1, k + 1)
2. Deslizar a peça de cima para a direita = dp(i, j + 1, k + 1)
3. Deslizar a peça de baixo para a direita = dp(i + 1, j, k + 1)

E os casos especiais:
1. Se já fizemos escolhas para todas as peças da primeira ou da segunda fileira, retornar 0 pois não há mais combinações a serem feitas
2. (Esse é o caso novo que descobrimos com a exemplificação acima) Se a coluna `k` que eu estou estiver fora do "alcance de deslize" de qualquer uma das peças, retornar -infinito para que não consideremos esse estado.

Podemos calcular o alcance de deslize de qualquer uma das peças como sendo `colunas do tabuleiro - numero de peças da fileira`

Segue [código da solução comentado](https://github.com/sarmentow/editoriais-obi/tree/main/2020/codigo) para compreender a implementação. Eu implementei essa DP com uma função recursiva. Também seria possível implementar uma DP bottom-up, mas eu não penso dessa maneira normalmente.

## Agradecimentos e referências

- Jonathans do servidor do Neps Academy que me explicou essa maneira de ver o problema pela primeira vez

- [edit distance](https://cses.fi/problemset/task/1639)

- Se você quiser contribuir escrevendo editoriais, toda ajuda é bem-vinda! Informações sobre como contribuir estão no [README](https://github.com/sarmentow/editoriais-obi) do repositório.
