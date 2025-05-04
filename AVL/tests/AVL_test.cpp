#include <gtest/gtest.h>
#include "AVL.h"

TEST(AVLTreeTest, Insertion) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_EQ(tree.root()->value, 20);
}

TEST(AVLTreeTest, Deletion) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.remove(20);
    EXPECT_EQ(tree.root()->value, 30);
}

TEST(AVLTreeTest, Balance) {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_TRUE(tree.isBalanced());
}