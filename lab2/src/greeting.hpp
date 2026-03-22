#pragma once

#include <string>
#include <string_view>

#include <docs/definitions/hello.hpp>

namespace lab2::hello {

HelloResponseBody SayHelloTo(HelloRequestBody&& body);

} 