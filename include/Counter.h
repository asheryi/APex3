//
// Created by yishay on 11/23/17.
//

#ifndef EX3_COUNTER_H
#define EX3_COUNTER_H


class Counter {
    int value;
public:
    int getValue() const;

    void setValue(int value);

    Counter(int initVal);
};


#endif //EX3_COUNTER_H
