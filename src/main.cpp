#include "DelimetedMessagesStreamParser.hpp"

void DebugAwfulness(const std::vector<char>& messages){
    prototask::WrapperMessage wm;
    std::string exper;
    std::vector<char> why;
    for (const char byte : messages){
        exper.push_back(byte);
        why.push_back(*std::string(1,byte).c_str());
    }
    std::cout<<exper[0]<<'\n';
    //google::protobuf::io::ArrayInputStream array_input(&exper[0],exper.size());
    google::protobuf::io::ArrayInputStream array_input(&why[0], why.size());
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
    //DebugAwfulness(messages);
    typedef DelimetedMessagesStreamParser<prototask::WrapperMessage> Parser;
    Parser parser;

    if (eh.has_request_for_slow_response()) int c = 1; else int c = 2;

    // идем по одному байту по входному потоку сообщений
    for(const char byte : messages)
    {
        std::cout<<"for iteration\n";
        const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte)); //тут создается строка из одного byte, НО ЗАЧЕМ????
        //верхний уровень -- отдаем байты, складируем сообщения
        for(const Parser::PointerToConstValue& value : parsedMessages){
                 //добавляем куда-то все сообщения, НО КУДА????
                //пусть пока будут в терминал печататься, не знаю
                if (value->has_fast_response()){
                    std::cout<<"Have fast response: "<< value->mutable_fast_response()->current_date_time()<<"\n";
                }
                if (value->has_slow_response()){
                    std::cout<<"Have slow response: "<< value->mutable_slow_response()->connected_client_count()<<'\n';
                }
                if (value->has_request_for_fast_response()){
                    std::cout<<"Have fast request\n";
                }
                if (value->has_request_for_slow_response()){
                    std::cout<<"Have slow request: "<< value->mutable_request_for_slow_response()->time_in_seconds_to_sleep()<<'\n';
                };
        }


  }

    // тут код проверки, что все сообщения расшифровались верно
    return 0;
}
