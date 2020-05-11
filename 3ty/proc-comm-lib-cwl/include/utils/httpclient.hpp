
#ifndef T2PC2_T2_UTIL_HTTPCLIENT_HPP
#define T2PC2_T2_UTIL_HTTPCLIENT_HPP

#include "beeblebrox/httpcontentfile.hpp"
#include "beeblebrox/httpcontentstring.hpp"
#include "beeblebrox/httpresponsestring.hpp"
#include "beeblebrox/uri.hpp"
#include "zaphodhands/zaphodhand.hpp"

#include <list>
#include <memory>

namespace T2 {

class HttpClient {
 private:
  bool followUri{true};

  long mGetFile(Beeblebrox::Uri::Method method, const std::string &url,
                std::list<std::string> *header, const std::string &path) {
    auto hand = std::make_unique<ZaphodHands::ZaphodHand>();

    auto uri = std::make_unique<Beeblebrox::Uri>(url);
    uri->followUri(followUri);
    *uri << method;
    if (header) {
      for (auto &h : *header) {
        *uri + h;
      }
    }

    auto res = std::make_unique<Beeblebrox::HttpResponseFile>(path);

    *hand << uri.get() << res.get();
    hand->Run();

    return uri->getHttpReturnCode();
  }

  long mGet(Beeblebrox::Uri::Method method, const std::string &url,
            std::list<std::string> *header, std::string &buffer) {
    auto hand = std::make_unique<ZaphodHands::ZaphodHand>();

    auto uri = std::make_unique<Beeblebrox::Uri>(url);
    uri->followUri(followUri);
    *uri << method;
    if (header) {
      for (auto &h : *header) {
        *uri + h;
      }
    }

    auto res = std::make_unique<Beeblebrox::HttpResponseString>();

    *hand << uri.get() << res.get();
    hand->Run();
    buffer.assign(res->getContent());

    return uri->getHttpReturnCode();
  }

  long mPostPut(Beeblebrox::Uri::Method method, const std::string &url,
                std::list<std::string> *header, const std::string &content,
                std::string &buffer) {
    auto hand = std::make_unique<ZaphodHands::ZaphodHand>();

    auto uri = std::make_unique<Beeblebrox::Uri>(url);
    uri->followUri(followUri);
    *uri << method;
    if (header) {
      for (auto &h : *header) {
        *uri + h;
      }
    }

    auto res = std::make_unique<Beeblebrox::HttpResponseString>();

    auto bContent = std::make_unique<Beeblebrox::HttpContentString>(content);

    *hand << uri.get() << res.get();
    if (!content.empty()) {
      *hand << bContent.get();
    }

    hand->Run();

    buffer.assign(res->getContent());

    return uri->getHttpReturnCode();
  }

 protected:
  long remove(const std::string &url, std::string &buffer) {
    return mGet(Beeblebrox::Uri::Method::DELETE, url, nullptr, buffer);
  }

  long get(const std::string &url, std::string &buffer) {
    return mGet(Beeblebrox::Uri::Method::GET, url, nullptr, buffer);
  }

  long get(const std::string &url, std::list<std::string> *header,
           std::string &buffer) {
    return mGet(Beeblebrox::Uri::Method::GET, url, header, buffer);
  }

  long put(const std::string &url, const std::string &content,
           std::string &buffer) {
    return mPostPut(Beeblebrox::Uri::Method::PUT, url, nullptr, content,
                    buffer);
  }

  long put(const std::string &url, std::list<std::string> *header,
           const std::string &content, std::string &buffer) {
    return mPostPut(Beeblebrox::Uri::Method::PUT, url, header, content, buffer);
  }

  long put(const std::string &url, std::string &buffer) {
    return mPostPut(Beeblebrox::Uri::Method::PUT, url, nullptr, "", buffer);
  }

  long post(const std::string &url, const std::string &content,
            std::string &buffer) {
    return mPostPut(Beeblebrox::Uri::Method::POST, url, nullptr, content,
                    buffer);
  }

  long post(const std::string &url, std::list<std::string> *header,
            const std::string &content, std::string &buffer) {
    return mPostPut(Beeblebrox::Uri::Method::POST, url, header, content,
                    buffer);
  }

 public:
  bool isFollowUri() const { return followUri; }
  void setFollowUri(bool pFollowUri) { HttpClient::followUri = pFollowUri; }

 public:
  static long Delete(const std::string &url, std::string &buffer) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = true;

    return client->mGet(Beeblebrox::Uri::Method::DELETE, url, nullptr, buffer);
  }

  static long GetFile(const std::string &url, const std::string &path,
                      bool followUri = true) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = true;

    return client->mGetFile(Beeblebrox::Uri::Method::GET, url, nullptr, path);
  }

  static long Get(const std::string &url, std::string &buffer,
                  bool followUri = true) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = followUri;

    return client->mGet(Beeblebrox::Uri::Method::GET, url, nullptr, buffer);
  }

  static long Get(const std::string &url, std::list<std::string> *header,
                  std::string &buffer, bool followUri = true) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = followUri;

    return client->mGet(Beeblebrox::Uri::Method::GET, url, header, buffer);
  }

  static long Post(const std::string &url, std::string &buffer,
                   const std::string &content = "", bool followUri = true) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = followUri;
    return client->mPostPut(Beeblebrox::Uri::Method::POST, url, nullptr,
                            content, buffer);
  }

  static long Post(const std::string &url, std::list<std::string> *header,
                   std::string &buffer, const std::string &content = "",
                   bool followUri = true) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = followUri;
    return client->mPostPut(Beeblebrox::Uri::Method::POST, url, header, content,
                            buffer);
  }

  static long Put(const std::string &url, std::string &buffer,
                  const std::string &content = "", bool followUri = true) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = followUri;

    return client->mPostPut(Beeblebrox::Uri::Method::PUT, url, nullptr, content,
                            buffer);
  }

  static long Put(const std::string &url, std::list<std::string> *header,
                  std::string &buffer, const std::string &content = "",
                  bool followUri = true) {
    auto client = std::make_unique<T2::HttpClient>();
    client->followUri = followUri;

    return client->mPostPut(Beeblebrox::Uri::Method::PUT, url, header, content,
                            buffer);
  }
};

}  // namespace T2

#endif  // T2PC2_T2_UTIL_HTTPCLIENT_HPP
