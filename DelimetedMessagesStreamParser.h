#ifndef PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#define PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
#include <iostream>
#include <list>

template<typename MessageType>
class DelimetedMessagesStreamParser {
public:
    typedef std::shared_ptr<const MessageType> PointerToConstValue;
    std::list<PointerToConstValue> parse(const std::string& data);
private:
    std::vector<char> m_buffer;

};




#endif //PROTOTASK_DELIMETEDMESSAGESSTREAMPARSER_H
