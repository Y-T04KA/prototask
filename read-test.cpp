#include <string>
#include "protobuf/work.pb.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    prototask::WrapperMessage wm;
    std::fstream input("proto_all.pb",std::ios::in | std::ios::binary);
    if (!wm.ParseFromIstream(&input)){
        std::cerr<<"fail to read\n";
        return -1;
    }
    if (wm.has_fast_response()){
        const prototask::FastResponse& fr = wm.fast_response();
        std::cout << fr.current_date_time() << std::endl;
    }
    if (wm.has_slow_response()){
        const prototask::SlowResponse& sr = wm.slow_response();
        std::cout << sr.connected_client_count() << std::endl;
    }
    if (wm.has_request_for_fast_response()){
        std::cout << "fast response!\n";
    }
    if (wm.has_request_for_slow_response()){
        const prototask::RequestForSlowResponse& rsr = wm.request_for_slow_response();
        std::cout << rsr.time_in_seconds_to_sleep();
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
