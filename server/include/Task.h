

#ifndef EX3_TASK_H
#define EX3_TASK_H

// Define the Task to be executed by a thread.

class Task {
public:
    // COnstructor.
    Task(void *(*funcToExecute)(void *arg), void *arg) :
            funcToExecute(funcToExecute), arg(arg) {}

    // Execute the task
    void execute() {
        funcToExecute(arg);
    }

    virtual ~Task() {}

private:
    // func to execute
    void *(*funcToExecute)(void *arg);

    // args to func
    void *arg;


};


#endif //EX3_TASK_H
