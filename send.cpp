


#include "hpp.hpp"

void go(){

  kul::File f("bin/receive/obj/205b20a1453fd8cf-receive.cpp.o");
  if(!f) std::runtime_error("no file");
  Message m;
  {
    kul::io::BinaryReader br(f);
    size_t red1 = 0, red2 = 0, rec = 0;
    uint8_t c2[SIZE];
    do{
      bzero(m.c1, SIZE);
      bzero(  c2, SIZE);
      m.len = red1 = br.read(m.c1, SIZE);
      red2         = br.read(  c2, SIZE);
      auto do_send = [](Message &msg){
        std::ostringstream ss(std::ios::out | std::ios::binary);
        {
            cereal::PortableBinaryOutputArchive oarchive(ss);
            oarchive(msg);
        }
        std::string s1(ss.str());
        kul::http::_1_1PostRequest p("localhost", "peep", 8080);
        p.withBody(s1)
         .withResponse([](const kul::http::_1_1Response& r){});
        p.send();
      };
      if(red2 == 0) m.last = 1;
      if(red1 > 0){
        do_send(m);
      } else break;
      if(red2 > 0){
        bzero(m.c1, SIZE);
        m.len = red2;
        memcpy(m.c1, c2, red2);
        do_send(m);
      }
    }while(red1 > 0);
  }
}

int main(int argc, char* argv[]){
  try{
    go();
  }
  catch(const std::runtime_error &e){
    std::cerr << e.what();
  }
  catch(...){
    std::cerr << "ERROR";
  }
  return 0;
}

