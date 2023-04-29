// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
    struct QueueItem {
        T data;
        QueueItem* next;
        QueueItem* prev;
    };
    QueueItem* head;
    QueueItem* tail;
    TPQueue::QueueItem* createQueueItem(const T&);

 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

template <typename T>
typename TPQueue<T>::QueueItem* TPQueue<T>::createQueueItem(const T& data) {
    QueueItem* item = new QueueItem;
    item->data = data;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
void TPQueue<T>::push(const T& d) {
    if (head == nullptr) {
        head = createQueueItem(d);
        tail = head;
    } else if (tail->data.prior >= d.prior) {
        if (tail->data.ch == d.ch) {
            tail->data = d;
        } else {
            tail->next = createQueueItem(d);
            tail->next->prev = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->prev = createQueueItem(d);
        head = tail->prev;
        head->next = tail;
    } else {
        QueueItem* tmp = tail;
        while (tmp != head && tmp->data.prior < d.prior) {
            tmp = tmp->prev;
        }
        if (tmp->data.prior > d.prior) {
            QueueItem* cell = new QueueItem;
            cell->next = tmp->next;
            cell->prev = tmp;
            cell->data = d;
            tmp->next->prev = cell;
            tmp->next = cell;
        }
        if (tmp == head && tmp->data.prior < d.prior) {
            head->prev = createQueueItem(d);
            head = head->prev;
            head->next = tmp;
        }
    }
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("Queue is empty!");
    } else {
        QueueItem* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    QueueItem* temp = head;
    while (temp) {
        std::cout << temp->data.ch << temp->data.prior << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
