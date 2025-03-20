#include <iostream>
using namespace std;

int main() {
    int a, b, c, x, y, z;
    cin >> a >> b >> c >> x >> y >> z;
    bool fits = false;

    asm (
        ".intel_syntax noprefix\n\t"
        "mov eax, %[a]\n\t"
        "mov ebx, %[b]\n\t"
        "mov ecx, %[c]\n\t"

        // Сортируем коробку (a, b, c)
        "cmp eax, ebx\n\t"
        "jle 1f\n\t"
        "xchg eax, ebx\n\t"
        "1:\n\t"
        "cmp ebx, ecx\n\t"
        "jle 2f\n\t"
        "xchg ebx, ecx\n\t"
        "2:\n\t"
        "cmp eax, ebx\n\t"
        "jle 3f\n\t"
        "xchg eax, ebx\n\t"
        "3:\n\t"

        // Сохраняем отсортированные размеры коробки
        "mov edx, %[x]\n\t"
        "mov esi, %[y]\n\t"
        "mov edi, %[z]\n\t"

        // Сортируем посылку (x, y, z)
        "cmp edx, esi\n\t"
        "jle 4f\n\t"
        "xchg edx, esi\n\t"
        "4:\n\t"
        "cmp esi, edi\n\t"
        "jle 5f\n\t"
        "xchg esi, edi\n\t"
        "5:\n\t"
        "cmp edx, esi\n\t"
        "jle 6f\n\t"
        "xchg edx, esi\n\t"
        "6:\n\t"

        // Проверяем, помещается ли коробка
        "cmp eax, edx\n\t"
        "jg 7f\n\t"
        "cmp ebx, esi\n\t"
        "jg 7f\n\t"
        "cmp ecx, edi\n\t"
        "jg 7f\n\t"
        "mov eax, 1\n\t"
        "jmp 8f\n\t"
        "7:\n\t"
        "xor eax, eax\n\t"
        "8:\n\t"
        "mov %[fits], al\n\t"
        ".att_syntax prefix"
        : [fits] "=r" (fits)
        : [a] "r" (a), [b] "r" (b), [c] "r" (c), [x] "r" (x), [y] "r" (y), [z] "r" (z)
        : "eax", "ebx", "ecx", "edx", "esi", "edi", "cc"
    );

    cout << (fits ? "Yes" : "No") << endl;
    return 0;
}