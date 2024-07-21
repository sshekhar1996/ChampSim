#include <algorithm>
#include <array>
#include <bitset>
#include <map>
#include "msl/fwcounter.h"
#include "ooo_cpu.h"

namespace
{
constexpr std::size_t GLOBAL_HISTORY_LENGTH = 15; //change
constexpr std::size_t COUNTER_BITS = 2;
constexpr std::size_t GS_HISTORY_TABLE_SIZE = 157287; //change

std::map<O3_CPU*, std::bitset<GLOBAL_HISTORY_LENGTH>> branch_history_vector;
std::map<O3_CPU*, std::array<champsim::msl::fwcounter<COUNTER_BITS>, GS_HISTORY_TABLE_SIZE>> gs_history_table;

std::size_t gs_table_hash(uint64_t ip, std::bitset<GLOBAL_HISTORY_LENGTH> bh_vector)
{
  std::size_t hash = bh_vector.to_ullong();
  hash ^= ip;
  hash ^= ip >> GLOBAL_HISTORY_LENGTH;
  hash ^= ip >> (GLOBAL_HISTORY_LENGTH * 2);

  return hash % GS_HISTORY_TABLE_SIZE;
}
} // namespace

//void O3_CPU::initialize_branch_predictor() {}

uint8_t gshare_predict_branch(uint64_t ip, O3_CPU* cpu)
{
  auto gs_hash = ::gs_table_hash(ip, ::branch_history_vector[cpu]);
  auto value = ::gs_history_table[cpu][gs_hash];
  return value.value() >= (value.maximum / 2);
}

void gshare_last_branch_result(uint64_t ip, uint64_t branch_target, uint8_t taken, uint8_t branch_type, O3_CPU* cpu)
{
  auto gs_hash = gs_table_hash(ip, ::branch_history_vector[cpu]);
  ::gs_history_table[cpu][gs_hash] += taken ? 1 : -1;

  // update branch history vector
  ::branch_history_vector[cpu] <<= 1;
  ::branch_history_vector[cpu][0] = taken;
}
