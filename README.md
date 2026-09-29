# 📊 Lista Encadeada Ordenada em C

Implementação acadêmica de uma **Lista Simplesmente Encadeada e Ordenada** desenvolvida em C para a disciplina de Estrutura de Dados. O projeto inclui controle por descritor, algoritmos de busca otimizados com parada antecipada, prevenção de duplicatas (Desafio B) e validação através de uma bateria de testes funcionais.

---

## 🛠️ Recursos e Funcionalidades

- **Controle por Descritor:** Gestão global da estrutura através do ponteiro inicial (`inicio`) e contagem dinâmica de elementos (`tamanho`).
- **Inserção Ordenada:** Garante a manutenção contínua do invariante de ordenação crescente na inclusão de novos nós.
- **Desafio B (Inserção Sem Duplicatas):** Validação de duplicidade no ponto exato de parada da busca com custo adicional $O(1)$ rejeitando chaves repetidas sem efetuar alocação desnecessária de memória.
- **Busca Otimizada:** Algoritmo com parada antecipada assim que um nó com chave maior que a buscada é encontrado.
- **Gestão Segura de Memória:** Liberação completa da memória RAM alocada via `free` com a função de destruição da lista.
- **Modo Interativo:** Interface via terminal (`main`) para testes do utilizador em tempo real.

---

## 📁 Estrutura do Repositório

```text
.
├── lista_ordenada.c          # Implementação base da lista encadeada ordenada
├── lista_ordenada_desafio.c  # Versão interativa com validação do Desafio B
├── lista_ordenada_testes.c   # Bateria com os 15 cenários de teste automatizados
└── .gitignore                 # Filtro para omissão de binários (.exe) e arquivos temporários
```

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos
- Compilador **GCC** instalado (`MinGW`, `w64devkit` ou equivalente em Windows/Linux).
- Terminal de comandos (PowerShell, Bash ou o terminal integrado do VS Code).

### Instruções Passo a Passo

1. **Clonar o repositório:**
   ```bash
   git clone [https://github.com/Stelariz/pratica_listas.git](https://github.com/Stelariz/pratica_listas.git)
   cd pratica_listas
   ```
2. **Compilar e executar o código do Desafio B (Modo Interativo):**
   ```bash
   gcc -Wall lista_ordenada_desafio.c -o lista_desafio
   ./lista_desafio
   ```
3. **Compilar e executar a Bateria de Testes:**
   ```bash
   gcc -Wall lista_ordenada_testes.c -o testes
   ./testes
   ```
4. **Compilar e executar a implementação base:**
   ```bash
   gcc -Wall lista_ordenada.c -o lista_base
   ./lista_base
   ```
## 📈 Análise de Complexidade

| Operação | Pior Caso | Melhor Caso | Justificativa / Análise |
| :--- | :---: | :---: | :--- |
| **Inserção Ordenada** | $O(n)$ | $O(1)$ | Percurso linear até encontrar o ponto de ordenação. O melhor caso ocorre ao inserir no início. |
| **Verificação de Duplicatas (Desafio B)** | $O(1)$ | $O(1)$ | Custo extra constante. Valida a chave no ponto exato de parada do `while` sem laços adicionais. |
| **Busca com Parada Antecipada** | $O(n)$ | $O(1)$ | Interrompe a busca assim que encontra um nó com chave maior que o valor procurado. |
| **Remoção** | $O(n)$ | $O(1)$ | Localiza o nó a ser removido e reencadeia os ponteiros do nó anterior. |
| **Destruição da Lista** | $O(n)$ | $O(n)$ | Percorre toda a estrutura liberando a memória RAM alocada nó a nó com `free`. |

---

## 🏫 Sobre o Projeto

Este projeto foi desenvolvido como parte das atividades práticas da disciplina de **Estrutura de Dados**, no curso de **Big Data para a Indústria** da **FATEC São Carlos**.
