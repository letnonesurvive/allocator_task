#include <iostream>
#include <map>

#include "Container.h"

using namespace std;

int main()
{ 
    container<int> aContainer(4);
    aContainer.push_back(1);
    aContainer.push_back(2);

    while (aContainer.has_next()) {
        cout << aContainer.next();
    }

}
