#pragma once
#include <iostream>
#include <iostream>
#include <stdexcept>

namespace ariel
{
    template <typename T>
    class BinaryTree
    {
    private:
        // inner class
        struct Node
        {
            T val;
            Node *R_Node;
            Node *L_Node;
            Node *Parent;
            Node(const T &value) : val(value), R_Node(nullptr), L_Node(nullptr), Parent(nullptr) {}
        };

        // fields
        Node *ROOT;

    public:
        BinaryTree() : ROOT(nullptr) {}

        BinaryTree(const BinaryTree &other_tree) : ROOT(nullptr)
        {
            add_root(other_tree.ROOT->val);
            CopyTree(other_tree.ROOT);
        }

        BinaryTree(BinaryTree &&other) noexcept
        {
            this->ROOT = other.ROOT;
            other.ROOT = nullptr;
        }

        BinaryTree &operator=(const BinaryTree &other_tree)
        {
            if (this == &other_tree) // make sure not the same tree
            {
                return *this;
            }

            add_root(other_tree.ROOT->val);
            CopyTree(other_tree.ROOT);
            return *this;
        }

        BinaryTree &operator=(BinaryTree &&other_tree) noexcept
        {
            this->ROOT = other_tree.ROOT;
            other_tree.ROOT = nullptr;
            return *this;
        }

        ~BinaryTree()
        {
            if (ROOT != nullptr)
            {
                deleteTree(ROOT);
            }
        }

        BinaryTree &add_root(const T &data)
        {
            if (ROOT == nullptr)
            {
                Node *node = new Node(data);
                ROOT = node;
            }
            else
            {
                ROOT->val = data;
            }
            return *this;
        }

        BinaryTree &add_right(const T &val1, const T &val2)
        {
            if (ROOT == nullptr)
            {
                throw std::invalid_argument{"No root"};
            }
            Node *n = find_node(ROOT, val1);
            if (n == nullptr)
            {
                throw std::invalid_argument{"No such node"};
            }

            if (n->R_Node != nullptr) // we have val1 and it has a right son
            {
                n->R_Node->val = val2; // has right son so we updatuing its val
            }
            else // val1 dont have a right son so we will make it
            {
                Node *newNode = new Node{val2};
                n->R_Node = newNode;
                newNode->Parent = n;
            }
            return *this;
        }

        BinaryTree &add_left(const T &val1, const T &val2)
        {
            if (ROOT == nullptr)
            {
                throw std::invalid_argument{"No root"};
            }
            Node *n = find_node(ROOT, val1);
            if (n == nullptr)
            {
                throw std::invalid_argument{"No such node"};
            }

            if (n->L_Node != nullptr) // we have val1 and it has a left son
            {
                n->L_Node->val = val2; // has left son so we updatuing its val
            }
            else // val1 dont have a left son so we will make it
            {
                Node *newNode = new Node{val2};
                n->L_Node = newNode;
                newNode->Parent = n;
            }
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree)
        {
            return os;
        }

    private:
        Node *find_node(Node *n, const T &data)
        {
            if (n != nullptr)
            {
                if (n->val == data)
                {
                    return n;
                }
                //else
                Node *foundNode = find_node(n->L_Node, data);
                if (foundNode == nullptr)
                {
                    foundNode = find_node(n->R_Node, data);
                }
                return foundNode;
            }
            return nullptr;
        }

        void deleteTree(Node *n)
        {
            if (n->L_Node != nullptr)
            {
                deleteTree(n->L_Node);
            }
            if (n->R_Node != nullptr)
            {
                deleteTree(n->R_Node);
            }
            delete n;
        }

        void CopyTree(const Node *original_tree)
        {
            if (original_tree->R_Node != nullptr)
            {
                add_right(original_tree->val, original_tree->R_Node->val);
                CopyTree(original_tree->R_Node);
            }
            if (original_tree->L_Node != nullptr)
            {
                add_left(original_tree->val, original_tree->L_Node->val);
                CopyTree(original_tree->L_Node);
            }
        }

    public:
        /*preorder itterator*/
        class preorder_it
        {
        private:
            //fields
            Node *pointer_to_current_node;

        public:
            preorder_it(Node *ptr = nullptr) : pointer_to_current_node(ptr) {}

            bool operator!=(const preorder_it &it) const
            {
                return pointer_to_current_node != it.pointer_to_current_node;
            }

            bool operator==(const preorder_it &it) const
            {
                return pointer_to_current_node == it.pointer_to_current_node;
            }

