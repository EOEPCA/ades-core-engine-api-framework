//
// Created by bla on 30/04/20.
//

#ifndef RESTJSON_WORKFLOW_HPP
#define RESTJSON_WORKFLOW_HPP


#include <string>
#include <map>
#include <any>
#include <list>
#include "commandlinetool.hpp"

namespace Workflow {
/**
 * CommandOutputBinding class
 * https://www.commonwl.org/v1.0/Workflow#CommandOutputBinding
 */
    class CommandOutputBinding {
    private:
        std::string glob;
        bool loadContents;
        std::string outputEval;
    public:
        const std::string &getGlob() const;
        void setGlob(const std::string &glob);

        bool isLoadContents() const;
        void setLoadContents(bool loadContents);

        const std::string &getOutputEval() const;
        void setOutputEval(const std::string &outputEval);

        void loadCwlModel(CWLModel &model);

    };

/**
 * WorkflowOutputParameter class
 * https://www.commonwl.org/v1.0/Workflow#WorkflowOutputParameter
 */
    class WorkflowOutputParameter {
    private:
        std::string id;
        std::string label;
        std::list<std::string> secondaryFiles;
        bool streamable;
        std::string doc;
        CommandOutputBinding outputBinding;
        std::string format;
        std::string outputSource;
        // linkmerge
        std::string type;
    public:
        const std::string &getId() const;
        void setId(const std::string &id);

        const std::string &getLabel() const;
        void setLabel(const std::string &label);

        const std::list<std::string> &getSecondaryFiles() const;
        void setSecondaryFiles(const std::list<std::string> &secondaryFiles);

        bool isStreamable() const;
        void setStreamable(bool streamable);

        const std::string &getDoc() const;
        void setDoc(const std::string &doc);

        const CommandOutputBinding &getOutputBinding() const;
        void setOutputBinding(const CommandOutputBinding &outputBinding);

        const std::string &getFormat() const;
        void setFormat(const std::string &format);

        const std::string &getOutputSource() const;
        void setOutputSource(const std::string &outputSource);

        const std::string &getType() const;
        void setType(const std::string &type);

        void loadCwlModel(CWLModel &model);

    };

/**
 * class WorkflowStepInput
 * https://www.commonwl.org/v1.0/Workflow#WorkflowStepInput
 */
    class WorkflowStepInput {
    private:
        std::string id;
        std::list<std::string> source;
        //linkmerge
        std::string defaultValue;
        std::string valueFrom;
    public:
        const std::string &getId() const;
        void setId(const std::string &id);

        const std::list<std::string> &getSource() const;
        void setSource(const std::list<std::string> &source);

        const std::string &getDefaultValue() const;
        void setDefaultValue(const std::string &defaultValue);

        const std::string &getValueFrom() const;
        void setValueFrom(const std::string &valueFrom);
    };

    /**
     * class WorkflowStepOutput
     * https://www.commonwl.org/v1.0/Workflow#WorkflowStepOutput
     */

    class WorkflowStepOutput {
    private:
        std::string id;
    public:
        const std::string &getId() const;
        void setId(const std::string &id);
    };

/**
 * class  WorkflowStep
 * https://www.commonwl.org/v1.0/Workflow#WorkflowStep
 */
    class WorkflowStep {
    private:
        std::string id;
        //std::map<std::string, WorkflowStepInput> in;
        std::map<std::string, std::string> in;
        //std::map<std::string, WorkflowStepOutput> out;
        std::list<std::string> out;
        CommandLineTool::CommandLineTool run;
        std::list<CommandLineTool::Requirement> requirements;
        std::list<CommandLineTool::Hint> hints;
        std::string label;
        std::string doc;
        std::string scatter;
        //ScatterMethod
    public:
        const std::string &getId() const;
        void setId(const std::string &id);

        const std::map<std::string, std::string> &getIn() const;
        void setIn(const std::map<std::string, std::string> &in);

        const std::list<std::string> &getOut() const;
        void setOut(const std::list<std::string> &out);

        const CommandLineTool::CommandLineTool &getRun() const;
        void setRun(const CommandLineTool::CommandLineTool &run);

        const std::list<CommandLineTool::Requirement> &getRequirements() const;
        void setRequirements(const std::list<CommandLineTool::Requirement> &requirements);

        const std::list<CommandLineTool::Hint> &getHints() const;
        void setHints(const std::list<CommandLineTool::Hint> &hints);

        const std::string &getLabel() const;
        void setLabel(const std::string &label);

        const std::string &getDoc() const;
        void setDoc(const std::string &doc);

        const std::string &getScatter() const;
        void setScatter(const std::string &scatter);

        void loadCwlModel(CWLModel &cwlModel);

    };

/**
 * class Workflow
 * https://www.commonwl.org/v1.0/Workflow#Workflow
 */
    class Workflow {
    private:
        std::string id;
        std::string label;
        std::string doc;
        std::list<CommandLineTool::Input> inputs;
        std::list<WorkflowOutputParameter> outputs;
        std::list<CommandLineTool::Requirement> requirements;
        std::list<CommandLineTool::Hint> hints;
        std::string cwlVersion;
        std::list<WorkflowStep> steps;
//    steps;

    public:
        const std::string &getId() const;
        void setId(const std::string &id);

        const std::string &getLabel() const;
        void setLabel(const std::string &label);

        const std::string &getDoc() const;
        void setDoc(const std::string &doc);

        const std::list<WorkflowOutputParameter> &getOutputs() const;
        void setOutputs(const std::list<WorkflowOutputParameter> &outputs);

        const std::list<CommandLineTool::Requirement> &getRequirements() const;
        void setRequirements(const std::list<CommandLineTool::Requirement> &requirements);

        const std::list<CommandLineTool::Hint> &getHints() const;
        void setHints(const std::list<CommandLineTool::Hint> &hints);

        const std::string &getCwlVersion() const;
        void setCwlVersion(const std::string &cwlVersion);

        const std::list<CommandLineTool::Input> &getInputs() const;
        void setInputs(const std::list<CommandLineTool::Input> &inputs);

        const std::list<WorkflowStep> &getSteps() const;
        void setSteps(const std::list<WorkflowStep> &steps);

        void loadCwlModel(CWLModel cwlModel);


    };

}
#endif //RESTJSON_WORKFLOW_HPP
