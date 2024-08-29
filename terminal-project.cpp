#include "explorer.h"

int main() {
    explorer ex = explorer();
    while (ex.isWorking())
    {
        ex.printCurrentLocation();
        ex.getCommand();
        ex.executeLastCommand();
    }
    return 0;
}