
#include "../../include/Counter.h"

int Counter::getValue() const {
    return value;
}

void Counter::setValue(int value) {
    Counter::value = value;
}

Counter::Counter(int initVal) {
    value = initVal;
}
