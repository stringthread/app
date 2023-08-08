#include "wavelet_tree.h"
#include <bitset>

using namespace wavelet_tree;

code wavelet_tree::encode_char(const char c)
{
  auto bs = std::bitset<CODE_SIZE>(c);
  code code;
  for (size_t i = 0; i < CODE_SIZE; i++)
  {
    code.push_front(bs[i]);
  }
  return code;
}

code_seq encode_str(const std::string &str)
{
  std::bitset<CODE_SIZE> bs;
  code_seq encoded_str;
  encoded_str.reserve(str.size());
  for (const char &c : str)
  {
    encoded_str.push_back(encode_char(c));
  }
  return encoded_str;
}

WaveletTree::WaveletTree(const std::string &str)
{
  _size = str.size();
  root = std::make_shared<WaveletTreeNode>(encode_str(str), 0, nullptr);
}

char WaveletTree::access(int i) const
{
  std::bitset<CODE_SIZE> c;
  bool curr;
  auto node = root;
  i;
  for (size_t h = 0; h < CODE_SIZE; h++)
  {
    curr = node->bv->Access(i);
    c[CODE_SIZE - 1 - h] = curr;
    i = node->bv->Rank(curr, i) - 1;
    if (curr)
      node = node->right;
    else
      node = node->left;
  }
  return static_cast<char>(c.to_ulong());
}

int WaveletTree::rank(char c, int i) const
{
  auto code = encode_char(c);
  auto node = root;
  for (auto itr = code.begin(); itr != code.end(); ++itr)
  {
    i = node->bv->Rank(*itr, i) - 1;
    if (*itr)
      node = node->right;
    else
      node = node->left;
  }
  return i + 1;
}

int WaveletTree::select(char c, int i) const
{
  auto code = encode_char(c);
  auto node = root;
  for (auto itr = code.begin(); itr != code.end(); ++itr)
  {
    if (*itr)
    {
      if (node->right)
        node = node->right;
    }
    else
    {
      if (node->left)
        node = node->left;
    }
  }
  for (auto itr = code.rbegin(); itr != code.rend(); itr++)
  {
    i = node->bv->Select(*itr, i);
    node = node->parent;
  }
  return i;
}
