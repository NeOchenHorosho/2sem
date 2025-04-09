extern "C" void _cdecl InsertSort(int* p, int n);
extern "C" void _cdecl SelectSort(int* p, int n);


#include <iostream>

using namespace std;

int main()
{
	int n;
	cout << "Enter number of elements\n";
	cin >> n;
	cout << "Enter elements\n";
	int* p = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
	}
	int sort_n;
	cout << "1)Insert sort\n2)Select Sort\nWhich sort you wanna use?\n";
	cin >> sort_n;
	switch (sort_n)
	{
	case 1:
		InsertSort(p, n);
		break;
	case 2:
        SelectSort(p, n);
        break;
    case 3:
        
	default:
		cout << "Invalid sort \n";
		return 0;
	}
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << p[i] << "\t";
	}
	return 0;
}