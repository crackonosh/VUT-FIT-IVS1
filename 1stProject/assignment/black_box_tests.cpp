//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include <iostream>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

TEST(EmptyTree, InsertNode)
{
    BinaryTree *bt = new BinaryTree;
    ASSERT_EQ(NULL, bt->GetRoot());
    std::pair<bool, Node_t *> tmp = bt->InsertNode(3);
    bool val = std::get<0>(tmp);
    ASSERT_EQ(true, val);
    ASSERT_EQ(tmp.second, bt->GetRoot());
    delete(bt);
}
TEST(EmptyTree, DeleteNode)
{
    BinaryTree *bt = new BinaryTree;
    bool val = bt->DeleteNode(35);
    ASSERT_EQ(false, val);
    delete(bt);
}
TEST(EmptyTree, FindNode)
{
    BinaryTree *bt = new BinaryTree;
    Node_t *val = bt->FindNode(35);
    ASSERT_EQ(NULL, val);
    delete(bt);
}



TEST(NonEmptyTree, InsertNode)
{
    BinaryTree *bt = new BinaryTree;
    std::pair<bool, Node_t *> hold = bt->InsertNode(35);
    ASSERT_EQ(true, std::get<0>(hold));
    hold = bt->InsertNode(35);
    ASSERT_EQ(false, std::get<0>(hold));
    hold = bt->InsertNode(36);
    ASSERT_EQ(true, std::get<0>(hold));
    delete(bt);
}
TEST(NonEmptyTree, DeleteNode)
{

    BinaryTree *bt = new BinaryTree;
    std::pair<bool, Node_t *> hold = bt->InsertNode(35);
    ASSERT_EQ(true, std::get<0>(hold));
    ASSERT_EQ(false, bt->DeleteNode(36));
    ASSERT_EQ(true, bt->DeleteNode(35));
    delete(bt);
}
TEST(NonEmptyTree, FindNode)
{
    BinaryTree *bt = new BinaryTree;
    std::pair<bool, Node_t *> hold = bt->InsertNode(35);
    ASSERT_EQ(true, std::get<0>(hold));
    ASSERT_EQ(NULL, bt->FindNode(36));
    ASSERT_TRUE(bt->FindNode(35) != NULL);
    delete(bt);
}


TEST(TreeAxioms, Axiom1)
{
    BinaryTree *bt = new BinaryTree;
    std::vector<int> values = {2, 1, 5, 4, 15, 32, 33, 7};
    std::vector<std::pair<bool, Node_t *> > outVal;
    std::vector<BinaryTree::Node_t *> leafNodes;
    bt->InsertNodes(values, outVal);
    bt->GetLeafNodes(leafNodes);

    for (BinaryTree::Node_t *el: leafNodes)
    {
        ASSERT_EQ(BinaryTree::BLACK, el->color);
    }
    delete(bt);
}
TEST(TreeAxioms, Axiom2)
{
    BinaryTree *bt = new BinaryTree;
    std::vector<int> values = {2, 1, 5, 6, 7, 8};
    std::vector<std::pair<bool, Node_t *> > outVal;
    bt->InsertNodes(values, outVal);

    for (std::pair<bool, Node_t *> el: outVal)
    {
        if (el.second->color == BinaryTree::RED)
        {
            ASSERT_EQ(BinaryTree::BLACK, el.second->pLeft->color);
            ASSERT_EQ(BinaryTree::BLACK, el.second->pRight->color);
        }
    }

    delete(bt);
}
TEST(TreeAxioms, Axiom3)
{
    BinaryTree *bt = new BinaryTree; 
    std::vector<int> values = {2, 1, 5, 4, 15, 32, 33, 7};
    std::vector<std::pair<bool, Node_t *> > outVal;
    std::vector<BinaryTree::Node_t *> leafNodes;
    std::vector<int> leafLengths;
    bt->InsertNodes(values, outVal);
    bt->GetLeafNodes(leafNodes);

    for (Node_t *el: leafNodes)
    {
        Node_t *tmp = el;
        int length = 0;
        while (tmp != bt->GetRoot())
        {
            if (tmp->pParent->color != RED)
                length++;
            tmp = tmp->pParent;
        }
        leafLengths.push_back(length);
    }

    int refLength = leafLengths[0];
    for (int l: leafLengths)
    {
        ASSERT_EQ(refLength, l);
    }
}
/*** Konec souboru black_box_tests.cpp ***/
