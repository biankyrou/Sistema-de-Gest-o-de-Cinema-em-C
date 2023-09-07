# Sistema de Gestão de Cinema em C

Este projeto é um sistema de gestão de cinema desenvolvido em linguagem C, como parte de um exercício acadêmico. O sistema permite o cadastro, consulta, alteração e exclusão de informações sobre salas, filmes e sessões de cinema, com os dados persistidos em arquivos binários específicos.

## Funcionalidades

- **Cadastro e Gerenciamento de Salas:** O sistema permite cadastrar informações sobre salas de cinema, incluindo código, nome, capacidade, tipo de exibição e acessibilidade. Você pode listar, alterar e excluir salas individualmente ou em conjunto.

- **Cadastro e Gerenciamento de Filmes:** É possível cadastrar informações sobre filmes, como código, nome, ano de lançamento, diretor e atores. O sistema suporta o cadastro de vários atores para cada filme. Você pode listar, alterar e excluir filmes individualmente ou em conjunto.

- **Cadastro e Gerenciamento de Sessões:** As sessões de exibição de filmes são agendadas com informações como código da sala, código do filme, data, horário e preço do ingresso. Você pode listar, alterar e excluir sessões individualmente ou em conjunto.

- **Relatórios:** O sistema oferece a geração de relatórios com base em critérios específicos, incluindo:
  - Mostrar salas com um tipo de exibição específico e capacidade mínima.
  - Mostrar filmes lançados a partir de um ano específico.
  - Mostrar sessões exibidas entre duas datas específicas.


## Habilidades Desenvolvidas

- **Alocação Dinâmica de Memória:** utilizei alocação dinâmica de memória ao lidar com vetores e structs. Nesse sentido, utilizei malloc, realloc e free no trabalho.

- **Conhecimento em Ponteiros:** em decorrência da primeira habilidade, aprofundei meu conhecimento em ponteiros, que são fundamentais para manipular e acessar dados em memória de forma direta e eficaz.

- **Manipulação de Arquivos em C:** implementei a leitura e gravação de dados em arquivos binários para persistir informações sobre salas, filmes e sessões.

- **Implementação de Menus Interativos:** criei menus e submenus interativos que permitem ao usuário realizar diversas operações de gerenciamento de dados de forma intuitiva.

- **Parâmetros em Funções:** Aprendi a passar parâmetros para funções, permitindo a transferência de valores e informações entre partes diferentes do programa de forma organizada e eficiente.


