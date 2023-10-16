#ifndef PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#define PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#include <list>
#include "helpers.hpp"

template<typename MessageType>
class DelimetedMessagesStreamParser {
public://уровень пониже -- строим кэш и отдаем его на парсинг, получаем одно сообщение, отдаем его наверх
    typedef std::shared_ptr<MessageType> PointerToConstValue;
    std::list<PointerToConstValue> parse(const std::string& data){
        for (auto sym : data) m_buffer.push_back(sym);//now it goes through all symblols in string
        while (isBigEnough()){
            auto res = parseDelimeted<MessageType>(static_cast<const void*>(m_buffer.data()),m_buffer.size(),&bytes_consumed);
            retval.push_back(res);
            prepareForNextMessage();
        }
        return retval;
    };

private:
    std::list<PointerToConstValue> retval;
    std::vector<char> m_buffer;
    size_t messageSize = 0;
    size_t bytes_consumed = 0;
    size_t parseSizeFromBuffer(std::vector<char> input){
        google::protobuf::io::ArrayInputStream array_input(&input[0], input.size());
        google::protobuf::io::CodedInputStream coded_input(&array_input);
        uint32_t size;
        if(!coded_input.ReadVarint32(&size)){
            throw std::runtime_error("Wrong data passed as varint");
        }
        return size;
    }
    bool isBigEnough(){
        if (m_buffer.size()>=2) {
            if (messageSize == 0) messageSize = parseSizeFromBuffer(m_buffer);
            return messageSize + 1 <= m_buffer.size();
        } else return false;
    }
    void prepareForNextMessage(){
        for (int i=0;i!=bytes_consumed;i++) m_buffer.erase(m_buffer.begin());
        messageSize = 0;
        bytes_consumed=0;
    }
};



#endif //PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
