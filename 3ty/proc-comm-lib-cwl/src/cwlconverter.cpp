#include <converter/model.hpp>
#include <utils/echostd.hpp>
#include <utils/yamlutils.hpp>

class CwlConverter {

public:
    static std::optional<CWLModel> find(const CWLModel &mdl, const std::string &id, const std::string &value) {
        if (mdl.getId() == id && value.empty()) {
            return mdl;
        }

        if (mdl.getId() == id && mdl.getVal() == value) {
            return mdl;
        }

        for (auto &m : mdl.getList()) {
            if (m.getId() == id && value.empty()) {

                return m;
            }

            if (m.getId() == id && m.getVal() == value) {
                return mdl;
            }

            auto k = find(m, id, value);
            if (k != std::nullopt) {
                return k.value();
            }
        }

        return std::nullopt;
    }

    static void dumpCWLMODEL(const CWLModel &m, int level) {
        level++;
        std::string tab = std::string((level * 4), ' ');
        std::cout << tab << "id: \"" << m.getId() << "\" val: \"" << m.getVal() << "\"" << "\n";

        for (auto &i : m.getList()) {
            dumpCWLMODEL(i, level);
        }
    }

    static void loadModel(const YAML::Node &node, CWLModel *father) {
        if (father == nullptr) {
            return;
        }

        if (YamlUtils::isScalarValid(node)) {
            father->setVal(node.as<std::string>());
        } else if (YamlUtils::isSequenceValid(node)) {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
                if (YamlUtils::isScalarValid(*it)) {
                    CWLModel e((*it).as<std::string>());
                    father->insert(e);
                } else {
                    CWLModel e;
                    loadModel(*it, &e);
                    father->insert(e);
                }
            }
        } else if (YamlUtils::isMapValid(node)) {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
                std::string key("");
                if (YamlUtils::isScalarValid(it->first)) {
                    key = it->first.as<std::string>();
                }
                if (YamlUtils::isScalarValid(it->second)) {
                    if (!key.empty()) {
                        CWLModel e(it->second.as<std::string>());
                        e.setId(key);

                        father->insert(e);
                    }
                } else {
                    if (!key.empty()) {
                        CWLModel e;
                        e.setId(key);
                        loadModel(it->second, &e);
                        father->insert(e);
                    }
                }
            }
        }
    }

    static void LoadModel(const char *program, CWLModel &father) {
        try {
            YAML::Node node = YAML::Load(program);
            loadModel(node, &father);

            dumpCWLMODEL(father, 0);
            std::cout << ".....\n";

            auto graph = find(father, "$graph", "");

            //    dumpCWLMODEL(graph.value(), 0);

            auto workflow = find(graph.value(), "class", "Workflow");

            dumpCWLMODEL(workflow.value(), 0);

            std::cout << "zzz.....\n";
            auto inputs = find(workflow.value(), "inputs", "");

            dumpCWLMODEL(inputs.value(), 0);

            std::cout << "zzz.....\n";


        } catch (YAML::ParserException &e) {
            throw std::runtime_error(e.what());
        } catch (std::runtime_error &e) {
            throw std::runtime_error(e);
        } catch (...) {
            throw std::runtime_error("error undefined!");
        }
    }
};