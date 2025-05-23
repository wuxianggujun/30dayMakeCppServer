//
// Created by WuXiangGuJun on 2024/1/4.
//

#pragma once

#include <cassert>
#include <stdexcept>

#define OS_LINUX

// Macros to disable copying and moving
#define DISALLOW_COPY(cname)                             \
  cname(const cname &) = delete;            /* NOLINT */ \
  cname &operator=(const cname &) = delete; /* NOLINT */

#define DISALLOW_MOVE(cname)                        \
  cname(cname &&) = delete;            /* NOLINT */ \
  cname &operator=(cname &&) = delete; /* NOLINT */

#define DISALLOW_COPY_AND_MOVE(cname) \
  DISALLOW_COPY(cname);               \
  DISALLOW_MOVE(cname);

#define ASSERT(expr, message) assert((expr) && (message))

#define UNREACHABLE(message) throw std::logic_error(message)