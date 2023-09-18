#ifndef PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#define PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#include <iostream>
#include <list>
#include "parseDelimited.cpp"

template<typename MessageType>
class DelimetedMessagesStreamParser {
public:
    typedef std::shared_ptr<const MessageType> PointerToConstValue;
    //std::list<PointerToConstValue> parse(const std::string& data){
    std::list<PointerToConstValue> parse(const char& data){
        //пока будет внутри хедера, потому что иначе передача PointerToConstValue становится ужасом
        if (count == -1){
            size = data;
            count = size;
        } else {
            count--;
            m_buffer.push_back(data);//то есть идея такая что мы сначала читаем размер, а потом билдим буфер этого размера
        }
        if (count!=0){
            //возвращаем что-то как знак ожидания?
        } else {
            std::string payload;
            for (auto sym : m_buffer){
                payload.append(&sym);
            }
            auto res = parseDelimeted<MessageType>(payload,size,bytes_consumed);

        }
    };

private:
    std::vector<char> m_buffer;
    size_t size = -1;
    int count=-1;
    size_t* bytes_consumed = nullptr;
};


#endif //PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