            preorder_it &operator++()
            {
                if (pointer_to_current_node->L_Node != nullptr) // if we can go left we will go left
                {
                    pointer_to_current_node = pointer_to_current_node->L_Node;
                }
                else if (pointer_to_current_node->R_Node != nullptr) // cant go left so try to go right can only go right
                {
                    pointer_to_current_node = pointer_to_current_node->R_Node;
                }
                else // if we can go "down" any more we will need to go to the "closest" right sub tree
                {
                    if (pointer_to_current_node->Parent == nullptr) // in case we only have a root
                    {
                        pointer_to_current_node = nullptr;
                        return *this;
                    }
                    while (pointer_to_current_node->Parent->R_Node == nullptr ||               // we will go "up" as long as there isn't a right sub tree
                           pointer_to_current_node->Parent->R_Node == pointer_to_current_node) // or in the if im the right sub tree
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent; // going "up"
                        if (pointer_to_current_node->Parent == nullptr)            // if we can't go any more to right sub tree we will eventually go back to the root
                        {                                                          // and if we will get back to it we will know that we finished iterating the tree
                            pointer_to_current_node = nullptr;
                            return *this;
                        }
                    }
                    pointer_to_current_node = pointer_to_current_node->Parent->R_Node; // found our first ancestor with a right sub-tree
                }
                return *this;
            }
            preorder_it operator++(int)
            {
                preorder_it Temp = *this;

                if (pointer_to_current_node->L_Node != nullptr) // if we can go left we will go left
                {
                    pointer_to_current_node = pointer_to_current_node->L_Node;
                }
                else if (pointer_to_current_node->R_Node != nullptr) // cant go left so try to go right can only go right
                {
                    pointer_to_current_node = pointer_to_current_node->R_Node;
                }
                else // if we can go "down" any more we will need to go to the "closest" right sub tree
                {
                    if (pointer_to_current_node->Parent == nullptr) // in case we only have a root
                    {
                        pointer_to_current_node = nullptr;
                        return Temp;
                    }

                    while (pointer_to_current_node->Parent->R_Node == nullptr ||               // we will go "up" as long as there isn't a right sub tree
                           pointer_to_current_node->Parent->R_Node == pointer_to_current_node) // or in the if im the right sub tree
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent; // going "up"
                        if (pointer_to_current_node->Parent == nullptr)            // if we can't go any more to right sub tree we will eventually go back to the root
                        {                                                          // and if we will get back to it we will know that we finished iterating the tree
                            pointer_to_current_node = nullptr;
                            return Temp;
                        }
                    }
                    pointer_to_current_node = pointer_to_current_node->Parent->R_Node; // found our first ancestor with a right sub-tree
                }
                return Temp;
            }
            T &operator*() const
            {
                return pointer_to_current_node->val;
            }

