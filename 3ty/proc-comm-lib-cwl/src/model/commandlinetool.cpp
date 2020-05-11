//
// Created by bla on 30/04/20.
//

#include "commandlinetool.hpp"
#include "graph.hpp"
#include "../cwlconverter.cpp"

namespace CommandLineTool {
    const std::string &CommandLineTool::getId() const {
        return id;
    }

    void CommandLineTool::setId(const std::string &id) {
        CommandLineTool::id = id;
    }

    const std::string &CommandLineTool::getLabel() const {
        return label;
    }

    void CommandLineTool::setLabel(const std::string &label) {
        CommandLineTool::label = label;
    }

    const std::string &CommandLineTool::getDoc() const {
        return doc;
    }

    void CommandLineTool::setDoc(const std::string &doc) {
        CommandLineTool::doc = doc;
    }

    const std::string &CommandLineTool::getCwlVersion() const {
        return cwlVersion;
    }

    void CommandLineTool::setCwlVersion(const std::string &cwlVersion) {
        CommandLineTool::cwlVersion = cwlVersion;
    }

    const std::string &CommandLineTool::getBaseCommand() const {
        return baseCommand;
    }

    void CommandLineTool::setBaseCommand(const std::string &baseCommand) {
        CommandLineTool::baseCommand = baseCommand;
    }

    const std::string &CommandLineTool::getSuccessCodes() const {
        return successCodes;
    }

    void CommandLineTool::setSuccessCodes(const std::string &successCodes) {
        CommandLineTool::successCodes = successCodes;
    }

    const std::string &CommandLineTool::getTemporaryFailCodes() const {
        return temporaryFailCodes;
    }

    void CommandLineTool::setTemporaryFailCodes(const std::string &temporaryFailCodes) {
        CommandLineTool::temporaryFailCodes = temporaryFailCodes;
    }

    const std::string &CommandLineTool::getPermanentFailCodes() const {
        return permanentFailCodes;
    }

    void CommandLineTool::setPermanentFailCodes(const std::string &permanentFailCodes) {
        CommandLineTool::permanentFailCodes = permanentFailCodes;
    }
    const std::list<Hint> &CommandLineTool::getHints() const {
        return hints;
    }
    void CommandLineTool::setHints(const std::list<Hint> &hints) {
        CommandLineTool::hints = hints;
    }
    const std::list<Input> &CommandLineTool::getInputs() const {
        return inputs;
    }
    void CommandLineTool::setInputs(const std::list<Input> &inputs) {
        CommandLineTool::inputs = inputs;
    }
    const std::list<Output> &CommandLineTool::getOutputs() const {
        return outputs;
    }
    void CommandLineTool::setOutputs(const std::list<Output> &outputs) {
        CommandLineTool::outputs = outputs;
    }
    const std::list<Requirement> &CommandLineTool::getRequirements() const {
        return requirements;
    }
    void CommandLineTool::setRequirements(const std::list<Requirement> &requirements) {
        CommandLineTool::requirements = requirements;
    }
    const std::list<std::string> &CommandLineTool::getArguments() const {
        return arguments;
    }
    void CommandLineTool::setArguments(const std::list<std::string> &arguments) {
        CommandLineTool::arguments = arguments;
    }
    const std::string &CommandLineTool::getStdIn() const {
        return std_in;
    }
    void CommandLineTool::setStdIn(const std::string &stdIn) {
        std_in = stdIn;
    }
    const std::string &CommandLineTool::getStdErr() const {
        return std_err;
    }
    void CommandLineTool::setStdErr(const std::string &stdErr) {
        std_err = stdErr;
    }
    const std::string &CommandLineTool::getStdOut() const {
        return std_out;
    }
    void CommandLineTool::setStdOut(const std::string &stdOut) {
        std_out = stdOut;
    }

