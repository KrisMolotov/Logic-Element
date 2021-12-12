#include "LogicElement.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
namespace Lab3
{
    LogicElement::LogicElement():SZ(QUOTA), count(2) // конструктор по умолчанию имеет 2 клеммы
    {
        try
        {
            arr = new Terminal[QUOTA];
        }
        catch (std::bad_alloc &ba)
        {
            throw ba;
        }
        arr[0].info = input;
        arr[0].connects = 0;
        arr[0].sig = 'X';
        arr[1].info = output;
        arr[1].connects = 0;
        arr[1].sig = 'X';
    }

    LogicElement::LogicElement(int in, int out):count(0)
    {
        if(in < 0 || out < 0)
        {
            throw std::invalid_argument("invalid input and output number");
        }
        count = in + out;
        SZ = count;
        try
        {
            arr = new Terminal[count];
        }
        catch (std::bad_alloc &ba)
        {
            throw ba;
        }
        for(int i = 0; i < in; ++i)
        {
            arr[i].info = input;
            arr[i].connects = 0;
            arr[i].sig = 'X';
        }
        for(int i = in; i < count; ++i)
        {
            arr[i].info = output;
            arr[i].connects = 0;
            arr[i].sig = 'X';
        }
    }

    LogicElement::LogicElement(const LogicElement& t):count(t.count), SZ(t.SZ), arr(new Terminal[t.count])
    {
        cout << "copy constructor" << endl;
        for (int i = 0; i < count; ++i)
        {
            arr[i] = t.arr[i];
        }
    }

    LogicElement::LogicElement(LogicElement && t) noexcept:count(t.count), SZ(t.SZ), arr(t.arr)
    {
        cout << "move constructor" << endl;
        t.arr = nullptr;
    }

    void LogicElement::correctMemory()
    {
        Terminal* tmp;
        try
        {
            tmp = new Terminal[count + QUOTA];
            SZ += QUOTA;
        }
        catch (std::bad_alloc &ba)
        {
            throw ba;
        }
        for (int i = 0; i < count; ++i)
        {
            tmp[i] = arr[i];
        }
        delete[] arr;
        arr = tmp;
    }

    void LogicElement::correctSig(char sg)
    {
        if(sg != '0' && sg != '1' && sg != 'X')
        {
            throw std::invalid_argument("invalid signal");
        }
    }

    void LogicElement::correctInfo(Type inf)
    {
        if(inf != input && inf != output)
        {
            throw std::invalid_argument("invalid info");
        }
    }

    void LogicElement::correctNumber(int num) const
    {
        if(num < 1 || num > count)
        {
            throw std::invalid_argument("invalid number");
        }
    }

    void LogicElement::correctConnectsInput(int num)
    {
        if(num > 1 || num < 0)
        {
            throw std::invalid_argument("invalid connections");
        }
    }

    void LogicElement::correctConnectsOutput(int num)
    {
        if(num > 3 || num < 0)
        {
            throw std::invalid_argument("invalid connections");
        }
    }

    LogicElement& LogicElement::connection(int num)
    {
        correctNumber(num);
        if(arr[num - 1].info == input && arr[num - 1].connects == 1)
        {
            throw std::invalid_argument("connects is overflow");
        }
        else if(arr[num - 1].info == output && arr[num - 1].connects == 3)
        {
            throw std::invalid_argument("connects overflow");
        }
        ++arr[num - 1].connects;
        return *this;
    }

    LogicElement& LogicElement::disconnection(int num)
    {
        correctNumber(num);
        if(arr[num - 1].connects < 1)
        {
            throw std::invalid_argument("Impossible to decrease the connections");
        }
        if(arr[num - 1].connects == 1)
        {
            arr[num - 1].sig = 'X';
        }
        --arr[num - 1].connects;
        return *this;
    }

