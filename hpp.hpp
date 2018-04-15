
#include "kul/http.hpp"

#include "kul/io.hpp"
#include "kul/threads.hpp"
#include "kul/signal.hpp"

#include <cereal/archives/portable_binary.hpp>

const constexpr size_t PORT = 8080;

enum class MessageType : uint16_t { NON = 0, REQUEST, RESPONSE };


class NodeMessage{
 private:
  uint16_t segment = 0, segments = 0;


};