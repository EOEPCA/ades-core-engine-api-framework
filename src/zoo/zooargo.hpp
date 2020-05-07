#ifndef ADES_CODE_ENGINE_API_FRAMEWORK_ZOOARGO_HPP
#define ADES_CODE_ENGINE_API_FRAMEWORK_ZOOARGO_HPP

#include <dlfcn.h>

#include <stdexcept>
#include <string>

#include <list>
#include <utility>

namespace mods {
class IModInterface {
  bool valid{false};

protected:
public:
  IModInterface() = delete;

  IModInterface(const IModInterface &) = delete;

  explicit IModInterface(std::string path) : path_(std::move(path)) {
    handle = dlopen(path_.data(), RTLD_LAZY);
    if (!handle) {
      handle = nullptr;
      setValid(false);
      setLastError(std::string(dlerror()));
    }
    setValid(true);
    resetError();
  }

  virtual ~IModInterface() {
    if (handle != nullptr) {
      dlclose(handle);
      handle = nullptr;
      resetError();
    }
  }

  bool isValid() const { return valid; }
  void setValid(bool val) { IModInterface::valid = val; }

  const std::string &getLastError() const { return lastError; }
  void resetError() { lastError.clear(); }
  void setLastError(std::string strError) {
    IModInterface::lastError = std::move(lastError);
  }

protected:
  std::string lastError{""};
  void *handle{nullptr};

private:
  std::string path_{""};
};

class ArgoInterface : protected mods::IModInterface {
public:
  ArgoInterface() = delete;
  explicit ArgoInterface(const std::string &path)
      : mods::IModInterface(path), start(nullptr), getStatus(nullptr),
        getResults(nullptr) {

    setValid(true);

    start = (int (*)(const std::string &cwlContent,
                     std::list<std::pair<std::string, std::string>> &inputList,
                     const std::string &uuidBaseID, const std::string &runId,
                     std::string &id))dlsym(handle, "start");
    if (!start) {
      setValid(false);
      return;
    }

    getStatus = (int (*)(const std::string &argoWorkfloId, int &percent,
                          std::string &message))dlsym(handle, "getStatus");
    if (!getStatus) {
      setValid(false);
      return;
    }
    getResults =
        (void (*)(const std::string &argoWorkfloId,
                  std::list<std::pair<std::string, std::string>> &outPutList))
            dlsym(handle, "getResults");
    if (!getResults) {
      setValid(false);
      return;
    }
  }

public:

  bool IsValid() { return this->isValid(); }
  std::string GetLastError() {
    return std::move(std::string(this->getLastError()));
  };

  /***
   *
   * @param cwlContent contains the cwl Content
   * @param inputList the list of all inputParameter
   * @param uuidBaseID represents id to be used as the basis of the workflow
   * name
   * @param runId represents the WPS Id of the run
   * @param id argoWorkflow complateID
   * @return 0 ok  >0 notOk
   */
  int (*start)(const std::string &cwlContent,
            std::list<std::pair<std::string, std::string>> &inputList,
            const std::string &uuidBaseID, const std::string &runId,
            std::string &id);

  /***
   *
   * @param argoWorkfloId
   * @param percent
   * @param message
   * @return 0 continue >0 stop
   */
  int (*getStatus)(const std::string &argoWorkfloId, int &percent,
                 std::string &message);
  void (*getResults)(const std::string &argoWorkfloId,
                  std::list<std::pair<std::string, std::string>> &outPutList);
};

} // namespace mods

#endif // ADES_CODE_ENGINE_API_FRAMEWORK_ZOOARGO_HPP
