# CompiladorCMenos
Compilador para a linguagem C menos. A geração de código assembly e executável é específica para a arquitetura [RVSP](https://github.com/fpelogia/RVSP).


## Instruções
- Cole seu código em C- em "sample.c"
- Rode o script run.sh (ou os comandos dentro dele)

## Observações
- O compilador apenas gera código intermediário de 3 endereços, representado por quadruplas. Sendo assim, as demais etapas da fase de síntese ainda estão implementadas.
- O código da maior parte dos módulos do computador foi amplamente inspirado nas explicações e no código diponibilizado pelo livro [1].

## Referências
- [1] LOUDEN, K. C., SILVA F. S. C. __Compiladores - Princípios e Práticas__ - Editora Pioneira Thomson Learning, 2004
ISBN 8522104220, 9788522104222

