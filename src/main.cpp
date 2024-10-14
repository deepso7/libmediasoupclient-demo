#include "mediasoupclient.hpp"
#include "api/peer_connection_interface.h"
#include <iostream>

int main()
{
  try
  {
    // Initialize libmediasoupclient
    mediasoupclient::Initialize();

    std::cout << "libmediasoupclient initialized successfully!" << std::endl;

    // Your code using libmediasoupclient goes here
    // For example, you might create a Device:
    mediasoupclient::Device device;

    std::cout << "Device created successfully!" << std::endl;

    // When you're done, cleanup libmediasoupclient
    mediasoupclient::Cleanup();

    std::cout << "libmediasoupclient cleaned up successfully!" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}