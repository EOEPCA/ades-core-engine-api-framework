#include <iostream>
#include <converter/model.hpp>
#include "model/graph.hpp"
#include "cwlconverter.cpp"


int main() {

    Graph graph;
    graph.loadCwlFile("./workflow.yaml");
    //graph.loadCwlFile("./fb.yaml");


    std::cout<< graph.getCommandLineTool().getBaseCommand() << std::endl;
    std::cout<< graph.getCommandLineTool().getInputs().front().getInputBinding().getPosition() << std::endl;
    std::cout<< graph.getCommandLineTool().getInputs().front().getInputBinding().getPrefix() << std::endl;


    std::cout<< graph.getWorkflow().getDoc() << std::endl;
    std::cout<< graph.getWorkflow().getInputs().front().getInputBinding().getPosition() << std::endl;
    std::cout<< graph.getWorkflow().getInputs().front().getInputBinding().getPrefix() << std::endl;


    return 0;
}