    std::istream &operator >> (std::istream &s, LogicElement &t)
    {
        char a;
        for(int i = 0; i < t.count; ++i)
        {
            s >> a;
            if(s.good())
            {
                t(i+1, a);
            }
            else
            {
                s.setstate(std::ios::failbit);
                break;
            }
        }
        return s;
    }

    std::ostream &operator << (std::ostream &s, const LogicElement &t)
    {
        for(int i = 0; i < t.count; ++i)
        {
            if(t.arr[i].info == input)
            {
                s << "info: input " << "connections: " << t.arr[i].connects << " condition: " << t.arr[i].sig << endl;
            }
            else
            {
                s << "info: output " << "connections: " << t.arr[i].connects << " condition: " << t.arr[i].sig << endl;
            }
        }
        return s;
    }

    LogicElement &LogicElement::operator += (const Terminal &t)
    {
        if(count == SZ)
        {
            correctMemory();
        }
        correctSig(t.sig);
        correctInfo(t.info);
        if(t.info == input)
        {
            correctConnectsInput(t.connects);
        }
        else
        {
            correctConnectsOutput(t.connects);
        }
        arr[count] = t;
        ++count;
        return *this;
    }

    LogicElement &LogicElement::operator()(int num, char sg)
    {
        correctNumber(num);
        correctSig(sg);
        arr[num - 1].sig = sg;
        return *this;
    }

    bool LogicElement::operator == (const LogicElement &t) const
    {
        int n = 0;
        if(count != t.count)
        {
            return false;
        }
        for (int i = 0; i < count; ++i)
        {
            if(arr[i].info == t.arr[i].info && arr[i].connects == t.arr[i].connects && arr[i].sig == t.arr[i].sig)
            {
                ++n;
            }
        }
        if(n == count)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    LogicElement &LogicElement::operator++()
    {
        for (int i = 0; i < count; ++i)
        {
            arr[i].info = input;
        }
        return *this;
    }

    LogicElement &LogicElement::operator--()
    {
        for (int i = 0; i < count; ++i)
        {
            arr[i].info = output;
        }
        return *this;
    }

    bool LogicElement::operator!() const
    {
        for (int i = 0; i < count; ++i)
        {
            if(arr[i].connects == 0 && arr[i].sig == 'X')
            {

                return true;
            }
        }
        return false;
    }

    int LogicElement::GetInfo(int num) const
    {
        if(num < 1 || num > count)
        {
            throw std::invalid_argument("Invalid argument");
        }
        if(arr[num-1].info == input)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int LogicElement::GetConnects(int num) const
    {
        if(num < 1 || num > count)
        {
            throw std::invalid_argument("Invalid argument");
        }
        return arr[num-1].connects;
    }

    const LogicElement LogicElement::operator ++ (int)
    {
        LogicElement dop(*this);
        for (int i = 0; i < count; ++i)
        {
            arr[i].info = input;
        }
        return dop;
    }

    LogicElement &LogicElement::operator = (LogicElement &&t) noexcept
    {
        cout << "move assignment" << endl;
        int tmp = count;
        count = t.count;
        t.count = tmp;
        tmp = SZ;
        SZ = t.SZ;
        t.SZ = tmp;
        Terminal* ptr = arr;
        arr = t.arr;
        t.arr = ptr;
        return  *this;
    }

    LogicElement &LogicElement::operator = (const LogicElement &t)
    {
        cout << "copy assignment" << endl;
        if (this != &t)
        {
            delete[] arr;
            count = t.count;
            SZ = t.SZ;
            arr = new Terminal[count];
            for (int i = 0; i < count; i++)
            {
                arr[i] = t.arr[i];
            }
        }
        return *this;
    }

    int getInt (int &a)
    {
        cin >> a;
        if (!std::cin.good())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }
        if(a == 0 || a == 1)
        {
            return 1;
        }
        return 0;
    }

    LogicElement func(LogicElement p)
    {
        ++p;
        return p;
    }
}
