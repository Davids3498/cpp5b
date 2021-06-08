#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "BinaryTree.hpp"
using namespace ariel;

TEST_CASE("exeptions")
{
    BinaryTree<int> tree;
    //no root
    CHECK_THROWS(tree.add_left(1, 2));
    CHECK_THROWS(tree.add_right(1, 2));
    tree.add_root(2);
    //root exist but no were to put nodes
    CHECK_THROWS(tree.add_left(1, 2));
    CHECK_THROWS(tree.add_right(1, 2));
}

TEST_CASE("adding sons shouldn't throw exeprions")
{
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(3, 6));
    CHECK_NOTHROW(tree.add_right(3, 7));
}

TEST_CASE("Copying Tree")
{
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(3, 6));
    CHECK_NOTHROW(tree.add_right(3, 7));
    int arr[7] = {1, 2, 4, 5, 3, 6, 7};
    int i = 0;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK((*it) == arr[i]);
        i++;
    }

    BinaryTree<int> new_tree{tree};
    i = 0;
    for (auto it1 = new_tree.begin_preorder(); it1 != new_tree.end_preorder(); ++it1)
    {
        CHECK((*it1) == arr[i]);
        i++;
    }
    BinaryTree<int> new_tree = tree;
    i = 0;
    for (auto it2 = new_tree.begin_preorder(); it2 != new_tree.end_preorder(); ++it2)
    {
        CHECK((*it2) == arr[i]);
        i++;
    }
}

TEST_CASE("Change Tree =")
{
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(3, 6));
    CHECK_NOTHROW(tree.add_right(3, 7));
    int arr[7] = {1, 2, 4, 5, 3, 6, 7};
    BinaryTree<int> new_tree{tree};
    int i = 0;

    new_tree.add_root(11);
    CHECK_NOTHROW(tree.add_left(11, 12));
    CHECK_NOTHROW(tree.add_right(11, 13));
    CHECK_NOTHROW(tree.add_left(12, 14));
    CHECK_NOTHROW(tree.add_right(12, 15));
    CHECK_NOTHROW(tree.add_left(13, 16));
    CHECK_NOTHROW(tree.add_right(13, 17));
    int new_arr[7] = {11, 12, 14, 15, 13, 16, 17};

    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK((*it) == arr[i]);
        i++;
    }

    i = 0;
    for (auto it = new_tree.begin_preorder(); it != new_tree.end_preorder(); ++it)
    {
        CHECK((*it) == new_arr[i]);
        i++;
    }
}

TEST_CASE("Preorder iterator")
{
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(3, 6));
    CHECK_NOTHROW(tree.add_right(3, 7));
    int arr[7] = {1, 2, 4, 5, 3, 6, 7};
    int i = 0;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK((*it) == arr[i]);
        i++;
    }
}

TEST_CASE("Inorder iterator")
{
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(3, 6));
    CHECK_NOTHROW(tree.add_right(3, 7));
    int arr[7] = {4, 2, 5, 1, 6, 3, 7};
    int i = 0;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK((*it) == arr[i]);
        i++;
    }
}

TEST_CASE("Postorder iterator")
{
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(3, 6));
    CHECK_NOTHROW(tree.add_right(3, 7));
    int arr[7] = {4, 5, 2, 6, 7, 3, 1};
    int i = 0;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK((*it) == arr[i]);
        i++;
    }
}