#ifndef CUSTOMMAP
#define CUSTOMMAP
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include "Pair.h"
#include"Dequeue.h"
using namespace std;

const int DEFAULT_CAPACITY_Map = 10000;
template<typename KeyType, typename ValueType>
class CustomMap {
private:
    Pair <KeyType, ValueType>* data;
    int myCapacity;
    int mySize;

public:
    int partition(int low, int high)
    {


        KeyType pivot = data[high].first();

        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (data[j].first() < pivot) {
                i++;
                data[j].swapPair(data[i]);

            }
        }
        i++;
        data[i].swapPair(data[high]);


        return i;
    }

    void quickSort(int low, int high) {

        if (low < high) {

            int pi = partition(low, high);

            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }

        //    if (low == 0 && high == mySize - 1) {
        //     for (int i = 0; i < mySize; i++) {
        //         cout << data[i].first() << " " << data[i].second() << "\n";
        //     }
        //    }

    }

    CustomMap(int numElements = DEFAULT_CAPACITY_Map) {

        myCapacity = numElements;
        data = new (nothrow) Pair<KeyType, ValueType>[myCapacity];
        //   for (int i = 0; i < myCapacity; i++) {
        //     data[i] = Pair<KeyType, ValueType>(); 
        // }

        mySize = 0;

    }
    int size() {
        return mySize;
    }
    void insert(const KeyType& key, const ValueType& value) //value will be added to the initial value
    {
        quickSort(0, mySize - 1);
        int l = 0, r = mySize - 1, m;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (data[m].first() < key)
            {
                l = m + 1;

            }
            else if (data[m].first() > key)
                r = m - 1;
            else
            {
                data[m].second() += value;
                return;
            }
        }

        if (myCapacity > mySize)
        {

            data[mySize].first(key);

            data[mySize].second(value);
            // cout<<value<<" n "<< data[mySize].second()<<"\n";
            mySize++;
        }
        //   for (int i = 0; i < mySize; i++)
        //         {
        //             cout << "key: " << data[i].first() << " value: " << data[i].second() << " ";
        //         }
        //         cout << endl;    
    }
    bool contains(const KeyType& key) {
        quickSort(0, mySize - 1);
        int l = 0, r = mySize - 1, m;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (data[m].first() < key)
            {
                l = m + 1;
            }
            else if (data[m].first() > key)
                r = m - 1;
            else
                return true;
        }
        return false;
    }
    ValueType second(int i)
    {
        if (mySize > i)
        {
            return data[i].second();
        }
    }
    KeyType first(int i)
    {
        if (mySize > i)
        {
            return data[i].first();
        }

    }
    const ValueType& at(const KeyType& key) const {
        quickSort(0, mySize - 1);
        int l = 0, r = mySize - 1, m;
        while (l <= r)
        {
            m = (l + r) / 2;
            if (data[m].first() < key)
            {
                l = m + 1;
            }
            else if (data[m].first() > key)
                r = m - 1;
            else
            {

                return data[m].second();
            }
        }

        cerr << "Key not found";

    }
    void display(ostream& out) const {
        if (mySize == 0) {
            cerr << "Map-empty!" << endl;
            return;
        }
        for (int i = 0; i < mySize; i++)
        {
            out << "key: " << data[i].first() << " value: " << data[i].second() << " ";
        }
        cout << endl;
    }
};

ostream& operator<< (ostream& out, const CustomMap<int, int>& aList) {
    aList.display(out);
    return out;
}

#endif