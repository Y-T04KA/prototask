#include <iostream>
#include <string>
#include <fstream>
#include "serialize.cpp"
//#include "protobuf/work.pb.h"
#include "DelimetedMessagesStreamParser.h"

prototask::WrapperMessage makeMessage(int mode){//изначально эта фукция была в serialize.cpp, но там линкер начал
    prototask::WrapperMessage wm; //бухтеть, мол я функцию определяю и там и тут, а теперь тут она почему-то определяется
    switch (mode) {//без инклуда. Или он подтягивается из сериалайза?
        default:
        {
            prototask::FastResponse fr;
            fr.set_current_date_time("19851019T333");
            wm.set_allocated_fast_response(&fr);
            return wm;
        }
    }
}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::vector<char> messages;
    auto eh = makeMessage(1);
    serializeDelimited<prototask::WrapperMessage>(eh);
    //serializeDelimited() - тут надо будет генерить данные и как-то совать в messages

    //typedef DelimitedMessagesStreamParser<WrapperMessage> Parser;
    //Parser parser;

    // идем по одному байту по входному потоку сообщений
    //for(const char byte, messages){
//        const std::list<PointerToConstValue>& parsedMessages = parser.parse(std::string(1, byte));
//        for(const PointerToConstValue& value, parsedMessages)
//        {
//            // добавляем куда-то все сообщения
//        }
//
//
//    }

    // тут код проверки, что все сообщения расшифровались верно
    return 0;
}
