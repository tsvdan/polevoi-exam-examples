#include <iostream>

// Полевой ругается минимум на 5 мест здесь, и по делу так
// Учите его требования, исправляйте, смотрите чужие репы

template <typename T>
class PriorityQueue {
public:
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T front() const = 0;
    virtual void insert(const T&, int) = 0;
    virtual T pop_front() = 0;
};


template <typename T>
class PQList : public PriorityQueue<T> {
public:
    PQList() {}
    ~PQList() {
        Node* tmp{nullptr};
        while (!empty()) {
            tmp = head;
            head = tmp->next;
            delete tmp;
        }
        head = nullptr;  // test passes with line commented
    }
    /* -- other constructors -- */

    void insert(const T& data, int priority = 0) {
        Node* node = new Node(data, priority);
        ++size_;

        if (empty() || (head->priority < priority)) {
            node->next = head;
            head = node;
        } else {
            Node* current_node = head;
            while (current_node->next
            && (priority < current_node->next->priority)) {
                current_node = current_node->next;
            }
            node->next = current_node->next;
            current_node->next = node;
        }
    }

    bool empty() const override {
        return !head;
    }  // implicit conversion of ptr_t to bool

    int size() const override {
        return size_;
    }

    T front() const override {
        return head->data;
    }

    T pop_front() {
        if (empty()) {
            std::cerr << "\nCan't pop: Queue empty\n";
            throw("empty");
        }
        Node* tmp = head;
        T ret_data = head->data;

        head = head->next;
        --size_;
        delete tmp;
        return ret_data;
    }

    friend std::ostream& operator<<(std::ostream& os, const PQList<T>& pq) {
        Node* tmp = pq.head;
        os << "Data \t\t\tPriority\n";  // KPACUBO (net)
        while (tmp) {
            os << tmp->data << '\t' << tmp->priority << '\n';
            tmp = tmp->next;
        }
        return os;
    }

private:
    struct Node {
        Node(const T& t_data, int t_priority)
        : data(t_data)
        , priority(t_priority)
        {}

        ~Node() = default;
        T data;
        Node* next{nullptr};
        int priority{0};
    };
    Node* head{nullptr};
    int size_{0};
};


int main() {
    #include <string>
    using namespace std;

    PQList<string> pq;
    pq.insert("bass               ", 56);
    pq.insert("repeat             "    );
    pq.insert("eat                ",  3);
    pq.insert("sleep              ",  1);

    auto test_destruction = []() {
        PQList<string>* outer_pointer;
        {
            PQList<string> pq;
            pq.insert("bass               ", 56);
            pq.insert("repeat             "    );
            pq.insert("eat                ",  3);
            pq.insert("sleep              ",  1);
            outer_pointer = &pq;
            cout << pq << endl;
        }
        cout << *outer_pointer << endl;
    };
    
    test_destruction();
    /*

    cout << pq << "\n\n";
    cout << pq.empty() << ", should be 0" << endl;
    cout << pq.size()  << ", should be 4" << endl;

    cout << pq.front() << "\n\n";
    pq.insert("boundary conditions",   2);
    pq.insert("boundary conditions", 900);
    pq.insert("boundary conditions",  -1);
    cout << pq << endl;

    {
        int s = pq.size();
        for (int i = 0; i < s; ++i) {
            cout << pq.pop_front() << endl;
        }
    }

    cout << pq.empty() << ", should be 1 (yes, empty)" << endl;
    cout << pq.size()  << ", should be 0"              << endl;
    // cout << pq.front() << endl;  // segfault
    pq.pop_front();  // err dump
    */
}
