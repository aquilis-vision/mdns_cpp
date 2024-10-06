#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#endif

#include "mdns_cpp/logger.hpp"
#include "mdns_cpp/mdns.hpp"

void onInterruptHandler(int s) {
  std::cout << "Caught signal: " << s << std::endl;
  exit(0);
}

int main() {
  signal(SIGINT, onInterruptHandler);

#ifdef _WIN32
  WSADATA wsaData;
  // Initialize Winsock
  const int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

  if (iResult != 0) {
    std::cout << "WSAStartup failed: " << iResult << "\n";
    return 1;
  }
#endif

  mdns_cpp::Logger::setLoggerSink([](const std::string& log_msg) {
    std::cout << "MDNS_LIBRARY: " << log_msg;
    std::flush(std::cout);
  });

  mdns_cpp::mDNS mdns;
  const std::string service = "_http._tcp.local.";

  auto result = mdns.executeQuery(service);

  for (auto item : result) {
    std::cout << "----------" << std::endl;
    std::cout << item->host << std::endl;
    std::cout << item->ipv4 << std::endl;
    std::cout << item->ipv6 << std::endl;
    std::cout << "TXT Records number:" << item->txt_records.size() << std::endl;
    for (auto txt : item->txt_records) {
      std::cout << txt.first << " = " << txt.second << std::endl;
    }
    std::cout << "----------" << std::endl;
  }

  return 0;
}
