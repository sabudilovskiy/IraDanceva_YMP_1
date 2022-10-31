#include <gtest/gtest.h>
#include <algorithm>
#include "../src/containers/forward_list.hpp"


TEST(BaseTests, PushFront10Elements){
    LMP::forward_list forward_list;
    std::vector<int> test = {0,1,2,3,4,5,6,7,8,9,10};
    for (auto i : test){
        forward_list.push_front(i);
    }
    EXPECT_EQ(forward_list.size(), test.size()) << "проверяем размер листа";
    auto it_test = std::next(test.begin(), test.size() - 1);
    auto it_list = forward_list.begin();
    while (it_list != forward_list.end()){
        EXPECT_EQ(*it_list, *it_test);
        ++it_list;
        if (it_test != test.begin()) --it_test;
    }
}

TEST(BaseTests, Insert){
    LMP::forward_list forward_list;
    std::vector<int> vector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto it_input_list = forward_list.begin();
    for (auto i : vector){
        forward_list.insert_before(it_input_list, i);
        ++it_input_list;
    }
    EXPECT_EQ(forward_list.size(), vector.size()) << "проверяем размер листа";
    auto it_list = forward_list.begin();
    auto it_vector = vector.begin();
    while (it_list != forward_list.end()){
        EXPECT_EQ(*it_list, *it_vector);
        ++it_list;
        ++it_vector;
    }
}

TEST(BaseTests, EraseAfterOneElement){
    LMP::forward_list forward_list;
    std::vector<int> vector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto it_input_list = forward_list.begin();
    for (auto i : vector){
        forward_list.insert_before(it_input_list, i);
        ++it_input_list;
    }
    EXPECT_EQ(forward_list.size(), vector.size()) << "проверяем размер листа";
    size_t index_erased = 4;
    vector.erase(std::next(vector.begin(), index_erased));
    forward_list.erase_after(next(forward_list.begin(), index_erased - 1));
    EXPECT_EQ(forward_list.size(), vector.size()) << "проверяем размер листа";
    auto it_list = forward_list.begin();
    auto it_vector = vector.begin();
    while (it_list != forward_list.end()){
        EXPECT_EQ(*it_list, *it_vector);
        ++it_list;
        ++it_vector;
    }
}

