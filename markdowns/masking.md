# Máscaras e Carregamento Condicional

## Máscaras em Vetores

Na aula anterior, foi apresentado o conceito de máscara. Como é um conceito chave para controlar o fluxo de dados, é necessária uma explicação detalhada.

Uma máscara é um resultado de uma operação lógica entre vetores. Possui muitas similaridades com booleanos (eles são o resultado de operações lógicas em números únicos, ou em outros valores booleanos), mas internamente, cada máscara deve ser composta somente por _bits_ 1 ou por _bits_ 0.

Vamos comparar dois vetores _float_ AVX com o operador maior que (>):

![Mask AVX](/images/mask.png)

As entradas são dois vetores com valores _float_. A saída dessa operação lógica também é um vetor de valores _float_, mas os valores devem ter somente bits 0's ou somente bits 1's. Todos os 1's representam o valor lógico `TRUE`, enquanto os 0's são o valor lógico `FALSE`. O valor 1's é impresso como `-nan` para _floats_, ou como -1 para inteiros. O valor real armazenado não é importante, somente é necessário saber que possui valores verdadeiros (`TRUE`) ou valores falsos (`FALSE`).

**Resultado dos operadores lógicos (>, <, ==, &&, ||, etc)**

Utilizando o operador && como um exemplo:

- `vector && vector` = `mask`
- `mask && mask` = `mask`
- `vector && mask` = `?????` 

Eu ainda não testei o último caso, eu acho que retornará resultados inesperados. É como realizar `3 > false`, talvez em C++ funcione, mas no aspecto lógico, é incorreto.

>**NOTA:** Diferentemente dos valores booleanos, em que qualquer valor diferente de zero é `TRUE`. Somente um vetor composto com todos os bits 1's é considerado `TRUE`. Não utilize outros valores como máscara, pois falhará ou retornará resultados inesperados.

## Carregamento Condicional

Máscaras podem ser utilizadas para carregar condicionalmente valores em vetores. Se você relembrar as funções _blend-based_. Todas elas utilizam máscaras para controlar condicionalmente o carregamento de valores nos vetores:
**`if_select`**`(mask,value_true,value_false)` pode ser representado como:

![if_select](/images/ifselect.png)

Quando a máscara é definida como `FALSE`, o dado é carregado do vetor `value_false`, e quando é `TRUE`, o dado vem do vetor `value_true`. O conceito é simples, mas efetivo.

No próximo exercício, você precisa carregar um vetor de acordo com as seguintes condições:
```cpp
if (value > 3.0f || (value <= -3.7f && value > -15.0f)) {
   return sqrt(2.0f * value + 1.5f);
 }
 else {
   return (-2.0f * value - 8.7f);
 }
```
@[Masked load]({"stubs": ["masked/masked.cpp","masked/v8f.h"], "command": "./mycompile.sh masked ./masked"})


>**NOTA:** **`if_select`** NÃO É um nome de função intrínseca. É o meu wrapper para **`_mm256_blendv_ps`**. Por favor, note que `_mm256_blendv_ps` possui uma ordem de parâmetros bem diferente! _blendv_ tem a máscara como o úlitmo parâmetro!

## Desempenho

Carregamento condicional utilizando máscaras não são uma _branch_ real, então não possuem previsões errôneas, dessa forma a CPU pode fazer melhor uso da execução fora de ordem. Mas isso vem com um preço. Como vem sem uma _branch_, e toda a execução condicional é feita com operação em máscaras, ambas as _branches_ são sempre calculadas e executadas.

Se você tiver um cálculo complexo para o `valu  e_false`, ele será sempre calculado, mesmo que ele aconteça em 0,00001% das vezes. Isso acarreta em problemas de desempenho se tiver partes do código que são realmente necessárias, mas computacionalmente caras.

Na próxima lição, nós iremos aprender algumas formas de controlar o fluxo de dados, sendo capazes de sair de laçoes baseado em algumas condições.
