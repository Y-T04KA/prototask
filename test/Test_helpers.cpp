#include "helpers.hpp"
#include "gtest/gtest.h"


class parseDelimitedTest : public ::testing::Test{};

TEST(parseDelimitedTest, SingleFastResponse) {
    std::string reference = "20230926T192839.111";
    auto sample = makeMessage(1, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    size_t size = messages.size();
    auto theTest = parseDelimeted<prototask::WrapperMessage>(static_cast<const void*>(messages.data()),messages.size(),
                                                             &size);
    ASSERT_EQ(reference,theTest->mutable_fast_response()->current_date_time());
    ASSERT_FALSE(theTest->has_slow_response());
    ASSERT_FALSE(theTest->has_request_for_fast_response());
    ASSERT_FALSE(theTest->has_request_for_slow_response());
}

TEST(parseDelimitedTest, SingleSlowResponse) {
    std::string reference = "24";
    auto sample = makeMessage(2, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    size_t size = messages.size();
    auto theTest = parseDelimeted<prototask::WrapperMessage>(static_cast<const void*>(messages.data()),messages.size(),
                                                             &size);
    ASSERT_EQ(std::stoi(reference),theTest->mutable_slow_response()->connected_client_count());
    ASSERT_FALSE(theTest->has_fast_response());
    ASSERT_FALSE(theTest->has_request_for_fast_response());
    ASSERT_FALSE(theTest->has_request_for_slow_response());
}

TEST(parseDelimitedTest, SingleFastRequest) {
    std::string reference = "24";
    auto sample = makeMessage(3, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    size_t size = messages.size();
    auto theTest = parseDelimeted<prototask::WrapperMessage>(static_cast<const void*>(messages.data()),messages.size(),
                                                             &size);
    ASSERT_FALSE(theTest->has_slow_response());
    ASSERT_FALSE(theTest->has_fast_response());
    ASSERT_TRUE(theTest->has_request_for_fast_response());
    ASSERT_FALSE(theTest->has_request_for_slow_response());
}

TEST(parseDelimitedTest, SingleSlowRequest) {
    std::string reference = "88";
    auto sample = makeMessage(4, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    size_t size = messages.size();
    auto theTest = parseDelimeted<prototask::WrapperMessage>(static_cast<const void*>(messages.data()),messages.size(),
                                                             &size);
    ASSERT_EQ(std::stoi(reference),theTest->mutable_request_for_slow_response()->time_in_seconds_to_sleep());
    ASSERT_FALSE(theTest->has_fast_response());
    ASSERT_FALSE(theTest->has_request_for_fast_response());
    ASSERT_FALSE(theTest->has_slow_response());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}