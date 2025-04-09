extern "C" int _cdecl SumInt(int, int); 
#include <iostream>
using namespace std; 
int main() 
{ 
      int x, y; 
      cout << "Enter 2 number";
       cin >> x >> y;
       int S = SumInt(x, y);
      cout << S << endl; 
}