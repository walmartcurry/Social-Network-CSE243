#ifndef QUEUE
#define QUEUE

// #define SQUEUE
 #define DQUEUE
//#define LLQUEUE

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
const int DEFAULT_CAPACITY = 10000;
template <typename QueueElement>
class Dequeue {

public:
    Dequeue(int numElements = DEFAULT_CAPACITY) : myFront(0), myBack(0) {
        if (numElements <= 0) {
            cerr << "Error: Negative or zero capacity required -- terminating execution\n";
            exit(1);
        }
        myCapacity = numElements;
        myArray = new (nothrow) QueueElement[myCapacity];
        if (myArray == 0) {
            cerr << "Error: Inadequate memory to allocate queue -- terminating execution\n";
            exit(1);
        }
    }
    Dequeue(const Dequeue& original) : myFront(original.myFront), myBack(original.myBack), myCapacity(original.myCapacity) {
        myArray = new (nothrow) QueueElement[myCapacity];
        if (myArray == 0) {
            cerr << "Error: Inadequate memory to allocate queue -- terminating execution\n";
            exit(1);
        }
        else {
            for (int pos = myFront; pos < myBack; pos++) { // Smaller than BUT NOT EQUAL!!!!!!!!!!!!!11!1!!!!!
                myArray[pos] = original.myArray[pos];
            }
        }
    }
    ~Dequeue() {
        delete[] myArray;
    }
    const Dequeue& operator= (const Dequeue& rhs) {
        if (this != &rhs) {
            if (myCapacity != rhs.myCapacity) {
                this->~Dequeue();
                myCapacity = rhs.myCapacity;
                myArray = new(nothrow) QueueElement[myCapacity];
                if (myArray == 0) {
                    cerr << "Error: Inadequate memory to allocate stack -- terminating execution\n";
                    exit(1);
                }
            }
            myFront = rhs.myFront;
            myBack = rhs.myBack;
            for (int pos = myFront; pos < myBack; pos++) { // Smaller than BUT NOT EQUAL!!!!!!!!!!!!!11!1!!!!!
                myArray[pos] = rhs.myArray[pos];
            }
        }
        return *this;
    }
    bool empty() const {
        return myFront == myBack;
    }
    void push_back(const QueueElement& value) {
        int newBack = (myBack + 1) % myCapacity;
        if (newBack != myFront) { // i.e., queue isn't full
            myArray[myBack] = value;
            myBack = newBack;
        }
        else {
            cerr << "Dequeue-full! " << endl;
            exit(1);
        }
    }
    void display(ostream& out) const {
        if (empty()) {
            cerr << "Dequeue-empty!" << endl;
            return;
        }
        for (int i = myFront; i != myBack; i = (i + 1) % myCapacity) {
            out << myArray[i] << ' ';
        }
        cout << endl;
    }
    QueueElement front() const {
        if (!empty())
            return myArray[myFront];
        /* else {
             cerr << "Dequeue Empty -- Returning garbage." << endl;
             QueueElement garbage;
             return garbage;
         }*/
    }
    QueueElement back() const {
        if (!empty())
            return myArray[myBack - 1];
        /** else {
             cerr << "Dequeue Empty -- Returning garbage." << endl;
             QueueElement garbage;
             return garbage;
         }*/
    }
    void pop_front() {
        if (!empty())
            myFront = (myFront + 1) % myCapacity;
        else {
            cerr << "Dequeue Empty!" << endl;
        }
    }
    void pop_back() {
        if (!empty())
        {
            if ((myBack - 1) < 0)
                myBack = ((myBack - 1) + myCapacity) % myCapacity;
            else
                myBack = (myBack - 1) % myCapacity;
        }
        else {
            cerr << "Dequeue Empty!" << endl;
        }
        }
    void push_front(const QueueElement& value) {
        int newFront;
        if ((myFront - 1) < 0)
            newFront = ((myFront - 1) + myCapacity) % myCapacity;
        else
            newFront = (myFront - 1) % myCapacity;
        if (newFront != myBack) { // i.e., queue isn't full
            myFront = newFront;
            myArray[myFront] = value;
            
        }
        else {
            cerr << "Dequeue-full! " << endl;
            exit(1);
        }
    }
   
