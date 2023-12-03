#include <iostream>
#include <map>

#include "Container.h"
#include "Allocator.h"

using namespace std;

int main()
{ 
    try {
        container<int, Allocator<int>> aContainer (30);

        aContainer.push_back(1);
        aContainer.push_back(2);
        aContainer.push_back(3);

        while (aContainer.has_next()) {
            cout << aContainer.next() << endl;
        }

    } catch (exception anException) {
        cout << anException.what();
    }

    

    /*while (aContainer.has_next()) {
        cout << aContainer.next() << endl;
    }*/
    
}
