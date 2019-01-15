#include <vector>
#include <map>
#include <iostream>

int main() {
    using namespace std;
    vector<int> v = {3, 4, 6, 5, -1, 7};

    // for with iterators
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << endl;
    }
        {
            // Итераторы случайного доступа похожи на обычные указатели
            cout << endl;
            for (int* p = &v[0]; p != &v[v.size()]; ++p) {
                cout << *p << endl;
        }
    }
    cout << "---------------------------------------\n";

    // 4th element (-1)
    auto it = v.begin() + 4;
    cout << *it << endl;

    cout << "---------------------------------------\n";

    map<int, int> m;  // <key, val>
    m.emplace(make_pair(4, 5));
    m.emplace(make_pair(2, 15));
    m.emplace(make_pair(3, 255));
    cout << m[3] << endl;
    cout << "---------------------------------------\n";
    // *(m.begin() + 3) (или ещё как-нибудь) -- уже не работает,
    // т.к. внутренняя структура итератора другая
    auto tree_it = m.begin();
    cout << (*tree_it).first << ' ' << (*tree_it).second << endl;
    cout << "---------------------------------------\n";

    // После добавления элемента старый итератор продолжит указывать на соответствующее значение,
    // в то время как итератор, соотвествующий m.begin() может указывать на другой элемент
    // (конкретно здесь похоже min heap по ключам сторится)
    m.emplace(make_pair(0, 1));
    tree_it = m.begin();
    cout << (*tree_it).first << ' ' << (*tree_it).second << endl;
    cout << "---------------------------------------\n";

    m.erase(0);
    for (auto kvp : m) {
        cout << kvp.first << ' ' << kvp.second << endl;
    }
    cout << "---------------------------------------\n";

    // Итератор всё ещё укажет на старый элемент, хоть его уже нет в map'е
    // "Инвалидация итератора"
    cout << (*tree_it).first << ' ' << (*tree_it).second << endl;

}
