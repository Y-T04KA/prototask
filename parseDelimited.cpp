#include "serialize.cpp"
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
std::shared_ptr<Message> parseDelimeted(const void* data, size_t size, size_t* bytesConsumed = nullptr){
    Message msg;
    google::protobuf::io::ArrayInputStream array_input(static_cast<const char*>(data), size);
    google::protobuf::io::CodedInputStream coded_input(&array_input);
    uint32_t sizeInternal;
    coded_input.ReadVarint32(&sizeInternal);
    //google::protobuf::io::CodedInputStream::Limit lim = coded_input.PushLimit(sizeInternal);
    msg.ParseFromCodedStream(&coded_input);//изначально я хотел чтобы bytesConsumed писался только в случае успешного парса
    *bytesConsumed = sizeInternal++;//но фукнция почему-то умеет возвращать только фолс
    //coded_input.PopLimit(lim);
    return std::shared_ptr<Message>(new Message{msg});

}

