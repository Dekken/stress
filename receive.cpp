

#include "hpp.hpp"



class SocketServer : public kul::tcp::SocketServer<char>{
 private:
  std::atomic<bool> busy;
  std::ostringstream ss;
  kul::io::BinaryWriter bw;
 public:
  bool handle(
          char*const in,
          const size_t& inLen,
          char*const out,
          size_t& outLen) override {

      ss << in;

      KLOG(INF) << inLen;

      for(size_t i = 0; i < inLen; i++) bw << in[i];

      std::strcpy(out, "OK");
      outLen = 2;
      return false; // if true, close connection
  }
  SocketServer(const uint16_t port = 8080) : kul::tcp::SocketServer<char>(port), ss((std::ios::out | std::ios::binary)), bw(kul::File("bin/receive/obj/nah.o")){

  }
  void operator()(){
    start();
  }
};

int main(int argc, char* argv[]){

  kul::Signal sig;
  {
    SocketServer ser;
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
