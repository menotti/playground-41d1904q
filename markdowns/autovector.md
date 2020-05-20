# Vetorização automática

## _Flags_ de autovetorização do GCC

O GCC é um compilador com recursos avançados, e, com as _flags_ de otimização `-O3` ou `-ftree-vectorize`, o programador pode indicar ao compilador para que procure por laços e otimize-os (lembre-se de também especificar a _flag_ `-mavx`). O código fonte continua o mesmo, contudo, o código compilado pelo GCC é completamente diferente.

Por padrão, o GCC não irá indicar se ou onde foi aplicada a autovetorização, exceto que as seguintes _flags_ sejam utilizadas:

- `-fopt-info-vec` ou `-fopt-info-vec-optimized`: O compilador vai informar quais laços (por N° de linha) estão sendo otimizados por vetorização.
- `-fopt-info-vec-missed`: Fornece informações detalhadas sobre os laços nos quais não foram otimizados, permitindo ao programador que realize mudanças no código para que tal otimização seja possível.
- `-fopt-info-vec-note`: Informações detalhadas sobre todos os laços e otimizações feitas.
- `-fopt-info-vec-all`: Todas as _flags_ anteriores.

>**NOTA:** Há _flags_ similares para outras otimizações que seguem o formato `-fopt-info-[opção]-optimized` tal como a otimização `inline` na qual pode ser indicada com a _flag_ `-fopt-info-inline-optimized`

Neste exemplo, utilizaremos a otimização de autovetorização do GCC. Para isso, habilite as _flags_ `-O3` e com o modo verboso `-fopt-info-vec-optimized`. Você pode alterar as _flags_ de compilação para ver diferentes opções de saída:
@[Autovectorization]({"stubs": ["autovector/autovector.cpp","autovector/compilerflags.txt"], "command": "./mycompileLOG.sh autovector ./autovector"})

Se tudo estiver correto, os resultados dos testes devem ser iguais aos seguintes:
```
/project/target/autovector/autovector.cpp:22:21: note: loop vectorized
/project/target/autovector/autovector.cpp:15:23: note: loop vectorized
```
Com o mesmo código fonte, é possível realizar dois testes distintos:

- No arquivo `compilerflags.txt`, altere as opções de exibição de informações para `-fopt-info-vec-all`, e execute novamente o exemplo.
- Na primeira linha de do arquivo `autovector.cpp`, altere `optimize("O3",` para `optimize("O2",`, e execute novamente.

Compilações que não utilizam otimizações de vetorização serão mais lentas que as vetorizadas.

## Requisitos para a vetorização de laços

Nem todos os laços podem ser vetorizados. Para que tal otimização seja realizada, existem algumas ressalvas:

- A contagem do laço não pode ser alterada assim que as iterações se iniciarem. Isso significa que o final do laço deve ser previsível, sem a utilização de variáveis dinâmicas para esse controle, isto é, alterarem-se sem comportamento previsível, aleatoriamente crescendo ou descrescendo.
- O uso das palavras chave `break` ou `continue` também impõem limitações. Algumas vezes o compilador é inteligente o suficiente para aplicar a otimização mesmo com o uso delas, mas este não é sempre o caso. Tente adicionar a linha `if (j == 27) continue;` logo antes da atribuição `result[j]` na linha 25, e execute novamente a compilação.
- Há alguns limites na realização de chamadas de funções externas dentro do laço.
- Não deve haver dependência de dados com outros índices do laço. Por exemplo, `for (int i = 1; i < N; i++) x[i] = x[i - 1] * 2;`, neste caso, o laço é percorrido com a variável `i`, e o dado na posição `x[i]` depende no valor resultante anterior `x[i - 1]`. De modo que os registradores AVX são carregados utilizando 8 valores de ponto flutuante, o compilador não consegue fazer tal operação de forma otimizada.
- Comandos condicionais (`if` / `else`) podem ser utilizados desde que não alterem o fluxo de controle, e apenas para, por exemplo, condicionamente carregar os valores `A` ou `B` na variável `C`. Para selecionar os valores `A` ou `B` o compilador aplica o uso de máscaras, de modo que ambos os caminhos de dados `A` e `B` são calculados, e `C` vai carregar um valor ou outro. Por exemplo:
```cpp
 if ( s >= 0 ) {
   x[i] = (-b[i]+s)/(2.0f*a[i]);
   y[i] = (-b[i]-s)/(2.0f*a[i]);
 }
 else {
   x[i] = 0.0f;
   y[i] = 0.0f;
 }
```
Este é um laço vetorizável. Note que o fluxo de controle nunca é alterado, e as posições `x[i]` e `y[i]` são sempre definidas para um ou outro valor.

Leia [Vectorization with Intel C++ Compilers](https://software.intel.com/sites/default/files/m/4/8/8/2/a/31848-CompilerAutovectorizationGuide.pdf) para informações adicionais sobre autovetorização. Este documento refere-se a compiladores da Intel, mas fornece informações completas e interessantes sobre o assunto. Também é possível encontrar informações na página [Auto-vectorization in GCC](https://gcc.gnu.org/projects/tree-ssa/vectorization.html) do compilador GCC.

Um detalhe interessante sobre autovetorização é que ela vem de graça. O programador não precisa realizar mudanças drásticas no código, e possivelmente o laço será vetorizado. Algumas vezes, especialmente em computações de alto desempenho, os laços e a vetorização precisam ser otimizados manualmente para utilizar os registradores AVX, garantindo maior vazão. Tal tópico será explorado nas próximas lições.
