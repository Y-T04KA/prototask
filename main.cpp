#include <string>
#include <fstream>
#include "serialize.cpp"
#include "DelimetedMessagesStreamParser.h"

prototask::WrapperMessage makeMessage(int mode){//изначально эта фукция была в serialize.cpp, но там линкер начал
    prototask::WrapperMessage wm; //бухтеть, мол я функцию определяю и там и тут, а теперь тут она почему-то определяется
    switch (mode) {//без инклуда. Или он подтягивается из сериалайза?
        default:
        {
            wm.mutable_fast_response()->set_current_date_time("19851019T333");//я дебил и заполнял сообщение все это время неправильно. Штош
            return wm;
        }
    }
}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::vector<char> messages;
    auto eh = makeMessage(1);
    auto temp = serializeDelimited<prototask::WrapperMessage>(eh);
    messages.insert(messages.end(),temp->begin(),temp->end());

    typedef DelimetedMessagesStreamParser<prototask::WrapperMessage> Parser;
    Parser parser;

    // идем по одному байту по входному потоку сообщений
    for(const char byte : messages)
    {
//        auto test = std::string(1,byte);
//        int l = byte;
//        std::cout<<l;
        //const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte)); //тут создается строка из одного byte, НО ЗАЧЕМ????
        //const std::list<Parser::PointerToConstValue>& parsedMessages = parser.parse(byte);//пока попробую байт напрямую
        //for(const Parser::PointerToConstValue& value : parsedMessages){
                // добавляем куда-то все сообщения, НО КУДА????
        //}


  }

    // тут код проверки, что все сообщения расшифровались верно
    return 0;
}
