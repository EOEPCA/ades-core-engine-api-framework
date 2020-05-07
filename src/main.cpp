
#include "zoo/zooargo.hpp"
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unistd.h>

#define ARGO_URI "http://dsads:22222/adsdssdf/sdfdsfsdfsd/fdsdfsdfs"
#define CWLPATH                                                                \
  "/Users/rdirienzo/Project/EOEPCA/ades-core-engine-api-framework/src/zoo/"    \
  "argo.cwl"
#define LIBPATH                                                                \
  "/Users/rdirienzo/Project/EOEPCA/ades-core-engine-api-framework/"            \
  "cmake-build-debug/libargo_interface.dylib"

struct Util {

  static int loadFile(const char *filePath, std::stringstream &sBuffer) {
    std::ifstream infile(filePath);
    if (infile.good()) {
      sBuffer << infile.rdbuf();
      return 0;
    }
    return 1;
  }
};

int main(int a, char **b) {

  auto argoInterface = std::make_unique<mods::ArgoInterface>(LIBPATH);
  if (!argoInterface->IsValid()) {

    std::cerr << "libargo_interface.dylib NOT VALID\n";
    return 1;
  }

  std::stringstream cwlBuffer;
  Util::loadFile(CWLPATH, cwlBuffer);

  auto argoConfig = std::make_unique<mods::ArgoInterface::ArgoWorkflowConfig>();
  argoConfig->uri = ARGO_URI;

  std::string uuidBaseID("argoservice");
  std::string runId("6f189344-9074-11ea-b9ca-3b5c9fef9034");
  std::string argoWorkflowId("");

  std::list<std::pair<std::string, std::string>> inputList{};
  inputList.emplace_back("input_string", "una string a caso");

  argoInterface->start(*argoConfig.get(), cwlBuffer.str(), inputList,
                       uuidBaseID, runId, argoWorkflowId);

  int percent = 0;
  std::string message("");
  while (argoInterface->getStatus(*argoConfig.get(), argoWorkflowId, percent,
                                  message)) {
    std::cout << "percent: " << percent << " message: " << message;
    sleep(5);
  }

  std::list<std::pair<std::string, std::string>> outPutList{};
  argoInterface->getResults(*argoConfig.get(), argoWorkflowId, outPutList);

  for (auto &[k, p] : outPutList) {
    std::cout << k << " " << p << "\n";
  }

  return 0;
}