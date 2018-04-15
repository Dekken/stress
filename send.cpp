




#include "hpp.hpp"

void go(){

  kul::tcp::Socket<char> sock;
  if (!sock.connect("localhost", PORT))
    throw std::runtime_error("TCP FAILED TO CONNECT!");

  kul::File f("bin/receive/obj/205b20a1453fd8cf-receive.cpp.o");
  if(!f) std::runtime_error("no file");
  char c[_KUL_TCP_READ_BUFFER_], r[_KUL_TCP_READ_BUFFER_];
  {
    kul::io::BinaryReader br(f);
    size_t red = 0, rec = 0;
    do{
      bzero(c, _KUL_TCP_READ_BUFFER_);
      bzero(r, _KUL_TCP_READ_BUFFER_);
      red = br.read(c, _KUL_TCP_READ_BUFFER_ - 1);
      if(red > 0){
        KLOG(INF) << red;
        sock.write(c, red);
        rec = sock.read(r, _KUL_TCP_READ_BUFFER_ - 1);
        KLOG(INF) << r;
      }
    }while(red > 0);
  }
  sock.close();
}

int main(int argc, char* argv[]){
  try{
    go();
  }
  catch(...){
    std::cerr << "ERROR";
  }
  return 0;
}
