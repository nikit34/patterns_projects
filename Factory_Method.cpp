#include <iostream>
#include <string>

using namespace std;


class Product { // 6. базовый продукт
    public:
    virtual ~Product(){}; // вируальный деструктор - для того, чтобы дропнуть из другого класса
    virtual string Operation() const = 0;
};

class ConcreteProduct_1: public Product { // 8. продукт_1 - наследник класса базового продукта
    public:
    string Operation() const override { // 15. отлавливаем переопределенный оператион для конретного продукта
        return "res of ContreteProduct_1";
    }
};

class ConcreteProduct_2: public Product {
    public:
    string Operation() const override {
        return "res of ConcreteProduct_2";
    }
};

class Creator { // 3. базовый создатель
    public:
    virtual ~Creator(){}; // вируальный деструктор - для того, чтобы дропнуть из другого класса
    virtual Product* FactoryMethod() const = 0; // 5. виртуальная функция - указывает на базовый продукт

    string SomeOperation() const {
        Product* product = this->FactoryMethod(); // 12. по указателю на базовый класс продукта - берем фабричный метод, который имеет оператион - виртуальную константную функцию
        string res = "some creator`s code has just worked with " + product->Operation(); // 13. обращаемся к оператион
        delete product; // 15. грохаем указатель на продукт
        return res;
    }
};

class ConcreteCreator_1: public Creator { // 2. который является наследником базового создателя
    public:
    Product* FactoryMethod() const override { // 4. переопределяем виртуальную функцию, объявленную в классе базовый создатель
        return new ConcreteProduct_1(); // 7. возвращаем созданный продукт_1
    }
};

class ConcreteCreator_2: public Creator {
    public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct_2();
    }
 };

void ClientCode(const Creator& creator) { // 10. принимаем создателя
    cout << "bumbumbum govnocode - shokding shkoding)" << endl << creator.SomeOperation() << endl; // 11. вызываем методы фабрики, чтобы получить объект-продукт
}

int main(){
    cout << "init Concrete Creator 1" << endl;
    Creator* creator1 = new ConcreteCreator_1(); // 1. инициализируем создателя_1
    ClientCode(*creator1); // 9. выполняем необходимые операции, для этого передаем объект создателя
    cout << "blablabla" << endl;
    cout << "init Concrete Creator 2" << endl;
    Creator* creator2 = new ConcreteCreator_2();
    ClientCode(*creator2);

    delete creator1; // 16. грохаем два указателя на создателей
    delete creator2; // все умерли - осталась одна Лена
    return 0;
}