//
// Created by bla on 06/05/20.
//


#include <fstream>
#include <gtest/gtest.h>
#include <graph.hpp>

TEST(TEST1_CWL_PARSER, Parsing_cwl_1) {

    std::string workflow_yaml = "tests/application/data/workflow.yaml";


    Graph graph;
    graph.loadCwlFile(workflow_yaml);

    std::string baseCommand = graph.getCommandLineTool().getBaseCommand();
    std::string expected_baseCommand="echo";

    int firstInputPosition = graph.getCommandLineTool().getInputs().front().getInputBinding().getPosition();
    int expected_firstInputPosition=1;

    std::string firstInputPrefix = graph.getCommandLineTool().getInputs().front().getInputBinding().getPrefix();
    std::string expected_firstInputPrefix="--input";


    EXPECT_EQ(baseCommand, expected_baseCommand);
    EXPECT_EQ(firstInputPosition, expected_firstInputPosition);
    EXPECT_EQ(firstInputPrefix, expected_firstInputPrefix);


    std::string expected_workflowDoc = "Hello World Test Workflow";
    std::string workflowDoc = graph.getWorkflow().getDoc();

    std::string expected_workflowFirstInputType = "string";
    std::string workflowFirstInputType = graph.getWorkflow().getInputs().front().getType();

    std::string expected_workflowFirstInputPrefix="";
    std::string workflowFirstInputPrefix =  graph.getWorkflow().getInputs().front().getInputBinding().getPrefix();

    EXPECT_EQ(workflowDoc, expected_workflowDoc);
    EXPECT_EQ(workflowFirstInputType, expected_workflowFirstInputType);
    EXPECT_EQ(workflowFirstInputPrefix, expected_workflowFirstInputPrefix);


}

TEST(TEST1_CWL_PARSER, Parsing_cwl_2) {

    std::string workflow_yaml = "tests/application/data/fb.yaml";


    Graph graph;
    graph.loadCwlFile(workflow_yaml);

    std::string baseCommand = graph.getCommandLineTool().getBaseCommand();
    std::string expected_baseCommand="s2-thermal-index";

    int firstInputPosition = graph.getCommandLineTool().getInputs().front().getInputBinding().getPosition();
    int expected_firstInputPosition=2;

    std::string firstInputPrefix = graph.getCommandLineTool().getInputs().front().getInputBinding().getPrefix();
    std::string expected_firstInputPrefix="--data_path";


    EXPECT_EQ(baseCommand, expected_baseCommand);
    EXPECT_EQ(firstInputPosition, expected_firstInputPosition);
    EXPECT_EQ(firstInputPrefix, expected_firstInputPrefix);


    std::string expected_workflowDoc = "";
    std::string workflowDoc = graph.getWorkflow().getDoc();

    std::string expected_workflowFirstInputType = "";
    std::string workflowFirstInputType = graph.getWorkflow().getInputs().front().getType();

    std::string expected_workflowId="mainWorkflow";
    std::string workflowFirstId =  graph.getWorkflow().getId();

    EXPECT_EQ(workflowDoc, expected_workflowDoc);
    EXPECT_EQ(workflowFirstInputType, expected_workflowFirstInputType);
    EXPECT_EQ(workflowFirstId, expected_workflowId);

}