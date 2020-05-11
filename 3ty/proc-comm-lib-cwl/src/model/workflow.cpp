//
// Created by bla on 30/04/20.
//

#include "workflow.hpp"
#include "../cwlconverter.cpp"

namespace Workflow {
    const std::string &Workflow::getId() const {
        return id;
    }

    void Workflow::setId(const std::string &id) {
        Workflow::id = id;
    }

    const std::string &Workflow::getLabel() const {
        return label;
    }

    void Workflow::setLabel(const std::string &label) {
        Workflow::label = label;
    }

    const std::string &Workflow::getDoc() const {
        return doc;
    }

    void Workflow::setDoc(const std::string &doc) {
        Workflow::doc = doc;
    }

    const std::list<WorkflowOutputParameter> &Workflow::getOutputs() const {
        return outputs;
    }
    void Workflow::setOutputs(const std::list<WorkflowOutputParameter> &outputs) {
        Workflow::outputs = outputs;
    }
    const std::list<CommandLineTool::Requirement> &Workflow::getRequirements() const {
        return requirements;
    }
    void Workflow::setRequirements(const std::list<CommandLineTool::Requirement> &requirements) {
        Workflow::requirements = requirements;
    }
    const std::list<CommandLineTool::Hint> &Workflow::getHints() const {
        return hints;
    }
    void Workflow::setHints(const std::list<CommandLineTool::Hint> &hints) {
        Workflow::hints = hints;
    }
    const std::string &Workflow::getCwlVersion() const {
        return cwlVersion;
    }
    void Workflow::setCwlVersion(const std::string &cwlVersion) {
        Workflow::cwlVersion = cwlVersion;
    }

