#include <iostream>
using namespace std;

class Base {
public:
    void Hello() { cout << "Base::Hello" << endl; }
    void virtual Hey() { cout << "Base::Hey" << endl; }
};

class Derived : public Base {
public:
    // объявление вида 'void Hello(){...}' так же скрывает
    void Hello(int) { cout << "Derived::Hello (замещает Base::Hello)" << endl; }
    void Hey() override { cout << "Derived::Hey" << endl; }
};

int main() {
    Base b;
    Derived d;

    b.Hello();
    d.Hello(2);
    //d.Hello();  // ошибка компиляции

    b.Hey();
    d.Hey();

    b = d;       // повышающее преобразование безопасно (?)
    b.Hello();
    b.Hey();
}
