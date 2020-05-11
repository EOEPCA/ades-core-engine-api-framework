#include <list>
#include <string>
#include <utility>

#include <eoepca/argo/eoepcaargo.hpp>
#include <graph.hpp>
#include <zconf.h>

#include "zooargo.hpp"


extern "C" int start(mods::ArgoInterface::ArgoWorkflowConfig &awConfig, const std::string &cwlContent, std::list<std::pair<std::string, std::string>> &inputList, const std::string &uuidBaseID, const std::string &runId, std::string &id) {


    std::cerr<<"start is called"<<std::endl;

    // argolib
    auto argoLib = std::make_unique<EOEPCA::EOEPCAargo>(awConfig.eoepcaargoPath);

    std::cerr<<"starting parser bb " <<std::endl;
    // parsing Graph
    auto cwl_graph = std::make_unique<Graph>();
    std::cerr<<"starting parser bb2 " <<std::endl;
    cwl_graph->loadCwlFileContent(cwlContent);

    std::cerr<<"parse complete"<<std::endl;
    // COMMAND LINE TOOL
    auto cwl_commandLineTool = cwl_graph->getCommandLineTool();

    // basecommand
    std::string baseCommand = cwl_commandLineTool.getBaseCommand();
    // hints
    std::string dockerImageName = cwl_commandLineTool.getHints().front().getDockerRequirement().getDockerPull();

    std::cerr<<"basecommand and dockerimage retrieved"<<std::endl;

    // WORKFLOW
    auto cwl_workflow = cwl_graph->getWorkflow();
    std::string stepName = cwl_workflow.getSteps().front().getLabel();


    // APPLICATION
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setDockerImage(dockerImageName);
    application->setUseShell(true);
    application->setCommand(baseCommand);

    std::cerr<<"inputs"<<std::endl;
    for (auto const input : inputList) {

        std::cerr<<input.first<< input.second<<std::endl;
        application->addParam(input.first, input.second);
    }

    std::string yaml;
    argoLib->create_workflow_yaml_from_app(application.get(),yaml);
    std::cerr<<yaml<<std::endl;

    std::string argoNamespace="default";
    proc_comm_lib_argo::model::Workflow workflow;

    argoLib->submit_workflow(application.get(),argoNamespace,workflow,awConfig.argoUri);

    id=workflow.get_metadata()->get_name()->c_str();



    return 0;
}

extern "C" int getStatus(mods::ArgoInterface::ArgoWorkflowConfig &awConfig, const std::string &argoWorkfloId, int &percent, std::string &message) {

    sleep(2);

    // argolib
    auto argoLib = std::make_unique<EOEPCA::EOEPCAargo>(awConfig.eoepcaargoPath);

    std::string argoNamespace="default";
    proc_comm_lib_argo::model::Workflow workflow;
    argoLib->get_workflow_from_name(argoWorkfloId,argoNamespace,workflow,awConfig.argoUri);
    message = workflow.get_status()->get_phase()->c_str();

    int totNumberOfWorkflows=workflow.get_status()->get_nodes()->size();
    int completedWorkflows=0;
std::string succeededString="Succeeded";
    for(auto const node : *workflow.get_status()->get_nodes()){
        if(succeededString.compare(node.second.get_phase()->c_str())==0){
            completedWorkflows++;
        }
    }


    percent=completedWorkflows*100/totNumberOfWorkflows;
    return 0;
}

extern "C" int getResults(mods::ArgoInterface::ArgoWorkflowConfig &awConfig, const std::string &argoWorkflowId, std::list<std::pair<std::string, std::string>> &outPutList) {

    // argolib
    auto argoLib = std::make_unique<EOEPCA::EOEPCAargo>(awConfig.eoepcaargoPath);

    std::string argoNamespace="default";
    argoLib->get_workflow_results_from_name(argoWorkflowId,argoNamespace,outPutList,awConfig.argoUri,awConfig.k8Uri);

    return 0;
}
