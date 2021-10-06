# Rede Social
[Problema](https://olimpiada.ic.unicamp.br/pratique/p2/2020/f3/rede/)

Assuntos: Binary search

As restrições do problema implicam que a solução precisa ser ou O(n) ou O(n log n). O jeito mais fácil de fazer isso seria com algo que envolvesse sortar a lista e aproveitar a posição dos elementos da lista pra dar a resposta. 

Com isso você pode chegar à seguinte conclusão: se a lista estiver sortada, eu posso usar binary search para achar a primeira postagem com índice de repostagem maior ou igual a um número `x` e checar quantas postagens existem até o fim da lista (ou seja, com índice maior ou igual a `x`). Se existirem pelo menos `x` postagens com índice de repostagem maior ou igual a `x`, então eu posso guardar `x` como sendo o fator de influência até que eu encontre um fator de influência `y` (seguindo as mesmas regras) que seja maior do que `x`.

A implementação funcionaria da seguinte maneira: iterar por todos os índices de repostagem (de 1 até 10ˆ6 no pior caso) possíveis e checar quantas postagens têm índice maior ou igual ao que está sendo analisado. Caso exista um número maior ou igual de postagens ao próprio índice (um pouco confuso, mas é o que o problema pede), guarda-se o índice como sendo o fator de influência já que necessariamente (já que estamos iterado do menor índice para o maior) é o maior índice possível atualmente para ser fator de influência.

Segue [código comentado](https://github.com/sarmentow/editoriais-obi/blob/main/2020/codigo/rede-social.cpp) para melhor compreensão.

## Referências e material
- [Compressão de coordenadas](https://usaco.guide/silver/sorting-custom?lang=cpp) (mencionado no código embora não seja necessário para resolver o problema)
- [Binary search](https://usaco.guide/silver/binary-search?lang=cpp)
