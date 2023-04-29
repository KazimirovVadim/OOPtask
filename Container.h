#pragma once

#include "iostream"

template <class T> class Container {

private:
    struct Element {
        T data;
        Element *prev;
        Element *next;

        Element() {
            prev = NULL;
            next = NULL;
        }

        Element(T data) {
            this->data = data;
            prev = NULL;
            next = NULL;
        }
    };
    Element *_firstEl;
    Element *_lastEl;
    int numberOfElements;

public:

    Container() {
        _firstEl = NULL;
        _lastEl = NULL;
        numberOfElements = 0;
    }

    ~Container() {
        clearContainer();
    }

    void addFirst(T data) {
        Element *temp = new Element(data);

        if (_firstEl == NULL) {
            _firstEl = temp;
            _lastEl = _firstEl;
        }
        else {
            temp->next = _firstEl;
            _firstEl->prev = temp;
            _firstEl = _firstEl->prev;
        }

        ++numberOfElements;
    }

    void addLast(T data) {
        Element *temp = new Element(data);

        if (_lastEl == NULL) {
            _lastEl = temp;
            _firstEl = _lastEl;
        }
        else {
            temp->prev = _lastEl;
            _lastEl->next = temp;
            _lastEl = _lastEl->next;
        }

        ++numberOfElements;
    }

    void delFirst() {
        if (_firstEl != NULL) {
            Element *temp = _firstEl;
            _firstEl = _firstEl->next;
            --numberOfElements;
            delete temp;
        }
    }

    void delLast() {
        if (_lastEl != NULL) {
            Element *temp = _lastEl;
            _lastEl = _lastEl->prev;
            --numberOfElements;
            delete temp;
        }
    }

    void clearContainer() {
        while (_firstEl != NULL) {
            Element *temp = _firstEl;
            if (_firstEl == _lastEl) {
                _lastEl = _lastEl->next;
            }
            _firstEl = _firstEl->next;
            delete temp;
            --numberOfElements;
        }
    }

    T& getFirst() {
        if (_firstEl != NULL) {
            return _firstEl->data;
        }
        else {
            throw std::range_error("Container has no elements");
        }
    }

    T& getLast() {
        if (_lastEl != NULL) {
            return _lastEl->data;
        }
        else {
            throw std::range_error("Container has no elements");
        }
    }

    int size() {
        return numberOfElements;
    }

    bool isEmpty() {
        if (numberOfElements > 0) return 0;
        else return 1;
    }

    void swap (Container<T> &other) {
        if (this != &other) {
            std::swap(_firstEl, other._firstEl);
            std::swap(_lastEl, other._lastEl);
            std::swap(numberOfElements, other.numberOfElements);
        }
    }

    void reverse() {
        Element *iteratorContainer = _lastEl;

        for (int i = 0; i < numberOfElements; i++){
            std::swap(iteratorContainer->next, iteratorContainer->prev);
            iteratorContainer = iteratorContainer->next;
        }
        std::swap(_lastEl,_firstEl);
    }

    class iterator {

        friend class Container<T>;

        Element* _ptr;

        public:

        explicit iterator(Element* ptr) : _ptr(ptr) {}

        explicit iterator() : _ptr(nullptr) {}

        bool operator==(const iterator& other) const noexcept {
            return _ptr == other._ptr;
        }

        bool operator!=(const iterator& other) const noexcept {
            return !(_ptr == other._ptr);
        }

        iterator& operator++() noexcept {   // prefix
            _ptr = _ptr->next;
            return *this;
        }

        iterator operator++(int) noexcept {    // postfix
            iterator result(*this);
            ++(*this);
            return result;

        }

        iterator& operator--() noexcept {   // prefix
            _ptr = _ptr->prev;
            return *this;
        }

        iterator operator--(int) noexcept {    // postfix
            iterator result(*this);
            --(*this);
            return result;
        }

        T& operator*() const noexcept {
            return _ptr->data;
        }

        T* operator->() const noexcept {
            return &(_ptr->data);
        }

        void setdata(const T& data) noexcept {   // will be changed later probably
            _ptr->data = data;
        }
    };

    iterator begin() {
        return (iterator(this->_firstEl));
    }

    iterator end() {
        return (iterator(this->_lastEl));
    }

    T popFirst() {
        if (isEmpty()){
            throw std::logic_error("Container has no elements.");
        }

        if (_firstEl == _lastEl) {
            _lastEl = NULL;
        }
        Element* temp = _firstEl;
        T tempData = temp->data;
        _firstEl = _firstEl->next;
        if (_firstEl != NULL) {
            _firstEl->prev = NULL;
        }
        delete temp;
        numberOfElements--;
        return (tempData);
    }

};