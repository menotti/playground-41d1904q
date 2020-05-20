# Uso de SSE & AVX

CPU's com SSE/AVX têm instruções assembly para operar com registradores `XMM` e `YMM`. Mas, na maioria dos compiladores o processo é simplificado usando funções intrínsecas, para que programadores não precisem usar assembly diretamente.

## Funções intrínsecas

Compiladores encapsulam instruções assembly como funções, e usá-las é tão fácil quanto chamar uma função com os parâmetros corretos. Ás vezes essas funções intrínsecas são emuladas se a CPU não suportar o conjunto de instruções.

Funções intrínsecas de SSE/AVX usam a seguinte convenção de nomenclatura:

 ```cpp
 _<vector_size>_<intrin_op>_<suffix>
 ```

- `<vector_size>` é `mm` para vetores 128 bit (SSE), `mm256` para vetores 256 bit (AVX e AVX2), e `mm512` para AVX512.
- `<intrin_op>` Declara a operação da função intrínseca. I.e. `add`, `sub`, `mul`, etc...
- `<suffix>` Indica o tipo de dado. `ps` para float, `pd` para double, e `ep<int_type>` é para tipos de dado inteiro `epi32` para inteiro de 32 bit com sinal, `epu16` para inteiro de 16 bit sem sinal, etc..

Você pode encontrar todas as funções intrínsecas no [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide)
É uma referência completa para qualquer função intrínseca disponível em SSE/AVX, com categorias e barra de pesquisa.
Há também a [x86 Intrinsics Cheat Sheet](https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.2.pdf?lang=en)
Mas é mais complicada de ler porque é mais complexa.

## Funções ausentes nas intrínsecas SSE/AVX

**Ausência de divisão inteira**

Por alguma razão, SSE e AVX não possuem operadores de divisão inteira. Existem algumas maneiras de contornar isso:

