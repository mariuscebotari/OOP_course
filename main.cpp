#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string name, int age) : name(name), age(age) {}

    void setName(std::string name) { this->name = name; }
    void setAge(int age) { this->age = age; }

    std::string getName() const { return name; }
    int getAge() const { return age; }

    void showInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

class Animal {
protected:
    std::string name;

public:
    Animal(std::string name) : name(name) {
        std::cout << "Animal constructor called.\n";
    }

    virtual ~Animal() {
        std::cout << "Animal destructor called.\n";
    }

    void speak() const {
        std::cout << name << " is making a sound." << std::endl;
    }
};

class Dog : public Animal {
public:
    Dog(std::string name) : Animal(name) {
        std::cout << "Dog constructor called.\n";
    }

    ~Dog() {
        std::cout << "Dog destructor called.\n";
    }

    void bark() const {
        std::cout << name << " is barking." << std::endl;
    }
};

class ClassB;

class ClassA {
private:
    int valueA;

public:
    ClassA(int val) : valueA(val) {}

    friend class ClassB;
};

class ClassB {
private:
    int valueB;

public:
    ClassB(int val) : valueB(val) {}

    void showValues(const ClassA& objA) {
        std::cout << "Value from ClassA: " << objA.valueA << std::endl;
        std::cout << "Value from ClassB: " << valueB << std::endl;
    }
};

int main() {
    // Ex. 1
    std::cout << "Encapsulation Example:\n";
    Person person("John", 30);
    person.showInfo();

    person.setName("Maria");
    person.setAge(25);
    person.showInfo();
    std::cout << std::endl;

    // Ex. 2 si 3
    std::cout << "Inheritance Example:\n";
    Dog dog("Bob");
    dog.speak();
    dog.bark();
    std::cout << std::endl;

    // Ex. 4
    std::cout << "Friend Example:\n";
    ClassA objA(10);
    ClassB objB(20);
    objB.showValues(objA);

    return 0;
}
