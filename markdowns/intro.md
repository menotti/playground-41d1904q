# O que são SSE e AVX?

## História

Nos anos recentes, as CPUs alcançaram algumas limitações físicas e de energia, logo as velocidades de CPU não cresceram expressivamente, em termos de GHz.
Conforme necessidades computacionais continuaram a crescer, projetistas de CPU decidiram resolver este problema com três soluções:

-  Adicionando mais núcleos. Desse modo, os Sistemas Operacionais podem distribuir aplicações em execução através dos diferentes núcleos. Além disso, programas podem criar múltiplas threads a fim de maximizar a utilização dos núcleos.
-  Adicionando operações vetoriais a cada núcleo. Esta solução permite com que o processador execute uma mesma instrução a todo um vetor de dados. Isto só pode ser feito a nível de aplicação.
-  Execução fora de ordem de múltiplas instruções. CPUs modernas são capazes de executar até quatro instruções ao mesmo tempo, se elas forem independentes.
Leia http://www.agner.org/optimize/blog/read.php?i=417 para mais informações

Registradores vetoriais começaram em 1997 com o conjunto de instruções MMX, contendo registradores de 80-bit. Mais tarde, os conjuntos de instruções SSE foram lançados (diversas versões deles, do SSE1 ao SSE4.2), com registradores de 128-bits.
Em 2011, a Intel lançou a arquitetura Sandy Bridge, com o conjunto de instruções AVX (registradores de 256-bits).
Em 2016 o primeiro processador AVX-512 foi lançado, com registradores de 512-bits (até 16x 32-bit vetores de float).

Nesse curso iremos focar em ambos os conjuntos de instrução - SSE e AVX - porque ambos são comumente encontrados em processadores recentes. O AVX-512 está fora do escopo do curso, mas a maior parte do curso pode ser reutilizada, mudando apenas os registradores de 256-bit para as suas contrapartes de 512-bits (registradores ZMM).

## Registradores SSE & AVX

O SSE e AVX têm 16 registradores cada. No SSE estes são referenciados como XMM0-XMM15, e no AVX são chamados YMM0-YMM15. Registradores XMM têm 128 bits de tamanho, enquanto YMM são 256bit.

SSE adiciona três typedefs: `__m128` , `__m128d` e `__m128i`. Float, double (d) e integer (i) 
respectivamente.

AVX adiciona três typedefs: `__m256` , `__m256d` e `__m256i`. Float, double (d) e integer (i) 
respectivamente.

![SSE & AVX Registers](/images/avx.png)

>**NOTE:** Os XMM e YMM se sobrepoem! Os registradores XMM são tratados como a metade inferior do correspondente registrador YMM. Isso pode introduzir alguns problemas de performance ao misturar código SSE e AVX.

Tipos de dado float (\_\_m128, \_\_m128d, \_\_m256 and \_\_m256d) têm apenas uma espécie de estrutura de dados. Por causa disso, o GCC permite o acesso à componentes de dado como um arranjo (array).
 I.e: Isto é válido:
 
```cpp
  __m256 myvar = _mm256_set1_ps(6.665f); //Atribui um único float a todos os valores do vetor
  myvar[0] = 2.22f;                       //Válido em um compilador GCC
  float f = (3.4f + myvar[0]) * myvar[7]; //Isto é válido em um compilador GCC
```

\_\_m128i e \_\_m256i são unions, então os tipos de dados devem ser referenciados. Eu não encontrei uma maneira apropriada de obter a declaração da union, então utilizo funções _mm_extract_epiXX() para obter valores individuais de dados de vetores do tipo integer.

## Exemplo de operação com AVX

Quando uma instrução em AVX é executada, o processo é o seguinte:

![AVX Add](/images/avxplus.png)

Todas as operações são aplicadas no mesmo instante. Em termos de desempenho, o custo de execução para um único `Add` em um float é similar ao de executar `VAdd` em 8 floats em AVX. Em [Agner Fog's Instruction Tables](http://www.agner.org/optimize/instruction_tables.pdf), você tem maiores informações no que concerne à latência e taxa de transferência das instruções. Na arquitetura Sandy Bridge, `VADDPS/D` tem latência 3 and taxa de transferência 1, exatamente como `FADD(P)`