- Calculando a divisão em código linear. Recuperando os dados únicos, dividindo-os e armazenando-os novamente no vetor. Isso é bem lento.
- Convertendo o vetor de inteiro para float, dividindo-o e convertendo-o novamente para inteiro.
- Para divisores conhecidos em tempo de compilação, existem alguns números mágicos para converter uma divisão por uma constante em uma operação de multiplicação. Veja [libdivide](https://libdivide.com/) e [Exact Division by Constants](http://www.icodeguru.com/Embedded/Hacker's-Delight/077.htm) para mais informações.
- Para divisões por potências de dois, usando a operação de deslocamento de bits. Dividir pelo inteiro 2 é a mesma coisa que efetuar um deslocamento à direita. Isso pode ser feito apenas se todos os vetores forem divididos pela mesma potência de dois. Preste atenção quando efetuar um deslocamento à direita em números com sinal! Use operações de deslocamento de bits que reconheçam o sinal.

**Ausência de funções trigonométricas**

Não existem funções trigonométricos em funções intrínsecas de vetor. Soluções possíveis são calculá-las com código linear (uma a uma para cada valor do vetor), ou criar funções de aproximação. As aproximações de Séries de Taylor e Remez dão bons resultados.

**Ausência de um gerador de números aleatórios**

Além disso, não existem geradores de números aleatórios para vetores como intrínsecos. Mas é simples recriar um bom gerador pseudoaleatório a partir de uma versão linear. Apenas certifique-se dos bits usados no gerador de números pseudoaleatórios. Geradores de 32 ou 64 bits são preferíveis para preencher vetores.


## Penalidades de desempenho

**Alinhamento de dados**

Arquiteturas de CPU mais antigas não podem usar vetorização à menos que os dados estejam alinhadas em memória ao tamanho do vetor. Algumas outras CPUs podem usar dados não alinhados com algumas penalidades de desempenho. Nos processadores recentes a penalidade parece ser insignificante [Data alignment for speed: myth or reality?](http://lemire.me/blog/2012/05/31/data-alignment-for-speed-myth-or-reality/).
Mas, para garantir, pode ser uma boa ideia alinhar os dados se isso não adicionar uma sobrecarga excessiva.

No GCC, o alinhamento de dados pode ser feito com esses atributos de variável:
 `__attribute__((aligned(16)))`
 `__attribute__((aligned(32)))`

Reveja [Specifying Attributes of Variables](https://gcc.gnu.org/onlinedocs/gcc-3.2/gcc/Variable-Attributes.html) para mais informações.

Eu faço apenas: `#define ALIGN __attribute__((aligned(32)))` para simplificar a declaração de alinhamento em variáveis.

**Penalidades de transição SSE <-> AVX**

Há outro grande problema ao misturar bibliotecas legadas SSE e a nova arquitetura AVX. Como o XMM e o YMM compartilham os 128 bits inferiores, transicionar entre AVX e SSE pode levar a valores indefinidos nos 128 bits superiores. Para resolver isso, o compilador precisa salvar os 128 bits inferiores, limpá-los, executar a operação SSE antiga e restaurar o valor antigo. Isso adiciona uma sobrecarga perceptível às operações do AVX, resultando em desempenho reduzido.

>**NOTA:** Esse problema NÃO SIGNIFICA que você não pode usar \_\_m128 and \_\_m256 ao mesmo tempo sem penalidades de desempenho. AVX tem um novo conjunto de instruções para \_\_m128, com prefixos VEX. Essas novas instruções VEX não têm nenhum problema em combinar com instruções \_\_m256. A penalidade de transição ocorre quando instruções \_\_m128 não-VEX são combinadas com instruções \_\_m256. Isso acontece quando você usa bibliotecas SSE antigas ligadas à programas AVX novos.

Para evitar penalidades de transição, o compilador pode adicionar automaticamente chamadas para `VZEROUPPER` (limpa os 128 bits superiores) ou `VZEROALL` (limpa todo o registrador YMM) com o parâmetro `-mvzeroupper`, ou o programador pode fazê-lo manualmente. Se você não estiver usando nenhuma biblioteca SSE externa, e tiver certeza de que tudo que você programa é habilitado para VEX e compilado com extensões AVX habilitadas, você pode instruir o compilador a evitar adicionar chamadas `VZEROUPPER`, com: `-mno-vzeroupper`

Confira [Avoiding AVX-SSE Transition Penalties](https://software.intel.com/en-us/articles/avoiding-avx-sse-transition-penalties) e [Why is this SSE code 6 times slower without VZEROUPPER on Skylake?](https://stackoverflow.com/questions/41303780/why-is-this-sse-code-6-times-slower-without-vzeroupper-on-skylake) para informações adicionais.

**Carregamento, descarregamento e embaralhamento de dados**

Mover dados dos registradores AVX pra lá e pra cá pode ser custoso. Em alguns casos, se você tem alguns dados armazenados em estruturas lineares, enviar esses dados para vetores AVX, executar algumas operações e recuperar esses dados pode ser mais custoso que simplesmente realizar os cálculos linearmente.

Algum tempo atrás, eu tentei simular um pouco de física em um jogo, [Codingame's Poker Chip Race](https://www.codingame.com/multiplayer/bot-programming/poker-chip-race), com AVX. Esse jogo é baseado em N entidades circulares colidindo em um espaço 2D. Então, naquele cenário eu precisava calcular até N*(N-1)/2 possíveis colisões. Minha primeira tentativa envolveu ter classes de entidade normais (com posição, raio, etc) e para o cálculo de colisão eu embaralhei todas as possíveis colisões de entidades em vetores AVX, as calculei em AVX e as retornei de volta para as classes de entidade. Quando terminei, os resultados que obtive foram medíocres, com uma melhoria não superior à 30% em relação ao código linear, com muita sobrecarga e um código difícil de manter. Depois de usar um profiler eu detectei que 90% do tempo de CPU estava sendo usado em carregamento e descarregamento de dados.

Portanto, os programadores devem levar em consideração a sobrecarga de carregamento e descarregamento de dados. Lembre-se de que em alguns casos isso se torna um gargalo.
