#ifndef BENCHMARKS_DATABASE_H_H
#define BENCHMARKS_DATABASE_H_H

const int EXECUTIONS = 30;

struct execution_t {
    double time[EXECUTIONS];
    time_t timestamp[EXECUTIONS];
};

#endif //BENCHMARKS_DATABASE_H_H