    int find(const QueueElement& value)
    {
        int i = myFront;
        while (i != myBack)
        {
            if (myArray[i] == value)
                return i;
            else
                i = (i + 1) % myCapacity;

        }
        return -1;
    }
    QueueElement* myArray;
private:
#ifdef SQUEUE
    QueueElement myArray[DEFAULT_CAPACITY];
#else
    
#endif


#ifdef LLQUEUE
    class Node {
    public:
        QueueElement data;
        Node* next;
        Node(QueueElement value, Node* link = 0) : data(value), next(link) {}
    };
    typedef Node* NodePointer;
    NodePointer myFront, myBack;
#else
    int myFront, myBack, myCapacity;
#endif
};
template <typename QueueElement>
ostream& operator<< (ostream& out, const Dequeue<QueueElement>& aList) {
    aList.display(out);
    return out;
}
template class Dequeue<int>;
template ostream& operator<<(ostream& out,const Dequeue<int>& aList);

#endif /* QUEUE */
#ifndef MAP_CUSTOM_H
#define MAP_CUSTOM_H
typedef int KeyType;
typedef int ValueType;
const int DEFAULT_CAPACITY_map = 10000;
class CustomMap {
private:
    pair<KeyType, ValueType>* data;
    int myCapacity;
    int mySize;

public:
    CustomMap(int numElements = DEFAULT_CAPACITY) {
        myCapacity = numElements;
       data = new (nothrow) pair<KeyType, ValueType>[myCapacity];
       mySize = 0;

    }
    void insert(const KeyType& key, const ValueType& value) //value will be added to the initial value
    {
        for (int i = 0;i < mySize;i++)
        {
            if (data[i].first == key)
            {
                data[i].second += value;
                return;
            }
        }
        if (myCapacity > mySize)
        {
            data[mySize].first = key;
            data[mySize].second = value;
            mySize++;
        }
    }
    bool contains(const KeyType& key) const {
        for (int i = 0;i < mySize;i++)
        {
            if (data[i].first == key)
            {
                return true;
            
            }
        }
        return false;
    }

    const ValueType& at(const KeyType& key) const {
        for (int i = 0;i < mySize;i++)
        {
            if (data[i].first == key)
            {
                return data[i].second;

            }
        }
        
            cerr<<"Key not found";
        
    }
    void display(ostream& out) const {
        if (mySize==0) {
            cerr << "Map-empty!" << endl;
            return;
        }
        for (int i = 0;i < mySize;i++)
        {
            out << "key: " << data[i].first << " value: " << data[i].second << " ";
        }
        cout << endl;
    }
};
ostream& operator<< (ostream& out, const CustomMap& aList) {
    aList.display(out);
    return out;
}

#endif

template<typename type1, typename type2>
class Priority_Queue {
private:
    class Node {
    public:
        type1 value;
        type2 index;
        Node* next;

        Node(type1 item, type2 key) {
            value = item;
            index = key;
            next = 0;
        }

    };
    Node* mytop;
    int size;
public:
    Priority_Queue() {
        mytop = 0;
        size = 0;
    }
    ~Priority_Queue() {
        while (mytop != 0) {
            Priority_Queue<type1, type2>::Node* ptr = mytop;
            mytop = mytop->next;
            delete ptr;
        }
    }
    bool empty() const {
        return size == 0;
    }

    int get_size() const {
        return size;
    }
    void push(const type1& item, const type2& key) {

        Priority_Queue<type1, type2>::Node* ptr1 = mytop;
        Priority_Queue<type1, type2>::Node* ptr2 = new Node(item, key);

        if (empty() or item > mytop->value) {
            ptr2->next = mytop;
            mytop = ptr2;
            size++;
            return;
        }

        while (ptr1->next != 0 and ptr1->next->value >= item) {
            ptr1 = ptr1->next;
        }
        ptr2->next = ptr1->next;
        ptr1->next = ptr2;

        size++;
        return;
    }
    void pop() {
        if (empty()) {
            cerr << "nothing to pop\n";
            return;
        }

        Priority_Queue<type1, type2>::Node* ptr = mytop;
        mytop = mytop->next;
        delete ptr;
        size--;
        return;
    }
    type1 top1() const {
        if (empty()) {
            cerr << "nothing in top\n";
            type1 garbage = NULL;
            return garbage;
        }
        return mytop->value;
    }
    type2 top2()  {
        if (empty()) {
            cerr << "nothing in top\n";
            type2 garbage = NULL;
            return garbage;
        }
        return mytop->index;
    }


};
template class Priority_Queue<int, int>;
template class Priority_Queue<int, string>;