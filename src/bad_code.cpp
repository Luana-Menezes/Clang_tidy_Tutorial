#include <iostream>
#include <vector>


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