

#include "hpp.hpp"

class FileWriter{
public:
  std::unique_ptr<kul::io::BinaryWriter> bw;
};

class Server : public kul::http::Server{
 private:
  std::atomic<bool> busy;
  FileWriter fw;
 public:
  Server(const uint16_t port = 8080) : kul::http::Server(port){}

  kul::http::_1_1Response respond(const kul::http::A1_1Request& req) {
    Message m;
    std::istringstream iss(req.body());
    {
        cereal::PortableBinaryInputArchive iarchive(iss);
        iarchive(m);
    }
    if(fw.bw == nullptr) fw.bw.reset(new kul::io::BinaryWriter(kul::File("bin/receive/obj/nah.o")));
    for(size_t i = 0; i < m.len; i++) (*fw.bw) << m.c1[i];
    if(m.last) fw.bw.reset();
    kul::http::_1_1Response r;
    return r.withBody("PROVIDED BY KUL: " + req.method())
        .withDefaultHeaders();
  }

  void operator()(){
    try{
      start();
    }
    catch(const std::runtime_error &e){
      KLOG(ERR) << e.what();
    }
    catch(...){
      KLOG(ERR) << "UNKNOWN ERROR";
    }
  }
};

int main(int argc, char* argv[]){

  kul::Signal sig;
  {
    Server ser;
    kul::Thread th(std::ref(ser));
    sig.intr([&](int16_t) {
      KERR << "Interrupted";
      th.interrupt();
    });
    th.run();
    th.join();
  }

  return 0;
}
