#include <gtest/gtest.h>
#include "Tree.h"

TEST(BinarySearchTreeTest, Insertion) {
    BinarySearchTree bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    EXPECT_EQ(bst.root->value, 5);
    EXPECT_EQ(bst.root->left->value, 3);
    EXPECT_EQ(bst.root->right->value, 7);
}

TEST(BinarySearchTreeTest, Search) {
    BinarySearchTree bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    EXPECT_TRUE(bst.search(3));
    EXPECT_TRUE(bst.search(7));
    EXPECT_FALSE(bst.search(10));
}

TEST(BinarySearchTreeTest, Deletion) {
    BinarySearchTree bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.remove(3);
    EXPECT_FALSE(bst.search(3));
}