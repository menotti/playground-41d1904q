# Primeiro código AVX: cálculo da SQRT

Agora que analisamos todos os requisitos, a autovectorização e as intrínsecas do AVX, podemos criar nosso primeiro programa vetorizado manualmente. Neste exercício, você precisa vetorizar um cálculo sqrt de números de ponto flutuante. Usaremos explicitamente o tipo de dados \_\_m256 para armazenar nossos números de ponto flutuante, reduzindo a sobrecarga no carregamento de dados.

@[Vectorized SQRT]({"stubs": ["sqrt/sqrt.cpp"], "command": "./mycompile.sh sqrt ./sqrt"})

Você provavelmente verá uma melhoria de desempenho de 600% ou mais.
Ou seja, depois de carregar os dados, o AVX executará até 7 vezes mais rápido que o sqrtf normal. O limite teórico é de 800%, mas raramente é alcançado. Você pode esperar um aumento médio entre 300% e 600%.
