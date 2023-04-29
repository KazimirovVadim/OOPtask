#include "Container.h"
#include "iostream"
#include "Classes.h"

void test1() {      // get/add test
    Container<int> test1;
    test1.addFirst(1);
    test1.addLast(2);
    int b = test1.getFirst();
    b++;
    int &c = test1.getFirst();
    c--;
    int result = test1.getFirst();
    std::cout << b << c << test1.getFirst() << std::endl;
    test1.clearContainer();
    std::cout << test1.getFirst() << std::endl;
}

void test2() {      // iterator test
    Container<int> test2;
    for (int i = 0; i < 10; i++) {
        test2.addLast(i);
    }

    int count = 50;

    for (Container<int>::iterator k = test2.begin(); k != test2.end(); ++k) {
        std::cout << *k << std::endl;
//        std::cout << "iteration " <<  count << std::endl;
        k.setdata(count);
        count++;
    }

    std::cout << std::endl;

    for (Container<int>::iterator k = test2.begin(); k != test2.end(); ++k) {
        std::cout << *k << std::endl;
    }
}

void test3() {      // reverse test
    Container<int> test3;
    for (int i = 0; i < 10; i++) {
        test3.addLast(i);
    }

    for (Container<int>::iterator k = test3.begin(); k != ++test3.end(); ++k) {
        std::cout << *k << std::endl;
    }

    std::cout << std::endl;
    test3.reverse();

    for (Container<int>::iterator k = test3.begin(); k != ++test3.end(); ++k) {
        std::cout << *k << std::endl;
    }
}

void test4() {
    Container<Task*> containerWithTasks;
    Container<std::string> containerInfo;
    containerWithTasks.addLast(new BinaryCalculation(12312, '+', 138912));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(1, '+', 1)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(1, '-', 1)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(1, '*', 1)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(1, '/', 10)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(4, '/', 2)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(4, '*', 0)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(5, '/', 0)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(6, '-', 1)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(7, '-', 1)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(12, '*', 13)));
    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(51, '/', 4)));

    NumberOfObjects* tasksCounter = new NumberOfObjects;
    tasksCounter->apply();
    std::cout << tasksCounter->toString() << std::endl;

    while(!containerWithTasks.isEmpty()){
        Task* task = containerWithTasks.popFirst();
        task->apply();
        containerInfo.addLast(task->toString());
        delete task;
    }

    for (auto iterator = containerInfo.begin(); iterator!= ++containerInfo.end(); ++iterator){
        std::cout << (*iterator) << std::endl;
    }

    delete tasksCounter;

    std::cout << Object::getCount() << std::endl;

} // Task3 on site

void test5() {

    Container<Task*> containerWithTasks;

    containerWithTasks.addLast(new AddTaskToContainer(&containerWithTasks, new BinaryCalculation(40, '*', 10)));
    containerWithTasks.addLast(new BinaryCalculation(1456, '-', 123));

    ClearContainer customTask1(&containerWithTasks);
    NumberOfObjects customTask2;

    NumberOfTasksWithResult customTask3(&containerWithTasks);

    customTask2.apply();
    std::cout << customTask2.getResult() << std::endl;
    std::cout << containerWithTasks.size() << std::endl;

    customTask3.apply();
    ObjectsInContainer customTask4 (&containerWithTasks);
    customTask4.apply();
    std::cout << customTask3.toString() << std::endl;
    std::cout << customTask4.toString() << std::endl;

    customTask1.apply();
    customTask2.apply();
    std::cout << customTask2.getResult() << std::endl;
    std::cout << containerWithTasks.size() << std::endl;

    containerWithTasks.addLast(new ClearContainer(&containerWithTasks));
    containerWithTasks.getFirst()->apply();
    std::cout << containerWithTasks.size() << std::endl;
    
}

int main() {

//    test1();
//    test2();
//    test3();
//    test4();
    test5();

}