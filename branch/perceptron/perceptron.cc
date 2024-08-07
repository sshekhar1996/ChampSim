#include <ooo_cpu.h>
#include "perceptron.h"

perceptron perceptron_predict[NUM_CPUS];

void O3_CPU::initialize_branch_predictor()
{
    perceptron_predict[cpu].init();
}

uint8_t O3_CPU::predict_branch(uint64_t ip)
{
    return perceptron_predict[cpu].predict1(ip);
}

void O3_CPU::last_branch_result(uint64_t ip, uint64_t branch_target, uint8_t taken, uint8_t branch_type)
{
    perceptron_predict[cpu].update1(ip, taken);
}