            T *operator->() const
            {
                return &(pointer_to_current_node->val);
            }
        };

        preorder_it begin_preorder()
        {
            if (ROOT == nullptr)
            {
                return {nullptr};
            }
            return preorder_it{ROOT};
        }

        preorder_it end_preorder()
        {
            return nullptr;
        }

        /*inorder itterator*/
        class inorder_it
        {
        private: //fields
            Node *pointer_to_current_node;

        public:
            inorder_it(Node *ptr = nullptr) : pointer_to_current_node(ptr) {}

            bool operator!=(const inorder_it &it) const
            {
                return pointer_to_current_node != it.pointer_to_current_node;
            }

            bool operator==(const inorder_it &it) const
            {
                return pointer_to_current_node == it.pointer_to_current_node;
            }

            inorder_it &operator++()
            {
                if (pointer_to_current_node->R_Node != nullptr)
                {
                    pointer_to_current_node = pointer_to_current_node->R_Node;
                    while (pointer_to_current_node->L_Node != nullptr)
                    {
                        pointer_to_current_node = pointer_to_current_node->L_Node;
                    }
                }
                else
                {
                    while (pointer_to_current_node->Parent != nullptr && pointer_to_current_node == pointer_to_current_node->Parent->R_Node)
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent;
                    }
                    pointer_to_current_node = pointer_to_current_node->Parent;
                }

                return *this;
            }

            inorder_it operator++(int)
            {
                inorder_it Temp = *this;
                if (pointer_to_current_node->R_Node != nullptr)
                {
                    pointer_to_current_node = pointer_to_current_node->R_Node;
                    while (pointer_to_current_node->L_Node != nullptr)
                    {
                        pointer_to_current_node = pointer_to_current_node->L_Node;
                    }
                }
                else
                {
                    while (pointer_to_current_node->Parent != nullptr && pointer_to_current_node == pointer_to_current_node->Parent->R_Node)
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent;
                    }
                    pointer_to_current_node = pointer_to_current_node->Parent;
                }

                return Temp;
            }
            T &operator*() const
            {
                return pointer_to_current_node->val;
            }

            T *operator->() const
            {
                return &(pointer_to_current_node->val);
            }
        };

        inorder_it begin_inorder()
        {
            if (ROOT == nullptr)
            {
                return {nullptr};
            }
            Node *temp = ROOT;
            while (temp->L_Node != nullptr)
            {
                temp = temp->L_Node;
            }
            return inorder_it{temp};
        }

        inorder_it end_inorder()
        {
            return {nullptr};
        }

        /*postorder itterator*/
        class postorder_it
        {
        private:
            //fields
            Node *pointer_to_current_node;

        public:
            postorder_it(Node *ptr = nullptr) : pointer_to_current_node(ptr) {}

            bool operator!=(const postorder_it &it) const
            {
                return pointer_to_current_node != it.pointer_to_current_node;
            }

            bool operator==(const postorder_it &it) const
            {
                return pointer_to_current_node == it.pointer_to_current_node;
            }

            postorder_it &operator++()
            {
                if (pointer_to_current_node->Parent == nullptr) // taking care of if we reached the root
                {
                    pointer_to_current_node = nullptr;
                    return *this;
                }

                if (pointer_to_current_node->Parent->L_Node == pointer_to_current_node) //if im the left son for my father
                {
                    if (pointer_to_current_node->Parent->R_Node != nullptr) // if my father have a right son go to him and "as deep as it can"
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent->R_Node;

                        while (pointer_to_current_node->L_Node != nullptr || pointer_to_current_node->R_Node != nullptr) // going "as deep as e can" | right sub-tree
                        {
                            if (pointer_to_current_node->L_Node != nullptr) //we will always want to go left if we can
                            {
                                pointer_to_current_node = pointer_to_current_node->L_Node;
                            }
                            else if (pointer_to_current_node->R_Node != nullptr) // else go right if you can | no actual need for the if statment
                            {
                                pointer_to_current_node = pointer_to_current_node->R_Node;
                            }
                        }
                    }
                    else // else my father have no right son so the next node is my father
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent;
                    }
                }
                else // else im a right child and the next node is my father
                {
                    pointer_to_current_node = pointer_to_current_node->Parent;
                }
                return *this;
            }

            postorder_it operator++(int)
            {
                postorder_it Temp = *this;

                if (pointer_to_current_node->Parent == nullptr) // taking care of if we reached the root
                {
                    pointer_to_current_node = nullptr;
                    return Temp;
                }

                if (pointer_to_current_node->Parent->L_Node == pointer_to_current_node) //if im the left son for my father
                {
                    if (pointer_to_current_node->Parent->R_Node != nullptr) // if my father have a right son go to him and "as deep as it can"
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent->R_Node;

                        while (pointer_to_current_node->L_Node != nullptr || pointer_to_current_node->R_Node != nullptr) // going "as deep as e can" | right sub-tree
                        {
                            if (pointer_to_current_node->L_Node != nullptr) //we will always want to go left if we can
                            {
                                pointer_to_current_node = pointer_to_current_node->L_Node;
                            }
                            else if (pointer_to_current_node->R_Node != nullptr) // else go right if you can | no actual need for the if statment
                            {
                                pointer_to_current_node = pointer_to_current_node->R_Node;
                            }
                        }
                    }
                    else // else my father have no right son so the next node is my father
                    {
                        pointer_to_current_node = pointer_to_current_node->Parent;
                    }
                }
                else // else im a right child and the next node is my father
                {
                    pointer_to_current_node = pointer_to_current_node->Parent;
                }
                return Temp;
            }

            T &operator*() const
            {
                return pointer_to_current_node->val;
            }

            T *operator->() const
            {
                return &(pointer_to_current_node->val);
            }
        };

        postorder_it begin_postorder()
        {
            if (ROOT == nullptr)
            {
                return {nullptr};
            }
            Node *Temp = ROOT;
            while (Temp->L_Node != nullptr || Temp->R_Node != nullptr)
            {
                if (Temp->L_Node != nullptr) //we will always want to go left if we can
                {
                    Temp = Temp->L_Node;
                }
                else if (Temp->R_Node != nullptr) // else go right if you can
                {
                    Temp = Temp->R_Node;
                }
            }
            return postorder_it{Temp}; // pointer_to_current_node = Temp
        }

        postorder_it end_postorder()
        {
            return {nullptr};
        }

        /*for each loop*/
        inorder_it begin()
        {
            if (ROOT == nullptr)
            {
                return {nullptr};
            }
            Node *temp = ROOT;
            while (temp->L_Node != nullptr)
            {
                temp = temp->L_Node;
            }
            return inorder_it{temp};
        }

        inorder_it end()
        {
            return {nullptr};
        }
    };
}
