#include <iostream>
#include "work.pb.h"
#if GOOGLE_PROTOBUF_VERSION >= 3012004
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong())
#else
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize())
#endif
typedef std::vector<char> Data;
typedef std::shared_ptr<const Data> PointerToConstData;
typedef std::shared_ptr<Data> PointerToData;

template <typename Message>
PointerToConstData serializeDelimited(const Message& msg)
{
    const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);
    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);

    const PointerToData& result = std::make_shared<Data>(headerSize + messageSize);
    google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(&*result->begin());

    google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
    msg.SerializeWithCachedSizesToArray(buffer + headerSize);

    return result;
}

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
    uint32_t sizeInternal;//второй раз считать размер незачем, но проще посчитать размер дважды, чем высчитывать сколько отрезать от буфера чтобы не сломать сообщение целиком
    coded_input.ReadVarint32(&sizeInternal);
    //google::protobuf::io::CodedInputStream::Limit lim = coded_input.PushLimit(sizeInternal);
    msg.ParseFromCodedStream(&coded_input);//изначально я хотел чтобы bytesConsumed писался только в случае успешного парса
    *bytesConsumed = sizeInternal++;//но фукнция почему-то умеет возвращать только фолс
    //coded_input.PopLimit(lim); //лимиты нам тут не нужны ибо класс гарантирует что байты будут ровно на одно сообщение
    return std::shared_ptr<Message>(new Message{msg});

}
