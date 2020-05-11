//
// Created by bla on 05/05/20.
//


#include <fstream>
#include <iostream>
#include "graph.hpp"
#include "../cwlconverter.cpp"

const std::string &Graph::getCwvlVersion() const {
    return cwvlVersion;
}
void Graph::setCwvlVersion(const std::string &cwvlVersion) {
    Graph::cwvlVersion = cwvlVersion;
}
const CommandLineTool::CommandLineTool &Graph::getCommandLineTool() const {
    return commandLineTool;
}
void Graph::setCommandLineTool(const CommandLineTool::CommandLineTool &commandLineTool) {
    Graph::commandLineTool = commandLineTool;
}
const Workflow::Workflow &Graph::getWorkflow() const {
    return workflow;
}
void Graph::setWorkflow(const Workflow::Workflow &workflow) {
    Graph::workflow = workflow;
}

void Graph::loadFile(std::string_view filePath, std::string &buffer) {

    std::ifstream t(filePath.data());
    std::stringstream sBuffer;
    sBuffer << t.rdbuf();

//    buffer.clear();
    buffer.assign(sBuffer.str());

}

void Graph::loadCwlFile(std::string cwlFile) {
    std::ifstream infile(cwlFile);
    if (!infile.good()) {
        std::cout<<"File not found "<<cwlFile<<std::endl;
        throw;
    }
    std::string buffer;
    Graph::loadFile(cwlFile,buffer);
    Graph::loadCwlFileContent(buffer);
}


void Graph::loadCwlFileContent(std::string buffer) {



    std::cout<<"Start loadCwlFileContent"<<std::endl;
    CWLModel cwlRootModel;
    YAML::Node node = YAML::Load(buffer);
    CwlConverter::loadModel(node, &cwlRootModel);

    auto cwlVersion = CwlConverter::find(cwlRootModel, "cwlVersion", "");
    if (cwlVersion.has_value()) {
        Graph::setCwvlVersion(cwlVersion->getVal());
    }

    std::cout<<"Start graph"<<std::endl;
    auto graph = CwlConverter::find(cwlRootModel, "$graph", "");


    std::cout<<"Start workflowCwlModel"<<std::endl;
    auto workflowCwlModel = CwlConverter::find(graph.value(), "class", "Workflow");
    if (workflowCwlModel.has_value()) {
        Workflow::Workflow workflow1;
        workflow1.loadCwlModel(workflowCwlModel.value());
        setWorkflow(workflow1);
    }


    std::cout<<"Start commandLineToolCwlModel"<<std::endl;
    auto commandLineToolCwlModel = CwlConverter::find(graph.value(), "class", "CommandLineTool");
    if (commandLineToolCwlModel.has_value()) {
        CommandLineTool::CommandLineTool commandLineTool;
        commandLineTool.loadCwlModel(commandLineToolCwlModel.value());
        setCommandLineTool(commandLineTool);
    }
    std::cout<<"End"<<std::endl;


}
