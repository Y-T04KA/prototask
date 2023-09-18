#include <string>
#include <fstream>
#include "serialize.cpp"
#include "DelimetedMessagesStreamParser.h"

size_t testSize = 0;

prototask::WrapperMessage makeMessage(int mode){//изначально эта фукция была в serialize.cpp, но там линкер начал
    prototask::WrapperMessage wm; //бухтеть, мол я функцию определяю и там и тут, а теперь тут она почему-то определяется
    switch (mode) {//без инклуда. Или он подтягивается из сериалайза?
        case 1:{
            wm.mutable_fast_response()->set_current_date_time("19851019T333");
            testSize = wm.ByteSizeLong();
            return wm;
        }
        case 2:{
            wm.mutable_slow_response()->set_connected_client_count(69);
            testSize = wm.ByteSizeLong();
            return wm;
        }
        case 3:{
            wm.mutable_request_for_fast_response()->New();
            testSize = wm.ByteSizeLong();
            return wm;
        }
        case 4:{
            wm.mutable_request_for_slow_response()->set_time_in_seconds_to_sleep(420);
            testSize = wm.ByteSizeLong();
            return wm;
        }
        case 5:{
            wm.mutable_fast_response()->set_current_date_time("SOME VERY LONG STRING JUST TO TEST THE LIMITS OF THIS THING AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAfkdjfdsfjdsjfiopwejfewjfewoifjewofjewofijAAAAAAAAAAAAAAA");
            wm.mutable_slow_response()->set_connected_client_count(4234567890);
            wm.mutable_request_for_fast_response()->New();
            wm.mutable_request_for_slow_response()->set_time_in_seconds_to_sleep(3876543210);
            testSize = wm.ByteSizeLong();
            return wm;
        }
        case 6:{
            wm.mutable_fast_response()->set_current_date_time("ANOTHER SLiGHTY SHORTER MESSAGE AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAfkdjfdsfjdsjfiopwejfewjfewoifjewofjewofijAAAAAAAAAAAAAAA");
            wm.mutable_slow_response()->set_connected_client_count(4234567890);
            wm.mutable_request_for_fast_response()->New();
            wm.mutable_request_for_slow_response()->set_time_in_seconds_to_sleep(3876543210);
            testSize = wm.ByteSizeLong();
            return wm;
        }
        default:
        {
            wm.mutable_fast_response()->set_current_date_time("YYYYMMDDThhmmss.fff");//я дебил и заполнял сообщение все это время неправильно. Штош
            return wm;
        }
    }
}

void DebugAwfulness(std::vector<char> messages){
    prototask::WrapperMessage wm;
    google::protobuf::io::ArrayInputStream array_input(&messages[0], messages.size());
    google::protobuf::io::CodedInputStream coded_input(&array_input);
    uint32_t size;
    coded_input.ReadVarint32(&size);
    google::protobuf::io::CodedInputStream::Limit lim = coded_input.PushLimit(size);
    wm.ParseFromCodedStream(&coded_input);
    coded_input.PopLimit(lim);
}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::vector<char> messages;
    auto eh = makeMessage(6);
    auto temp = serializeDelimited<prototask::WrapperMessage>(eh);
    messages.insert(messages.end(),temp->begin(),temp->end());
    DebugAwfulness(messages);
    typedef DelimetedMessagesStreamParser<prototask::WrapperMessage> Parser;
    Parser parser;

    // идем по одному байту по входному потоку сообщений
    for(const char byte : messages)
    {
        auto test = std::string(1,byte);
        int l = byte;
        std::cout<<l;
        //const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte)); //тут создается строка из одного byte, НО ЗАЧЕМ????
        //const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(byte);//пока попробую байт напрямую
        //for(const Parser::PointerToConstValue& value : parsedMessages){
                // добавляем куда-то все сообщения, НО КУДА????
                //пусть пока будут в терминал печататься, не знаю
        //}


  }

    // тут код проверки, что все сообщения расшифровались верно
    return 0;
}
