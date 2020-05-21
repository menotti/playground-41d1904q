# Frameworks C++ SSE & AVX 

## Complexidade de funções intrínsecas

Trabalhar diretamente com funções intrínsecas pode ser complicado de ser codificado e mantido. O problema é que os nomes intrínsecos são longos e as operações aritméticas são escritas na notação de função: `add(a,b)` ao invés de `a+b`.
O código a seguir é dificil de ler:
```cpp
x = _mm256_div_ps(_mm256_add_ps(b , _mm256_sqrt_ps(_mm256_sub_ps(_mm256_mul_ps(b , b) , _mm256_mul_ps(_mm256_mul_ps(a , c),_mm256_set1_ps(4.0f))))) , _mm256_mul_ps(a,_mm256_set1_ps(2.0f)));
```
Muito simples, correto? Por outro lado, essa versão empacotada é muito legível:
```cpp
x = (b + sqrt( b*b - a*c*4.0f))/(a*2.0f);
```
É como trabalhar com pontos flutuantes (floats). Você apenas precisa se lembrar que essas variáveis são vetores. Como você pode notar, o empacotamento permite operações aritméticas de um vetor com um valor escalar (vetor * escalar = vetor).

## Frameworks C++ para computação SIMD

Existem frameworks que agrupam tipos de dados vetoriais dentro de novas classes. Em seguida, sobrecarregam os operadores aritméticos, lógicos e de atribuição para simplificar os cálculos.
Entre outros, você pode usar esses dois frameworks:

1. [Biblioteca de classes vetoriais C++ de Agner Fog's](http://www.agner.org/optimize/#vectorclass). Completo e atualizado regularmente. Inclui funções trigonométricas.
2. [Ambiente Multicore Unificado](https://gain-performance.com/ume/). É a biblioteca mais recente. Eu não usei pessoalmente.

## Frameworks de tamanho reduzido

Infelizmente, essas dois frameworks são enormes, pelo menos para programação competitiva onde o código é limitado a cem KBs ou menos. 
Nos casos em que você tem limitações no tamanho do código, você precisará reduzir para uma versão menor de um desses frameworks.

Eu tenho alguns empacotadores de vetor com tamanho reduzido, focados apenas em um ou dois tipos (por exemplo, \_\_m256 8x float e \_\_m128i 8x short, para trabalhar com um tamanho de vetor de 8, tanto em floats (pontos flutuantes) quanto em números inteiros).

@[Empacotar vetores menores]({"stubs": ["framework/framework.cpp","framework/vrandom.h","framework/vconvert.h","framework/v8i.h","framework/v8f.h"], "command": "./mycompile.sh framework ./framework"})

Mesmo sendo uma versão reduzida, cada declaração de tipo de dados vetorial ocupa até 150 linhas em média (mais algumas funções auxiliares). Por favor, use esses empacotadores como referência para as suas próprias versões, pois elas podem conter bugs.

As classes empacotadas podem adicionar sobrecarga às chamadas, reduzindo o seu desempenho. Mas, na minha opinião, trabalhar diretamente com as funções intrínsecas dificilmente será mantido, além de ser embaraçoso e propenso a erros. A partir de agora, usarei classes empacotadas para abstrair o código dos intrínsecos fundamentais.

Em todas os frameworks vetoriais, você encontrará algumas funções especiais. Essas funções especiais serão amplamente usadas nas lições a seguir. Se você não entender à primeira vista, não se preocupe. Você eventualmente entenderá a lógica por trás deles.

**Funções baseadas em mesclagem**: A mesclagem é o processo de carregar condicionalmente valores vetoriais com base em uma máscara. Isso será explicado melhor nas lições a seguir. Em ambos, no empacotamento de Agner Fog e no meu empacotamento, as funções derivadas são:

1. **`if_select`**`(mask,value_true,value_false)`: Carga condicional de um vetor baseado em uma máscara. Se `mask` for verdadeiro para um componente vetorial, `value_true` é retornado, ou `value_false` caso contrário. É um `if` "fake".
2. **`if_add`**`(mask,value,add_when_true)`: Adição condicional. Retorna `value + (mask? add_when_true:0)`, para cada componente vetorial.
3. **`if_sub`, `if_mul`, `if_div`**: Semelhante a `if_add`, apenas com uma operação aritmética diferente.

**Funções horizontais**: O horizontal significa que essas funções operam dentro de uma única variável vetorial, calculando algum valor lógico ou aritmético.

1. **`horizontal_or`**`(mask)`: Se qualquer componente vetorial em `mask` for verdadeiro. Retorna um booleano.

2. **`horizontal_add`**`(vector)`: Retorna a soma de todos os componentes do vetor. O valor retornado é um número (float ou double ou int, dependendo do tipo de vetor).

> **NOTE:** Agner Fog usa classes diferentes para máscaras (com sufixo `b`), enquanto eu uso as mesmas classes de vetores para simplificar e reduzir o código.