    void CommandLineTool::loadCwlModel(CWLModel cwlModel) {

        std::cout<<"Inside commandLineToolCwlModel loadCwlModel"<<std::endl;

        auto id = CwlConverter::find(cwlModel, "id", "");
        if (id.has_value()) { setId(id->getVal()); }

        auto label = CwlConverter::find(cwlModel, "label", "");
        if (label.has_value()) { setLabel(label->getVal()); }

        auto doc = CwlConverter::find(cwlModel, "doc", "");
        if (doc.has_value()) { setDoc(doc->getVal()); }

        auto cwlVersion = CwlConverter::find(cwlModel, "cwlVersion", "");
        if (cwlVersion.has_value()) { setCwlVersion(cwlVersion->getVal()); }

        auto baseCommand = CwlConverter::find(cwlModel, "baseCommand", "");
        if (baseCommand.has_value()) { setBaseCommand(baseCommand->getVal()); }

        auto successCodes = CwlConverter::find(cwlModel, "successCodes", "");
        if (successCodes.has_value()) { setSuccessCodes(successCodes->getVal()); }

        auto temporaryFailCodes = CwlConverter::find(cwlModel, "temporaryFailCodes", "");
        if (temporaryFailCodes.has_value()) { setTemporaryFailCodes(temporaryFailCodes->getVal()); }

        auto permanentFailCodes = CwlConverter::find(cwlModel, "permanentFailCodes", "");
        if (permanentFailCodes.has_value()) { setPermanentFailCodes(permanentFailCodes->getVal()); }

        auto std_in = CwlConverter::find(cwlModel, "std_in", "");
        if (std_in.has_value()) { setStdIn(std_in->getVal()); }

        auto std_err = CwlConverter::find(cwlModel, "std_err", "");
        if (std_err.has_value()) { setStdErr(std_err->getVal()); }

        auto std_out = CwlConverter::find(cwlModel, "std_out", "");
        if (std_out.has_value()) { setStdOut(std_out->getVal()); }


        auto hintsCwlModel = CwlConverter::find(cwlModel, "hints", "");
        if (hintsCwlModel.has_value()) {
            std::list<Hint> hints;

            // dockerRequirementHint
            auto dockerRequirementCwlModel = CwlConverter::find(hintsCwlModel.value(), "DockerRequirement", "");
            if (dockerRequirementCwlModel.has_value()) {
                auto dockerPullCwlModel = CwlConverter::find(dockerRequirementCwlModel.value(), "dockerPull", "");
                if (dockerPullCwlModel.has_value()) {
                    DockerRequirement dockerRequirement;
                    dockerRequirement.setDockerPull(dockerPullCwlModel->getVal());
                    Hint dockerRequirementHint;
                    dockerRequirementHint.setDockerRequirement(dockerRequirement);
                    hints.emplace_back(dockerRequirementHint);
                }
            }

            setHints(hints);
        }

        std::cout<<"Inside commandLineToolCwlModel inputs"<<std::endl;
        // inputs
        auto inputsCwlModel = CwlConverter::find(cwlModel, "inputs", "");
        std::list<Input> inputs;
        if (inputsCwlModel.has_value()) {
            std::cout<<"Inside commandLineToolCwlModel inputs inside"<<std::endl;
            for (auto const &inputData : inputsCwlModel->getList()) {
                std::string argName = inputData.getId();
                auto inpCwlModel = CwlConverter::find(inputsCwlModel.value(), argName, "");
                Input input;
                input.loadCwlModel(inpCwlModel.value());
                inputs.emplace_back(input);
            }
        }
        CommandLineTool::setInputs(inputs);

        // outputs
        auto outputCwlModel = CwlConverter::find(cwlModel, "outputs", "");
        std::list<Output> outputs;
        if (outputCwlModel.has_value()) {
            std::cout<<"Inside commandLineToolCwlModel outputs inside"<<std::endl;
            for (auto const &outputData : outputCwlModel->getList()) {
                std::string argName = outputData.getId();
                auto outCwlModel = CwlConverter::find(outputCwlModel.value(), argName, "");
                Output output;
                output.loadCwlModel(outCwlModel.value());
                outputs.emplace_back(output);
            }
        }
        CommandLineTool::setOutputs(outputs);

        // Requirements
        auto requirementsCwlModel = CwlConverter::find(cwlModel, "requirements", "");
        std::list<Requirement> requirements;
        if (requirementsCwlModel.has_value()) {
            std::cout<<"Inside requirementsCwlModel inside"<<std::endl;

            // dockerRequirementHint
            auto dockerRequirementCwlModel = CwlConverter::find(requirementsCwlModel.value(), "DockerRequirement", "");
            if (dockerRequirementCwlModel.has_value()) {
                auto dockerPullCwlModel = CwlConverter::find(dockerRequirementCwlModel.value(), "dockerPull", "");
                if (dockerPullCwlModel.has_value()) {
                    std::cout<<"creating dockerreq"<<std::endl;
                    DockerRequirement dockerRequirement;
                    dockerRequirement.setDockerPull(dockerPullCwlModel->getVal());
                    requirements.emplace_back(dockerRequirement);
                    std::cout<<" dockerreq added"<<std::endl;
                }
            }


            // envVarRequirement
            auto envVarRequirementCwlModel = CwlConverter::find(requirementsCwlModel.value(), "EnvVarRequirement", "");
            std::cout<<"envVarRequirementCwlModel"<<std::endl;
            if (envVarRequirementCwlModel.has_value()) {
                EnvVarRequirement envVarRequirement;
                EnvironmentDef def;

                auto envDefCwlModel = CwlConverter::find(envVarRequirementCwlModel.value(), "envDef", "");
                if (envDefCwlModel.has_value()) {
                    EnvironmentDef envVarRequirement;
                    std::list<EnvironmentDef> environmentDefList;
                    for (auto const &envDefData : envDefCwlModel->getList()) {
                        std::string envName = envDefData.getId();
                        std::string envValue = CwlConverter::find(envDefCwlModel.value(), envName, "")->getVal();
                        EnvironmentDef env;
                        env.setEnvName(envName);
                        env.setEnvValue(envValue);
                        environmentDefList.emplace_back(env);
                    }
                }
                requirements.emplace_back(envVarRequirement);
            }

            CommandLineTool::setRequirements(requirements);
            std::cout<<"End setRequirements"<<std::endl;
        }

        std::cout<<"End "<<std::endl;
    }

