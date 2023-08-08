#include "wavelet_tree.h"
#include <stdexcept>

using namespace wavelet_tree;

std::string wavelet_tree::bits2str(const std::deque<bool> &bits)
{
  std::string result = "";
  for (auto itr = bits.begin(); itr != bits.end(); itr++)
  {
    result += (*itr) ? "1" : "0";
  }
  return result;
}

uint64_t ExBitVector::Rank(bool b, uint64_t x) const
{
  if (b)
  {
    if (all_0)
      throw std::runtime_error("no such element");
    return bv1->Rank(x);
  }
  if (all_1)
    throw std::runtime_error("no such element");
  return bv0->Rank(x);
}
uint64_t ExBitVector::Select(bool b, uint64_t i) const
{
  if (b)
  {
    if (all_0)
      throw std::runtime_error("no such element");
    return bv1->Select(i);
  }
  if (all_1)
    throw std::runtime_error("no such element");
  return bv0->Select(i);
}
bool ExBitVector::Access(size_t i) const { return val[i]; }
bool ExBitVector::operator[](size_t i) const { return Access(i); }
ExBitVector::ExBitVector(const std::deque<bool> &v) : val{v}
{
  std::deque<bool> v_inv;
  all_1 = true;
  all_0 = true;
  for (auto itr = v.begin(); itr != v.end(); itr++)
  {
    v_inv.push_back(!(*itr));
    all_1 &= (*itr);
    all_0 &= !(*itr);
  }
  if (!all_0)
    bv1 = std::make_unique<succinct_bv::BitVector>(v);
  if (!all_1)
    bv0 = std::make_unique<succinct_bv::BitVector>(v_inv);
}
