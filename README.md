Trabalho Final – Disciplina de Algoritmos e Linguagem C
Sistema de Gerenciamento de Contatos
Objetivo
Desenvolver um sistema de gerenciamento de contatos utilizando a linguagem C, aplicando os conceitos estudados ao longo da disciplina, especialmente estruturas de dados, vetores, funções, manipulação de arquivos e construção de menus interativos.

Descrição do Trabalho
O sistema deverá permitir o cadastro e gerenciamento de contatos pessoais por meio de um menu de opções apresentado ao usuário.

Os dados deverão ser armazenados em um vetor com capacidade máxima para 100 contatos.

Cada contato deverá possuir, no mínimo, os seguintes campos:

Nome do contato;

E-mail;

Telefone;

Tipo do contato (ex.: Pessoal, Trabalho, Família, Cliente, Outro).

Funcionalidades Obrigatórias
O programa deverá apresentar um menu contendo as seguintes opções:

1. Cadastrar contato
Permitir a inclusão de um novo contato no vetor, desde que ainda exista espaço disponível.

2. Alterar contato
Permitir a localização de um contato já cadastrado e a alteração de suas informações.

3. Apagar contato
Permitir a remoção de um contato do sistema.

4. Procurar contato
Permitir a busca de contatos pelo nome e exibir suas informações.

5. Listar contatos
Exibir todos os contatos atualmente cadastrados.

6. Sair
Encerrar o programa.

Persistência dos Dados
O sistema deverá utilizar um arquivo para armazenar permanentemente os contatos.

Ao iniciar o programa:

O arquivo deverá ser carregado automaticamente;

Os contatos existentes deverão ser transferidos para o vetor em memória.

Ao encerrar o programa:

Todos os contatos deverão ser gravados novamente no arquivo.

Requisitos Técnicos
O trabalho deverá obrigatoriamente utilizar:

Linguagem C; (DEV C++)

Vetor de registros (struct) com capacidade para até 100 contatos;

Funções para cada funcionalidade do sistema;

Manipulação de arquivos para leitura e gravação dos dados;

Estruturas de repetição;

Estruturas de decisão;

Modularização adequada do código.

Requisitos Adicionais
O programa deve tratar situações de erro, como tentativa de cadastrar além da capacidade máxima ou procurar contatos inexistentes.

As mensagens exibidas ao usuário devem ser claras e organizadas.

O código deve estar devidamente indentado e comentado.

Entrega
A entrega deverá conter:

Código-fonte completo (.c);
