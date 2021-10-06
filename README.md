# Editoriais OBI
Editoriais e soluções para problemas da Olimpíada Brasileira de Informática

## Por que esse repositório existe?
Enquanto eu estudava pra OBI eu tive muita dificuldade em achar editoriais dos problemas de anos passados e isso foi um obstáculo enorme na minha aprendizagem. A UNICAMP disponibiliza o código para todas os problemas, sim, mas código de programação de competitiva não é muito legível ou didático.

Por conta disso, eu tive que ir atrás de comunidades com pessoas que pudessem me ajudar, e eu sinto que não deveria ter sido tão difícil conseguir essas respostas, embora essa busca tenha tido seu lado positivo (de achar uma comunidade de programação competitiva com muitas pessoas das quais eu posso aprender muito). 

Logo, esse repositório existe como um lugar que contenha explicações didáticas para os problemas de (essa é a meta) todas as provas passadas da OBI.

## Como contribuir
Ajuda é muito bem-vinda nesse projeto.

Para ajudar com o projeto você pode escrever o editorial para um problema que ainda não tem editorial ou até recomendar o link de uma resolução que exista online para algum problema. No caso de recomendar um link, você pode criar o arquivo markdown para o problema em questão, inserir o link nele e mandar uma PR.

## Links alternativos
Esse não é o único lugar em que você pode encontrar tutoriais ou editoriais para os problemas da OBI. Como eu disse na seção que justifica a existência desse repositório, eu procurei bastante na internet materiais que explicassem esses problemas, porém os que eu achei tinham alguns problemas que eu gostaria de evitar nesse repositório:

1. Formalismo
2. Leitura difícil e maçante
3. Código pouco comentado (às vezes)
4. Poucos problemas

- Algumas observações que são importante de serem feitas:
    - Formalismo matemático pode ser necessário em alguns problemas, especialmente os que envolvem provas para certas afirmações, mas há problemas em que uma explicação por exemplificação e intuição representa o processo real de resolver um problema muito mais fielmente do que puro formalismo.
    - Além disso, o formalismo matemático pode tornar a leitura um pouco difícil e descontínua.
    - A questão da inconsistência é muito importante. Sites como o NOIC (lista abaixo) têm análises de anos muito restrita, o que restringe bastante o quanto se pode aprender com os problemas passados da OBI.
 
Mesmo assim, visto que o repositório ainda está com poucos problemas e que fontes alternativas são sempre bem-vindas, aqui estão alguns links onde podem ser lidos editoriais e análises de problemas da OBI:
- [NOIC](http://noic.com.br/)
- [Servidor do discord do Neps Academy](https://discord.gg/jdQgWed)

(sugestões de mais referências que podem ser inseridas aqui são bem-vindas)

## Como avaliar seu código
Caso você não consiga avaliar seu código usando o site da OBI, existem outras opções:
- [Neps Academy](neps.academy) (conta gratuita)
- [corretor.py](https://github.com/sarmentow/editoriais-obi/blob/main/corretor.py) é um script de python que corrige seu código pra você. Atualmente, o corretor não consegue te dizer se seu código excedeu o tempo limite, apenas se ele está dando as respostas corretas, então caso esteja demorando muito para corrigir, é sinal de que seu código está excedendo o tempo limite e você precisa cancelar a execução do script (usando CTRL-C). Para usar o corretor, leia a seção abaixo.

### corretor.py
Primeiro, é necessário instalar o pacote [Click](https://click.palletsprojects.com/en/8.0.x/) utilizando `pip install click`

Caso seu código esteja em python:
```
python corretor.py ARQUIVO_DO_CÓDIGO PASTA_DO_GABARITO
```
Caso seu código esteja em C++:
```
python corretor.py --lang=cpp ARQUIVO_DO_CÓDIGO_COMPILADO PASTA_DO_GABARITO
```

Para conseguir a pasta do gabarito, é necessário baixar o arquivo compactado [no site da OBI](https://olimpiada.ic.unicamp.br/passadas/) e extraí-lo.

Se sua solução estiver dando respostas erradas, o corretor vai mostrar os casos em que as respostas não batem. Caso as respostas estejam corretas, não será printado nada.
