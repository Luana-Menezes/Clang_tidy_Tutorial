# Tutorial Clang-Tidy

## 📋 Sobre o Clang-Tidy

**Clang-Tidy** é uma ferramenta de análise estática de código para C/C++ que:
- 🔍 Detecta bugs, code smells e problemas de performance
- 💡 Sugere melhorias seguindo boas práticas modernas de C++
- 🔧 Aplica correções automaticamente quando possível
- ✅ Verifica conformidade com padrões como C++ Core Guidelines

**Categoria**: Analisador Estático de Código

---


## 📝 Como testar este tutorial

Para acompanhar e testar os exemplos, faça o clone deste repositório:

```bash
git clone https://github.com/Luana-Menezes/Clang_tidy_Tutorial.git
cd Clang_tidy_Tutorial
```

---

## 🚀 Passo 1: Instalação

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install clang-tidy
```

### Verificar instalação
```bash
clang-tidy --version
```

---

## 📁 Passo 2: Estrutura do Projeto

Crie a seguinte estrutura simples:

```
clang-tidy-tutorial/
├── .github/
│   └── workflows/
│       └── clang-tidy-ci.yml  # CI/CD workflow
├── src/
│   ├── bad_code.cpp       # Código com problemas
│   └── good_code.cpp      # Código corrigido
├── .clang-tidy            # Configuração
└── README.md
```

---

## 🔧 Passo 3: Configuração

### Criar arquivo `.clang-tidy` na raiz do projeto

Este arquivo define quais regras o Clang-Tidy vai verificar (exemplo real):

```yaml
Checks: 
  - modernize-use-auto
  - readability-identifier-naming
  - performance-for-range-copy
  - cppcoreguidelines-avoid-magic-numbers
  - clang-analyzer-deadcode.DeadStores
  - clang-analyzer-cplusplus.NewDeleteLeaks
  - hicpp-special-member-functions
  - readability-function-size
  - readability-isolate-declaration
  - bugprone-branch-clone
  - bugprone-implicit-widening-conversion

WarningsAsErrors: 
  - modernize-use-auto
  - readability-identifier-naming
  - performance-for-range-copy
  - cppcoreguidelines-avoid-magic-numbers
  - clang-analyzer-deadcode.DeadStores
  - clang-analyzer-cplusplus.NewDeleteLeaks
  - hicpp-special-member-functions
  - readability-function-size
  - readability-isolate-declaration
  - bugprone-branch-clone
  - bugprone-implicit-widening-conversion

FormatStyle: 
  BasedOnStyle: Google
  IndentWidth: 4
  UseTab: Never
  AllowShortBlocksOnASingleLine: true
  AllowShortCaseLabelsOnASingleLine: true
  AllowShortFunctionsOnASingleLine: InlineOnly
  BreakBeforeBraces: Attach
  ColumnLimit: 0
```

**O que essas regras fazem:**
- `modernize-use-auto`: Sugere uso de `auto` para dedução de tipo.
- `readability-identifier-naming`: Garante nomes consistentes para variáveis, funções e classes.
- `performance-for-range-copy`: Detecta cópias desnecessárias em loops.
- `cppcoreguidelines-avoid-magic-numbers`: Evita números mágicos no código.
- `clang-analyzer-deadcode.DeadStores`: Detecta variáveis declaradas mas não usadas.
- `clang-analyzer-cplusplus.NewDeleteLeaks`: Detecta memory leaks.
- `readability-isolate-declaration`: Evita múltiplas declarações na mesma linha.
- `bugprone-branch-clone`: Detecta branches idênticas em if/else.
- Outras regras: checam tamanho de funções, conversões implícitas perigosas, e boas práticas modernas.

---

## 💻 Passo 4: Exemplos de Código


### 4.1 Criar `src/bad_code.cpp` (Código com problemas)

```cpp
#include <iostream>

// 1. Variável não usada
void unusedVariableExample() {
  int unusedVar = 42; // Nunca usada
  std::cout << "Exemplo de variável não usada" << std::endl;
}

// 2. Memory leak
void memoryLeakExample() {
  int* ptr = new int(5); // Alocação sem delete
  std::cout << "Memory leak: " << *ptr << std::endl;
  // delete ptr; // Esquecido de propósito
}

// 3. Magic number
int calculateArea(int width) {
  return width * 42; // 42 é um número mágico
}

// 4. Múltiplas declarações em uma linha
void multipleDeclarations() {
  int a, b, c; // Dificulta leitura
  a = b = c = 0;
  std::cout << a << b << c << std::endl;
}

// 5. Branches idênticas
void duplicateBranches(int x) {
  if (x > 10) {
    std::cout << "Big number" << std::endl;
  } else {
    std::cout << "Big number" << std::endl; // Código duplicado
  }
}

int main() {
  unusedVariableExample();
  memoryLeakExample();
  calculateArea(10);
  multipleDeclarations();
  duplicateBranches(15);
  return 0;
}
```


### 4.2 Criar `src/good_code.cpp` (Código corrigido)

```cpp
#include <iostream>
#include <memory>

// 1. Sem variável não usada
void noUnusedVariables() {
  std::cout << "Sem variável não usada" << std::endl;
}

// 2. Sem memory leak (usa smart pointer)
void noMemoryLeak() {
  auto ptr = std::make_unique<int>(5);
  std::cout << "Sem memory leak: " << *ptr << std::endl;
}