    const std::string &Input::getId() const {
        return id;
    }

    void Input::setId(const std::string &id) {
        Input::id = id;
    }

    const std::string &Input::getLabel() const {
        return label;
    }

    void Input::setLabel(const std::string &label) {
        Input::label = label;
    }

    const std::list<std::string> &Input::getSecondaryFiles() const {
        return secondaryFiles;
    }

    void Input::setSecondaryFiles(const std::list<std::string> &secondaryFiles) {
        Input::secondaryFiles = secondaryFiles;
    }

    bool Input::isStreamable() const {
        return streamable;
    }

    void Input::setStreamable(bool streamable) {
        Input::streamable = streamable;
    }

    const std::string &Input::getDoc() const {
        return doc;
    }

    void Input::setDoc(const std::string &doc) {
        Input::doc = doc;
    }

    const std::string &Input::getFormat() const {
        return format;
    }

    void Input::setFormat(const std::string &format) {
        Input::format = format;
    }
    const CommandLineBinding &Input::getInputBinding() const {
        return inputBinding;
    }
    void Input::setInputBinding(const CommandLineBinding &inputBinding) {
        Input::inputBinding = inputBinding;
    }
    const std::string &Input::getType() const {
        return type;
    }
    void Input::setType(const std::string &type) {
        Input::type = type;
    }

    void Input::loadCwlModel(CWLModel cwlModel) {

        //id
        auto id = CwlConverter::find(cwlModel, "id", "");
        if (id.has_value()) {
            Input::setId(id->getVal());
        }

        //label
        auto label = CwlConverter::find(cwlModel, "label", "");
        if (label.has_value()) {
            Input::setLabel(label->getVal());
        }

        //doc
        auto doc = CwlConverter::find(cwlModel, "doc", "");
        if (doc.has_value()) {
            Input::setDoc(doc->getVal());
        }

        //format
        auto format = CwlConverter::find(cwlModel, "format", "");
        if (format.has_value()) {
            Input::setFormat(format->getVal());
        }

        //type
        auto type = CwlConverter::find(cwlModel, "type", "");
        if (type.has_value()) {
            Input::setType(type->getVal());
        }

        //inputBinding
        auto inputBindingCwlModel = CwlConverter::find(cwlModel, "inputBinding", "");
        if (inputBindingCwlModel.has_value()) {
            CommandLineBinding inputBinding;
            inputBinding.loadCwlModel(inputBindingCwlModel.value());
            Input::setInputBinding(inputBinding);
        }


    }

