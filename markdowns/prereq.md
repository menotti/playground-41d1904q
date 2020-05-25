# Pré-Requisitos

SSE/AVX possuem pré-requisitos na arquitetura da máquina alvo. Nesse curso, as compilações binárias terão como alvo apenas a máquina atual. Para isso, nós usaremos `arch=native`, uma flag do GCC para detectar os recursos da CPU e usá-los de acordo.

>**Nota:** Binários compilados irão falhar em maquinas que não possuem compatibilidade para AVX. Se você precisa de um binário que se adapte a diferentes CPUs, você precisará fazer uso da identificação da CPU e utilizar funções diferentes, ou fazer diferentes binários destinados para cada conjunto de instruções diferente.

Como dito na introdução, o SO, o compilador e a CPU devem todos suportar extensões AVX. Nós podemos rodar esse script para detectar os recursos do sistema:

@[Detect System Capabilities]({"stubs": ["prereq/detect.sh"], "command": "./run.sh ./prereq/detect.sh"})

Em `CPU flag capabilities`, nós procuraremos pela flag `avx`. Isso identifica que a CPU é compatível com AVX. Se você tem `avx2` significa que a CPU suporta extensões AVX2. AVX é o suficiente para se ter vetores float de 8x32 bits. AVX2 adiciona vetores para inteiros de 256 bits (números inteiros de 8x32 bits, por exemplo). Mesmo assim, vetores inteiros de 256 bits parecem ser executados da mesma forma que dois vetores de 128 bits, então o desempenho não melhora significativamente em relação aos vetores inteiros SSE de 128 bits.

Em `GCC capabilities` nós procuraremos pelo pragma **`#define __AVX__ 1`**. Isso indica que as branch do AVX serão ativadas.
>**Sempre use -march=native ou -mavx !!** Se você roda o GCC sem elas, você **não conseguirá** a flag \_\_AVX\_\_!!! Os parâmetros padrões do GCC são genéricos e sem a flag não será possivel ativar o AVX mesmo que a CPU seja compatível.

Por fim, nós verificamos se o Kernel do Linux é `2.6.30` ou maior. Um Kernel `4.4.0` ou maior é o ideal.

Com todos esses pré-requisitos atendidos, nós estamos prontos para programar o nosso primeiro programa vetorizado AVX!
