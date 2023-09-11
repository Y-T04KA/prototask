#include <fstream>
#include <string>
#include "protobuf/work.pb.h"
#if GOOGLE_PROTOBUF_VERSION >= 3012004
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSizeLong())
#else
#define PROTOBUF_MESSAGE_BYTE_SIZE(message) ((message).ByteSize())
#endif

typedef std::vector<char> Data;
typedef std::shared_ptr<const Data> PointerToConstData;
//template <typename Message>
//PointerToConstData serializeDelimeted(const Message& msg){
//    const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(msg);
//    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);
//
//    const PointerConstToData& result = boost::make_shared<Data>(headerSize + messageSize);
//    google::protobuf::uint8* buffer = reinterpret_cast<google::protobuf::uint8*>(&*result->begin());
//
//    google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(messageSize, buffer);
//    msg.SerializeWithCachedSizesToArray(buffer + headerSize);
//
//    return result;
//}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    prototask::WrapperMessage wm;
    //auto wm = std::shared_ptr<google::protobuf::Message>(new prototask::WrapperMessage);
    std::string file, datetime;

    prototask::FastResponse fr;
    datetime = "31121488";
    fr.set_current_date_time(datetime);
    //wm.set_allocated_fast_response(&fr);
    file = "proto1.pb";

    prototask::SlowResponse sr;
    sr.set_connected_client_count(26);
    //wm.set_allocated_slow_response(&sr);
    //file = "proto2.pb";

    prototask::RequestForFastResponse rfr;
    rfr.New();
    //wm.set_allocated_request_for_fast_response(&rfr);
    //file = "proto3.pb";

    prototask::RequestForSlowResponse rsr;
    rsr.set_time_in_seconds_to_sleep(25);
    //wm.set_allocated_request_for_slow_response(&rsr);
    //file = "proto4.pb";

    fr.set_current_date_time("31121488");
    wm.set_allocated_fast_response(&fr);
    sr.set_connected_client_count(26);
    wm.set_allocated_slow_response(&sr);
    rfr.New();
    wm.set_allocated_request_for_fast_response(&rfr);
    rsr.set_time_in_seconds_to_sleep(25);
    wm.set_allocated_request_for_slow_response(&rsr);
    file = "proto5.pb";

    std::ofstream output(file,std::ios::out | std::ios::trunc | std::ios::binary);
    google::protobuf::io::OstreamOutputStream fos(&output);
    google::protobuf::io::CodedOutputStream cos(&fos);
    std::string container;
    wm.SerializeToString(&container);
    int size = PROTOBUF_MESSAGE_BYTE_SIZE(wm);
    cos.WriteVarint32(size);
    cos.WriteRaw(container.data(),size);

//
//    const size_t messageSize = PROTOBUF_MESSAGE_BYTE_SIZE(wm);
//    const size_t headerSize = google::protobuf::io::CodedOutputStream::VarintSize32(messageSize);
//    output->google::protobuf::io::CodedOutputStream::WriteVarint32(messageSize);
//    if (!wm.SerializeToOstream(&output)){
//        std::cerr<<"failed to write\n";
//        return -1;
//    }
//    output<<"some trash data\n";
//    std::cout<<wm.SerializeAsString()<<std::endl;

    output.close();




    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
