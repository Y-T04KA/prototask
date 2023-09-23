#ifndef PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#define PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#include <list>
#include "parseDelimited.cpp"

template<typename MessageType>
class DelimetedMessagesStreamParser {
public://уровень пониже -- строим кэш и отдаем его на парсинг, получаем одно сообщение, отдаем его наверх
    typedef std::shared_ptr<MessageType> PointerToConstValue;
    std::list<PointerToConstValue> parse(const std::string& data){
        //пока будет внутри хедера, потому что иначе передача PointerToConstValue становится ужасом
        if (messageSize==0 and m_buffer.size()<3){//наберем как минимум три байта чтобы хватило для чтения размера, по идее хватит и двух, но три для верности
            m_buffer.push_back(*data.c_str());
        } else if (messageSize==0 and m_buffer.size()>3) {//достаточно байт чтобы прочитать размер
            m_buffer.push_back(*data.c_str());
            messageSize = parseSizeFromBuffer(m_buffer);
        } else if (messageSize+1==m_buffer.size()){//+1 чтобы не стукнуться об конец вектора
            m_buffer.push_back(*data.c_str());
            auto res = parseDelimeted<MessageType>(m_buffer,messageSize,bytes_consumed);
            retval.push_back(res);
            messageSize=0;//обнуляем чтобы прочитать следующее сообщение
        } else {
            m_buffer.push_back(*data.c_str());
        }
        return retval;
    };

private:
    std::list<PointerToConstValue> retval;
    std::vector<char> m_buffer;
    size_t messageSize = 0;
    size_t* bytes_consumed = nullptr;
    size_t parseSizeFromBuffer(std::vector<char> input){
        google::protobuf::io::ArrayInputStream array_input(&input[0], input.size());
        google::protobuf::io::CodedInputStream coded_input(&array_input);
        uint32_t size;
        coded_input.ReadVarint32(&size);
        return size;
    }
};



#endif //PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
