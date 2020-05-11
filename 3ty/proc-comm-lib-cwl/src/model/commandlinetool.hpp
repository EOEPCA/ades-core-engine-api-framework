//
// Created by bla on 30/04/20.
//

#ifndef RESTJSON_COMMANDLINETOOL_HPP
#define RESTJSON_COMMANDLINETOOL_HPP

#include <string>
#include <list>
#include <converter/model.hpp>

namespace CommandLineTool {
/**
 * class CommandLineBinding
 * https://www.commonwl.org/v1.0/CommandLineTool.html#CommandLineBinding
 */
    class CommandLineBinding {
    private:
        bool loadContents;
        int position;
        std::string prefix;
        bool separate = true;
        std::string itemSeparator;
        std::string valueFrom;
        bool shellQuote = true;
    public:
        bool isLoadContents() const;
        void setLoadContents(bool loadContents);

        int getPosition() const;
        void setPosition(int position);

        const std::string &getPrefix() const;
        void setPrefix(const std::string &prefix);

        bool isSeparate() const;
        void setSeparate(bool separate);

        const std::string &getItemSeparator() const;
        void setItemSeparator(const std::string &itemSeparator);

        const std::string &getValueFrom() const;
        void setValueFrom(const std::string &valueFrom);

        bool isShellQuote() const;
        void setShellQuote(bool shellQuote);

        void loadCwlModel(CWLModel cwlModel);

    };

/**
 * Class Input
 * https://www.commonwl.org/v1.0/CommandLineTool.html#CommandInputParameter
 */
    class Input {
    private:
        std::string id;
        std::string label;
        std::list<std::string> secondaryFiles;
        bool streamable;
        std::string doc;
        std::string format;
        CommandLineBinding inputBinding;
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

        const std::string &getFormat() const;
        void setFormat(const std::string &format);

        const CommandLineBinding &getInputBinding() const;
        void setInputBinding(const CommandLineBinding &inputBinding);

        const std::string &getType() const;
        void setType(const std::string &type);

        void loadCwlModel(CWLModel cwlModel);
    };

/**
 * class CommandOutputBinding
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
 * Output class
 * https://www.commonwl.org/v1.0/CommandLineTool.html#CommandOutputParameter
 */
    class Output {
    private:
        std::string id;
        std::string label;
        std::list<std::string> secondaryFiles;
        bool streamable;
        std::string doc;
        std::string format;
        CommandOutputBinding outputBinding;
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

        const std::string &getFormat() const;
        void setFormat(const std::string &format);

        const CommandOutputBinding &getOutputBinding() const;
        void setOutputBinding(const CommandOutputBinding &outputBinding);

        const std::string &getType() const;
        void setType(const std::string &type);

        void loadCwlModel(CWLModel &model);
    };

    class Requirement {
    public:
        Requirement()=default;
        virtual ~Requirement() {}

    };

    /**
     * class EnvironmentDef
     * https://www.commonwl.org/v1.0/CommandLineTool.html#EnvironmentDef
     */

    class EnvironmentDef {
    private:
        std::string envName;
        std::string envValue;
    public:
        const std::string &getEnvName() const;
        void setEnvName(const std::string &envName);

        const std::string &getEnvValue() const;
        void setEnvValue(const std::string &envValue);
    };


    /**
     * class EnvVarRequirement
     *  https://www.commonwl.org/v1.0/CommandLineTool.html#EnvVarRequirement
     */
     class EnvVarRequirement : public Requirement {
     public:
         EnvVarRequirement():Requirement(){}
     private:

         std::list<EnvironmentDef> environmentDefs;

     };




    /**
     * class DockerRequirement
     * https://www.commonwl.org/v1.0/CommandLineTool.html#DockerRequirement
     */
    class DockerRequirement : public Requirement {
    public:
        DockerRequirement():Requirement(){}
    private:
        std::string dockerPull;
        std::string dockerLoad;
        std::string dockerFile;
        std::string dockerImport;
        std::string dockerImageId;
        std::string dockerOutputDirectory;
    public:
        const std::string &getDockerPull() const;
        void setDockerPull(const std::string &dockerPull);

        const std::string &getDockerLoad() const;
        void setDockerLoad(const std::string &dockerLoad);

        const std::string &getDockerFile() const;
        void setDockerFile(const std::string &dockerFile);

        const std::string &getDockerImport() const;
        void setDockerImport(const std::string &dockerImport);

        const std::string &getDockerImageId() const;
        void setDockerImageId(const std::string &dockerImageId);

        const std::string &getDockerOutputDirectory() const;
        void setDockerOutputDirectory(const std::string &dockerOutputDirectory);
    };

/**
 * Class Hint
 * https://www.commonwl.org/v1.0/CommandLineTool.html#Requirements_and_hints
 */
    class Hint {
    private :
        DockerRequirement dockerRequirement;
    public:
        void loadCwlModel(CWLModel cwlModel);
        const DockerRequirement &getDockerRequirement() const;
        void setDockerRequirement(const DockerRequirement &dockerRequirement);
    };

    class CommandLineTool {
    private:
        std::string id;
        std::string label;
        std::string doc;
        std::string cwlVersion;
        std::string baseCommand;
        std::string successCodes;
        std::string temporaryFailCodes;
        std::string permanentFailCodes;
        std::list<Hint> hints;
        std::list<Input> inputs;
        std::list<Output> outputs;
        std::list<Requirement> requirements;
        std::list<std::string> arguments;
        std::string std_in;
        std::string std_err;
        std::string std_out;

    public:
        const std::string &getId() const;
        void setId(const std::string &id);

        const std::string &getLabel() const;
        void setLabel(const std::string &label);

        const std::string &getDoc() const;
        void setDoc(const std::string &doc);

        const std::string &getCwlVersion() const;
        void setCwlVersion(const std::string &cwlVersion);

        const std::string &getBaseCommand() const;
        void setBaseCommand(const std::string &baseCommand);

        const std::string &getSuccessCodes() const;
        void setSuccessCodes(const std::string &successCodes);

        const std::string &getTemporaryFailCodes() const;
        void setTemporaryFailCodes(const std::string &temporaryFailCodes);

        const std::string &getPermanentFailCodes() const;
        void setPermanentFailCodes(const std::string &permanentFailCodes);

        const std::list<Hint> &getHints() const;
        void setHints(const std::list<Hint> &hints);

        const std::list<Input> &getInputs() const;
        void setInputs(const std::list<Input> &inputs);

        const std::list<Output> &getOutputs() const;
        void setOutputs(const std::list<Output> &outputs);

        const std::list<Requirement> &getRequirements() const;
        void setRequirements(const std::list<Requirement> &requirements);

        const std::list<std::string> &getArguments() const;
        void setArguments(const std::list<std::string> &arguments);

        const std::string &getStdIn() const;
        void setStdIn(const std::string &stdIn);

        const std::string &getStdErr() const;
        void setStdErr(const std::string &stdErr);

        const std::string &getStdOut() const;
        void setStdOut(const std::string &stdOut);

        void loadCwlModel(CWLModel cwlModel);
    };

}

#endif //RESTJSON_COMMANDLINETOOL_HPP
