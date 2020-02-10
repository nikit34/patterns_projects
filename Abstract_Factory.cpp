#include <iostream>
#include <string>

using namespace std;


class AbstractProduct_A {
    public:
    virtual ~AbstractProduct_A();
    virtual string UsefulFunc_A() const = 0;
};

class ConcreteProduct_A_1: public AbstractProduct_A {
    public:
    string UsefulFunc_A() const override {
        return "The result of product A_1";
    }
};

class ConcreteProduct_A_2: public AbstractProduct_A {
    string UsefulFunc_A() const override {
        return "The result of product A_2";
    }
};

class AbstractProduct_B {
    public:
    virtual ~AbstractProduct_B();
    virtual string UsefulFunc_B() const = 0;
    virtual string AnotherUsefulFunc_B(const AbstractProduct_A &collaborator) const = 0;
};

class ConcreteProduct_B_1: public AbstractProduct_B {
    public:
    string UsefulFunc_B() const override {
        return "The result of product B_1";
    }
    string AnotherUsefulFunc_B(const AbstractProduct_A &collaborator) const override {
        const string res = collaborator.UsefulFunc_A();
        return "The result of B_1 collaborating with " + res;
    }
};

class ConcreteProduct_B_2: public AbstractProduct_B {
    public:
    string UsefulFunc_B() const override {
        return "The result of product B_2";
    }
    string AnotherUsefulFunc_B(const AbstractProduct_A &collaborator) const override {
        const string res = collaborator.UsefulFunc_A();
        return "The result of B_2 collaborating with " + res;
    }
};

class AbstractFactory {
    public:
    virtual AbstractProduct_A *CreateProduct_A() const = 0;
    virtual AbstractProduct_B *CreateProduct_B() const = 0;
};

class ConcreteFactory_1: public AbstractFactory {
    public:
    AbstractProduct_A *CreateProduct_A() const override {
        return new ConcreteProduct_A_1();
    }
    AbstractProduct_B *CreateProduct_B() const override {
        return new ConcreteProduct_B_1();
    }
};

class ConcreteFactory_2: public AbstractFactory {
    public:
    AbstractProduct_A *CreateProduct_A() const override {
        return new ConcreteProduct_A_2();
    }
    AbstractProduct_B *CreateProduct_B() const override {
        return new ConcreteProduct_B_2();
    }
};

void ClientCode(const AbstractFactory &factory) {
    const AbstractProduct_A *product_a = factory.CreateProduct_A();
    const AbstractProduct_B *product_b = factory.CreateProduct_B();
    cout << product_b->UsefulFunc_B() << endl;
    cout << product_b->AnotherUsefulFunc_B(*product_a) << endl;
    delete product_a;
    delete product_b;
}

int main(){
    cout << "Client code with first factory type:" << endl;
    ConcreteFactory_1 *f1 = new ConcreteFactory_1();
    ClientCode(*f1);
    delete f1;
    cout << endl;
    cout << "Client code with second factory type:" << endl;
    ConcreteFactory_2 *f2 = new ConcreteFactory_2();
    ClientCode(*f2);
    delete f2;
    return 0;
}