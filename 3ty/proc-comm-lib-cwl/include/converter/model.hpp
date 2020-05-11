
#ifndef T2CWL_MODEL_HPP
#define T2CWL_MODEL_HPP
#include <list>
#include <optional>
#include <string>
#include <utility>

using PairIdValue = std::pair<std::string, std::string>;

class CWLModel {
 protected:
  std::string val{""};
  std::string id{""};
  std::list<CWLModel> list{};

 protected:
  std::optional<std::string> getKey(const std::string& theKey) const {
    for (auto& l : list) {
      if (l.getId() == theKey) {
        return std::string(l.getVal());
      }
    }

    return std::nullopt;
  }

 public:
  CWLModel() = default;

  CWLModel& operator=(const CWLModel& other) {
    if (this != &other) {
      this->val = other.val;
      this->id = other.id;
      for (auto& a : other.list) {
        CWLModel m;
        m = a;
        this->list.emplace_back(m);
      }
    }
    return *this;
  }

  //  Model(const Model&) = default;
  CWLModel(const CWLModel& other) {
    if (this != &other) {
      *this = other;
    }
  }

  CWLModel(CWLModel&&) = default;
  explicit CWLModel(std::string s) : val(std::move(s)) {}

  ~CWLModel() = default;

 public:
  void setVal(std::string v) { val = std::move(v); }
  void setId(std::string i) { CWLModel::id = std::move(i); }
  int size() const { return list.size(); }
  std::string getVal() const { return val; }
  std::string getId() const { return id; }

  std::optional<std::string> getTag(const std::string& tag) const {
    return std::move(getKey("tag"));
  }

  std::optional<std::string> getType() const {
    return std::move(getKey("type"));
  }

  std::optional<std::string> getClass() const {
    return std::move(getKey("class"));
  }

  std::optional<PairIdValue> getPair() const {
    if (id.empty()) {
      return std::nullopt;
    }
    return std::make_pair(id, val);
  }

  const std::list<CWLModel>& getList() const { return list; }
  void insert(CWLModel m) { list.emplace_back(std::move(m)); }
  bool hasChildren() { return list.size(); }

  void reset() {
    val.clear();
    id.clear();
    list.clear();
  }
};

#endif  // T2CWL_MODEL_HPP
