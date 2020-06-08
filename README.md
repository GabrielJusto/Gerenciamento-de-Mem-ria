## Trabalho Prático 2 - Sistemas Operacionais
## Gerenciamento de Memória
O presentetrabalho tem por objetivo explorar as abordagens de alocação de espaço contíguo para processos, e explorar as diferentes técnicas e políticas de alocação de espaços em uma memória.

### Estratégias de Alocação
A ferramenta deverá permitir a exploração de (i)partições fixas de mesmo tamanhoou(ii)partições variáveis.Comum  a  todos  os  métodos  deverá  ser  a  informação  do  tamanho  da  memória principal a  ser empregada, que define o tamanho total inicial disponível para alocação.Deverá ser assumido um tamanho sempre equivalente a uma potência de dois.
Para o sistema de partições fixas, deverá ser possível informar o tamanho da partição.Para o sistema de partições variáveis, deverá ser possível a política de alocação a ser empregada, se Best-fit, worst-fit, first-fit ou next-fit. A escolha do tipo de política a ser aplicadadeverá ser escolhidaem tempo de execução pelo usuário.
No  escopo  deste  trabalho,o  tratamento  de  alocações  de  processos  que  venham  a  ultrapassar  a quantidade de espaço disponível na memória principal, deverá se dar a partir da notificação de “ESPAÇO INSUFICIENTE DE MEMÓRIA”.

### Requisições de alocação de processos.
A sequência de requisições de alocação e liberação de espaços de memória deverá ser informadaem um arquivo. Uma requisição de alocação de espaço em memória deverá ser realizadaa partir da representação do comando (“IN”),do nome do processo (“ID”) edo tamanho do processo. Para o pedido de liberação de um espaço, ou seja, quando um processo deixa de existir na memória, um comando (“OUT”) e a identificação deste (“ID) deverãoser informados. Um exemplo de arquivo contendo asequência de alocações e liberações é apresentado abaixo.

|Arquivo |Significado |
|-----|-------|
|N(A, 10)|Requisita a alocação de 10 espaços para o processo A|
|N(B, 15)|Requisita a alocação de 15 espaços para o processo B|
|IN(C, 23)|Requisita a alocação de 23 espaços para o processo C|
|OUT(A)|Libera o espaço alocado pelo processo A|
|OUT(B)|Libera o espaço alocado pelo processo B|
|IN(D, 13)|Requisita a alocação de 13 espaços para o processo D|
|OUT(C)|Libera o espaço alocado pelo processo C|
|IN(E,32)|Requisita a alocação de 32 espaços para o processo E|
|OUT(E)|Libera o espaço alocado pelo processo E|
|OUT(D)|Libera o espaço alocado pelo processo D|

### Visualização de resultados
Da escolha da estratégia de alocação para o tipo de particionamento escolhido e do arquivo com a descrição das sequênciasde requisições, deverá ser possível visualizar os espaços livres para alocação.A execução da ferramenta deverá permitir a visualizaçãoa cada passo.
Comum a todas as abordagens deverá ser a listagem do total de blocos contíguos livrespara alocação a cada linha do arquivo lido. 
Exemplo 1: Assuma uma memória de 16 posições, que emprega particionamento fixo de 4 posiçõesparacada partição. Assuma ainda o seguinte arquivo de descrição de requisições, e o respectivo detalhamento da ocupação da memória.
|Arquivo |Significado |
|-----|-------|
|| \| 16 \| |
IN(A, 3)|\| 13 \| |
IN(B, 2)| \| 1 \| 10 \| |
IN(C, 1)| \| 1 \| 2 \| 7 \| |
OUT(B)| \|5 \| 7 \| |
IN(D, 4)| \| 1 \| 7 \| |
OUT(A)| \| 4 \| 7 \| |
OUT(C)| \| 4 \| 8 \| |
OUT(D)| \| 16 \| |

Exemplo 2:Assuma  uma  memória  de  16  posições,  que  emprega  particionamento variávelcom  a política de alocação first-fit. Assuma ainda o seguinte arquivo de descrição de requisições, e o respectivo detalhamento da ocupação da memória.
|Arquivo |Significado |
|-----|-------|
|| \| 16 \| |
|IN(A, 3)|\| 13 \||
|IN(B, 2)| \| 11 \||
|IN(C, 1)|\| 10 \||
|OUT(A)|\| 3 \| 10 \||
|IN(D, 4)|\| 3 \| 6 \||
|OUT(C)|\| 3 \| 1 \| 6 \||
|OUT(B)|\| 6 \| 6 \||
|OUT(D)|\| 16 \||


