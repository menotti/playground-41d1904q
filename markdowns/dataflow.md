# EN
# Controlling the Data Flow

## The shared data flow issue

In linear programming, there isn't any problem in creating conditional branches ( `if`, `switch`, `continue` and `break` ) for controlling the data flow.
You can just have an infinite loop and break out of it when a condition is satisfied. 
But as we saw in the previous lesson, a vector has not only a single condition result, but N condition results at the same time. Part of the vector can be ready to exit the loop (because the vector data has reached the exit condition), but the rest of the data still has active work to do before exiting. 

>**NOTE:** If a vector component is already finished, *freeze* it to avoid doing any further calculations on it. This is done by masking the finished components on any value assignment. The unfinished vector components will keep being updated, but finished ones won't. So if I have an 8x float vector, and components 0,1,4 and 7 have reached an end state, I'll need a mask `[false,false,true,true,false,true,true,false]` on each data load.

## Avoiding the execution of computationally expensive branches 

The simplest approach to save CPU time is by checking if all values inside a mask are the same, either all `TRUE` or all `FALSE`.
When all values inside the mask are the same, we indeed have a simple boolean, either true or false. This can be used to skip parts of the code, or using the normal conditional branches:  `if`, `switch`, `continue` and `break`...

In my wrapper classes I use the `horizontal_or(mask)` function (that wraps `_xxx_testz_xx` intrinsics) . "Horizontal OR" checks if any value inside the mask is `true`, and in that case returns a single boolean with the `true` value, and `false` in any other case.

The next exercise has some timeout problems due to a computationally expensive function that is only needed in some corner cases. Optimize the code to avoid the timeout:
@[Skipping Code Execution]({"stubs": ["skip/skip.cpp","skip/v8f.h"], "command": "./mycompile.sh skip ./skip"})


## Controlling the Data Flow

By using `horizontal_or`, you can also break out of a loop early. You can't get this optimization with autovectorization, but with manual vectorization it's possible, and preferred.

In this exercise, you are calculating a max combo score by doing 8 parallel simulations at once, with a limit of 200 turns.
You want to end the simulation once your reach more than 1700 points in any one of the parallel simulations, and return the max score (a float value, not the whole vector with all scores, just the max) and the turn where you get that score.
@[Early exiting a loop]({"stubs": ["exitloop/exitloop.cpp","exitloop/v8f.h"], "command": "./mycompile.sh exitloop ./exitloop"})

# PT/BR
# Controlando o Fluxo de dados

## A questão do fluxo de dado compartilhado

Em programação linear, não existem problemas com a criação de divisões condicionais (funções como `if`, `switch`, `continue` e `break`) para o controle do fluxo de dados.
Você pode simplesmente ter um loop infinito e bloquear sua execução quando a condição for satisfeita.
Mas, como visto na sessão anterior, um vetor não tem somente um resultado, mas N resultados no mesmo instante. Ainda, parte de um vetor pode estar pronta para sair do loop (por conta dos dados no vetor satisfazerem a condição de saida), e parte ainda estar sendo processada antes de finalizar sua execução.

>**OBSERVAÇÂO:** Se um elemento do vetor estiver finalizado, *congele* seu processamento para evitar gasto de processamento inútil. Isso é feito através de uma máscara de componentes finalizados. Os elementos não finalizados, seguiram com a atualização, e os finalizados não. Assim, suponhamos um vetor de 8 posições, e os elementos 0, 1, 4 e 7 já foram processados, teremos então uma máscara `[false,false,true,true,false,true,true,false]` que armazena o estado de cada elemento.


## Evitando a execução de divisões condicionais custosas

Uma boa abordagem para otimizar o tempo de CPU é checando se todos os valores na máscara são o mesmo, todos `True` ou `Falso`.
Quando todos os valores na máscara são os mesmos, temos um simples booleano, verdadeiro ou falso. Este pode ser utilizado para avançar em partes do código, ou usar divisões condicionais tradicionais: `if`, `switch`, `continue` e `break`...

Neste caso, foi utilizado a função `horizontal_or(mask)`. "Horizontal_OR" verifica se algum valor na máscara é `true`, e neste caso retorna um simples valor booleano, e `false` em caso contrário

O próximo exercicio contém alguns problemas de timeout ocasionados por algumas funções custosas que somente ocorrem em alguns casos. Otimize o código para evitar o timeout: 
@[Skipping Code Execution]({"stubs": ["skip/skip.cpp","skip/v8f.h"], "command": "./mycompile.sh skip ./skip"})


## Controlando o fluxo de dados

Utilizando `horizontal_or`, você pode travar ou encerrar o loop antes. Não é possível conseguir essa otimização com autovetorização, mas com a vetorização manual é possível e preferivel

Neste exercício, será calculado uma pontuação máxima entre 8 simulações paralelas ao mesmo tempo, com um limite de 200 execuções. Deseja-se finalizar a simulação quando atingir uma pontuação maior que 1700 pontos em qualquer uma das simulações, e retornar o valor máximo (um ponto flutuante, não todo o vetor de pontuação, somente o máximo) e o turno que se atingiu este valor.
@[Early exiting a loop]({"stubs": ["exitloop/exitloop.cpp","exitloop/v8f.h"], "command": "./mycompile.sh exitloop ./exitloop"})
