
#include "kul/http.hpp"

#include "kul/io.hpp"
#include "kul/threads.hpp"
#include "kul/signal.hpp"

#include <cereal/cereal.hpp>
#include <cereal/archives/portable_binary.hpp>

const constexpr size_t PORT = 8080;
const constexpr size_t SIZE = _KUL_TCP_READ_BUFFER_ - 666;

class Message{
public:
  bool last = 0;
  size_t len = 0;
  uint8_t c1[SIZE];

  template <class Archive>
  void serialize(Archive &ar) {
    ar(last);

    ar( cereal::make_size_tag( len ) );

    ar( cereal::binary_data( c1, sizeof(uint8_t) * len ) );
  }
};
