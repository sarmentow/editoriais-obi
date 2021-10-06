# Jogo do Preto e Branco
[Problema](https://olimpiada.ic.unicamp.br/pratique/p2/2020/f3/jogo/)

Assuntos: brute-force, backtracking 

O importante de se perceber nesse problema é que em cada casa do tabuleiro você pode botar ou não botar uma peça branca desde que sejam obedecidas as regras descritas no enunciado.

Devido às restrições baixas, basta escrever uma função recursiva que testa todas as possibilidades de jogo válidas e retorna o maior número de peças presentes no tabuleiro em qualquer momento. 

O que torna essa função "especial" é que antes de você fazer uma chamada recursiva, você atualiza o atual estado do tabuleiro para refletir a escolha que você fez (de colocar ou não colocar uma peça branca) e assim você garante que está respeitando as regras do jogo.

Para implementar o que foi descrito, pode-se utilizar um array 2d do tamanho do tabuleiro descrito pela entrada e marcar o atual estado de cada casa do tabuleiro antes de cada chamada recursiva.

A implementação funciona assim:

Vamos chamar nosso array que guarda as informações atuais do tabuleiro de `tabuleiro` e nossa função recursiva que testa todas as configurações de jogo possíveis de `max_peças(x, y)` na qual `x` representa a fileira e `y` representa a coluna.

Marcamos no tabuleiro a posição de todas as peças pretas e aí chamamos a função `max_peças(1, 1)`. Dentro da função testamos se é possível colocar uma peça nessa posição (respeitando as regras impostas pelo enunciado). Se sim, marcamos no tabuleiro que em `tabuleiro[1][1]` existe uma peça branca e avançamos para a próxima casa à direita ou abaixo (caso estejamos na última coluna) chamando a função recursivamente na próxima casa.

Além disso, declaramos no topo da função uma variável `res` que guarda o máximo número de peças no tabuleiro em qualquer momento. Toda vez que testarmos colocar ou não colocar uma peça, atualizamos `res` para ser o máximo entre 1 + função na próxima casa (quando optarmos por colocar) e seu atual valor e, quando ocorrer a chamada que opta por não colocar a peça na casa atual, será o máximo entre o seu atual valor e o valor da próxima chamada da função.

Caso já tenhamos analisado o tabuleiro inteiro, retornamos `0`.

[Código comentado para melhor compreensão](https://github.com/sarmentow/editoriais-obi/blob/main/2020/codigo/preto-e-branco.cpp)