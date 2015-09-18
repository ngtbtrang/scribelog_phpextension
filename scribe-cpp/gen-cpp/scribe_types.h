/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef scribe_TYPES_H
#define scribe_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>
#include "fb303_types.h"


namespace scribe { namespace thrift {

struct ResultCode {
  enum type {
    OK = 0,
    TRY_LATER = 1
  };
};

extern const std::map<int, const char*> _ResultCode_VALUES_TO_NAMES;

class LogEntry;

typedef struct _LogEntry__isset {
  _LogEntry__isset() : category(false), message(false) {}
  bool category :1;
  bool message :1;
} _LogEntry__isset;

class LogEntry {
 public:

  static const char* ascii_fingerprint; // = "07A9615F837F7D0A952B595DD3020972";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};

  LogEntry(const LogEntry&);
  LogEntry& operator=(const LogEntry&);
  LogEntry() : category(), message() {
  }

  virtual ~LogEntry() throw();
  std::string category;
  std::string message;

  _LogEntry__isset __isset;

  void __set_category(const std::string& val);

  void __set_message(const std::string& val);

  bool operator == (const LogEntry & rhs) const
  {
    if (!(category == rhs.category))
      return false;
    if (!(message == rhs.message))
      return false;
    return true;
  }
  bool operator != (const LogEntry &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const LogEntry & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const LogEntry& obj);
};

void swap(LogEntry &a, LogEntry &b);

}} // namespace

#endif
