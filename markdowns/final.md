# Palavras finais

Neste curso, você deve ter obtido um bom nível de compreensão sobre vetorização manual e automática de CPU:

- Requisitos de Hardware e software para usar instruções SSE e AVX no seu código.
- Os tipos de dados de vetores disponíveis.
- Informação sobre como checar o uso de autovetorização e dicas se loopes podem ser autovetorizados.
- Frameworks de vetores em C++.
- Mascaramento e carga condicional.
- Controle do fluxo de dados.

### Prós e contras

As vetorizações AVX e SSE são interessantes e, teoricamente, seu uso traz mais benefícios que qualquer otimização linear.

**Prós**

- Ganhos potenciais de 300% a 600% de performance quando comparados a código linear.
- Similaridades com CUDA, programação vetorizada no nível de GPU.

**Contras**

- A performance depende do hardware em que o código está sendo rodado.
- Má performance quando há muito carregamento e descarregamento de dados.
- O fluxo de dados pode se tornar bem difícil de controlar, e o tempo de execução de cada valor dentro do vetor afeta o tempo de execução geral. Você não pode sair antes que todos os valores satisfaçam a condição de saída.
- É complexo para programar.
- Carece de funções instrínsecas: Trigonometria, números aleatórios, divisão de inteiros.

### Outros cursos

*Em desenvolvimento: Offline MarsLander solver using a Genetic Algorithm (AVX enabled)/*

### Jogos Multiplayer Codingame

 Simulações com uso de AVX podem ser feitas em alguns Jogos Multiplayer Codingame:

- [Coders Strike Back](https://www.codingame.com/multiplayer/bot-programming/coders-strike-back) Minha versão do AVX alcançou entre 2.5 e 3.5 milhões de simulações por turno, com turnos de 150 milisegundos. Isso é feito paralelizando 8 simulações de estadoos jo jogo ao mesmo tempo. Uma versão anterior com cálculos seriais (isto é, com dados fora do AVX, colocando-os dentro de vetores AVX, calculando e, depois, retirando o resultado) alcançou apenas 600k simulações/turno.
- [Poker Chip Racer](https://www.codingame.com/multiplayer/bot-programming/poker-chip-race) Performance é bem dependente do número de indivíduos, entre 100k e 1.5M simulações/turno. Os turnos duram 150ms também.

Vários outros jogos podem ser paralelizados e simulados usando vetores AVX/SSE.

### Links úteis

- [Guia de funções Intrínsecas da Intel](https://software.intel.com/sites/landingpage/IntrinsicsGuide)
- [Tabela de x86 Intrinsics Cheat](https://db.in.tum.de/~finis/x86-intrin-cheatsheet-v2.2.pdf?lang=en)
- [Manual dos Desenvolvedores de Arquiteturas da Intel](http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-software-developer-vol-1-manual.pdf)
- [Software de otimização de recursos de Agner Fog](http://www.agner.org/optimize/)

