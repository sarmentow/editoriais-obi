# Festa Olímpica

(Esse editorial ainda está em construção)

Esse problema pode fazer parecer que é necessário a utilização de algum algoritmo para encontrar rapidamente os múltiplos do divisor de cada turno entre 1 e N, mas existe um jeito mais intuitivo de pensar sobre esse problema.

O que deveria sugerir essa ideia que vou explicar é essa parte do enunciado: "você deve listar apenas os 10.000 primeiros (ou seja, os com menores números) convidados".

O jeito "bruto" de resolver esse problema seria, para cada item da lista inicial, aplicar a operação de todas as rodadas e de alguma forma lidar com a possibilidade do número ser eliminado em alguma das rodadas, devido às consequências que isso teria no posicionamento relativo dos números. 

É possível observar que, no mínimo, isso acarretaria em 10^9 operações para N = 10^9 e M = 1. Para números maiores de M e em certas condições, o algoritmo não seria rapido o suficiente.

Enfim, não irei adentrar muito nesse pensamento, quero apenas demonstrar a intuição de que se fosse possível saber, em avanço, quais números não fariam parte da lista final, seria possível diminuir a complexidade do problema, pois não seria necessário desperdiçar tempo em operações com números que não vão fazer parte da lista final.

A partir disso, pode-se chegar à conclusão de que se houver uma maneira de começar com a posição relativa da lista final de cada membro e chegar à posição inicial, antes da primeira rodada, o algoritmo seria aceitável. 

Prova: A complexidade seria O(NM) - pois todos os números da lista final teriam que ser processados M vezes. Porém, já que a lista final tem no MÁXIMO 10000 membros, O maior número de operações, para M = 5000, seria 5 * 10^8
