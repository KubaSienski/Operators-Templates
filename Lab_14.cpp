#include <iostream>
#include <string>

using namespace std;

class Integer {
    int i{ 0 };
public:
    Integer() { i = 0; }
    Integer(int i) { this->i = i; }

    void setInt(int i) { this->i = i; }
    int getInt() { return i; }

    bool operator==(const Integer& obj) const {
        if (this->i == obj.i)return true;
        return false;
    }

    friend ostream& operator<< (ostream& b, const Integer& p);
};

ostream& operator<< (ostream& out, const Integer& obj) {
    return out << obj.i;
}

template <class T>
class kontener {
private:
    struct lista {
        T var;
        lista* nast = NULL;
        lista* poprz = NULL;
    };

    lista* glowa = NULL;
    lista* tmp = NULL;

public:
    // delete first list elem
    void get() {
        if (glowa != NULL) {
            tmp = glowa;
            glowa = glowa->nast;
            glowa->poprz = NULL;
            delete tmp;
        }
    }

    // add list element
    void put(T nowy) {
        if (glowa == NULL) {
            glowa = new lista;
            glowa->var = nowy;
            glowa->nast = NULL;
            glowa->poprz = NULL;
        }
        else {
            tmp = glowa;
            while (tmp->nast != NULL) {
                tmp = tmp->nast;
            }
            tmp->nast = new lista;
            tmp->nast->poprz = tmp;
            tmp = tmp->nast;
            tmp->var = nowy;
            tmp->nast = NULL;

        }
    }

    // delete elems if they are the same next to each other
    void purge() {
        if (glowa != NULL) {
            tmp = glowa;
            while (tmp != NULL && tmp->nast != NULL) {
                while (tmp->var == tmp->nast->var) {
                    lista* tmp2 = tmp->nast;
                    if (tmp->nast->nast != NULL) {
                        tmp->nast = tmp->nast->nast;
                        tmp->nast->poprz = tmp;
                        delete tmp2;
                    }
                    else {
                        tmp->nast = NULL;
                        delete tmp2;
                        break;
                    }
                }
                tmp = tmp->nast;
            }
        }
    }

    // print list
    void show() {
        tmp = glowa;
        while (tmp != NULL) {
            cout << tmp->var << endl;
            tmp = tmp->nast;
        }
    }
};

int main()
{
    // testing
    kontener<string> obj;
    
    obj.put("a");
    obj.put("a");
    obj.put("c");
    obj.put("b");
    obj.put("b");
    
    cout << "Put:\n";
    obj.show();

    obj.purge();
    cout << "\nPurge:\n";
    obj.show();

    obj.get();
    cout << "\nGet:\n";
    obj.show();

    kontener<int> obj2;

    obj2.put(2);
    obj2.put(1);
    obj2.put(1);
    obj2.put(1);
    obj2.put(2);
    obj2.put(2);

    cout << "\nPut:\n";
    obj2.show();

    obj2.purge();
    cout << "\nPurge:\n";
    obj2.show();

    obj2.get();
    cout << "\nGet:\n";
    obj2.show();

    kontener<Integer> obj3;
    Integer a, b(2), c(3);

    obj3.put(a);
    obj3.put(a);
    obj3.put(c);
    obj3.put(b);
    obj3.put(c);
    obj3.put(c);

    cout << "\nPut:\n";
    obj3.show();

    obj3.purge();
    cout << "\nPurge:\n";
    obj3.show();

    obj3.get();
    cout << "\nGet:\n";
    obj3.show();
}