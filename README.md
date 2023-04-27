# CC0021_progconcorrente

## OpenMP Tasks

### Introdução

O OpenMP (Open Multi-Processing) é uma API de programação paralela que permite a criação de programas que podem ser executados em paralelo em múltiplos núcleos de processamento. O OpenMP Tasks é uma funcionalidade do OpenMP que permite a execução de tarefas independentes em paralelo.

### Como utilizar

Para utilizar o OpenMP Tasks em um programa, é necessário incluir a diretiva #pragma omp task, seguida do código que será executado em paralelo. É importante notar que as tarefas devem ser independentes umas das outras, para que possam ser executadas em paralelo.

Exemplo:

```C

`#pragma omp parallel
{
    #pragma omp single
    {
        #pragma omp task
        {
            // Código da tarefa 1
        }
        #pragma omp task
        {
            // Código da tarefa 2
        }
    }
}
```

### Exemplos de utilização

As tarefas podem ser utilizadas em diversas aplicações, tais como:

-   Processamento de imagens: cada tarefa pode ser responsável por processar uma região da imagem, tornando o processo mais eficiente.
-   Computação científica: cálculos matemáticos podem ser executados em tarefas independentes.
-   Simulações: tarefas podem ser utilizadas para executar simulações independentes, acelerando o processo de obtenção de resultados.

### Diferença para as OpenMP Sections

As OpenMP Sections permitem que diferentes seções de código sejam executadas em paralelo. Já as OpenMP Tasks permitem que tarefas independentes sejam executadas em paralelo, sem a necessidade de dividir o código em seções.

### Quando utilizar?

O OpenMP Tasks é mais indicado para problemas em que é possível identificar tarefas independentes que podem ser executadas em paralelo. Problemas que envolvem operações em grandes conjuntos de dados, como processamento de imagens ou simulações, são bons candidatos para a utilização de tarefas paralelas. No entanto, é importante avaliar o custo-benefício da utilização de paralelismo, já que nem sempre a execução em paralelo é mais eficiente do que a execução serial.
