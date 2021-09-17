#include <string>
#include <iostream>
#include <functional>
#include <typeinfo>
#include <vector>


template <typename T>
class StandartEqual
{
public:
    static int equal(T v1, T v2);
};

int StandartEqual<int>::equal(int v1, int v2)
{
    if (v1 > v2)
        return 1;
    else if (v1 < v2)
        return -1;
    else
        return 0;
}

int StandartEqual<float>::equal(float v1, float v2)
{
    if (v1 > v2)
        return 1;
    else if (v1 < v2)
        return -1;
    else
        return 0;
}

int StandartEqual<double>::equal(double v1, double v2)
{
    if (v1 > v2)
        return 1;
    else if (v1 < v2)
        return -1;
    else
        return 0;
}

int StandartEqual<std::string>::equal(std::string v1, std::string v2)
{
    return v1.compare(v2);
}

template <typename T>
class BaseBinaryTree
{
public:
    struct Node
    {
        T value;
        Node* left;
        Node* right;
    };

    Node* root;

public:

    void delete_node(Node* node) {
        if (node)
        {
            Node* r = node->right;
            delete_node(node->left);
            delete node;
            node = nullptr;
            delete_node(r);
        }
    }

    ~BaseBinaryTree()
    {
        delete_node(this->root);
    }

    void show_tree()
    {
        _show_tree(root, 0);
    }

protected:

    const int BASIC_INDENT = 10;

    void _create_point(T value, Node*& node)
    {
        node = new Node;
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
    }

    void _show_tree(Node*& node, int indent)
    {
        if (node)
        {

            indent += BASIC_INDENT;

            _show_tree(node->right, indent);

            std::cout << std::endl;
            for (int i = BASIC_INDENT; i < indent; i++)
                std::cout << " ";

            std::cout << node->value << "\n";

            _show_tree(node->left, indent);

        }
    }
};


template <typename T>
class SearchBinaryTree : public BaseBinaryTree<T>
{
private:
    std::function<int(T, T)> equal;

public:
    SearchBinaryTree()
    {
        this->root = nullptr;
        this->equal = StandartEqual<T>().equal;
    }

    SearchBinaryTree(std::function<int(T, T)> equal)
    {
        this->root = nullptr;
        this->equal = equal;
    }
    
    void add_node (T value)
    {
        _add_node(value, this->root);
    }

    BaseBinaryTree<T>::Node* Search(T value, BaseBinaryTree<T>::Node* node)
    {
        if (node)
        {
            if (equal(value, node->value) == 0)
                return node;

            if (equal(value, node->value) < 0)
                return Search(value, node->left);
            else
                return Search(value, node->right);
        }
        else return nullptr;

    }

private:
    void _add_node(T value, BaseBinaryTree<T>::Node*& node)
    {
        if (!node)
            BaseBinaryTree<T>::_create_point(value, node);

        if (equal(value, node->value) < 0)
        {
            if (node->left)
                _add_node(value, node->left);
            else
                BaseBinaryTree<T>::_create_point(value, node->left);
        }

        if (equal(value, node->value) > 0)
        {
            if (node->right)
                _add_node(value, node->right);
            else
                BaseBinaryTree<T>::_create_point(value, node->right);
        }
    }

};


template <typename T>
class BalancedBinaryTree : public BaseBinaryTree<T>
{
public:
    BalancedBinaryTree(std::vector<T>& v)
    {
        this->root = _create_balanced_tree(v, 0, v.size() - 1);
    }

private:
    BaseBinaryTree<T>::Node* _create_balanced_tree(std::vector<T>& v, int start, int end)
    {
        if (end < start)
            return nullptr;

        int mid = (start + end) / 2;

        typename BaseBinaryTree<T>::Node* node = new typename BaseBinaryTree<T>::Node;
        node->value = v[mid];

        node->left = _create_balanced_tree(v, start, mid - 1);
        node->right = _create_balanced_tree(v, mid + 1, end);

        return node;
    }
};
