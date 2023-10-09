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

TEST(DmspTest, DoubleFastResponse) {
    std::vector<char> messages;
    std::string reference = "20230926T192839.111";
    auto sample = makeMessage(1, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    reference = "20250926T192839.222";
    sample = makeMessage(1,reference);
    pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    bool first = false, second = false;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        first = false, second = false;
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (value->has_fast_response() and !value->has_slow_response() and !value->has_request_for_slow_response() and !value->has_request_for_fast_response()){
                if (!first) first= true; else second= true;
            }
        }
    }
    ASSERT_TRUE(first);
    ASSERT_TRUE(second);
}

TEST(DmspTest, DoubleSlowResponse) {
    std::vector<char> messages;
    std::string reference = "22";
    auto sample = makeMessage(2, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    reference = "8";
    sample = makeMessage(2,reference);
    pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    bool first = false, second = false;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        first = false, second = false;
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (!value->has_fast_response() and value->has_slow_response() and !value->has_request_for_slow_response() and !value->has_request_for_fast_response()){
                if (!first) first= true; else second= true;
            }
        }
    }
    ASSERT_TRUE(first);
    ASSERT_TRUE(second);
}

TEST(DmspTest, DoubleFastRequest) {
    std::vector<char> messages;
    std::string reference = "22";
    auto sample = makeMessage(3, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    reference = "8";
    sample = makeMessage(3,reference);
    pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    bool first = false, second = false;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        first = false, second = false;
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (!value->has_fast_response() and !value->has_slow_response() and !value->has_request_for_slow_response() and value->has_request_for_fast_response()){
                if (!first) first= true; else second= true;
            }
        }
    }
    ASSERT_TRUE(first);
    ASSERT_TRUE(second);
}

TEST(DmspTest, DoubleSlowRequest) {
    std::vector<char> messages;
    std::string reference = "04";
    auto sample = makeMessage(4, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    reference = "51";
    sample = makeMessage(4,reference);
    pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());
    Parser parser;
    bool first = false, second = false;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        first = false, second = false;
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (!value->has_fast_response() and !value->has_slow_response() and value->has_request_for_slow_response() and !value->has_request_for_fast_response()){
                if (!first) first= true; else second= true;
            }
        }
    }
    ASSERT_TRUE(first);
    ASSERT_TRUE(second);
}

TEST(DmspTest, QuadAll) {
    std::vector<char> messages;
    std::string reference = "20230926T192839.111";
    auto sample = makeMessage(1, reference);
    auto pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());

    reference = "51";
    sample = makeMessage(2,reference);
    pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());

    reference = "51";
    sample = makeMessage(3,reference);
    pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());

    reference = "33";
    sample = makeMessage(4,reference);
    pointers = serializeDelimited<prototask::WrapperMessage>(sample);
    messages.insert(messages.end(),pointers->begin(),pointers->end());

    Parser parser;
    bool first = false, second = false, third = false, forth = false;
    for(const char byte : messages) {
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
        first = false, second = false, third, forth;
        for(const Parser::PointerToConstValue& value : parsedMessages){
            if (value->has_fast_response()) first= true;
            if (value->has_slow_response()) second= true;
            if (value->has_request_for_fast_response()) third= true;
            if (value->has_request_for_slow_response()) forth= true;
        }
    }
    ASSERT_TRUE(first);
    ASSERT_TRUE(second);
    ASSERT_TRUE(third);
    ASSERT_TRUE(forth);
}

class ProvidedParserTest : public ::testing::Test{};

TEST(ProvidedParserTest,OneFastRequest){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    prototask::WrapperMessage message;
    message.mutable_request_for_fast_response();
    auto data = serializeDelimited(message);
    messages = parser.parse(std::string(data->begin(),data->end()));
    ASSERT_EQ(1,messages.size());
    auto item = messages.front();
    ASSERT_TRUE(item->has_request_for_fast_response());
}

