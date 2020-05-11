
#include "zoo/zooargo.hpp"
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unistd.h>

#define ARGO_URI "http://localhost:8080"
#define K8_URI "http://127.0.0.1:2746"
#define CWLPATH                                                                \
  "/home/bla/dev/EOEPCA_dev/ades-core-engine-api-framework/src/zoo/argo.cwl"
#define LIBPATH                                                                \
  "/home/bla/dev/EOEPCA_dev/ades-core-engine-api-framework/cmake-build-debug/libargo_interface.so"

#define EOEPCAARGOPATH "/home/bla/dev/EOEPCA_dev/ades-core-engine-api-framework/cmake-build-debug/3ty/proc-comm-lib-argo/proc-comm-lib-argo-build/libeoepcaargo.so"


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
  argoConfig->argoUri = ARGO_URI;
  argoConfig->k8Uri = K8_URI;
  argoConfig->eoepcaargoPath=EOEPCAARGOPATH;

  std::string uuidBaseID("argoservice");
  std::string runId("6f189344-9074-11ea-b9ca-3b5c9fef9034");
  std::string argoWorkflowId("");

  std::list<std::pair<std::string, std::string>> inputList{};
  inputList.emplace_back("input_string", "una string a caso");

  argoInterface->start(*argoConfig.get(), cwlBuffer.str(), inputList,uuidBaseID, runId, argoWorkflowId);

  std::cout<<"argoWorkflowId: "<<argoWorkflowId<<std::endl;
  int percent = 0;
  std::string message("Running");

  while(message.compare("Running")==0 ) {
      argoInterface->getStatus(*argoConfig.get(), argoWorkflowId, percent, message);
      std::cout << "percent: " << percent << " message: " << message<<std::endl;
  }



  sleep(4);
  std::list<std::pair<std::string, std::string>> outPutList;
  argoInterface->getResults(*argoConfig.get(), argoWorkflowId, outPutList);

  for (auto &[k, p] : outPutList) {
    std::cout << k << " " << p << "\n";
  }

  return 0;
}