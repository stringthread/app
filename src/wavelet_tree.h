#ifndef WAVELET_TREE_
#define WAVELET_TREE_
#include "bit_vector.h"
#include <memory>
#include <deque>
#include <vector>
#include <string>
#include <iostream>

namespace wavelet_tree
{
  constexpr size_t CODE_SIZE = 8;
  using code = std::deque<bool>;
  using code_seq = std::vector<code>;

  std::string bits2str(const std::deque<bool> &bits);
  code encode_char(const char c);

  class ExBitVector
  {
  private:
    std::unique_ptr<succinct_bv::BitVector> bv0;
    std::unique_ptr<succinct_bv::BitVector> bv1;
    const std::deque<bool> val;
    bool all_1;
    bool all_0;

  public:
    uint64_t Rank(bool b, uint64_t x) const;
    uint64_t Select(bool b, uint64_t i) const;
    bool Access(size_t i) const;
    bool operator[](size_t i) const;
    ExBitVector() = delete;
    ExBitVector(const std::deque<bool> &v);
  };

  class WaveletTreeNode
  {
  public:
    WaveletTreeNode(const code_seq &v, int depth, WaveletTreeNode *parent_);
    WaveletTreeNode(const WaveletTreeNode &obj) = default;
    WaveletTreeNode(WaveletTreeNode &&obj) = default;
    ~WaveletTreeNode() = default;
    WaveletTreeNode &operator=(const WaveletTreeNode &obj) = default;
    WaveletTreeNode &operator=(WaveletTreeNode &&obj) = default;

    std::unique_ptr<ExBitVector> bv;
    std::shared_ptr<WaveletTreeNode> left;
    std::shared_ptr<WaveletTreeNode> right;
    std::shared_ptr<WaveletTreeNode> parent;
  };

  class WaveletTree
  {
  private:
    std::shared_ptr<WaveletTreeNode> root;
    int _size;

  public:
    WaveletTree(const std::string &str);
    ~WaveletTree() = default;
    char access(int i) const;
    int rank(char c, int i) const;
    int select(char c, int i) const;
    int size() const { return _size; }
  };
}

#endif
