#include <iostream>
#include "work.pb.h"
/*!
       * \brief Расшифровывает сообщение, предваренное длиной из массива байтов.
       *
       * \tparam Message Тип сообщения, для работы с которым предназначена данная функция.
       *
       * \param data Указатель на буфер данных.
       * \param size Размер буфера данных.
       * \param bytesConsumed Количество байт, которое потребовалось для расшифровки сообщения в случае успеха.
       *
       * \return Умный указатель на сообщение. Если удалось расшифровать сообщение, то он не пустой.
       */
//уровень низкий вообще жесть -- получаем байты, отдаем сообщение
template<typename Message>
//std::shared_ptr<Message> parseDelimeted(const void* data, size_t size, size_t* bytesConsumed = 0){ оригинальная строчка
std::shared_ptr<Message> parseDelimeted(const std::vector<char> data, size_t size, size_t* bytesConsumed = 0){
    Message msg;
    google::protobuf::io::ArrayInputStream array_input(&data[0], data.size());
    google::protobuf::io::CodedInputStream coded_input(&array_input);
    uint32_t sizeInternal;
    coded_input.ReadVarint32(&sizeInternal);
    google::protobuf::io::CodedInputStream::Limit lim = coded_input.PushLimit(sizeInternal);
    msg.ParseFromCodedStream(&coded_input);
    coded_input.PopLimit(lim);
    //auto retval = std::make_shared<Message>(msg);
    return std::shared_ptr<Message>(static_cast<const std::shared_ptr<prototask::WrapperMessage>>(msg));
}

//size_t parseSize(std::vector<char> input){
//    google::protobuf::io::ArrayInputStream array_input(&input[0], input.size());
//    google::protobuf::io::CodedInputStream coded_input(&array_input);
//    uint32_t size;
//    coded_input.ReadVarint32(&size);
//    return size;
//}