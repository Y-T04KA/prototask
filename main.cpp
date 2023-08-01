#include <iostream>
#include <string>
#include "protobuf/work.pb.h"
#include "protobuf/addressbook.pb.h"


int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    prototask::WrapperMessage wm;
    tutorial::AddressBook addressBook;
    std::cout<<"1 to read, 2 to write\n";
    int mode;
    std::cin>>mode;
    if (mode==1){
        prototask::FastResponse fr;
        fr.set_current_date_time("31121488");
        wm.set_allocated_fast_response(&fr);
        prototask::SlowResponse sr;
        sr.set_connected_client_count(26);
        prototask::RequestForFastResponse rfr;
        rfr.New();
        prototask::RequestForSlowResponse rsr;
        rsr.set_time_in_seconds_to_sleep(25);

    } else {

    }
    return 0;
}