    void Workflow::loadCwlModel(CWLModel cwlModel) {

        auto id = CwlConverter::find(cwlModel, "id", "");
        if (id.has_value()) { setId(id->getVal()); }

        auto label = CwlConverter::find(cwlModel, "label", "");
        if (label.has_value()) { setLabel(label->getVal()); }

        auto doc = CwlConverter::find(cwlModel, "doc", "");
        if (doc.has_value()) { setDoc(doc->getVal()); }

        auto cwlVersion = CwlConverter::find(cwlModel, "cwlVersion", "");
        if (cwlVersion.has_value()) { setCwlVersion(cwlVersion->getVal()); }

        // inputs
        auto inputsCwlModel = CwlConverter::find(cwlModel, "inputs", "");
        std::list<CommandLineTool::Input> inputs;
        if (inputsCwlModel.has_value()) {
            for (auto const &inputData : inputsCwlModel->getList()) {
                std::string argName = inputData.getId();
                auto inpCwlModel = CwlConverter::find(inputsCwlModel.value(), argName, "");
                CommandLineTool::Input input;
                input.loadCwlModel(inpCwlModel.value());
                inputs.emplace_back(input);
            }
        }
        Workflow::setInputs(inputs);



        // outputs
        auto outputCwlModel = CwlConverter::find(cwlModel, "outputs", "");
        std::list<WorkflowOutputParameter> outputs;
        if (outputCwlModel.has_value()) {
            for (auto const &outputData : outputCwlModel->getList()) {
                std::string argName = outputData.getId();
                auto outCwlModel = CwlConverter::find(outputCwlModel.value(), argName, "");
                WorkflowOutputParameter output;
                output.loadCwlModel(outCwlModel.value());
                outputs.emplace_back(output);
            }
        }
        Workflow::setOutputs(outputs);


        // Requirements
        auto requirementsCwlModel = CwlConverter::find(cwlModel, "requirements", "");
        std::list<CommandLineTool::Requirement> requirements;
        if (requirementsCwlModel.has_value()) {


            // dockerRequirementHint
            auto dockerRequirementCwlModel = CwlConverter::find(requirementsCwlModel.value(), "DockerRequirement", "");
            if (dockerRequirementCwlModel.has_value()) {
                auto dockerPullCwlModel = CwlConverter::find(dockerRequirementCwlModel.value(), "dockerPull", "");
                if (dockerPullCwlModel.has_value()) {
                    CommandLineTool::DockerRequirement dockerRequirement;
                    dockerRequirement.setDockerPull(dockerPullCwlModel->getVal());
                    requirements.emplace_back(dockerRequirement);
                }
            }


            // envVarRequirement
            auto envVarRequirementCwlModel = CwlConverter::find(requirementsCwlModel.value(), "EnvVarRequirement", "");
            if (envVarRequirementCwlModel.has_value()) {
                CommandLineTool::EnvVarRequirement envVarRequirement;
                CommandLineTool::EnvironmentDef def;

                auto envDefCwlModel = CwlConverter::find(envVarRequirementCwlModel.value(), "envDef", "");
                if (envDefCwlModel.has_value()) {
                    CommandLineTool::EnvironmentDef envVarRequirement;
                    std::list<CommandLineTool::EnvironmentDef> environmentDefList;
                    for (auto const &envDefData : envDefCwlModel->getList()) {
                        std::string envName = envDefData.getId();
                        std::string envValue = CwlConverter::find(envDefCwlModel.value(), envName, "")->getVal();
                        CommandLineTool::EnvironmentDef env;
                        env.setEnvName(envName);
                        env.setEnvValue(envValue);
                        environmentDefList.emplace_back(env);
                    }
                }
                requirements.emplace_back(envVarRequirement);
            }
        }
        Workflow::setRequirements(requirements);

        // hints
        auto hintsCwlModel = CwlConverter::find(cwlModel, "hints", "");
        if (hintsCwlModel.has_value()) {
            std::list<CommandLineTool::Hint> hints;

            // dockerRequirementHint
            auto dockerRequirementCwlModel = CwlConverter::find(hintsCwlModel.value(), "DockerRequirement", "");
            if (dockerRequirementCwlModel.has_value()) {
                auto dockerPullCwlModel = CwlConverter::find(dockerRequirementCwlModel.value(), "dockerPull", "");
                if (dockerPullCwlModel.has_value()) {
                    CommandLineTool::DockerRequirement dockerRequirement;
                    dockerRequirement.setDockerPull(dockerPullCwlModel->getVal());
                    CommandLineTool::Hint dockerRequirementHint;
                    dockerRequirementHint.setDockerRequirement(dockerRequirement);
                    hints.emplace_back(dockerRequirementHint);
                }
            }
            Workflow::setHints(hints);
        }


        // steps
        auto stepsCwlModel = CwlConverter::find(cwlModel, "steps", "");
        if (stepsCwlModel.has_value()) {
            std::list<WorkflowStep> steps;
            for (auto const &stepData : stepsCwlModel->getList()) {
                std::string stepName = stepData.getId();
                auto stepCwlModel = CwlConverter::find(stepData, stepName, "");
                WorkflowStep workflowStep;
                workflowStep.setLabel(stepName);
                workflowStep.loadCwlModel(stepCwlModel.value());
                steps.emplace_back(workflowStep);
            }
            Workflow::setSteps(steps);
        }

    }
    const std::list<CommandLineTool::Input> &Workflow::getInputs() const {
        return inputs;
    }
    void Workflow::setInputs(const std::list<CommandLineTool::Input> &inputs) {
        Workflow::inputs = inputs;
    }
    const std::list<WorkflowStep> &Workflow::getSteps() const {
        return steps;
    }
    void Workflow::setSteps(const std::list<WorkflowStep> &steps) {
        Workflow::steps = steps;
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
    const std::string &WorkflowOutputParameter::getId() const {
        return id;
    }
    void WorkflowOutputParameter::setId(const std::string &id) {
        WorkflowOutputParameter::id = id;
    }
    const std::string &WorkflowOutputParameter::getLabel() const {
        return label;
    }
    void WorkflowOutputParameter::setLabel(const std::string &label) {
        WorkflowOutputParameter::label = label;
    }
    const std::list<std::string> &WorkflowOutputParameter::getSecondaryFiles() const {
        return secondaryFiles;
    }
    void WorkflowOutputParameter::setSecondaryFiles(const std::list<std::string> &secondaryFiles) {
        WorkflowOutputParameter::secondaryFiles = secondaryFiles;
    }
    bool WorkflowOutputParameter::isStreamable() const {
        return streamable;
    }
    void WorkflowOutputParameter::setStreamable(bool streamable) {
        WorkflowOutputParameter::streamable = streamable;
    }
    const std::string &WorkflowOutputParameter::getDoc() const {
        return doc;
    }
    void WorkflowOutputParameter::setDoc(const std::string &doc) {
        WorkflowOutputParameter::doc = doc;
    }
    const CommandOutputBinding &WorkflowOutputParameter::getOutputBinding() const {
        return outputBinding;
    }
    void WorkflowOutputParameter::setOutputBinding(const CommandOutputBinding &outputBinding) {
        WorkflowOutputParameter::outputBinding = outputBinding;
    }
    const std::string &WorkflowOutputParameter::getFormat() const {
        return format;
    }
    void WorkflowOutputParameter::setFormat(const std::string &format) {
        WorkflowOutputParameter::format = format;
    }
    const std::string &WorkflowOutputParameter::getOutputSource() const {
        return outputSource;
    }
    void WorkflowOutputParameter::setOutputSource(const std::string &outputSource) {
        WorkflowOutputParameter::outputSource = outputSource;
    }
    const std::string &WorkflowOutputParameter::getType() const {
        return type;
    }
    void WorkflowOutputParameter::setType(const std::string &type) {
        WorkflowOutputParameter::type = type;
    }
    void WorkflowOutputParameter::loadCwlModel(CWLModel &cwlModel) {


        //id
        auto id = CwlConverter::find(cwlModel, "id", "");
        if (id.has_value()) {
            WorkflowOutputParameter::setId(id->getVal());
        }

        //label
        auto label = CwlConverter::find(cwlModel, "label", "");
        if (label.has_value()) {
            WorkflowOutputParameter::setLabel(label->getVal());
        }

        //doc
        auto doc = CwlConverter::find(cwlModel, "doc", "");
        if (doc.has_value()) {
            WorkflowOutputParameter::setDoc(doc->getVal());
        }

        //format
        auto format = CwlConverter::find(cwlModel, "format", "");
        if (format.has_value()) {
            WorkflowOutputParameter::setFormat(format->getVal());
        }

        //type
        auto type = CwlConverter::find(cwlModel, "type", "");
        if (type.has_value()) {
            WorkflowOutputParameter::setType(type->getVal());
        }

        //outputBinding
        auto outputBindingCwlModel = CwlConverter::find(cwlModel, "outputBinding", "");
        if (outputBindingCwlModel.has_value()) {
            CommandOutputBinding outputBinding;
            outputBinding.loadCwlModel(outputBindingCwlModel.value());
            WorkflowOutputParameter::setOutputBinding(outputBinding);
        }


    }
    const std::string &WorkflowStepInput::getId() const {
        return id;
    }
    void WorkflowStepInput::setId(const std::string &id) {
        WorkflowStepInput::id = id;
    }
    const std::list<std::string> &WorkflowStepInput::getSource() const {
        return source;
    }
    void WorkflowStepInput::setSource(const std::list<std::string> &source) {
        WorkflowStepInput::source = source;
    }
    const std::string &WorkflowStepInput::getDefaultValue() const {
        return defaultValue;
    }
    void WorkflowStepInput::setDefaultValue(const std::string &defaultValue) {
        WorkflowStepInput::defaultValue = defaultValue;
    }
    const std::string &WorkflowStepInput::getValueFrom() const {
        return valueFrom;
    }
    void WorkflowStepInput::setValueFrom(const std::string &valueFrom) {
        WorkflowStepInput::valueFrom = valueFrom;
    }
    const std::string &WorkflowStepOutput::getId() const {
        return id;
    }
    void WorkflowStepOutput::setId(const std::string &id) {
        WorkflowStepOutput::id = id;
    }
    const std::string &WorkflowStep::getId() const {
        return id;
    }
    void WorkflowStep::setId(const std::string &id) {
        WorkflowStep::id = id;
    }
    const std::map<std::string, std::string> &WorkflowStep::getIn() const {
        return in;
    }
    void WorkflowStep::setIn(const std::map<std::string, std::string> &in) {
        WorkflowStep::in = in;
    }
    const std::list<std::string> &WorkflowStep::getOut() const {
        return out;
    }
    void WorkflowStep::setOut(const std::list<std::string> &out) {
        WorkflowStep::out = out;
    }
    const CommandLineTool::CommandLineTool &WorkflowStep::getRun() const {
        return run;
    }
    void WorkflowStep::setRun(const CommandLineTool::CommandLineTool &run) {
        WorkflowStep::run = run;
    }
    const std::list<CommandLineTool::Requirement> &WorkflowStep::getRequirements() const {
        return requirements;
    }
    void WorkflowStep::setRequirements(const std::list<CommandLineTool::Requirement> &requirements) {
        WorkflowStep::requirements = requirements;
    }
    const std::list<CommandLineTool::Hint> &WorkflowStep::getHints() const {
        return hints;
    }
    void WorkflowStep::setHints(const std::list<CommandLineTool::Hint> &hints) {
        WorkflowStep::hints = hints;
    }
    const std::string &WorkflowStep::getLabel() const {
        return label;
    }
    void WorkflowStep::setLabel(const std::string &label) {
        WorkflowStep::label = label;
    }
    const std::string &WorkflowStep::getDoc() const {
        return doc;
    }
    void WorkflowStep::setDoc(const std::string &doc) {
        WorkflowStep::doc = doc;
    }
    const std::string &WorkflowStep::getScatter() const {
        return scatter;
    }
    void WorkflowStep::setScatter(const std::string &scatter) {
        WorkflowStep::scatter = scatter;
    }

    void WorkflowStep::loadCwlModel(CWLModel &cwlModel) {

        auto inCwlModel = CwlConverter::find(cwlModel, "in", "");

        if (inCwlModel.has_value()) {
            std::map<std::string, std::string> in;
            for (auto const &stepData : inCwlModel->getList()) {
                std::string stepInArg = stepData.getId();
                std::string stepInArgValue = CwlConverter::find(stepData, stepInArg, "")->getVal();
                in[stepInArg]=stepInArgValue;
            }
            WorkflowStep::setIn(in);
        }


        auto outCwlModel = CwlConverter::find(cwlModel, "out", "");
        if (outCwlModel.has_value()) {
            std::list<std::string> out;
            for (auto const &stepData : outCwlModel->getList()) {
                std::string stepOutArg = stepData.getVal();
                out.emplace_back(stepOutArg);
            }
            WorkflowStep::setOut(out);
        }

        auto runCwlModel = CwlConverter::find(cwlModel, "run", "");
    }
}

