#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <cstring>

using namespace std;
struct Unknown_symb
{
    const char symb;
    Unknown_symb(char _symb) : symb(_symb) {}
    void show_error()
    {
        cout << "Unknown symobl occured: " << symb << '\n';
    }
};
struct Zero_div
{
    const int a, b;
    Zero_div(int f, int s) : a(f), b(s) {}
    void show_error()
    {
        cout << "Zero division occured with these values: " << " " << a << " / " << b << '\n';
    }
};

class PolishNotaion
{
public:
    stack<int> numbers;
    stack<char> opers;
    string line;

public:
    PolishNotaion()
    {
        line = "";
    }
    bool contain(const char a, const char *b)
    {
        return strchr(b, a) != nullptr;
    }
    int priority(char a)
    {
        if (a == '*' || a == '/')
            return 2;
        if (a == '+' || a == '-')
            return 1;
        return 0;
    }
    int calculate(const char oper, int a, int b)
    {
        switch (oper)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
                throw Zero_div(a, b);
            return a / b;
            break;
        default:
            throw Unknown_symb(oper);
        }
    }
    void pop_count(const char op)
    {
        int a = numbers.top();
        numbers.pop();
        int b = numbers.top();
        numbers.pop();
        numbers.push(calculate(op, b, a));
    }
    void convert_to_polish()
    {
        string temp_line = "";
        for (int i = 0; i < line.size(); i++)
        {
            if (contain(line[i], "0123456789"))
            {
                temp_line += line[i];
            }
            else if (line[i] == '(')
            {
                opers.push('(');
            }
            else if (line[i] == ')')
            {
                while (!opers.empty() && opers.top() != '(')
                {
                    temp_line += opers.top();
                    opers.pop();
                }
                if (!opers.empty())
                    opers.pop();
            }
            else if (contain(line[i], "+-/*"))
            {
                while (!opers.empty() && priority(opers.top()) >= priority(line[i]))
                {
                    temp_line += opers.top();
                    opers.pop();
                }
                opers.push(line[i]);
            }
        }
        while (!opers.empty())
        {
            temp_line += opers.top();
            opers.pop();
        }
        line = temp_line;
    }
    int find_result()
    {
        for (int i = 0; i < line.size(); i++)
        {
            if (contain(line[i], "0123456789"))
            {
                numbers.push(line[i] - '0');
            }
            else
            {
                pop_count(line[i]);
            }
        }
        return numbers.top();
    }
    friend istream &operator>>(istream &in, PolishNotaion &X)
    {
        getline(in, X.line);
        return in;
    }
};
int main()
{
    ifstream inp("input.txt");
    PolishNotaion haha;
    inp >> haha;
    cout << haha.line << endl;
    haha.convert_to_polish();
    cout << haha.line << endl;
    try
    {
        cout << haha.find_result() << endl;
    }
    catch (Zero_div err)
    {
        err.show_error();
        return 0;
    }
    catch (Unknown_symb err)
    {
        err.show_error();
        return 0;
    }
    return 0;
}

// цифры выталкиваем
// открывающие свобки в стек
// закрывающие выталкивают всё, что между
// менее приоритетные операции выталкивают не менее приоритетные операции и попадают в стек
// когда закончилось выражение, а стек не пустой, выталкивается всё