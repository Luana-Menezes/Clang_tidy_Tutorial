#include <iostream>
#include <memory>

// Exemplos de constantes para evitar "magic numbers"
constexpr int kInitialValue = 5;
constexpr int kExampleWidth = 10;
constexpr int kExampleX = 15;

// 1. Sem variável não usada
void noUnusedVariables() {
    std::cout << "Sem variável não usada" << std::endl;
}

// 2. Sem memory leak (usa smart pointer)
void noMemoryLeak() {
    auto ptr = std::make_unique<int>(kInitialValue);
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
    calculateArea(kExampleWidth);
    separateDeclarations();
    noDuplicateBranches(kExampleX);
    return 0;
}