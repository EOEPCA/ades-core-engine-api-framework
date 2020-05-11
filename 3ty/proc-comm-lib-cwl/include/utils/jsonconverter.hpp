
#ifndef T2PC2_JSONENTITY_HPP
#define T2PC2_JSONENTITY_HPP

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <list>
#include <map>
#include <memory>
#include <ostream>

#include <iostream>

namespace json {

using DOCUMENT = rapidjson::Document;
using VALUE = rapidjson::Value;
using POINTER = rapidjson::Pointer;
using CONSTMEMBERITERATOR = rapidjson::Value::MemberIterator;
using STRINBUFFER = rapidjson::StringBuffer;

class JsonConverter {
private:
  void parse() {
    document = std::make_unique<DOCUMENT>();
    document->Parse(theJson.data());

    if (!document->IsObject() && !document->IsArray()) {
      std::string s{"Wrong data json > \r\n"};
      s.append(theJson);
      s.append("<");
      throw std::runtime_error(s);
    }
  }

public:
  JsonConverter() = delete;

  JsonConverter(const JsonConverter &) = delete;

  JsonConverter(JsonConverter &&) = delete;

  explicit JsonConverter(std::string json) {
    theJson = std::move(json);
    parse();
  }

  template <typename... Args>
  static std::string format(const std::string &format, Args... args) {
    size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) +
                  1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(),
                       buf.get() + size - 1); // We don't want the '\0' inside
  }

  template <class T> void as(const std::string &val, T &t) {

    auto res = POINTER(val.data()).Get(*document);
    if (res) {
      t = __GET<T>(res);
    }
  }

  bool exist(const std::string &val) {
    auto theValue = POINTER(val.data()).Get(*document);
    return theValue != nullptr;
  }

  std::list<std::string> getNames(const std::string &val) {
    std::list<std::string> list;
    auto theValue = POINTER(val.data()).Get(*document);
    if (theValue) {
      if (theValue->IsObject()) {
        for (CONSTMEMBERITERATOR itr = theValue->MemberBegin();
             itr != theValue->MemberEnd(); ++itr) {
          if (itr->name.IsString()) {
            list.emplace_back(itr->name.GetString());
          }
        }
      }
    }
    return list;
  }

  int getArrayCount(std::string_view point) {
    if (!document) {
      return -1;
    }

    auto data = POINTER(point.data()).Get(*document);
    if (data && data->IsArray()) {
      return data->GetArray().Size();
    }

    return 0;
  }

  unsigned char isArray(std::string_view point) {
    if (!document) {
      return 0x2;
    }

    auto data = POINTER(point.data()).Get(*document);
    if (data && data->IsArray()) {
      return 0x1;
    }

    return 0x0;
  }

  std::string getTheJson() const {
    if (document) {
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      document->Accept(writer);
      return std::string(buffer.GetString());
    }

    return "";
  }

  static auto getStringRef(const std::string &str) {
    return rapidjson::StringRef(str.data(), std::strlen(str.data()));
  }

  template <class T> T as(const VALUE *pNode) { return __GET<T>(*pNode); }

  template <class T> T as(CONSTMEMBERITERATOR res) {
    return __GET<T>(&res->value);
  }

  template <class T> T as(const std::string &path, const VALUE *pNode) {

    if (pNode) {
      auto node = POINTER(path.data()).Get(*pNode);
      if (node) {
        return __GET<T>(node);
      }
    }

    return T();
  }

  template <class T> T as(const std::string &buff) {

    auto val = POINTER(buff.data()).Get(*document);
    if (val) {
      return __GET<T>(val);
    }
    return T();
  }

  template <class T> T __GET(const VALUE *val) {

    if (val) {

      if (val->Is<T>()) {
        return val->Get<T>();
      }
    }

    throw std::runtime_error("/.....");
  }

private:
  static bool __checkArray(VALUE *val) {
    return (val != nullptr && val->IsArray());
  }

  static bool __checkString(VALUE *val) {
    return (val != nullptr && val->IsString());
  }

private:
  std::string theJson;
  std::unique_ptr<DOCUMENT> document{nullptr};

public:
  DOCUMENT *getDocument() { return document.get(); }
};

template <> std::string JsonConverter::__GET<std::string>(const VALUE *val) {
  if (val) {
    std::string str;
    if (val->IsString()) {
      str = val->GetString();
    } else if (val->IsNull()) {
    } else if (val->IsUint()) {
      str = std::to_string(val->GetUint());
    } else if (val->IsBool()) {
      if (val->IsTrue()) {
        str = "true";
      } else {
        str = "false";
      }
    } else if (val->IsNumber()) {
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      val->Accept(writer);
      return std::string(buffer.GetString());

    } else if (val->IsObject() || val->IsArray()) {
      rapidjson::StringBuffer buffer;
      rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
      val->Accept(writer);
      return std::string(buffer.GetString());
    }
    return str;
  }
  return "";
}

template <>
std::map<std::string, std::string>
JsonConverter::__GET<std::map<std::string, std::string>>(const VALUE *init) {

  std::map<std::string, std::string> map{};

  if (init)
    if (init->IsObject()) {
      for (auto itr = init->MemberBegin(); itr != init->MemberEnd(); ++itr) {
        if (itr->name.IsString() /*&& itr->value.IsString()*/) {
          map[itr->name.GetString()] = __GET<std::string>(&itr->value);
        }
      }
    }

  return map;
}

template <>
std::list<std::string>
JsonConverter::__GET<std::list<std::string>>(const VALUE *init) {

  std::list<std::string> list;

  if (init && init->IsArray()) {
    for (auto &itr : init->GetArray()) {
      if (itr.IsString()) {
        list.emplace_back(itr.GetString());
      }
    }
  }

  return list;
}

template <>
std::list<std::pair<std::string, std::string>>
JsonConverter::__GET<std::list<std::pair<std::string, std::string>>>(
    const VALUE *init) {

  std::list<std::pair<std::string, std::string>> list{};

  if (init)
    if (init->IsObject()) {
      for (auto itr = init->MemberBegin(); itr != init->MemberEnd(); ++itr) {
        if (itr->name.IsString() /*&& itr->value.IsString()*/) {
          // map[itr->name.GetString()] = __GET<std::string>(&itr->value);

          list.emplace_back(std::pair<std::string, std::string>(
              itr->name.GetString(),
              __GET<std::string>(&itr->value) /*itr->value.GetString()*/));
        }
      }
    }

  return list;
}

} // namespace json

#endif
