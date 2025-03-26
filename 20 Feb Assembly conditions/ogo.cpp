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
            "lea esi, %[A]\n"
            "lea edi, %[B]\n"
            "mov ecx, %[msize]\n"
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
            :[A]"x"(A), [B]"x"(B), [msize]"r"(msize)
            :"eax", "ebx", "esi", "ecx", "edi", "memory"
        );

        cout << "\n\n";
        for (int i = 0; i < msize; i++)
            cout << B[i] << '\t';
        return 0;
    }
