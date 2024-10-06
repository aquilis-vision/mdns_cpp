#pragma once

#include <cstdint>
#include <string>
#include <map>

namespace mdns_cpp {

class ServiceRecord {
 public:
  const char *service;
  const char *hostname;
  const char *txt_rec;
  uint32_t address_ipv4;
  uint8_t *address_ipv6;
  uint16_t port;
};


struct QueryResult {
  std::string host;
  std::string ipv4;
  std::string ipv6;
  std::map<std::string, std::string> txt_records;
};

}  // namespace mdns_cpp
