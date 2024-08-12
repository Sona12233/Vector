#include "headers/Vector.hpp"

#include <gtest/gtest.h>

TEST(VectorInt, Size)
{
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
}

TEST(VectorInt, SizeAndValueConstructor)
{
    Vector<int> v(5, 3);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 3);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 3);
    EXPECT_EQ(v[4], 3);
}

TEST(VectorInt, MaxSize)
{
    Vector<int> v;
    unsigned long result = 18446744073709551615UL;
    EXPECT_EQ(v.max_size(), result);
}

TEST(VectorInt, Capacity)
{
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorInt, Reserve)
{
    Vector<int> v(5);
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorInt, Resize)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    v.resize(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
    EXPECT_EQ(v[2], 0);
}

TEST(VectorInt, ResizeBack)
{
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    v.resize(3);
    EXPECT_EQ(v.size(), 3);
}

TEST(VectorInt, Clear)
{
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    v.clear();
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorInt, PushBackSizeIsZero)
{
    Vector<int> v;

    v.push_back(5);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 1);
    EXPECT_EQ(v[0], 5);

    v.push_back(2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 2);
    EXPECT_EQ(v[1], 2);

    v.push_back(9);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 4);
    EXPECT_EQ(v[2], 9);
}

TEST(VectorInt, PushBackSizeNotZero)
{
    Vector<int> v(5);
    v.push_back(5);
    EXPECT_EQ(v.size(), 6);
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_EQ(v[5], 5);
}

TEST(VectorInt, PopBack)
{
    Vector<int> v;
    v.push_back(5);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 1);
    EXPECT_EQ(v[0], 5);

    v.pop_back();
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 1);
}

TEST(VectorInt, EqualityAndUnequality)
{
    Vector<int> v1(3, 2); /// 222
    Vector<int> v2(3, 3); /// 333
    Vector<int> v3(4, 1); /// 1111
    EXPECT_TRUE(v1 < v2);
    EXPECT_TRUE(v1 <= v3);
    EXPECT_TRUE(v2 > v1);
    EXPECT_TRUE(v2 >= v1);
    EXPECT_TRUE(v2 >= v2);
    EXPECT_TRUE(v2 == v2);
    EXPECT_TRUE(v1 != v2);
}

TEST(ConstItertor, AddAndSubtract)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Vector<int>::const_iterator it = v.begin();
    ++it;
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 2);
    it--;
    EXPECT_EQ(*it, 1);
    it += 2;
    EXPECT_EQ(*it, 3);
    it -= 2;
    EXPECT_EQ(*it, 1);
    it = it + 2;
    EXPECT_EQ(*it, 3);
    it = it - 2;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it[2], 3);
}

TEST(Itertor, AddAndSubtract1)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Vector<int>::iterator it = v.begin();
    ++it;
    EXPECT_EQ(*it, 2);
    it++;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 2);
    it--;
    EXPECT_EQ(*it, 1);
    it += 2;
    EXPECT_EQ(*it, 3);
    it -= 2;
    EXPECT_EQ(*it, 1);
    it = it + 2;
    EXPECT_EQ(*it, 3);
    it = it - 2;
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it[2], 3);
}

TEST(Vector, Beginend)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

TEST(Vector, RBeginRend)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    for (Vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << std::endl;
    }
}

TEST(Vector, RangeConstructor)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    Vector<int>::const_iterator itBegin = v.begin();
    Vector<int>::const_iterator itEnd = v.end();

    Vector<int> v1(itBegin, itEnd);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);
    EXPECT_EQ(v1[3], 4);
    EXPECT_EQ(v1[4], 5);
}

TEST(Vector, Insert)
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    EXPECT_EQ(v.size(), 5);

    Vector<int>::iterator position = v.begin();
    const int a = 2;
    v.insert(position, 3, a);

    EXPECT_EQ(v.size(), 8);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 0);
    EXPECT_EQ(v[4], 1);
    EXPECT_EQ(v[5], 2);
    EXPECT_EQ(v[6], 3);
    EXPECT_EQ(v[7], 4);
}

TEST(Vector, InsertBySize)
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    EXPECT_EQ(v.size(), 5);

    Vector<int>::iterator position = v.begin();
    Vector<int>::iterator finalPosition = v.insert(position, 2);

    EXPECT_EQ(v.size(), 6);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 0);
    EXPECT_EQ(v[2], 1);
    EXPECT_EQ(v[3], 2);
    EXPECT_EQ(v[4], 3);
    EXPECT_EQ(v[5], 4);
}

TEST(Vector, InsertByRange)
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    EXPECT_EQ(v.size(), 5);

    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);

    Vector<int>::iterator position = v.begin();
    v.insert(position, v1.begin(), v1.end() - 1);

    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 0);
    EXPECT_EQ(v[3], 1);
    EXPECT_EQ(v[4], 2);
    EXPECT_EQ(v[5], 3);
    EXPECT_EQ(v[6], 4);
}

TEST(Vector, Erase)
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    EXPECT_EQ(v.size(), 5);

    Vector<int>::iterator position = v.begin() + 2;
    Vector<int>::iterator finalPosition = v.erase(position);

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(Vector, EraseByRange)
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    EXPECT_EQ(v.size(), 6);

    Vector<int>::iterator finalPosition = v.erase(v.begin() + 1, v.begin() + 3);

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
    EXPECT_EQ(v[3], 5);
}

TEST(Vector, EraseByRange1)
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);

    EXPECT_EQ(v.size(), 10);

    Vector<int>::iterator finalPosition = v.erase(v.begin() + 2, v.begin() + 8);

    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 8);
    EXPECT_EQ(v[3], 9);
}

int
main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
