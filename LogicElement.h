#ifndef LAB3_LOGIC_ELEMENT_H
#define LAB3_LOGIC_ELEMENT_H
#include <iostream>
#include <limits>
using std::cin;
namespace Lab3
{
    enum Type{input, output}; // типы клеммы

    struct Terminal
    {
        Type info; // информация о типе клеммы
        int connects; // количество соединений
        // входная клемма может иметь не больше 1 соединения, а выходная клемма – не больше 3 соединений
        char sig; //состоянии сигнала - значение уровня 0, 1 или Х (неопределенное состояние).
    };

    class LogicElement
    {
    private:
        static const int QUOTA = 10; // размер квоты для выделения памяти
        int SZ; // максимальный размер массива клемм
        int count; // текущее количество клемм
        Terminal* arr; // массив описателей клемм
        static void correctInfo(Type inf) ; //вспомогательная функция для проверки корректности типа клеммы
        void correctNumber(int num) const;// вспомогательная функция для проверки вводимого номера клеммы
        static void correctConnectsInput(int num) ; // проверка количества соединений
        static void correctConnectsOutput(int num) ;// проверка количества соединений
        static void correctSig(char sg) ; // проверка состояния сигнала
        void correctMemory (); // проверка на нехватку памяти
    public:
        //конструкторы
        LogicElement(); //  пустой конструктор для инициализации экземпляров по умолчанию (“инвертор”);
        LogicElement(int in, int out); // ининциализирующий конструктор количеством входных и выходных клемм логического элемента;
        LogicElement(const LogicElement& t); // инициализирующий конструктор массивом клемм заданной длины, он же копирующий конструктор
        LogicElement(LogicElement&&) noexcept ; // перемещающий конструктор
        ~LogicElement() {delete[] arr;} // деструктор
        //сеттеры
        LogicElement& operator = (const LogicElement &t); //перегруженный оператор присваивания
        LogicElement& operator = (LogicElement &&) noexcept ; //перемещающий оператор присваивания
        LogicElement& connection(int num); // увеличение соединений
        LogicElement& disconnection(int num); // уменьшение соединений
        LogicElement& operator ++ (); // инверсия информации с out на in
        const LogicElement operator ++ (int); // инверсия информации с out на in с возвратом исходного значения
        LogicElement& operator -- (); // инверсия информации с in на out
        LogicElement& operator += (const Terminal &t); // добавить клемму
        LogicElement& operator () (int num, char sg); // ввод нового состояния клеммы по номеру
        // геттеры
        friend std::ostream& operator << (std::ostream &, const LogicElement &);//вывод логического элемента
        [[nodiscard]] int GetInfo(int num) const;
        [[nodiscard]] int GetConnects(int num) const;
        char operator [] (int num) const {correctNumber(num); return arr[num - 1].sig;}
        char &operator [] (int num) {correctNumber(num); return arr[num - 1].sig;} // текущее состояние клеммы с заданным номером
        //методы-операции
        friend std::istream& operator >> (std::istream &, LogicElement &);//ввод состояний сигналов всех клемм
        bool operator == (const LogicElement &t) const; // перегруженный бинарный оператор сравнения двух логических элементов
        bool operator ! () const; // перегруженный унарный оператор логического НЕ
    };

    template <class T>
    int getNum (T &a)
    {
        cin >> a;
        if (!std::cin.good())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 1;
    }
    int getInt (int &a);
    LogicElement func (LogicElement p);
}
#endif
