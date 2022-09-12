//
// Created by jamal on 12/09/2022.
//
#include <gtest/gtest.h>
#include <utils/vector.h>

//template<typename TActual, typename TExpected>
//
//class TestValue {
//    std::vector<TActual> actual;
//    std::vector<TExpected> expected;
//};
//

using std::string;
using std::vector;
using namespace utils::vector;

namespace {

    class TransformTestFixture : public ::testing::Test {
    public:


    protected:
        std::function<string(int &)> int_string_transform_func;

        TransformTestFixture() {
            int_string_transform_func = [](int &val) {
                return std::to_string(val);
            };
        };
    };


    TEST_F(TransformTestFixture, TransformsToNewType) {

        int v1 = 20;
        string expected_value = std::to_string(v1);

        vector<int> base_vector{v1};
        vector<string> expected_vector{expected_value};

        auto actual_vector = transform(base_vector, int_string_transform_func);

        EXPECT_EQ(actual_vector, expected_vector);
    }

    class TransformTestFixtureSizedTest : public TransformTestFixture, public ::testing::WithParamInterface<int> {
    protected:
        using _vector_t = int;

        std::function<_vector_t(_vector_t &)> transform_func;

        TransformTestFixtureSizedTest() {
            // default transform func
            transform_func = [](_vector_t &val) {
                return val;
            };
        }
    };

    TEST_P(TransformTestFixtureSizedTest, ReturnsNewVector) {
        _vector_t vector_size = GetParam();
        vector<_vector_t> base_vector(vector_size);

        auto transform_vector = transform(base_vector, transform_func);

        // if the vectors do not point to the same beginning, then they are not equal, at least in order.
        EXPECT_NE(transform_vector.begin(), base_vector.begin());

        // if they do not have the same address, then they are not the same vector. (a new vector was created)
        EXPECT_NE(std::addressof(transform_vector), std::addressof(base_vector));
    }

    TEST_P(TransformTestFixtureSizedTest, KeepsVectorSize) {
        _vector_t vector_size = GetParam();

        vector<_vector_t> base_vector(vector_size);

        auto transform_vector = transform(base_vector, transform_func);

        // assert it's the same size, and no elements are left over.
        ASSERT_EQ(base_vector.size(), transform_vector.size());
    }

    INSTANTIATE_TEST_SUITE_P(VectorTests,
                             TransformTestFixtureSizedTest,
                             ::testing::Values(
                                     1, 711, 1989, 2013
                             ));
}