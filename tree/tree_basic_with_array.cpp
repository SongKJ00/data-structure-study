#include <iostream>
#include <vector>

class Tree
{
public:
  std::vector<char> nodes_;

public:
  /* Constructor */
  /* Set root node */
  Tree(int node_size, char root_data)
  {
    nodes_.resize(node_size);
    nodes_[0] = root_data;
  }

  /* Set left child node */
  void SetLeft(char data, int parent_idx)
  {
    nodes_[parent_idx*2+1] = data;
  }

  /* Set right child node */
  void SetRight(char data, int parent_idx)
  {
    nodes_[parent_idx*2+2] = data;
  }

  /* Print all nodes of tree */
  void PrintTree()
  {
    for(auto& node: nodes_)
    {
      std::cout << node << " ";
    }
    std::cout << std::endl;
  }
};

int main(void)
{
  /*       A(0)
  *       <-  ->
  *    B(1)      C(2)
  *  <- ->      <- ->
  * D(3)  E(4) F(5)  G(6)
  * */

  Tree t(7, 'A');
  t.SetLeft('B', 0);
  t.SetRight('C', 0);

  t.SetLeft('D', 1);
  t.SetRight('E', 1);

  t.SetLeft('F', 2);
  t.SetRight('G', 2);

  t.PrintTree();

  return 0;
}