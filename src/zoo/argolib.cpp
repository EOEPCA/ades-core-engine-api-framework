
#include <list>
#include <string>
#include <utility>

#include <eoepca/argo/eoepcaargo.hpp>

#include "zooargo.hpp"

extern "C" int start(mods::ArgoInterface::ArgoWorkflowConfig& awConfig,const std::string &cwlContent,
                     std::list<std::pair<std::string, std::string>> &inputList,
                     const std::string &uuidBaseID, const std::string &runId,
                     std::string &id) {




  auto argoLib = std::make_unique<EOEPCA::EOEPCAargo>(awConfig.eoepcaargoPath);


  return 0;
}

extern "C" int getStatus(mods::ArgoInterface::ArgoWorkflowConfig& awConfig,const std::string &argoWorkfloId, int &percent,
                          std::string &message) {

  return 0;
}

extern "C" void
getResults(mods::ArgoInterface::ArgoWorkflowConfig& awConfig,const std::string &argoWorkfloId,
           std::list<std::pair<std::string, std::string>> &outPutList) {

  outPutList.emplace_back("result_osd","http://ciao.a.tutti/results/ref.xml");
}
