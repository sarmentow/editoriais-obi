# Cubo e Quadrado

A maneira mais simples de resolver esse problema era perceber que para as restrições (B = 10^8) o maior número cujo cubo fique abaixo de 10^8 seria a raiz cúbica de 10^8, que é aproximadamente 464. 

Ou seja, para qualquer número que pudesse ser quadrado e cubo ao mesmo tempo, no pior dos intervalos (1 <= x <= 10^8), ele seria no máximo cubo e quadrado de 464.

Outra maneira de dizer isso é que para números acima de 464, mesmo que o quadrado desse número fosse menor que 10^8, o cubo seria maior, e portanto não haveria como existir números que fossem cubos e quadrados de um número maior que 464.

Como 464 é um número baixo, o algoritmo é: 

1. Gerar todos os cubos dos números entre 1 e 464, guardar de alguma maneira - um map por exemplo - o resultado do cubo desses números. 

2. Fazer a mesma coisa com o mesmo intervalo entre 1 e 464, sendo que dessa vez gerando os quadrados dessa sequência. Caso um desses quadrados também fosse cubo, de acordo com a informação guardada na etapa anterior, somar 1 à resposta. 

Como os passos anteriores são limitados pelo maior número cujo cubo é menor ou igual a B, esse algoritmo é O(Raiz cúbica de B).

