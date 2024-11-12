#include "EnvironmentSensorsAPI.hpp"

namespace Environment
{

SensorsAPI::SensorsAPI(String postURI) : m_postURI(std::move(postURI))
{
  m_client.setInsecure();
}

int SensorsAPI::postData(const Data& data)
{
  int httpCode{-1};

  if (m_https.begin(m_client, createURIWithParams(data)))
  {
    httpCode = m_https.GET();

    m_https.end();
  }

  return httpCode;
}

String SensorsAPI::createURIWithParams(const Data& data)
{
  return m_postURI + "&field1=" + String(data.temperature) + "&field2=" + String(data.humidity);
}
 
}