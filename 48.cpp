#include <iostream>
using namespace std;

template <typename T>
class Base {
public:
    T data;
    Base(T val) { data = val; }
    Base() { data = 0; }
    static void Hello() { cout << "Base::Hello" << endl; }
};

template class Base<uint8_t>;  /* Явная инстанциация
    aka Explicit Instantiation
    Контролирует место в файле,
    где будет сгенерирован конкретный
    код конкретного класса (где известно, что T=uint8_t, например)
*/

// Чуть более сложный шаблонный класс для иллюстрации специализации
template <typename T, int I>
class Derived : public Base<T> {
public:
    using Base<T>::Hello;

    static void Greetings() {
        for (int i = 0; i < I; ++i){
            std::cout << i << ' ';
            Hello();
        }
    }
};

// Частично специализированный класс
template <typename T>
class Derived<T, 5> : public Base<T> {
    using Base<T>::Hello;

    static void Greetings() {
        for (int i = 5; i < 10; i++) {
            std::cout << i << ' ';
            Hello();
        }
    }
};

// Полностью специализированный класс
template <>
class Derived<int, 5> : public Base<int> {
public:
    using Base<int>::Hello;

    Derived(int val) { data = val; }

    void Greetings() {
        for (int i = 5; i < 10; i++) {
            std::cout << i * data << ' ';
            Hello();
        }
    }
};


int main() {
    Base<int> b(25);  /* (Неявная) инстанциация, 
    aka Implicit Instantiation. 
    Код для класса Base<int> хрен знает где, но он есть
*/

    Base<float>::Hello(); // Так же происходит и без создания экземпляров
    Derived<int, 4>::Greetings(); // То же, что и прошлое

    // Создание экземпляра полностью специализированного класса
    Derived<int, 5> fully_spec(2);
    fully_spec.Greetings();

    // Не допускается специализация после инстанциации соответствующего класса
    // (попробуйте расшифровать, что здесь написано, и подумать, почему так)
}
