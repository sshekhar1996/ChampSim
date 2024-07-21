#include <map>

#include "msl/fwcounter.h"
#include "ooo_cpu.h"
#include "../gshare/gshare.h"
#include "../perceptron/perceptron.h"

namespace
{
constexpr std::size_t BIMODAL_TABLE_SIZE = 4096;
constexpr std::size_t BIMODAL_PRIME = 4093;

std::map<O3_CPU*, std::array<champsim::msl::fwcounter<COUNTER_BITS>, BIMODAL_TABLE_SIZE>> bimodal_table;
} // namespace


uint8_t gpred;
uint8_t ppred;

void O3_CPU::initialize_branch_predictor() {}

uint8_t O3_CPU::predict_branch(uint64_t ip)
{
  auto hash = ip % ::BIMODAL_PRIME;
  auto value = ::bimodal_table[this][hash];

    if ( value.value() >= (value.maximum / 2))
     {
        ppred = perceptron_predict_branch(ip, this);
        return ppred;
     }   
    else
    {
        gpred = gshare_predict_branch(ip, this);
        return gpred;
    }
}

void O3_CPU::last_branch_result(uint64_t ip, uint64_t branch_target, uint8_t taken, uint8_t branch_type)
{
  auto hash = ip % ::BIMODAL_PRIME;
  if(taken == gpred && taken != ppred)
    ::bimodal_table[this][hash] += -1;
  else if(taken != gpred && taken == ppred)
    ::bimodal_table[this][hash] += 1;
  
  gshare_last_branch_result(ip,branch_target, taken, branch_type, this);
  perceptron_last_branch_result(ip, branch_target, taken, branch_type, this);
}
