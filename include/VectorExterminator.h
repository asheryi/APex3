
#ifndef EX3_DELETEVECTOR_H
#define EX3_DELETEVECTOR_H

#include <vector>

/**
     * Deleting a vector of pointers.
     * @param nodes - vector of pointers.
     */
template<class T>
void deleteVector(std::vector<T *> &nodes) {
    for (unsigned int i = 0; i < nodes.size(); i++) {
        delete nodes[i];
    }
    nodes.clear();
}

#endif //EX3_DELETEVECTOR_H
