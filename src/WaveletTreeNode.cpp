#include "wavelet_tree.h"

using namespace wavelet_tree;

WaveletTreeNode::WaveletTreeNode(const code_seq &v, int depth, WaveletTreeNode *parent_)
{
  parent = std::shared_ptr<WaveletTreeNode>(parent_);
  code_seq codes_left, codes_right;
  std::deque<bool> curr_bits;
  for (auto itr = v.begin(); itr != v.end(); itr++)
  {
    if (CODE_SIZE <= depth)
      break;
    curr_bits.push_back((*itr)[depth]);
    if ((*itr)[depth])
    {
      codes_right.push_back(*itr);
    }
    else
    {
      codes_left.push_back(*itr);
    }
  }
  bv = std::make_unique<ExBitVector>(curr_bits);
  if (CODE_SIZE > depth + 1)
  {
    if (codes_left.size() > 0)
      left = std::make_shared<WaveletTreeNode>(codes_left, depth + 1, this);
    if (codes_right.size() > 0)
      right = std::make_shared<WaveletTreeNode>(codes_right, depth + 1, this);
  }
}
