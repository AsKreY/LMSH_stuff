#include <iostream>
#include <functional>
#pragma once

template <typename T, class C>
class BinomialHeap
{
public:
private:
  struct Node{
    T key;
    Node* parent=nullptr;
    Node* child=nullptr;
    Node* sibling=nullptr;
    size_t degree = 0;
  };
};