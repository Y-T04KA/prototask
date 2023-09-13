#include <iostream>
#include "protobuf/work.pb.h"
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
template<typename Message>
//std::shared_ptr<Message> parseDelimeted(const void* data, size_t size, size_t* bytesConsumed = 0){
std::shared_ptr<Message> parseDelimeted(const std::string* data, size_t size, size_t* bytesConsumed = 0){
    prototask::WrapperMessage wm;
    wm.ParseFromString(*data);
    //std::shared_ptr<Message> retval = NULL;
    return wm;
}