TEST(ProvidedParserTest, SomeFastRequests){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    prototask::WrapperMessage message;
    message.mutable_request_for_fast_response();
    auto data = serializeDelimited(message);
    size_t count = 5;
    std::string stream;
    for (int i = 0; i<count; ++i) stream.append(data->begin(),data->end());
    messages = parser.parse(stream);
    ASSERT_EQ(count,messages.size());
    for(auto &item : messages) ASSERT_TRUE(item->has_request_for_fast_response());
}

TEST(ProvidedParserTest,OneSlowRequest){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    prototask::WrapperMessage message;
    message.mutable_request_for_slow_response()->set_time_in_seconds_to_sleep(0);
    auto data = serializeDelimited(message);
    messages = parser.parse(std::string(data->begin(),data->end()));
    ASSERT_EQ(1,messages.size());
    auto item = messages.front();
    ASSERT_TRUE(item->has_request_for_slow_response());
    EXPECT_EQ(item->request_for_slow_response().time_in_seconds_to_sleep(),
              message.request_for_slow_response().time_in_seconds_to_sleep());
}

TEST(ProvidedParserTest, SomeSlowRequests){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    prototask::WrapperMessage message;
    message.mutable_request_for_slow_response()->set_time_in_seconds_to_sleep(0);
    auto data = serializeDelimited(message);
    size_t count = 5;
    std::string stream;
    for (int i = 0; i<count; ++i) stream.append(data->begin(),data->end());
    messages = parser.parse(stream);
    ASSERT_EQ(count,messages.size());
    for(auto &item : messages) {
        ASSERT_TRUE(item->has_request_for_fast_response());
        EXPECT_EQ(item->request_for_slow_response().time_in_seconds_to_sleep(),
                  message.request_for_slow_response().time_in_seconds_to_sleep());
    }
}

TEST(ProvidedParserTest,SomeRequests){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    prototask::WrapperMessage fastRequest;
    fastRequest.mutable_request_for_fast_response();
    prototask::WrapperMessage slowRequest;
    slowRequest.mutable_request_for_slow_response()->set_time_in_seconds_to_sleep(0);
    auto fReqData = serializeDelimited(fastRequest);
    auto sReqData = serializeDelimited(slowRequest);
    size_t count = 5;
    std::string stream;
    for (int i = 0; i<count; ++i)
        stream.append(std::rand() % 2 > 0 ? std::string(fReqData->begin(),fReqData->end()) : std::string (sReqData->begin(),sReqData->end()));
    messages = parser.parse(stream);
    ASSERT_EQ(count,messages.size());
    for (auto &item : messages){
        ASSERT_TRUE(item->has_request_for_fast_response() || item->has_request_for_slow_response());
        if (item->has_request_for_slow_response()){
            EXPECT_EQ(item->request_for_slow_response().time_in_seconds_to_sleep(),
                      slowRequest.request_for_slow_response().time_in_seconds_to_sleep());
        }
    }
}

TEST(ProvidedParserTest,EmptyData){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    messages = parser.parse("");
    EXPECT_EQ(0,messages.size());
}

TEST(ProvidedParserTest,SlicedData){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    prototask::WrapperMessage message;
    message.mutable_request_for_fast_response();
    auto data = serializeDelimited(message);
    size_t middle = data->size()/2;
    messages = parser.parse(std::string(data->begin(),data->begin()+middle));
    EXPECT_EQ(messages.size(),0);
    messages = parser.parse(std::string(data->begin()+middle,data->end()));
    EXPECT_EQ(messages.size(),1);
    auto item = messages.front();
    ASSERT_TRUE(item->has_request_for_fast_response());
}

TEST(ProvidedParserTest,WrongData){
    Parser parser;
    EXPECT_THROW(parser.parse("\x05wrong"),std::runtime_error);
}

TEST(ProvidedParserTest,CorruptedData){
    std::list<Parser::PointerToConstValue> messages;
    Parser parser;
    prototask::WrapperMessage message;
    message.mutable_fast_response()->set_current_date_time("0");
    auto data = serializeDelimited(message);
    size_t count = 3;
    std::string stream;
    for (int i = 0; i<count; ++i) stream.append(std::string(data->begin(),data->end()));
    stream[data->size()] = '\x03';
    EXPECT_THROW(parser.parse(stream),std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}