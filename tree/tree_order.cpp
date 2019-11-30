#include <iostream>

class Node
{
public:
  int data_;
  Node* left_;
  Node* right_;

public:
  Node(int data, Node* left, Node* right) :
  data_(data),
  left_(left),
  right_(right)
  {
  }
};

class Tree
{
public:
  Node* pRootNode_;

public:
  void SetRootNode(Node* rootNode)
  {
    pRootNode_ = rootNode;
  }

  Node* GetRootNode()
  {
    return pRootNode_;
  }

  void Inorder(Node* node)
  {
    if(node != nullptr)
    {
      std::cout << node->data_ << " ";
      Inorder(node->left_);
      Inorder(node->right_);
    }
  }

  void Preorder(Node* node)
  {
    if(node != nullptr)
    {
      Preorder(node->left_);
      std::cout << node->data_ << " ";
      Preorder(node->right_);
    }
  }

  void Postorder(Node* node)
  {
    if(node != nullptr)
    {
      Postorder(node->left_);
      Postorder(node->right_);
      std::cout << node->data_ << " ";
    }
  }
};

int main(void)
{
  /*       1
   *     <- ->
   *    2     3
   *  <- ->
   * 4     5
   * */

  Tree t;
  Node* n4 = new Node(4, nullptr, nullptr);
  Node* n5 = new Node(5, nullptr, nullptr);
  Node* n2 = new Node(2, n4, n5);
  Node* n3 = new Node(3, nullptr, nullptr);
  Node* n1 = new Node(1, n2, n3);

  t.SetRootNode(n1);

  std::cout << "Inorder" << std::endl;
  t.Inorder(t.GetRootNode());
  std::cout << std::endl;

  std::cout << "Preorder" << std::endl;
  t.Preorder(t.GetRootNode());
  std::cout << std::endl;

  std::cout << "Postorder" << std::endl;
  t.Postorder(t.GetRootNode());
  std::cout << std::endl;

  return 0;
}