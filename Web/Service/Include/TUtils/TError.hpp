#pragma once

#include "OdPlatformSettings.h"
#include <iostream>

#include "CloudLibTools.h"

enum TErrorType {
  INTERNAL_ERROR,
  JSON_PARSE_ERROR,
  CONFIG_ERROR,
  COMMAND_ERROR,
  INVALID_REQUEST,
  SERIALIZE_ERROR,
  CONNECTION_ERROR
};

namespace OdWeb {

 class CLOUD_UTILS_EXPORT TError {
  public:
    TError() {};

    TError(const std::string &str, unsigned error_type)
      : m_text(str), m_error_code(error_type) {}

    std::string text() const {
      return m_text;
    }

    unsigned errorCode() {
      return m_error_code;
    }

  private:
    std::string m_text;
    unsigned m_error_code;
  };
}