    const std::string &DockerRequirement::getDockerPull() const {
        return dockerPull;
    }
    void DockerRequirement::setDockerPull(const std::string &dockerPull) {
        DockerRequirement::dockerPull = dockerPull;
    }
    const std::string &DockerRequirement::getDockerLoad() const {
        return dockerLoad;
    }
    void DockerRequirement::setDockerLoad(const std::string &dockerLoad) {
        DockerRequirement::dockerLoad = dockerLoad;
    }
    const std::string &DockerRequirement::getDockerFile() const {
        return dockerFile;
    }
    void DockerRequirement::setDockerFile(const std::string &dockerFile) {
        DockerRequirement::dockerFile = dockerFile;
    }
    const std::string &DockerRequirement::getDockerImport() const {
        return dockerImport;
    }
    void DockerRequirement::setDockerImport(const std::string &dockerImport) {
        DockerRequirement::dockerImport = dockerImport;
    }
    const std::string &DockerRequirement::getDockerImageId() const {
        return dockerImageId;
    }
    void DockerRequirement::setDockerImageId(const std::string &dockerImageId) {
        DockerRequirement::dockerImageId = dockerImageId;
    }
    const std::string &DockerRequirement::getDockerOutputDirectory() const {
        return dockerOutputDirectory;
    }
    void DockerRequirement::setDockerOutputDirectory(const std::string &dockerOutputDirectory) {
        DockerRequirement::dockerOutputDirectory = dockerOutputDirectory;
    }
    bool CommandLineBinding::isLoadContents() const {
        return loadContents;
    }
    void CommandLineBinding::setLoadContents(bool loadContents) {
        CommandLineBinding::loadContents = loadContents;
    }
    int CommandLineBinding::getPosition() const {
        return position;
    }
    void CommandLineBinding::setPosition(int position) {
        CommandLineBinding::position = position;
    }
    const std::string &CommandLineBinding::getPrefix() const {
        return prefix;
    }
    void CommandLineBinding::setPrefix(const std::string &prefix) {
        CommandLineBinding::prefix = prefix;
    }
    bool CommandLineBinding::isSeparate() const {
        return separate;
    }
    void CommandLineBinding::setSeparate(bool separate) {
        CommandLineBinding::separate = separate;
    }
    const std::string &CommandLineBinding::getItemSeparator() const {
        return itemSeparator;
    }
    void CommandLineBinding::setItemSeparator(const std::string &itemSeparator) {
        CommandLineBinding::itemSeparator = itemSeparator;
    }
    const std::string &CommandLineBinding::getValueFrom() const {
        return valueFrom;
    }
    void CommandLineBinding::setValueFrom(const std::string &valueFrom) {
        CommandLineBinding::valueFrom = valueFrom;
    }
    bool CommandLineBinding::isShellQuote() const {
        return shellQuote;
    }
    void CommandLineBinding::setShellQuote(bool shellQuote) {
        CommandLineBinding::shellQuote = shellQuote;
    }

    void CommandLineBinding::loadCwlModel(CWLModel cwlModel) {

        // prefix
        auto prefix = CwlConverter::find(cwlModel, "prefix", "");
        if (prefix.has_value()) {
            CommandLineBinding::setPrefix(prefix->getVal());
        }

        //itemSeparator
        auto itemSeparator = CwlConverter::find(cwlModel, "itemSeparator", "");
        if (itemSeparator.has_value()) {
            CommandLineBinding::setItemSeparator(itemSeparator->getVal());
        }

        //valueFrom
        auto valueFrom = CwlConverter::find(cwlModel, "valueFrom", "");
        if (valueFrom.has_value()) {
            CommandLineBinding::setValueFrom(valueFrom->getVal());
        }

        //position
        auto position = CwlConverter::find(cwlModel, "position", "");
        if (position.has_value()) {
            CommandLineBinding::setPosition(std::stoi(position->getVal()));
        }

    }

