// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <cassert>

using namespace std;

// Add your test cases here
TEST(empty_list) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    ASSERT_EQUAL(empty_list.size(), 0);
}

TEST(empty_list_add) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
    empty_list.push_back(1);
    empty_list.push_back(3);
    ASSERT_EQUAL(empty_list.size(), 2);
    empty_list.pop_front();
    ASSERT_EQUAL(empty_list.size(), 1);
    ASSERT_EQUAL(*(empty_list.begin()), 3);
    empty_list.push_front(2);
    empty_list.push_front(1);
    empty_list.push_front(0);
    empty_list.push_back(4);
    int i = 0;
    for (List<int>::Iterator it = empty_list.begin(); it != empty_list.end(); ++it) {
        ASSERT_EQUAL(*it, i);
        ++i;
    }
    List<int>::Iterator iter = empty_list.begin();
    empty_list.insert(iter, 98);
    ASSERT_EQUAL(*(empty_list.begin()), 98);
    ASSERT_EQUAL(*(++empty_list.begin()), 0);
    empty_list.erase(iter);
    ASSERT_EQUAL(*(++empty_list.begin()), 1);
    empty_list.clear();
    ASSERT_EQUAL(empty_list.size(), 0);
}

TEST(one_element_1) {
    List<int> one_element;
    ASSERT_EQUAL(one_element.size(), 0);
    List<int>::Iterator iter = one_element.begin();
    one_element.insert(iter, 8);
    ASSERT_EQUAL(*(one_element.begin()), 8);
    one_element.push_front(43);
    ASSERT_EQUAL(*(one_element.begin()), 43);
    ASSERT_EQUAL(one_element.size(), 2);
    one_element.pop_back();
    ASSERT_EQUAL(*(one_element.begin()), 43);
    ASSERT_EQUAL(one_element.size(), 1);
    one_element.pop_back();
    ASSERT_EQUAL(one_element.size(), 0);
    ASSERT_TRUE(one_element.empty());
}

TEST(one_element_2) {
    List<int> one_element;
    ASSERT_EQUAL(one_element.size(), 0);
    List<int>::Iterator iter = one_element.begin();
    one_element.insert(iter, 11);
    ASSERT_EQUAL(*(one_element.begin()), 11);
    one_element.push_front(43);
    ASSERT_EQUAL(*(one_element.begin()), 43);
    ASSERT_EQUAL(one_element.size(), 2);
    one_element.pop_front();
    ASSERT_EQUAL(*(one_element.begin()), 11);
    ASSERT_EQUAL(one_element.size(), 1);
    one_element.pop_front();
    ASSERT_EQUAL(one_element.size(), 0);
    ASSERT_TRUE(one_element.empty());
}

TEST(overloaded_assignment_list_1) {
    List<int> list1;
    List<int> list2;
    
    list2.push_back(12);
    list2.push_front(4);
    list1.push_front(0);
    list2.push_back(23);
    list2.push_back(76);
    
    list1 = list2;
    ASSERT_EQUAL(list1.front(), list2.front());
    ASSERT_EQUAL(list1.back(), list2.back());
    ASSERT_EQUAL(*(++list1.begin()), *(++list2.begin()));
}

TEST(overloaded_assignment_list_2) {
    List<int> list1;
    List<int> list2;
    
    list1.push_back(11);
    list1.push_back(9);
    list1.push_front(30);
    list1.push_back(23);
    list1.push_back(8);
    
    list2.push_front(4);
    list2.push_back(12);
    list1.push_front(0);
    list2.push_back(23);
    list2.push_back(76);
    
    list1 = list2;
    ASSERT_EQUAL(list1.front(), list2.front());
    ASSERT_EQUAL(list1.back(), list2.back());
    ASSERT_EQUAL(*(++list1.begin()), *(++list2.begin()));
}

TEST(copy_constructor_list) {
    List<int> list1;
    list1.push_back(34);
    list1.push_back(7);
    list1.push_front(26);
    list1.push_back(29);
    list1.push_front(30);
    
    List<int> list2 = list1;
    ASSERT_EQUAL(*(list2.begin()), 30);
    ASSERT_EQUAL(list1.front(), list2.front());
    ASSERT_EQUAL(list1.back(), list2.back());
    ASSERT_EQUAL(*(++list1.begin()), *(++list2.begin()));
}

TEST(copy_constructor_iterator) {
    List<int> list;
    list.push_back(19);
    list.push_back(91);
    list.push_front(9);
    list.push_front(1);
    
    List<int>::Iterator iter1 = list.begin();
    List<int>::Iterator iter2 = iter1;
    ASSERT_EQUAL(iter2, iter1);
    ASSERT_EQUAL(*(iter2), 1);
    iter1 = (++list.begin());
    iter2 = iter1;
    ASSERT_EQUAL(*(iter2), 9);
    iter1 = (++iter1);
    iter2 = iter1;
    ASSERT_TRUE(iter1 == iter2);
    ASSERT_EQUAL(*(iter2), 19);
    iter1 = (--iter1);
    iter2 = iter1;
    ASSERT_EQUAL(*(iter2), 9);
    iter1 = (--iter1);
    ASSERT_TRUE(iter1 != iter2);
    
    list.push_back(33);
    iter1 = list.end();
    ASSERT_TRUE(iter1 != iter2);
}

TEST(erase) {
    List<int> erase_list;
    erase_list.push_front(10);
    erase_list.push_front(9);
    erase_list.push_front(1);
    erase_list.push_back(6);
    erase_list.push_front(0);
    
    // 0 1 9 10 6
    List<int>::Iterator iter = erase_list.begin();
    // erase first one
    erase_list.erase(iter);
    iter = erase_list.begin();
    ASSERT_EQUAL(*(iter), 1);
    iter = (++erase_list.begin());
    erase_list.erase(iter);
    iter = (++erase_list.begin());
    ASSERT_EQUAL(*(iter), 10);
    iter = (++erase_list.begin());
    iter = (++iter);
    erase_list.erase(iter);
    iter = (++erase_list.begin());
    ASSERT_EQUAL(*(iter), 10);
}

TEST(erase_one_element) {
    List<int> erase_one;
    erase_one.push_back(1);
    
    List<int>::Iterator iter = erase_one.begin();
    erase_one.erase(iter);
    ASSERT_TRUE(erase_one.empty());
    ASSERT_EQUAL(erase_one.size(), 0);
}

TEST(insert_in_empty_list) {
    List<int> insert_list;
    List<int>::Iterator iter = insert_list.begin();
    insert_list.insert(iter, 5);
    iter = insert_list.begin();
    ASSERT_EQUAL(*(iter), 5);
}

TEST(insert_in_list) {
    List<int> insert_list;
  
    insert_list.push_back(23);
    insert_list.push_back(32);

    List<int>::Iterator iter = insert_list.begin();
    insert_list.insert(iter, 5);
    iter = insert_list.begin();
    ASSERT_EQUAL(*(iter), 5);
    // 5 23 32
    iter = (++insert_list.begin());
    insert_list.insert(iter, 9);
    iter = (++insert_list.begin());
    ASSERT_EQUAL(*(iter), 9);
    // 5 9 23 32
    iter = (++iter);
    iter = (++iter);
    iter = (++iter);
    insert_list.insert(iter, 30);
    iter = (insert_list.begin());
    iter = (++iter);
    iter = (++iter);
    iter = (++iter);
    iter = (++iter);
    ASSERT_EQUAL(*(iter), 30);
    // 5 9 23 32 30
}

TEST_MAIN()
