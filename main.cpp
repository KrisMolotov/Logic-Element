#include <iostream>
#include "../Lib/src/LogicElement.h"
using std::cin;
using std::cout;
using std::endl;
using namespace Lab3;
int main()
{
    LogicElement el1;
    int key1;
    int n;
    int a;
    char st;
    while (true)
    {
        cout << "Make your choice!" << endl;
        cout << "0. Quit" << endl;
        cout << "1. Enter the conditions of all terminals" << endl;
        cout << "2. Enter the condition of a terminal by its number" << endl;
        cout << "3. Get the condition of a terminal by its number" << endl;
        cout << "4. Get the condition of a const terminal by its number(Just checking,new object isn't used)" << endl;
        cout << "5. Get the information of a terminal by its number" << endl;
        cout << "6. Get the number of connects of a terminal by its number" << endl;
        cout << "7. Increase number of connects of a terminal by one" << endl;
        cout << "8. Decrease number of connects of a terminal by one" << endl;
        cout << "9. Add new terminal to a logic element" << endl;
        cout << "10. Print all information about logic element" << endl;
        cout << "11. Make all terminals input" << endl;
        cout << "12. Make all terminals input with returning of previous object(Just checking,new object isn't used)" << endl;
        cout << "13. Make all terminals output" << endl;
        cout << "14. Compare two logic elements" << endl;
        cout << "15. Find out if there are terminals in an undefined state" << endl;
        cout << "16. Test of move constructor" << endl;
        cout << "17.Test of copy assignment" << endl;
        cout << "18.Test of move assignment" << endl;
        if (!getNum(key1))
        {
            cout << "Enter the correct symbol!" << endl;
            continue;
        }
        if (key1 == 0)
        {
            break;
        }
        try
        {
            switch(key1)
            {
                case 1:
                {
                    cout << "Enter values of signal statements: 0, 1 or X" << endl;
                    cin >> el1;
                }
                break;
                case 2:
                {
                    cout << "Enter the number of a terminal" << endl;
                    while(!getNum(n))
                    {
                        cout << "Enter the correct symbol!" << std::endl;
                    }
                    cout << "Enter the value of signal statement: 0, 1 or X" << endl;
                    cin >> st;
                    el1(n, st);
                }
                break;
                case 3:
                {
                    std::cout << "Enter number of a terminal" << endl;
                    while(!getNum(n))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Condition is: " << el1[n] << endl;
                }
                break;
                case 4:
                {
                    const LogicElement dop(2, 3);
                    cout << "Condition is: " << dop[2] << endl;
                }
                break;
                case 5:
                {
                    std::cout << "Enter number of a terminal" << endl;
                    while(!getNum(n))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Information is: " << el1.GetInfo(n) << endl;
                }
                break;
                case 6:
                {
                    std::cout << "Enter number of a terminal" << endl;
                    while(!getNum(n))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout <<"Number of connections: " << el1.GetConnects(n) << endl;
                }
                break;
                case 7:
                {
                    std::cout << "Enter number of a terminal" << endl;
                    while(!getNum(n))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    el1.connection(n);
                }
                break;
                case 8:
                {
                    std::cout << "Enter number of a terminal" << endl;
                    while(!getNum(n))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    el1.disconnection(n);
                }
                break;
                case 9:
                {
                    Terminal t{};
                    cout << "Enter type of terminal: 0 for input, 1 for output" << endl;
                    while (!getInt(a))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    if(a == 0)
                    {
                        t.info = input;
                    }
                    else
                    {
                        t.info = output;
                    }
                    cout << "Enter number of connects: not above 1 for input clamp and not above 3 for output clamp" << endl;
                    while (!getNum(t.connects))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    if (t.connects != 0)
                    {
                        cout << "Enter signal condition: 0, 1 or X" << endl;
                        cin >> t.sig;
                    }
                    else
                        t.sig = 'X';
                    el1 += t;
                }
                break;
                case 10:
                {
                    cout << el1;
                }
                break;
                case 11:
                {
                    ++el1;
                }
                break;
                case 12:
                {
                    LogicElement el2;
                    el2 = el1++;
                    cout << "el1 now is: \n" << el1;
                    cout << "el2 now is: \n" << el2;
                }
                break;
                case 13:
                {
                    --el1;
                }
                break;
                case 14:
                {
                    int in, out;
                    cout << "Enter the number of input terminals" << endl;
                    while(!getNum(in))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    cout << "Enter the number of output terminals" << endl;
                    while(!getNum(out))
                    {
                        cout << "Enter the correct symbol!" << endl;
                    }
                    LogicElement el1x(in, out);
                    if(el1 == el1x)
                    {
                        cout << "Elements are equal!" << endl;
                    }
                    else
                    {
                        cout << "Elements are not equal!" << endl;
                    }
                }
                break;
                case 15:
                {
                    if(!el1)
                    {
                        cout << "There are undefined terminals!" << endl;
                    }
                    else
                    {
                        cout << "There are not undefined terminals!" << endl;
                    }
                }
                break;
                case 16:
                {
                    LogicElement y;
                    LogicElement x = func(y);
                }
                break;
                case 17:
                {
                    LogicElement y(2,3), x;
                    x = y;
                }
                break;
                case 18:
                {
                    LogicElement y;
                    LogicElement x;
                    x = func(y);
                }
                break;
                default:
                {
                    cout << "Please, enter correct operation code" << endl;
                }
                //break;
            }
        }
        catch(std::exception &ex)
        {
            cout << ex.what() << endl;
        }
    }
    return 0;
}
