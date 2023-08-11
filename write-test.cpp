#include <fstream>
#include <string>
#include "protobuf/work.pb.h"
#include "protobuf/addressbook.pb.h"


int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    prototask::WrapperMessage wm;
    //auto wm = std::shared_ptr<google::protobuf::Message>(new prototask::WrapperMessage);
    int mode = 1;
    std::string file, datetime;
    prototask::FastResponse fr;
    datetime = "31121488";
    fr.set_current_date_time(datetime);
    wm.set_allocated_fast_response(&fr);
    file = "proto1.pb";
    switch (mode) {
        case 1:{
            //prototask::FastResponse fr;
            //datetime = "31121488";
            //fr.set_current_date_time(datetime);
            //wm.set_allocated_fast_response(&fr);
            //file = "proto1.pb";
            break;
        };
        case 2:{
            prototask::SlowResponse sr;
            sr.set_connected_client_count(26);
            wm.set_allocated_slow_response(&sr);
            wm.clear_fast_response();
            wm.clear_request_for_fast_response();
            wm.clear_request_for_slow_response();
            file = "proto2.pb";
            break;
        };
        case 3:{
            prototask::RequestForFastResponse rfr;
            rfr.New();
            wm.set_allocated_request_for_fast_response(&rfr);
            wm.clear_fast_response();
            wm.clear_slow_response();
            wm.clear_request_for_slow_response();
            file = "proto3.pb";
            break;
        };
        case 4:{
            prototask::RequestForSlowResponse rsr;
            rsr.set_time_in_seconds_to_sleep(25);
            wm.set_allocated_request_for_slow_response(&rsr);
            wm.clear_slow_response();
            wm.clear_fast_response();
            wm.clear_request_for_fast_response();
            file = "proto4.pb";
            break;
        };
        default:{
            prototask::FastResponse fr;
            fr.set_current_date_time("31121488");
            wm.set_allocated_fast_response(&fr);
            prototask::SlowResponse sr;
            sr.set_connected_client_count(26);
            wm.set_allocated_slow_response(&sr);
            prototask::RequestForFastResponse rfr;
            rfr.New();
            wm.set_allocated_request_for_fast_response(&rfr);
            prototask::RequestForSlowResponse rsr;
            rsr.set_time_in_seconds_to_sleep(25);
            wm.set_allocated_request_for_slow_response(&rsr);
            file = "proto_all.pb";
        };
    }
    std::fstream output(file,std::ios::out | std::ios::trunc | std::ios::binary);
    //if (!wm.SerializeToOstream(&output)){
    //    std::cerr<<"failed to write\n";
    //    return -1;
    //}

    std::cout<<wm.SerializeAsString()<<std::endl;
    output.close();
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
