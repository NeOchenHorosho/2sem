#include <iostream>
using namespace std;
//13.4
int main() {
    int x, m, y, n, k, p, r;
    cin >> x >> m >> y >> n >> k >> p >> r;  
    int res;
    int totalCost = 0;   
    int totalMoney = 0;  

    asm(".intel_syntax noprefix;"
        // Расчёт общей стоимости (x*m + y*n + k)
        "mov eax, %[x]\n\t"          
        "imul eax, %[m]\n\t"         
        "mov ebx, %[y]\n\t"          
        "imul ebx, %[n]\n\t"         
        "add eax, ebx\n\t"           
        "add eax, %[k]\n\t"          
        "mov edx, eax\n\t"       

        // Расчёт имеющихся денег (p*1000 + r*500)
        "mov eax, %[p]\n\t"          
        "imul eax, 1000\n\t"         
        "mov ebx, %[r]\n\t"          
        "imul ebx, 500\n\t"          
        "add eax, ebx\n\t"           
        "cmp eax, edx\n\t"
        "mov %[res], 0\n\t"
        "jl haha\n\t"
        "mov %[res], 1\n\t"
        "haha:\n\t"
        ".att_syntax prefix;"
        :
        [res]"=r"(res)
        :
        [x]"r"(x),
        [m]"r"(m),
        [y]"r"(y),
        [n]"r"(n),
        [k]"r"(k),
        [p]"r"(p),
        [r]"r"(r)
        : "eax", "ebx", "edx"
    );
    cout << '\n' << (res ? "priamougolni" : "ne priamougolni");
    return 0;
}