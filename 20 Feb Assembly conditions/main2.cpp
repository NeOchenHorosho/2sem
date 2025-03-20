#include <iostream>
using namespace std;
//13.14
int main() {
    int a, b, c;
    cin >> a >> b >> c;
    bool result;
    asm(
        ".intel_syntax noprefix\n"
        // Проверка положительности чисел
        "cmp %[a], 0\n"
        "jle not_triangle\n"
        "cmp %[b], 0\n"
        "jle not_triangle\n"
        "cmp %[c], 0\n"
        "jle not_triangle\n"
        
        // Вычисление квадратов
        "mov eax, %[a]\n"
        "imul eax, eax\n"    
        "mov ebx, %[b]\n"
        "imul ebx, ebx\n"    
        "mov ecx, %[c]\n"
        "imul ecx, ecx\n"    
        
        // проверка на прямоугольность
        "mov edx, eax\n"
        "add edx, ebx\n"
        "cmp edx, ecx\n"
        "je is_triangle\n"
        
        
        "mov edx, eax\n"
        "add edx, ecx\n"
        "cmp edx, ebx\n"
        "je is_triangle\n"
    
        "mov edx, ebx\n"
        "add edx, ecx\n"
        "cmp edx, eax\n"
        "je is_triangle\n"
        
        // Не прямоугольный треугольник
        "not_triangle:\n"
        "mov %[result], 0\n"
        "jmp end\n"
        
        // Прямоугольный треугольник
        "is_triangle:\n"
        "mov %[result], 1\n"
        
        "end:\n"
        ".att_syntax prefix\n"
        : [result] "=r" (result)
        : [a] "r" (a), [b] "r" (b), [c] "r" (c)
        : "eax", "edx", "ebx", "ecx", "cc"
    );
    cout << '\n' <<(result ? "priamougolni" : "ne priamougolni") << endl;
    return 0;
}