#include <iostream>
#include <vector>


#include "continuous.h"
#include "linked_doubly.h"
#include "linked_singly.h"


int main(int argc, char** argv)
{
    ContainerCont<int> continuous;
    ContainerListSingly<int> linkedSingly;
    ContainerListDoubly<int> linkedDoubly;

    std::cout << std::endl << "<<< container " << continuous.getName() << " example >>>" << std::endl;
    for(size_t i = 0; i < 10; i++)
    {
        continuous.push_back(i);
    }

    std::cout << "Print with dereference: ";
    for(auto iter = continuous.begin(); iter != continuous.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::cout << "Print with get(): ";
    for(auto iter = continuous.begin(); iter != continuous.end(); ++iter)
    {
        std::cout << iter.getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "Container 'vector' size: " << continuous.size() << std::endl;

    continuous.erase(2);
    continuous.erase(3);
    continuous.erase(4);
    std::cout << "Print after erasing: ";
    for(auto iter = continuous.begin(); iter != continuous.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    continuous.insert(0, 10);
    std::cout << "Print after inserting at the start: ";
    for(auto iter = continuous.begin(); iter != continuous.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    {
        size_t middle = continuous.size() / 2;
        auto iter = continuous.begin();
        for(size_t i = 0; i < middle; ++i)
        {
            ++iter;
        }
        iter = continuous.insert(iter, 20);

        std::cout << "Print after inserting in the middle: ";
        for(auto iter = continuous.begin(); iter != continuous.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }

    continuous.push_back(30);
    std::cout << "Print after inserting at the end: ";
    for(auto iter = continuous.begin(); iter != continuous.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;





    std::cout << std::endl << "<<< container " << linkedDoubly.getName() << " example >>>" << std::endl;
    for(size_t i = 0; i < 10; i++)
    {
        linkedDoubly.push_back(i);
    }

    std::cout << "Print with dereference: ";
    for(auto iter = linkedDoubly.begin(); iter != linkedDoubly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::cout << "Print with get(): ";
    for(auto iter = linkedDoubly.begin(); iter != linkedDoubly.end(); ++iter)
    {
        std::cout << iter.getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "Container 'doubly-linked list' size: " << linkedDoubly.size() << std::endl;

    linkedDoubly.erase(2);
    linkedDoubly.erase(3);
    linkedDoubly.erase(4);
    std::cout << "Print after erasing: ";
    for(auto iter = linkedDoubly.begin(); iter != linkedDoubly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    linkedDoubly.insert(0, 10);
    std::cout << "Print after inserting at the start: ";
    for(auto iter = linkedDoubly.begin(); iter != linkedDoubly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    {
        size_t middle = linkedDoubly.size() / 2;
        auto iter = linkedDoubly.begin();
        for(size_t i = 0; i < middle; ++i)
        {
            ++iter;
        }
        iter = linkedDoubly.insert(iter, 20);

        std::cout << "Print after inserting in the middle: ";
        for(auto iter = linkedDoubly.begin(); iter != linkedDoubly.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }

    linkedDoubly.push_back(30);
    std::cout << "Print after inserting at the end: ";
    for(auto iter = linkedDoubly.begin(); iter != linkedDoubly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;







    std::cout << std::endl << "<<< container " << linkedSingly.getName() << " example >>>" << std::endl;
    for(size_t i = 0; i < 10; i++)
    {
        linkedSingly.push_back(i);
    }

    std::cout << "Print with dereference: ";
    for(auto iter = linkedSingly.begin(); iter != linkedSingly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    std::cout << "Print with get(): ";
    for(auto iter = linkedSingly.begin(); iter != linkedSingly.end(); ++iter)
    {
        std::cout << iter.getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "Container 'singly-linked list' size: " << linkedSingly.size() << std::endl;

    linkedSingly.erase(2);
    linkedSingly.erase(3);
    linkedSingly.erase(4);
    std::cout << "Print after erasing: ";
    for(auto iter = linkedSingly.begin(); iter != linkedSingly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    linkedSingly.insert(0, 10);
    std::cout << "Print after inserting at the start: ";
    for(auto iter = linkedSingly.begin(); iter != linkedSingly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    {
        size_t middle = linkedSingly.size() / 2;
        auto iter = linkedSingly.begin();
        for(size_t i = 0; i < middle; ++i)
        {
            ++iter;
        }
        iter = linkedSingly.insert(iter, 20);

        std::cout << "Print after inserting in the middle: ";
        for(auto iter = linkedSingly.begin(); iter != linkedSingly.end(); ++iter)
        {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }

    linkedSingly.push_back(30);
    std::cout << "Print after inserting at the end: ";
    for(auto iter = linkedSingly.begin(); iter != linkedSingly.end(); ++iter)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    return 0;
}


