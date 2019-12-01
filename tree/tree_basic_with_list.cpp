#include <iostream>

class Node
{
public:
  char data_;
  Node* left_;
  Node* right_;

public:
  Node(char data) :
    data_(data),
    left_(nullptr),
    right_(nullptr)
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

  void SetLeft(Node* node, Node* parent)
  {
    parent->left_ = node;
  }

  void SetRight(Node* node, Node* parent)
  {
    parent->right_ = node;
  }
};

int main(void)
{
  /*       A
 *      <-  ->
 *    B       C
 *  <- ->   <- ->
 * D     E F     G
 * */

  Tree t;

  /* root node */
  Node* nA = new Node('A');
  t.SetRootNode(nA);

  /* level 2 */
  Node* nB = new Node('B');
  Node* nC = new Node('C');

  /* leaf nodes */
  Node* nD = new Node('D');
  Node* nE = new Node('E');
  Node* nF = new Node('F');
  Node* nG = new Node('G');

  /*    A
   *  <- ->
   * B     C
   */

  t.SetLeft(nB, nA);
  t.SetRight(nC, nA);

  /*  B-D-E subtree
   *    B
   *  <- ->
   * D     E
   */
  t.SetLeft(nD, nB);
  t.SetRight(nE, nB);

  /*  C-F-G subtree
   *    C
   *  <- ->
   * F     G
   */
  t.SetLeft(nF, nC);
  t.SetRight(nG, nC);

  return 0;
}
