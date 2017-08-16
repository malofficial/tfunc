#pragma once

#include <ostream>
#include <vector>

namespace tst {

  // clang-format off
struct A {bool operator==(const A) const { return true; }};
struct B {bool operator==(const B) const { return true; }};
struct C {bool operator==(const C) const { return true; }};
struct D {bool operator==(const D) const { return true; }};
  // clang-format on

  // A nicety so that Catch can print
  std::ostream &operator<<(std::ostream &os, A const &) {
    os << "A";
    return os;
  }
  std::ostream &operator<<(std::ostream &os, B const &) {
    os << "B";
    return os;
  }
  std::ostream &operator<<(std::ostream &os, C const &) {
    os << "C";
    return os;
  }
  std::ostream &operator<<(std::ostream &os, D const &) {
    os << "D";
    return os;
  }

  // f : A → B
  const auto f = [](A) -> B { return {}; };
  // g : B → C
  const auto g = [](B) -> C { return {}; };
  // h : C → D
  const auto h = [](C) -> D { return {}; };
  // id : T → T
  const auto id = [](auto x) { return x; };

  // Logs which constructor is called by pushing flags into a vector. Also
  // records if an instance was *moved from*!

  struct CtorLogger {
    enum CtorLoggerFlags {
      Default,
      CopyConstructed,
      CopiedFrom,
      MoveConstructed,
      MovedFrom
    };

    std::vector<CtorLoggerFlags> flags;
    CtorLogger() : flags{Default} {}
    CtorLogger(const CtorLogger &orig) : flags{orig.flags} {
      flags.push_back(CopyConstructed);
    }
    CtorLogger(CtorLogger &&orig) : flags{orig.flags} {
      flags.push_back(MoveConstructed);
      orig.flags.push_back(MovedFrom);
    }
  };

  std::ostream &operator<<(std::ostream &os,
                           CtorLogger::CtorLoggerFlags const &flag) {
    switch (flag) {
    case CtorLogger::CtorLoggerFlags::Default:
      os << "Def ";
      break;
    case CtorLogger::CtorLoggerFlags::CopyConstructed:
      os << "CpyCtd ";
      break;
    case CtorLogger::CtorLoggerFlags::CopiedFrom:
      os << "CpyFm ";
      break;
    case CtorLogger::CtorLoggerFlags::MoveConstructed:
      os << "MovCtd ";
      break;
    case CtorLogger::CtorLoggerFlags::MovedFrom:
      os << "MovFm ";
      break;
    default:
      os << "Unknown:";
      os << static_cast<int>(flag) << ' ';
      break;
    }
    return os;
  }

} // namespace tst
