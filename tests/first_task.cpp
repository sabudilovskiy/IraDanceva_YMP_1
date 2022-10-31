#include <gtest/gtest.h>
#include <algorithm>
#include "../src/tasks/first.hpp"

TEST(TaskTests, ReadAndSort10ElemsInverted){
    std::string test_file = "10 9 8 7 6 5 4 3 2 1 0";
    std::stringstream ss{test_file}, ss2{test_file};
    auto forward_list = read_and_sort(ss);
    std::vector<int> vector;
    while (!ss2.eof()){
        int temp;
        ss2 >> temp;
        vector.push_back(temp);
    }
    std::sort(vector.begin(), vector.end());
    ASSERT_EQ(vector.size(), forward_list.size());
    auto it_vector = vector.begin();
    auto it_list = forward_list.begin();
    auto it_end = forward_list.end();
    while (it_list!=it_end){
        EXPECT_EQ(*it_list, *it_vector);
        ++it_list, ++it_vector;
    }
}

TEST(TaskTests, Ok){
    std::string input_file = "10 9 8 7 6 5 4 3 2 1 0";
    std::string expected_file = "0 2 3 4 5 6 7 8 9 10 ";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}

TEST(TaskTests, Ok_random_1){
    std::string input_file = "0 5 8 7 9 3 6 10 2 1 4";
    std::string expected_file = "0 2 3 4 5 6 7 8 9 10 ";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}

TEST(TaskTests, Ok_random_2){
    std::string input_file = "1 8 5 7 6 9 0 2 3 4 10";
    std::string expected_file = "0 2 3 4 5 6 7 8 9 10 ";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}

TEST(TaskTests, Ok_random_3){
    std::string input_file = "1 6 10 7 4 5 0 8 2 9 3";
    std::string expected_file = "0 2 3 4 5 6 7 8 9 10 ";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}

TEST(TaskTests, Ok_random_4){
    std::string input_file = "10 2 9 6 3 5 7 1 4 8 0";
    std::string expected_file = "0 2 3 4 5 6 7 8 9 10 ";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}


TEST(TaskTests, OneNumber){
    std::string input_file = "10";
    std::string expected_file = "10 \n"
                                "Numbers not found";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}

TEST(TaskTests, TwoOddNumbers){
    std::string input_file = "10 10";
    std::string expected_file = "10 10 \n"
                                "Numbers not found";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}

TEST(TaskTests, SixOddNumbers){
    std::string input_file = "10 8 6 4 2 0";
    std::string expected_file = "0 2 4 6 8 10 \n"
                                "Numbers not found";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}

TEST(TaskTests, Empty){
    std::string input_file = "";
    std::string expected_file = "\n"
                                "Numbers not found";
    std::stringstream in {input_file}, out{};
    auto forward_list = read_and_sort(in);
    task_1(forward_list, out);
    std::string got_file = out.str();
    EXPECT_EQ(expected_file, got_file);
}