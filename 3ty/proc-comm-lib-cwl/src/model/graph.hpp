//
// Created by bla on 05/05/20.
//

#ifndef RESTJSON_GRAPH_HPP
#define RESTJSON_GRAPH_HPP

#include <string>
#include <converter/model.hpp>
#include <yaml-cpp/node/node.h>
#include <utils/yamlutils.hpp>
#include "commandlinetool.hpp"
#include "workflow.hpp"

class Graph {
private:
    std::string cwvlVersion;
    CommandLineTool::CommandLineTool commandLineTool;
    Workflow::Workflow workflow;

    void loadFile(std::string_view filePath, std::string &buffer);
    void LoadModel(const char *program, CWLModel &cwlModel);


public:
    const std::string &getCwvlVersion() const;
    void setCwvlVersion(const std::string &cwvlVersion);

    const CommandLineTool::CommandLineTool &getCommandLineTool() const;
    void setCommandLineTool(const CommandLineTool::CommandLineTool &commandLineTool);

    const Workflow::Workflow &getWorkflow() const;
    void setWorkflow(const Workflow::Workflow &workflow);

    void loadCwlFile(std::string cwlFile);

    void loadCwlFileContent(std::string buffer);
};

#endif //RESTJSON_GRAPH_HPP
