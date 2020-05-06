
#include <list>
#include <string>
#include <utility>

extern "C" int start(const std::string &cwlContent,
                     std::list<std::pair<std::string, std::string>> &inputList,
                     const std::string &uuidBaseID, const std::string &runId,
                     std::string &id) {

  return 0;
}

extern "C" int getStatus(const std::string &argoWorkfloId, int &percent,
                          std::string &message) {

  return 0;
}

extern "C" void
getResults(const std::string &argoWorkfloId,
           std::list<std::pair<std::string, std::string>> &outPutList) {

  outPutList.emplace_back("result_osd","http://ciao.a.tutti/results/ref.xml");
}
