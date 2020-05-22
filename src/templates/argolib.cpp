#include <list>
#include <string>
#include <utility>

#include <eoepca/argo/eoepcaargo.hpp>
#include <graph.hpp>
#include <zconf.h>
#include <memory>

#include "zooargo.hpp"

extern "C" int start(mods::ArgoInterface::ArgoWorkflowConfig &awConfig, const std::string &cwlContent, std::list<std::pair<std::string, std::unique_ptr<mods::ArgoInterface::tgInput>>> &inputList, const std::string &uuidBaseID, const std::string &runId, std::string &id) {

    // argolib
    auto argoLib = std::make_unique<EOEPCA::EOEPCAargo>(awConfig.eoepcaargoPath);

    // parsing Graph
    auto cwl_graph = std::make_unique<Graph>();
    cwl_graph->loadCwlFileContent(cwlContent);


    //--------------------
    // WORKFLOW

    // retrieve the step. We make the assumption that we only deal with a single step
    auto cwl_workflow_list = cwl_graph->getWorkflowList();
    auto cwl_workflow = cwl_workflow_list.front();
    if (cwl_workflow.getSteps().empty()) {
        throw std::runtime_error("cwl does not contain steps");
    }
    auto step = cwl_workflow.getSteps().front();

    // step name
    std::string stepName = step.getLabel();

    //step inputs
    auto inputs = step.getIn();


    //------------------------------
    // COMMAND LINE TOOL
    auto cwl_commandLineToolList = cwl_graph->getCommandLineToolList();
    auto cwl_commandLineTool = cwl_commandLineToolList.front();

    // basecommand
    std::string baseCommand = cwl_commandLineTool.getBaseCommand();

    // docker
    std::string dockerImageName = cwl_commandLineTool.getHints().front().getDockerRequirement().getDockerPull();

    //---------------------
    // APPLICATION
    std::unique_ptr<proc_comm_lib_argo::Application> application = std::make_unique<proc_comm_lib_argo::Application>();
    application->setRunId(runId);
    application->setUuidBaseId(uuidBaseID);
    application->setDockerImage(dockerImageName);
    application->setCommand(baseCommand);
    application->setUseShell(true);
    bool useStageIn = false;
    for (auto const &inputPair : inputList) {
        if (inputPair.second->mimeType.compare("application/atom+xml") == 0) { useStageIn = true; }
        application->addParam(inputPair.second->id, inputPair.second->value);
    }

    if (useStageIn) {
        // pre processing node
        std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageInApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
        stageInApplication->setDockerImage("blasco/eoepca-eo-tools");
        stageInApplication->setUseShell(true);
        stageInApplication->setCommand("stagein");
        application->setPreProcessingNode(stageInApplication);
    }

    std::unique_ptr<proc_comm_lib_argo::NodeTemplate> stageOutApplication = std::make_unique<proc_comm_lib_argo::NodeTemplate>();
    stageOutApplication->setDockerImage("blasco/eoepca-eo-tools");
    stageOutApplication->setUseShell(true);
    stageOutApplication->setCommand("cat");


    // temporary hardcoded
    std::map<std::string, std::string> volume;
    volume["volumeName"] = "workdir";
    volume["persistentVolumeClaimName"] = "eoepca-pvc";
    volume["volumeMountPath"] = "/tmp/eoepca";
    application->setVolume(volume);


    //std::string yaml;
    //argoLib->create_workflow_yaml_from_app(application.get(),yaml);
    //std::cout<<yaml<<std::endl;

    std::string argoNamespace = "default";
    proc_comm_lib_argo::model::Workflow workflow;

    argoLib->submit_workflow(application.get(), argoNamespace, workflow, awConfig.argoUri);

    id = workflow.get_metadata()->get_name()->c_str();

    return 0;
}

extern "C" int getStatus(mods::ArgoInterface::ArgoWorkflowConfig &awConfig, const std::string &argoWorkfloId, int &percent, std::string &message) {

    // argolib
    auto argoLib = std::make_unique<EOEPCA::EOEPCAargo>(awConfig.eoepcaargoPath);

    std::string argoNamespace = "default";
    proc_comm_lib_argo::model::Workflow workflow;
    try {
        argoLib->get_workflow_from_name(argoWorkfloId, argoNamespace, workflow, awConfig.argoUri);
        message = workflow.get_status()->get_phase()->c_str();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        message = ex.what();
        return 500;
    } catch (const std::string &ex) {
        std::cerr << ex << std::endl;
        message = ex;
        return 500;
    } catch (...) {
        std::string error = "An error occured while retrieve the status of workflow " + argoWorkfloId;
        std::cerr << error << std::endl;
        message = error;
        return 500;
    }
    int totNumberOfWorkflows = workflow.get_status()->get_nodes()->size();
    int completedWorkflows = 0;
    std::string succeededString = "Succeeded";
    for (auto const node : *workflow.get_status()->get_nodes()) {
        if (succeededString.compare(node.second.get_phase()->c_str()) == 0) {
            completedWorkflows++;
        }
    }

    percent = completedWorkflows * 100 / totNumberOfWorkflows;
    return 0;
}

extern "C" int getResults(mods::ArgoInterface::ArgoWorkflowConfig &awConfig, const std::string &argoWorkflowId, std::list<std::pair<std::string, std::string>> &outPutList) {

    // argolib
    auto argoLib = std::make_unique<EOEPCA::EOEPCAargo>(awConfig.eoepcaargoPath);

    std::string argoNamespace = "default";
    argoLib->get_workflow_results_from_name(argoWorkflowId, argoNamespace, outPutList, awConfig.argoUri, awConfig.k8Uri);

    return 0;
}