    const std::string &Output::getId() const {
        return id;
    }
    void Output::setId(const std::string &id) {
        Output::id = id;
    }
    const std::string &Output::getLabel() const {
        return label;
    }
    void Output::setLabel(const std::string &label) {
        Output::label = label;
    }
    const std::list<std::string> &Output::getSecondaryFiles() const {
        return secondaryFiles;
    }
    void Output::setSecondaryFiles(const std::list<std::string> &secondaryFiles) {
        Output::secondaryFiles = secondaryFiles;
    }
    bool Output::isStreamable() const {
        return streamable;
    }
    void Output::setStreamable(bool streamable) {
        Output::streamable = streamable;
    }
    const std::string &Output::getDoc() const {
        return doc;
    }
    void Output::setDoc(const std::string &doc) {
        Output::doc = doc;
    }
    const std::string &Output::getFormat() const {
        return format;
    }
    void Output::setFormat(const std::string &format) {
        Output::format = format;
    }
    const CommandOutputBinding &Output::getOutputBinding() const {
        return outputBinding;
    }
    void Output::setOutputBinding(const CommandOutputBinding &outputBinding) {
        Output::outputBinding = outputBinding;
    }
    const std::string &Output::getType() const {
        return type;
    }
    void Output::setType(const std::string &type) {
        Output::type = type;
    }
    void Output::loadCwlModel(CWLModel &cwlModel) {



        //id
        auto id = CwlConverter::find(cwlModel, "id", "");
        if (id.has_value()) {
            Output::setId(id->getVal());
        }

        //label
        auto label = CwlConverter::find(cwlModel, "label", "");
        if (label.has_value()) {
            Output::setLabel(label->getVal());
        }

        //doc
        auto doc = CwlConverter::find(cwlModel, "doc", "");
        if (doc.has_value()) {
            Output::setDoc(doc->getVal());
        }

        //format
        auto format = CwlConverter::find(cwlModel, "format", "");
        if (format.has_value()) {
            Output::setFormat(format->getVal());
        }

        //type
        auto type = CwlConverter::find(cwlModel, "type", "");
        if (type.has_value()) {
            Output::setType(type->getVal());
        }

        //outputBinding
        auto outputBindingCwlModel = CwlConverter::find(cwlModel, "outputBinding", "");
        if (outputBindingCwlModel.has_value()) {
            CommandOutputBinding outputBinding;
            outputBinding.loadCwlModel(outputBindingCwlModel.value());
            Output::setOutputBinding(outputBinding);
        }


    }
    const DockerRequirement &Hint::getDockerRequirement() const {
        return dockerRequirement;
    }
    void Hint::setDockerRequirement(const DockerRequirement &dockerRequirement) {
        Hint::dockerRequirement = dockerRequirement;
    }
    const std::string &CommandOutputBinding::getGlob() const {
        return glob;
    }
    void CommandOutputBinding::setGlob(const std::string &glob) {
        CommandOutputBinding::glob = glob;
    }
    bool CommandOutputBinding::isLoadContents() const {
        return loadContents;
    }
    void CommandOutputBinding::setLoadContents(bool loadContents) {
        CommandOutputBinding::loadContents = loadContents;
    }
    const std::string &CommandOutputBinding::getOutputEval() const {
        return outputEval;
    }
    void CommandOutputBinding::setOutputEval(const std::string &outputEval) {
        CommandOutputBinding::outputEval = outputEval;
    }

    void CommandOutputBinding::loadCwlModel(CWLModel &cwlModel) {
        auto glob = CwlConverter::find(cwlModel, "glob", "");
        if (glob.has_value()) {
            CommandOutputBinding::setGlob(glob->getVal());
        }

        auto loadContents = CwlConverter::find(cwlModel, "loadContents", "");
        if (glob.has_value()) {
            if (loadContents->getVal().compare("true") == 0) {
                CommandOutputBinding::setLoadContents(true);
            } else {
                CommandOutputBinding::setLoadContents(false);
            }
        }

        auto outputEval = CwlConverter::find(cwlModel, "outputEval", "");
        if (outputEval.has_value()) {
            CommandOutputBinding::setOutputEval(outputEval->getVal());
        }

    }
    const std::string &EnvironmentDef::getEnvName() const {
        return envName;
    }
    void EnvironmentDef::setEnvName(const std::string &envName) {
        EnvironmentDef::envName = envName;
    }
    const std::string &EnvironmentDef::getEnvValue() const {
        return envValue;
    }
    void EnvironmentDef::setEnvValue(const std::string &envValue) {
        EnvironmentDef::envValue = envValue;
    }
}