// 3. Constante nomeada ao invés de magic number
constexpr int kDefaultMultiplier = 42;
int calculateArea(int width) {
  return width * kDefaultMultiplier;
}

// 4. Declarações separadas
void separateDeclarations() {
  int a = 0;
  int b = 0;
  int c = 0;
  std::cout << a << b << c << std::endl;
}

// 5. Sem branches duplicadas
void noDuplicateBranches(int x) {
  std::cout << "Big number" << std::endl;
}

int main() {
  noUnusedVariables();
  noMemoryLeak();
  calculateArea(10);
  separateDeclarations();
  noDuplicateBranches(15);
  return 0;
}
```

---


## 🖥️ Passo 5: Usando o Clang-Tidy no Terminal

### Executar análise (forma simples):

```bash
# Executar clang-tidy no código ruim
clang-tidy src/bad_code.cpp -- -std=c++17

# Comparar com o código bom
clang-tidy src/good_code.cpp -- -std=c++17
```

**Explicação dos parâmetros:**
- `src/bad_code.cpp` = arquivo a ser analisado
- `--` = separador entre opções do clang-tidy e do compilador
- `-std=c++17` = padrão C++ a usar

**Saída esperada:**
O Clang-Tidy mostrará warnings como:
- `warning: unused variable 'unusedVar' [clang-analyzer-deadcode.DeadStores]`
- `warning: memory allocated by 'new' should be deleted [clang-analyzer-cplusplus.NewDeleteLeaks]`
- `warning: magic number used [cppcoreguidelines-avoid-magic-numbers]`
- `warning: multiple declarations in a single statement [readability-isolate-declaration]`
- `warning: identical branches in if/else [bugprone-branch-clone]`

---

## 🧩 Passo 6: Usando o Clang-Tidy pela Extensão no VS Code

Você pode usar o Clang-Tidy diretamente no VS Code para análise automática enquanto edita o código:

### 1. Instalar a extensão

- Abra o VS Code e vá em **Extensões** (Ctrl+Shift+X)
- Busque por **Clang-Tidy**
- Clique em **Instalar**

### 2. Configurar a extensão

- Certifique-se de que o arquivo `.clang-tidy` está na raiz do projeto (como mostrado acima)
- A extensão detecta automaticamente o arquivo de configuração
- Você pode ajustar configurações da extensão em: `File > Preferences > Settings` e buscar por "clang-tidy"

### 3. Usar no código

- Abra um arquivo `.cpp` no VS Code
- Os problemas detectados pelo Clang-Tidy aparecerão em tempo real como avisos e sugestões (sublinhados amarelos/vermelhos)
- Passe o mouse sobre o aviso para ver a explicação e sugestões de correção
- Algumas extensões permitem aplicar correções automáticas pelo menu de contexto (botão direito > Quick Fix)

**Vantagens:**
- Feedback instantâneo enquanto digita
- Integração com o sistema de problemas do VS Code
- Correções rápidas e navegação facilitada

---

## 🛠️ Passo 7: Integração CI/CD (GitHub Actions)

### Criar `.github/workflows/clang-tidy-ci.yml`

```yaml
name: Clang-Tidy CI

on:
  pull_request:
    branches:
      - main

jobs:
  clang-tidy:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout code
        uses: actions/checkout@v3

      - name: Install Clang-Tidy
        run: |
          sudo apt-get update
          sudo apt-get install -y clang-tidy

      - name: Run Clang-Tidy on all C++ files
        run: |
          clang-tidy src/*.cpp -- -std=c++17
```

**Como funciona:**
- Executa automaticamente em **pull requests** para a branch `main`
- Instala o Clang-Tidy no runner Ubuntu
- Executa análise em todos os arquivos `.cpp`
- Se houver problemas, o CI falhará e mostrará os warnings

## ✅ Pontos Positivos

- ✅ Detecção automática de problemas de código
- ✅ Correções automáticas disponíveis (`--fix`)
- ✅ Altamente configurável via `.clang-tidy`
- ✅ Integração fácil com IDEs e CI/CD
- ✅ Gratuito e open-source
- ✅ Suporta múltiplos padrões (C++ Core Guidelines, Google Style, etc)
- ✅ Não requer compilação do código para análise básica

## ❌ Pontos Negativos

- ❌ Pode gerar muitos avisos inicialmente (pode ser intimidante)
- ❌ Algumas correções automáticas podem precisar de revisão manual
- ❌ Configuração de regras pode ser complexa
- ❌ Tempo de análise pode ser longo em projetos grandes
- ❌ Falsos positivos ocasionais

## 📝 Nível de Dificuldade

**Básico a Intermediário**: 
- **Uso básico**: Fácil (apenas instalar e rodar)
- **Configuração avançada**: Intermediário (requer entender as regras)
- **Pré-requisitos**: Conhecimento básico de C++

## 🎯 Conclusão

Clang-Tidy é uma ferramenta essencial para manter qualidade de código em projetos C/C++. Com configuração simples via `.clang-tidy` e integração em VS Code e CI/CD, você pode garantir que seu código siga boas práticas automaticamente.

---

## 🔗 Recursos Adicionais

- [Documentação Oficial](https://clang.llvm.org/extra/clang-tidy/)
- [Lista de Checks](https://clang.llvm.org/extra/clang-tidy/checks/list.html)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)


---