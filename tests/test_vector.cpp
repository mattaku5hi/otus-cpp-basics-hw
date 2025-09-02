#include <gtest/gtest.h>
#include <vector>

#include "../inc/continuous.h"

/*
    Base test fixture for ContainerCont */
class VectorTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

/* Test fixture for basic operations */
class VectorBasicTest : public VectorTest {};

/* Test fixture for element access */
class VectorAccessTest : public VectorTest {};

/* Test fixture for copying operations */
class VectorCopyTest : public VectorTest {};

/* Test fixture for move operations */
class VectorMoveTest : public VectorTest {};

/* Test fixture for iterator operations */
class VectorIteratorTest : public VectorTest {};

/* Test fixture for capacity operations */
class VectorCapacityTest : public VectorTest {};

/* 
    Basic Operations Tests
*/
TEST_F(VectorBasicTest, Creation)
{
    ContainerCont<int> container;
    EXPECT_EQ(container.size(), 0);
    EXPECT_EQ(container.capacity(), 0);
}

TEST_F(VectorBasicTest, PushBack)
{
    ContainerCont<int> container;
    
    container.push_back(1);
    EXPECT_EQ(container.size(), 1);
    EXPECT_EQ(container[0], 1);

    container.push_back(2);
    container.push_back(3);
    EXPECT_EQ(container.size(), 3);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);
}

TEST_F(VectorBasicTest, Insert)
{
    ContainerCont<int> container;
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

TEST_F(VectorBasicTest, Erase)
{
    ContainerCont<int> container;
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
TEST_F(VectorAccessTest, OperatorBracket)
{
    ContainerCont<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(container[i], i);
    }
}

TEST_F(VectorAccessTest, ConstOperatorBracket)
{
    ContainerCont<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    const ContainerCont<int>& constContainer = container;
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(constContainer[i], i);
    }
}

/* Copy Operations Tests */
TEST_F(VectorCopyTest, CopyConstructor)
{
    ContainerCont<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerCont<int> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(copy[i], original[i]);
    }
}

TEST_F(VectorCopyTest, CopyAssignment)
{
    ContainerCont<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerCont<int> assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), original.size());
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(assigned[i], original[i]);
    }
}

/* Move Operations Tests */
TEST_F(VectorMoveTest, MoveConstructor)
{
    ContainerCont<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerCont<int> moved(std::move(original));
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(original.size(), 0);
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(moved[i], i);
    }
}

TEST_F(VectorMoveTest, MoveAssignment)
{
    ContainerCont<int> original;
    for(int i = 0; i < 5; ++i)
    {
        original.push_back(i);
    }

    ContainerCont<int> moved;
    moved = std::move(original);
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(original.size(), 0);
    for(int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(moved[i], i);
    }
}

/* Iterator Tests */
TEST_F(VectorIteratorTest, BasicIteration)
{
    ContainerCont<int> container;
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

TEST_F(VectorIteratorTest, ConstIteration)
{
    ContainerCont<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    const ContainerCont<int>& constContainer = container;
    int expected = 0;
    for(auto it = constContainer.begin(); it != constContainer.end(); ++it)
    {
        EXPECT_EQ(*it, expected++);
    }
}

TEST_F(VectorIteratorTest, IteratorInsert)
{
    ContainerCont<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    auto it = container.begin();
    ++it;
    container.insert(it, 10);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 10);
    EXPECT_EQ(container[2], 1);
    EXPECT_EQ(container[3], 2);
    EXPECT_EQ(container[4], 3);
    EXPECT_EQ(container[5], 4);
}

TEST_F(VectorIteratorTest, IteratorErase)
{
    ContainerCont<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    auto it = container.begin();
    ++it;
    container.erase(it);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
}

/* 
    Capacity Tests
*/
TEST_F(VectorCapacityTest, SizeAndCapacity)
{
    ContainerCont<int> container;
    EXPECT_EQ(container.size(), 0);
    EXPECT_EQ(container.capacity(), 0);

    container.push_back(1);
    EXPECT_EQ(container.size(), 1);
    EXPECT_GE(container.capacity(), 1);
}

TEST_F(VectorCapacityTest, Reserve)
{
    ContainerCont<int> container;
    container.reserve(10);
    EXPECT_EQ(container.size(), 0);
    EXPECT_GE(container.capacity(), 10);
}

TEST_F(VectorCapacityTest, Clear)
{
    ContainerCont<int> container;
    for(int i = 0; i < 5; ++i)
    {
        container.push_back(i);
    }

    container.clear();
    EXPECT_EQ(container.size(), 0);
    EXPECT_EQ(container.capacity(), 0);
}

