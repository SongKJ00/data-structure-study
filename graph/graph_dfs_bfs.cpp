#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>

class Node
{
public:
  int data_;
  std::list<Node*> adjacent_;
  bool marked_;
public:
  Node(int data) :
  data_(data), marked_(false)
  {
  }
};

class Graph
{
public:
  std::vector<Node*> nodes_;
public:
  Graph(int size)
  {
    nodes_.resize(size);
    for(int i = 0; i < size; i++)
    {
      nodes_[i] = (new Node(i));
    }
  }

  void AddEdge(int n1, int n2)
  {
    nodes_[n1]->adjacent_.push_back(nodes_[n2]);
    nodes_[n2]->adjacent_.push_back(nodes_[n1]);
  }

  void ClearMarked()
  {
    for(auto n: nodes_)
    {
      n->marked_ = false;
    }
  }

  void visit(Node* node)
  {
    std::cout << node->data_ << " ";
  }

  void dfs(int start)
  {
    std::stack<Node*> s;

    Node* root = nodes_[start];
    root->marked_ = true;
    for(auto n: root->adjacent_)
    {
      s.push(n);
      n->marked_ = true;
    }
    visit(root);

    while(!s.empty())
    {
      Node* node = s.top();
      s.pop();
      for(auto n: node->adjacent_)
      {
        if(n->marked_ == false)
        {
          s.push(n);
          n->marked_ = true;
        }
      }
      visit(node);
    }

    std::cout << std::endl;
  }

  void bfs(int start)
  {
    std::queue<Node*> q;
    Node* root = nodes_[start];
    root->marked_ = true;
    for(auto n: root->adjacent_)
    {
      q.push(n);
      n->marked_ = true;
    }
    visit(root);

    while(!q.empty())
    {
      Node* node = q.front();
      q.pop();
      for(auto n: node->adjacent_)
      {
        if(n->marked_ == false)
        {
          q.push(n);
          n->marked_ = true;
        }
      }
      visit(node);
    }

    std::cout << std::endl;
  }
};

int main(void)
{
  /*
   *   0
   *  /
   * 1 -- 3    7
   * |  / | \ /
   * | /  |  5
   * 2 -- 4   \
   *           6 - 8
   */
  Graph g(9);
  g.AddEdge(0, 1);
  g.AddEdge(1, 2);
  g.AddEdge(1, 3);
  g.AddEdge(2, 3);
  g.AddEdge(2, 4);
  g.AddEdge(3, 4);
  g.AddEdge(3, 5);
  g.AddEdge(5, 6);
  g.AddEdge(5, 7);
  g.AddEdge(6, 8);

  std::cout << "DFS" << std::endl;
  g.dfs(0);
  g.ClearMarked();

  std::cout << "BFS" << std::endl;
  g.bfs(0);
  g.ClearMarked();
  return 0;
}
