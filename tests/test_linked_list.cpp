#include <gtest/gtest.h>
#include <vector>

#include "../inc/linked_singly.h"

/*
    Base test fixture for ContainerListSingly
*/
class LinkedListTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/* Test fixture for basic operations */
class LinkedListBasicTest : public LinkedListTest {};

/* Test fixture for element access */
class LinkedListAccessTest : public LinkedListTest {};

/* Test fixture for copying operations */
class LinkedListCopyTest : public LinkedListTest {};

/* Test fixture for move operations */
class LinkedListMoveTest : public LinkedListTest {};

/* Test fixture for iterator operations */
class LinkedListIteratorTest : public LinkedListTest {};

/* Basic Operations Tests */
TEST_F(LinkedListBasicTest, Creation)
{
    ContainerListSingly<int> container;
    EXPECT_EQ(container.size(), 0);
}

TEST_F(LinkedListBasicTest, PushBack)
{
    ContainerListSingly<int> container;
    
    container.push_back(1);
    EXPECT_EQ(container.size(), 1);
    EXPECT_EQ(container[0], 1);

    container.push_back(2);
    container.push_back(3);
    EXPECT_EQ(container.size(), 3);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);
}

TEST_F(LinkedListBasicTest, Insert)
{
    ContainerListSingly<int> container;
    container.push_back(1);
    container.push_back(3);

    container.insert(1, 2);
    EXPECT_EQ(container.size(), 3);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);

    container.insert(0, 0);
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 0);
}

TEST_F(LinkedListBasicTest, Erase)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    container.erase(2);
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[2], 3);

    container.erase(0);
    EXPECT_EQ(container.size(), 3);
    EXPECT_EQ(container[0], 1);

    container.erase(container.size() - 1);
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[container.size() - 1], 3);
}

/*
    Element Access Tests
*/
TEST_F(LinkedListAccessTest, OperatorBracket)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(container[i], i);
    }
}

TEST_F(LinkedListAccessTest, ConstOperatorBracket)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    const ContainerListSingly<int>& constContainer = container;
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(constContainer[i], i);
    }
}

/*
    Copy Operations Tests
*/
TEST_F(LinkedListCopyTest, CopyConstructor)
{
    ContainerListSingly<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerListSingly<int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(copy[i], original[i]);
    }
}

TEST_F(LinkedListCopyTest, CopyAssignment)
{
    ContainerListSingly<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerListSingly<int> assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), original.size());
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(assigned[i], original[i]);
    }
}

/*
    Move Operations Tests
*/
TEST_F(LinkedListMoveTest, MoveConstructor)
{
    ContainerListSingly<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerListSingly<int> moved(std::move(original));
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(original.size(), 0);
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(moved[i], i);
    }
}

TEST_F(LinkedListMoveTest, MoveAssignment)
{
    ContainerListSingly<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerListSingly<int> moved;
    moved = std::move(original);
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(original.size(), 0);
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(moved[i], i);
    }
}

/*
    Iterator Tests
*/
TEST_F(LinkedListIteratorTest, BasicIteration)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    int expected = 0;
    for(auto it = container.begin(); it != container.end(); ++it)
    {
        EXPECT_EQ(*it, expected++);
    }
}

TEST_F(LinkedListIteratorTest, ConstIteration)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    const ContainerListSingly<int>& constContainer = container;
    int expected = 0;
    for(auto it = constContainer.begin(); it != constContainer.end(); ++it)
    {
        EXPECT_EQ(*it, expected++);
    }
}

TEST_F(LinkedListIteratorTest, IteratorInsert)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    auto it = container.begin();
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(it.getValue(), 0);
    
    ++it;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it.getValue(), 1);
    
    auto newIt = container.insert(it, 10);
    EXPECT_EQ(*newIt, 10);
    EXPECT_EQ(newIt.getValue(), 10);
    EXPECT_EQ(container[1], 10);
}

TEST_F(LinkedListIteratorTest, IteratorErase)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    auto it = container.begin();
    ++it;  // Points to 1
    
    auto nextIt = container.erase(it);  // Should point to 2
            
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
    
    EXPECT_EQ(*nextIt, 2);
    
    it = nextIt;
    EXPECT_EQ(*it, 2);
    
    nextIt = container.erase(it);
    
    EXPECT_EQ(container.size(), 3);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 3);
    EXPECT_EQ(container[2], 4);
    EXPECT_EQ(*nextIt, 3);
}

TEST_F(LinkedListIteratorTest, EraseFromBeginning)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    auto it = container.begin();
    auto nextIt = container.erase(it);

    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
    EXPECT_EQ(*nextIt, 1);
}

TEST_F(LinkedListIteratorTest, EraseFromEnd)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    auto it = container.begin();
    ++it;
    ++it;
    ++it;
    ++it;  // Points to last element
    
    auto nextIt = container.erase(it);
    
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
    EXPECT_EQ(container[2], 2);
    EXPECT_EQ(container[3], 3);
    EXPECT_EQ(nextIt, container.end());
}

TEST_F(LinkedListBasicTest, Clear)
{
    ContainerListSingly<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    container.clear();
    EXPECT_EQ(container.size(), 0);
}


