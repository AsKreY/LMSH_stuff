#include <vector>
#include <iostream>

class SegTree
{
private:
    struct Node
    {
        int left;
        int right;
        int summ;
        Node *parent = nullptr;
        Node *child1 = nullptr;
        Node *child2 = nullptr;
        Node(int right, int left, const std::vector<int> &source) : left(left), right(right)
        {
            if (right - left == 1)
            {
                summ = source[left];
                return;
            }
            child1 = new Node(left, (right + left) >> 1, source);
            child2 = new Node((left + right) >> 1, right, source);
            child1->parent = this;
            child2->parent = this;
            summ = child1->summ + child2->summ;
        }
        ~Node()
        {
            if (child1->right - child1->left == 1)
            {
                delete child1;
                delete child2;
            }
            else
            {
                child1->~Node();
                child2->~Node();
            }
        }
    };
    Node *tree_ = nullptr;

public:
    SegTree(const std:: vector<int>& source): tree_ (new Node(0,source.size(), source)){}
    ~SegTree(){
        tree_->~Node();
        delete tree_;
    }
    int bigsumm(int left, int right, Node* vertice=nullptr){
        if (vertice == nullptr)
            vertice = tree_;
        if (left<vertice->left && right>=vertice->right){
            return vertice->summ;
        }
        int summ = 0;
        if (left<(vertice->left+vertice->right)/2){
            summ+=bigsumm(left, right, vertice->child1);
        }
        if (right>(vertice->left+vertice->right)/2){
            summ+=bigsumm(left, right, vertice->child2);
        }
        return summ;
    }
};

int main(){
    SegTree a(std::vector<int>({1, 2, 3, 4, 5, 6, 8, 7}));
    std::cout<<a.bigsumm(1, 3);
}