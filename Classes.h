//
// Created by Kazim on 27.04.2023.
//
#include "iostream"
#include "Container.h"

class Object {
    static int counter;

public:
    Object() {
        counter++;
    }
    virtual ~Object() {
        counter--;
    }

    static int getCount() {
        return counter;
    }

    virtual std::string toString() const=0;
};
inline int Object::counter = 0;

class Task:public Object{
protected:
    bool isResulted = false;

public:
    virtual void apply()=0;

    bool hasResult() const{
        return isResulted;
    }
};

class Named:virtual public Task{

protected:
    std::string name;

public:
    virtual ~Named()=0;
    std::string getName() const{
        return name;
    }
};
inline Named::~Named(){}

class ResultedTask:virtual public Task{

protected:
    bool isSolved = false;
    double result;

public:
    ResultedTask(){
        isResulted = true;
    }

    double getResult() const{
        if (!isSolved) {
            throw std::logic_error("Task has not been solved yet.");
        }
        return result;
    }
};

class BinaryCalculation:public ResultedTask, public Named{

    char op;
    double a;
    double b;

public:

    BinaryCalculation(double a, char oper, double b) {
        this->a = a;
        op = oper;
        this->b = b;
        this->name = std::to_string(a) + ' ' + op + ' ' + std::to_string(b);
    }

    void apply() override {
        isSolved = true;
        switch(op){
            case '+': result = a + b;
                break;
            case '-': result = a - b;
                break;
            case '*': result = a * b;
                break;
            case '/': result = a / b;
                break;
            default: throw std::logic_error("Operator : \'" + std::to_string(op) + "\' is not defined.");
        }
    }

    std::string toString() const override {
        std::string stringResult=name;
        if (isSolved) {
            stringResult+= " = " + std::to_string(result);
        }
        stringResult += '.';
        return stringResult;
    }
};

class AddTaskToContainer:public Named {

    Container<Task*>* container;
    Task* task;

public:
    AddTaskToContainer(Container<Task*>* container, Task* task) {
        this->container = container;
        this->task = task;
        name = "Add \"" + task->toString() + "\" to container.";
    }

    void apply() override {
        container->addLast(task);
    }

    std::string toString() const override {
        return name;
    }
};

class ObjectsInContainer:public Named, public ResultedTask {
    Container<Task*>* container;

public:
    ObjectsInContainer(Container<Task*>* container) {
        this->container = container;
        name = "Counting objects in container.";
    }

    void apply() override {
        isSolved = true;
        result = container->size();
    }

    std::string toString() const override{
        std::string stringResult=name;
        if (isSolved) {
            stringResult+= " Number of objects: " + std::to_string(int(result));
        }
        stringResult += '.';
        return stringResult;
    }
};

class NumberOfTasksWithResult:public Named, public ResultedTask {
    Container<Task*>* container;

public:
    NumberOfTasksWithResult(Container<Task*>* container) {
        this->container = container;
        name = "Counting tasks with result in container.";
    }

    void apply() override {
        isSolved = true;
        int count = 0;
        for (auto iterator = container->begin(); iterator != ++container->end(); iterator++){
            if ((*iterator)->hasResult()) {
                ++count;
            }
        }
        result = count;
    }

    std::string toString() const override {
        std::string stringResult=name;
        if (isSolved) {
            stringResult+= " Number of tasks with result: " + std::to_string(int(result));
        }
        stringResult += '.';
        return stringResult;
    }
};

class ClearContainer:public Task {
    Container<Task*>* container;

public:
    ClearContainer(Container<Task*>* container) {
        this->container = container;
    }

    void apply() override {
        for (auto iterator = container->begin(); iterator != ++container->end();){
            auto newIterator = iterator;
            ++iterator;
            delete *newIterator;
        }
        container->clearContainer();
    }

    std::string toString() const override {
        return "Clear container.";
    }
};

class NumberOfObjects:public ResultedTask {

public:
    void apply() override {
        isSolved = true;
        result = getCount();
    }

    std::string toString() const override {
        std::string stringResult = "Counting objects in program.";
        if (isSolved){
            stringResult += " Number of objects: " + std::to_string(int(result)) + ".";
        }
        return stringResult;
    }
};