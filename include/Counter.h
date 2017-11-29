//
// Created by yishay on 11/23/17.
//

#ifndef EX3_COUNTER_H
#define EX3_COUNTER_H

// Counter class to count  , use is to pass counter to several uses for read/write purposes.
class Counter {
    int value;
public:
    /**
     * @return the value .
     */
    int getValue() const;

    /**
     * Sets the value of counter to be value .
     * @param value - to set to .
     */
    void setValue(int value);

    /**
     * Constructor of Counter based on initial value .
     * @param initVal
     */
    Counter(int initVal);
};


#endif //EX3_COUNTER_H
