#include <iostream>

using namespace std;

int main()
{
    int msize;
    cin >> msize;
    int* A = new int[msize];
    int* B = new int[msize];

    for (int i = 0; i < msize; i++)
        cin >> A[i];

        asm(
            ".intel_syntax noprefix\n"
            "mov esi, %0\n"         // ESI <- A
            "mov edi, %1\n"         // EDI <- B
            "mov ecx, %2\n"         // ECX <- msizeэээээээээээээээээээ
            "mov ebx, [esi]\n"
            "mov [edi], ebx\n"
            "mov ebx, [esi + 4]\n"
            "mov [edi + 4], ebx\n"
            "sub ecx, 2\n"
            
        "for1:\n"
            "mov eax, [esi]\n"
            "add eax, [esi + 4]\n"
            "mov [edi + 8], eax\n"
            "add esi, 4\n"
            "add edi, 4\n"
            "loop for1\n"
            ".att_syntax prefix"
            :
            : "r"(A), "r"(B), "r"(msize)
            : "eax", "ebx", "ecx", "esi", "edi"
        );

    for (int i = 0; i < msize; i++)
        cout << B[i] << " ";

    return 0;
}