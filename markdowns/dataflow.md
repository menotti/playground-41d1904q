# Controlando o Fluxo de dados

## A questão do fluxo de dado compartilhado

Em programação linear, não existem problemas com a criação de divisões condicionais (funções como `if`, `switch`, `continue` e `break`) para o controle do fluxo de dados.
Você pode simplesmente ter um loop infinito e bloquear sua execução quando a condição for satisfeita.
Mas, como visto na lição anterior, um vetor não tem somente um resultado, mas N resultados no mesmo instante. Ainda, parte de um vetor pode estar pronta para sair do loop (por conta dos dados no vetor satisfazerem a condição de saida), e parte ainda estar sendo processada antes de finalizar sua execução.

>**NOTA:** Se um elemento do vetor estiver finalizado, *congele* seu processamento para evitar gasto de processamento inútil. Isso é feito através de uma máscara de componentes finalizados. Os elementos não finalizados, seguiram com a atualização, e os finalizados não. Assim, suponhamos um vetor de 8 posições, e os elementos 0, 1, 4 e 7 já foram processados, teremos então uma máscara `[false,false,true,true,false,true,true,false]` que armazena o estado de cada elemento.

## Evitando a execução de ramificações computacionalmente custosas

Uma boa abordagem para otimizar o tempo de CPU é checando se todos os valores na máscara são o mesmo, todos `TRUE` ou `FALSE`.
Quando todos os valores na máscara são os mesmos, temos um simples booleano, verdadeiro ou falso. Este pode ser utilizado para avançar em partes do código, ou usar desvios condicionais tradicionais: `if`, `switch`, `continue` e `break`...

Nas minhas classes empacotadas, uso a função `horizontal_or (mask)` (que empacota intrínsecos `_xxx_testz_xx`). "Horizontal_OR" verifica se algum valor na máscara é `true`, e neste caso retorna um simples valor booleano, e `false` em caso contrário

O próximo exercício apresenta alguns problemas de tempo limite devido a uma função computacionalmente intensiva, necessária apenas em alguns casos específicos. Otimize o código para evitar o tempo limite: 
@[Skipping Code Execution]({"stubs": ["skip/skip.cpp","skip/v8f.h"], "command": "./mycompile.sh skip ./skip"})


## Controlando o fluxo de dados

Utilizando `horizontal_or`, você pode interromper o loop antes. Não é possível conseguir essa otimização com autovetorização, mas com a vetorização manual é possível e preferível. 

Neste exercício, será calculado uma pontuação máxima entre 8 simulações paralelas ao mesmo tempo, com um limite de 200 rodadas. Deseja-se finalizar a simulação quando atingir uma pontuação maior que 1700 pontos em qualquer uma das simulações, e retornar o valor máximo (um ponto flutuante, não todo o vetor de pontuação, somente o máximo) e a rodada que se atingiu este valor.
@[Early exiting a loop]({"stubs": ["exitloop/exitloop.cpp","exitloop/v8f.h"], "command": "./mycompile.sh exitloop ./exitloop"})
