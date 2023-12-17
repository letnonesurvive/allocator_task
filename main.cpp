#include <iostream>
#include <map>
#include <math.h>

#include "Container.h"
#include "Allocator.h"

using namespace std;

int main()
{ 
    /*std::allocator<int> alloc;
    alloc.deallocate(void*);*/
    //std::allocator<std::pair<int, int>> allocator;
    //auto* myMemory = allocator.allocate(10);
    //allocator.deallocate(myMemory, 10);

    map<int, int> aMap;

    for (int i = 0; i < 10; ++i) {
        aMap.insert (make_pair (i, static_cast<int> (tgamma (i+1))));
        cout << "i=" << i << " factorial=" << aMap[i] << endl;
    }

    cout << endl;

    map<int, int, std::less<>, Allocator<pair<int, int>>> aMapWithNewAllocator (Allocator<pair<const int, int>> (11));

    for (int i = 0; i < 10; ++i) {
        aMapWithNewAllocator.insert (make_pair (i, static_cast<int> (tgamma (i+1))));
        cout << "i=" << i << " factorial=" << aMapWithNewAllocator[i] << endl;
    }

    cout << endl;

    container<int> aContainer1 (10);
    for (int i = 0; i < 10; ++i) {
        aContainer1.push_back (i);
    }

    for (int i = 0; aContainer1.has_next(); ++i) {
        cout << "aContainer1[" << i << "]=" << aContainer1.next() << endl;
    }

    cout << endl;

    container<int, Allocator<int>> aContainer2 (Allocator<int> (10));
    for (int i = 0; i < 10; ++i) {
        aContainer2.push_back (i);
    }

    for (int i = 0; aContainer2.has_next(); ++i) {
        cout << "aContainer2[" << i << "]=" << aContainer2.next() << endl;
    }

}
