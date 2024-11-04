#pragma once

#include <WiFi.h>
#include <HTTPClient.h>
#include <NetworkClientSecure.h>

#include "EnvironmentData.hpp"

namespace Environment
{
  class SensorsAPI
  {
    public:
      SensorsAPI(String postURI);
      int postData(const Data& data);

    private:
      String createURIWithParams(const Data& data);

      NetworkClientSecure m_client{};
      HTTPClient m_https{};
      
      String m_postURI;
  };
}

