#include "DelimetedMessagesStreamParser.hpp"
#include "gtest/gtest.h"

class DmspTest : public ::testing::Test{};

typedef DelimetedMessagesStreamParser<prototask::WrapperMessage> Parser;

TEST(DmspTest, SingleFastResponse) {
    std::string reference = "20230926T192839.111";
    auto sample = makeMessage(1, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (value->has_fast_response() and !value->has_slow_response() and !value->has_request_for_slow_response() and !value->has_request_for_fast_response()){
                ASSERT_EQ(reference,value->mutable_fast_response()->current_date_time());
            }
        }
    }
}

TEST(DmspTest, SingleSlowResponse) {
    std::string reference = "28";
    auto sample = makeMessage(2, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (!value->has_fast_response() and value->has_slow_response() and !value->has_request_for_slow_response() and !value->has_request_for_fast_response()){
                ASSERT_EQ(std::stoi(reference),value->mutable_slow_response()->connected_client_count());
            }
        }
    }
}

TEST(DmspTest, SingleFastRequest) {
    std::string reference = "28";
    auto sample = makeMessage(3, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (!value->has_fast_response() and !value->has_slow_response() and !value->has_request_for_slow_response() and value->has_request_for_fast_response()){
                ASSERT_TRUE(value->has_request_for_fast_response());
            }
        }
    }
}

TEST(DmspTest, SingleSlowRequest) {
    std::string reference = "14";
    auto sample = makeMessage(4, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    std::vector<char> messages;
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (!value->has_fast_response() and !value->has_slow_response() and value->has_request_for_slow_response() and !value->has_request_for_fast_response()){
                ASSERT_EQ(std::stoi(reference),value->mutable_request_for_slow_response()->time_in_seconds_to_sleep());
            }
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}