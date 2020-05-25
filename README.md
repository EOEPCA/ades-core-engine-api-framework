
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
![Build][build-shield]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/EOEPCA/template-svce">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">ades-core-engine-api-framework</h3>

  <p align="center">
    <a href="http://zoo-project.org/">ades-core-engine-api-framework</a>
    <br />
    <a href="#table-of-contents"><strong>Explore the docs »</strong></a>
    <br />
    <a href="https://github.com/EOEPCA/ades-core-engine-api-framework"></a>
    ·
    <a href="https://github.com/EOEPCA/ades-core-engine-api-framework/issues">Report Bug</a>
    ·
    <a href="https://github.com/EOEPCA/ades-core-engine-api-framework/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->

## Table of Contents

- [About the Project](#about-the-project)
  - [Built With](#built-with)
  - [Resources](#resources)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Testing](#testing)        
 - [Usage](#usage)
    - [Prerequisites](#prerequisites)
    - [Start](#start)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgements](#acknowledgements)

<!-- ABOUT THE PROJECT -->

## About The Project

The purpose of this project is to test the ADES workflow.

The final result will be a simple phrase that will be composed from an input string and an elaborated string.

Input starts from the WMS server and analyzed by the WPS service and processed for Argo Workflow

 
### Built With

- [Docker](https://www.docker.com/)

### Resources

- assets/main.cfg: configuration file copied into the Docker image
- assets/zoo/http: httpd configuration files

<!-- GETTING STARTED -->

## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

- [Internet access](https://en.wikipedia.org/wiki/Internet_access)
- [Docker](https://www.docker.com/)
- [Linux bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell))
- [curl](https://en.wikipedia.org/wiki/CURL)

### Installation

1. Get into Linux terminal

2. Clone the repo

```sh
git clone https://github.com/EOEPCA/ades-core-engine-api-framework.git
```

3. Change local directory

```sh
cd ades-core-engine-api-framework
```

5. Build application

```sh
./scripts/build.sh
```

If you are performing a local build the script creates a Docker Images:

```text
eoepca-ades-core:1.0
proc-comm-zoo:1.0
```

### Testing

1. Run local image

```sh
docker run --rm  -d --name zoo -p 7777:80   eoepca-ades-core:1.0
```

2. Send a GetCapabilities request 

```ssh
curl -L  "http://localhost:7777/zoo/?service=WPS&version=1.0.0&request=GetCapabilities"
```

```xml
<?xml version="1.0" encoding="UTF-8"?>
<wps:Capabilities xmlns:ows="http://www.opengis.net/ows/1.1" xmlns:wps="http://www.opengis.net/wps/1.0.0" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.opengis.net/wps/1.0.0 http://schemas.opengis.net/wps/1.0.0/wpsGetCapabilities_response.xsd" service="WPS" version="1.0.0" xml:lang="en-US">
  <ows:ServiceIdentification>
    <ows:Title>Ellip-WPS</ows:Title>
    <ows:Fees>None</ows:Fees>
    <ows:AccessConstraints>none</ows:AccessConstraints>
  </ows:ServiceIdentification>
  <ows:ServiceProvider>
    <ows:ProviderName>xxxx</ows:ProviderName>
    <ows:ProviderSite xlink:href="https://www.xxxxx.com"/>
    <ows:ServiceContact>
      <ows:IndividualName>Operations Support team</ows:IndividualName>
      <ows:PositionName>xxxx</ows:PositionName>
      <ows:ContactInfo>
        <ows:Phone>
          <ows:Voice>+xxxxx</ows:Voice>
          <ows:Facsimile>False</ows:Facsimile>
        </ows:Phone>
        <ows:Address>
          <ows:DeliveryPoint>xxxxx</ows:DeliveryPoint>
          <ows:City>xx</ows:City>
          <ows:AdministrativeArea>False</ows:AdministrativeArea>
          <ows:PostalCode>xxx</ows:PostalCode>
          <ows:Country>IT</ows:Country>
          <ows:ElectronicMailAddress>support@xxxx.com</ows:ElectronicMailAddress>
        </ows:Address>
      </ows:ContactInfo>
    </ows:ServiceContact>
  </ows:ServiceProvider>
  <ows:OperationsMetadata>
    <ows:Operation name="GetCapabilities">
      <ows:DCP>
        <ows:HTTP>
          <ows:Get xlink:href="http://localhost:7777/zoo-bin/zoo_loader.cgi"/>
          <ows:Post xlink:href="http://localhost:7777/zoo-bin/zoo_loader.cgi"/>
        </ows:HTTP>
      </ows:DCP>
    </ows:Operation>
    <ows:Operation name="DescribeProcess">
      <ows:DCP>
        <ows:HTTP>
          <ows:Get xlink:href="http://localhost:7777/zoo-bin/zoo_loader.cgi"/>
          <ows:Post xlink:href="http://localhost:7777/zoo-bin/zoo_loader.cgi"/>
        </ows:HTTP>
      </ows:DCP>
    </ows:Operation>
    <ows:Operation name="Execute">
      <ows:DCP>
        <ows:HTTP>
          <ows:Get xlink:href="http://localhost:7777/zoo-bin/zoo_loader.cgi"/>
          <ows:Post xlink:href="http://localhost:7777/zoo-bin/zoo_loader.cgi"/>
        </ows:HTTP>
      </ows:DCP>
    </ows:Operation>
  </ows:OperationsMetadata>
  <wps:ProcessOfferings>
    <wps:Process wps:processVersion="1.0.0">
      <ows:Identifier>eoepcaadesundeployprocess</ows:Identifier>
      <ows:Title>Eoepca Deploy Process</ows:Title>
      <ows:Abstract>This method will undeploy an application encapsulated within a Docker container as a process accessible through the WPS interface.</ows:Abstract>
    </wps:Process>
    <wps:Process wps:processVersion="1">
      <ows:Identifier>longProcess</ows:Identifier>
      <ows:Title>Demo long process. </ows:Title>
      <ows:Abstract>This service doesn't do anything except taking its time, it demonstrates how to use the updateStatus function from your ZOO Service. </ows:Abstract>
      <ows:Metadata xlink:title="Demo GetStatus request"/>
    </wps:Process>
    <wps:Process wps:processVersion="1">
      <ows:Identifier>GetStatus</ows:Identifier>
      <ows:Title>Produce an updated ExecuteResponse document. </ows:Title>
      <ows:Abstract>Create an ExecuteResponse document from a sid (Service ID), it will use the niternal ZOO Kernel mechanisms to access the current status from a running Service and update the percentCompleted from the original backup file used by the ZOO Kernel when running a Service in background. </ows:Abstract>
      <ows:Metadata xlink:title="Demo GetStatus request"/>
    </wps:Process>
    <wps:Process wps:processVersion="1.0.0">
      <ows:Identifier>eoepcaadesdeployprocess</ows:Identifier>
      <ows:Title>Eoepca Deploy Process</ows:Title>
      <ows:Abstract>This method will deploy an application encapsulated within a Docker container as a process accessible through the WPS interface.</ows:Abstract>
    </wps:Process>
  </wps:ProcessOfferings>
  <wps:Languages>
    <wps:Default>
      <ows:Language>en-US</ows:Language>
    </wps:Default>
    <wps:Supported>
      <ows:Language>en-US</ows:Language>
      <ows:Language>en-GB</ows:Language>
    </wps:Supported>
  </wps:Languages>
</wps:Capabilities>
```

3. Send a OGC API - Processes request 

```ssh
curl -s -L "http://localhost:7777/wps3/processes" -H "accept: application/json"
```

```json
{
  "processes": [
    {
      "id": "eoepcaadesundeployprocess",
      "title": "Eoepca Deploy Process",
      "abstract": "This method will undeploy an application encapsulated within a Docker container as a process accessible through the WPS interface.",
      "version": "1.0.0",
      "jobControlOptions": [
        "sync-execute",
        "async-execute",
        "dismiss"
      ],
      "outputTransmission": [
        "value",
        "reference"
      ],
      "links": [
        {
          "rel": "canonical",
          "type": "application/json",
          "title": "Process Description",
          "href": "/watchjob/processes/eoepcaadesundeployprocess/"
        }
      ]
    },
    {
      "id": "longProcess",
      "title": "Demo long process. ",
      "abstract": "This service doesn't do anything except taking its time, it demonstrates how to use the updateStatus function from your ZOO Service. ",
      "version": "1.0.0",
      "jobControlOptions": [
        "sync-execute",
        "async-execute",
        "dismiss"
      ],
      "outputTransmission": [
        "value",
        "reference"
      ],
      "links": [
        {
          "rel": "canonical",
          "type": "application/json",
          "title": "Process Description",
          "href": "/watchjob/processes/longProcess/"
        }
      ]
    },
    {
      "id": "GetStatus",
      "title": "Produce an updated ExecuteResponse document. ",
      "abstract": "Create an ExecuteResponse document from a sid (Service ID), it will use the niternal ZOO Kernel mechanisms to access the current status from a running Service and update the percentCompleted from the original backup file used by the ZOO Kernel when running a Service in background. ",
      "version": "1.0.0",
      "jobControlOptions": [
        "sync-execute",
        "async-execute",
        "dismiss"
      ],
      "outputTransmission": [
        "value",
        "reference"
      ],
      "links": [
        {
          "rel": "canonical",
          "type": "application/json",
          "title": "Process Description",
          "href": "/watchjob/processes/GetStatus/"
        }
      ]
    },
    {
      "id": "eoepcaadesdeployprocess",
      "title": "Eoepca Deploy Process",
      "abstract": "This method will deploy an application encapsulated within a Docker container as a process accessible through the WPS interface.",
      "version": "1.0.0",
      "jobControlOptions": [
        "sync-execute",
        "async-execute",
        "dismiss"
      ],
      "outputTransmission": [
        "value",
        "reference"
      ],
      "links": [
        {
          "rel": "canonical",
          "type": "application/json",
          "title": "Process Description",
          "href": "/watchjob/processes/eoepcaadesdeployprocess/"
        }
      ]
    }
  ]
}
```

## Usage


### Prerequisites

- [dev-env-argo](https://github.com/EOEPCA/dev-env-argo)
- [curl](https://en.wikipedia.org/wiki/CURL)
- [Kubernetes Persistent Volume and Persistent Volume Claim](https://kubernetes.io/docs/concepts/storage/persistent-volumes/):	
To share a workspace among the various nodes of the workflow, we need a common filesystem, for this application we will use Kubernetes Persistent Volume. In order to create one, write the file **eoepca-pv-and-pvc.yaml** with the following content:

```
apiVersion: v1
kind: PersistentVolume
metadata:
  name: eoepca-pv
  labels:
    type: local
spec:
  storageClassName: manual
  capacity:
    storage: 10Gi
  accessModes:
    - ReadWriteOnce
  persistentVolumeReclaimPolicy: Retain
  storageClassName: standard
  hostPath:
    path: "/mnt/data"

---

apiVersion: v1
kind: PersistentVolumeClaim
metadata:
  name: eoepca-pvc
spec:
  accessModes:
  - ReadWriteOnce
  storageClassName: standard
  resources:
    requests:
      storage: 3Gi
```
and run the following  command:
```
 kubectl create -f eoepca-pv-and-pvc.yaml
```

### The application

#### CWL definition
The cwl that this sample Ades service runs can be found at the following address:
[https://github.com/EOEPCA/proc-ades/blob/develop/test/sample_apps/metadata_extractor/workflow.cwl](https://github.com/EOEPCA/proc-ades/blob/develop/test/sample_apps/metadata_extractor/workflow.cwl)

#### Docker Image
The docker image used in this sample application can be found at the following address:
[https://hub.docker.com/r/blasco/eoepca-eo-tools](https://hub.docker.com/r/blasco/eoepca-eo-tools)

The image contains the following two scripts necessary to run the workflow: 
**/usr/bin/stagein**
```
#!/bin/bash
URL=$1
echo  "retrieving enclosure of $URL"
enclosure=$(opensearch-client -p count=1 -p do=terradue $URL enclosure)

echo  "Enclosure: $enclosure"
DOWNLOAD_PATH="/tmp/eoepca"
mkdir -p $DOWNLOAD_PATH

echo  "Downloading product to $DOWNLOAD_PATH"
path=$(ciop-copy $enclosure -O $DOWNLOAD_PATH)

echo  "Downloaded to $path"
echo  $path >> /tmp/output.txt
```

**process_s3_metadata**
```
#!/bin/bash

metadata-extractor -p --format=atom -m SENTINEL3 $1 > /tmp/eopca/s3_metadata.atom
mkdir /tmp/eoepca
echo  "/tmp/eopca/s3_metadata.atom"
```

### Start

Our tutorial will start in the dev-env-argo environment

1) Start "eoepca-ades-core"

```shell script
docker run --rm  -d --name zoo -p 7777:80 --network host  eoepca-ades-core:1.0
```

with the option `--network host` the port 7777 will be ignored

2) run a getProcess to test the installation:

```shell script
curl -s -L "http://localhost/wps3/processes" -H "accept: application/json"
```


3) install the new service

create json file parameter `deploy.json`

```json
{
  "inputs": [
    {
      "id": "applicationPackage",
      "input": {
        "format": {
          "mimeType": "application/xml"
        },
        "value": {
          "inlineValue": "https://raw.githubusercontent.com/EOEPCA/proc-ades/develop/test/sample_apps/metadata_extractor/ows.xml"
        }
      }
    }
  ],
  "outputs": [
    {
      "format": {
        "mimeType": "string",
        "schema": "string",
        "encoding": "string"
      },
      "id": "deployResult",
      "transmissionMode": "value"
    }
  ],
  "mode": "async",
  "response": "raw"
}
```

run:
```shell script
curl -v -L -X POST "http://localhost:7777/wps3/processes/eoepcaadesdeployprocess/jobs" -H  \
  "accept: application/json" -H  "Prefer: respond-async" -H  "Content-Type: application/json" -d@deploy.json
```

```text
>   "accept: application/json" -H  "Prefer: respond-async" -H  "Content-Type: application/json" -d@deploy.json
* About to connect() to localhost port 7777 (#0)
*   Trying 127.0.0.1...
* Connected to localhost (127.0.0.1) port 7777 (#0)
> POST /wps3/processes/eoepcaadesdeployprocess/jobs HTTP/1.1
> User-Agent: curl/7.29.0
> Host: localhost:7777
> accept: application/json
> Prefer: respond-async
> Content-Type: application/json
> Content-Length: 543
>
* upload completely sent off: 543 out of 543 bytes
< HTTP/1.1 201 Created
< Date: Mon, 25 May 2020 14:11:43 GMT
< Server: Apache/2.4.6 (CentOS)
< X-Powered-By: ZOO@ZOO-Project
< Location: /watchjob/processes/eoepcaadesdeployprocess/jobs/a93616e8-9e91-11ea-a71d-0242ac110002
< Transfer-Encoding: chunked
< Content-Type: application/json;charset=UTF-8
<
* Connection #0 to host localhost left intact
```

running again the getProcess we can read a new service:

```json
{
      "id": "eo_metadata_generation_1_0",
      "title": "Earth Observation Metadata Generation",
      "abstract": "Earth Observation Metadata Generation",
      "version": "1.0.0.0",
      "jobControlOptions": [
        "sync-execute",
        "async-execute",
        "dismiss"
      ],
      "outputTransmission": [
        "value",
        "reference"
      ],
      "links": [
        {
          "rel": "canonical",
          "type": "application/json",
          "title": "Process Description",
          "href": "/watchjob/processes/eo_metadata_generation_1_0/"
        }
      ]
    }
```



4) Looking for the our service argo:
 
```shell script
curl -s -L "http://localhost/wps3/processes/eo_metadata_generation_1_0" -H "accept: application/json"
```

```json
{
  "process": {
    "id": "eo_metadata_generation_1_0",
    "title": "Earth Observation Metadata Generation",
    "abstract": "Earth Observation Metadata Generation",
    "version": "1.0.0.0",
    "jobControlOptions": [
      "sync-execute",
      "async-execute",
      "dismiss"
    ],
    "outputTransmission": [
      "value",
      "reference"
    ],
    "links": [
      {
        "rel": "canonical",
        "type": "application/json",
        "title": "Execute End Point",
        "href": "/watchjob/processes/eo_metadata_generation_1_0/jobs/"
      }
    ],
    "inputs": [
      {
        "id": "input_file",
        "title": "EO input file",
        "abstract": "Mandatory input file to generate metadata for",
        "minOccurs": "1",
        "maxOccurs": "0",
        "input": {
          "formats": [
            {
              "default": true,
              "mimeType": "application/json"
            },
            {
              "default": false,
              "mimeType": "application/json"
            },
            {
              "default": false,
              "mimeType": "application/yaml"
            },
            {
              "default": false,
              "mimeType": "application/atom+xml"
            },
            {
              "default": false,
              "mimeType": "application/opensearchdescription+xml"
            }
          ]
        }
      }
    ],
    "outputs": [
      {
        "id": "results",
        "title": "Outputs blah blah",
        "abstract": "results",
        "output": {
          "literalDataDomains": [
            {
              "dataType": {
                "name": "string"
              },
              "valueDefinition": {
                "anyValue": true
              }
            }
          ]
        }
      }
    ]
  }
}

```

For this release, "Argo" is only a simple ``echo workflow`` and is defined from CWL file:

```yaml
cwlVersion: v1.0

$namespaces:
  ows: http://www.opengis.net/ows/1.1
  stac: http://www.me.net/stac/cwl/extension
  opensearch: http://a9.com/-/spec/opensearch/1.1/

$graph:
- baseCommand: eoepca-metadata-extractor
  class: CommandLineTool
  hints:
    DockerRequirement:
      dockerPull: blasco/eoepca-eo-tools:latest
  id: metadata_extractor
  inputs:
    arg1:
    #   inputBinding:
    #     position: 1
    #     prefix: --base_dir
    #     valueFrom: $(self.path)
      type: Directory
      default: 
        class: Directory
        location: "/workspace"
    arg2:
      type: File
      inputBinding:
        position: 1
  outputs:
    results:
      outputBinding:
        glob: .
      type: Any
  requirements:
    EnvVarRequirement:
      envDef:
        PATH: /opt/anaconda/bin:/opt/anaconda/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
    ResourceRequirement: {}
    
  stderr: std.err
  stdout: std.out
- class: Workflow
  id: eo_metadata_generation # service id [WPS] map to wps:Input/ows:identifier
  label: Earth Observation Metadata Generation # title [WPS] map to wps:Input/ows:title
  doc: Earth Observation Metadata Generation # description [WPS] map to wps:Input/ows:abstract
  ows:version: 1.0 # workflow version
  inputs:
    base_dir: 
      type: Directory? 
      ows:ignore: True # [WPS] no mapping

    input_file:
      doc: Mandatory input file to generate metadata for # [WPS] maps to wps:Input/ows:abstract
      label: EO input file # [WPS] maps to wps:Input/ows:title
      type: File # no question mark indicates it is not optional. [WPS] maps to minOccurs = 1 (maxOccurs = 1 because it is not an array)
      # This file can be referenced by a STAC catalog
      stac:catalog: # [WPS] maps to wps:Supported/wps:Format with mimetype = application/json & application/yaml
        stac:href: catalog.json # optional catalogue URL. Default to file 'catalog.json'.
        stac:collection_id: post_event # name of the collection to fetch the input from
      # This file can be also referenced as an OpenSearch URL
      opensearch:url: {} # [WPS] maps to wps:Supported/wps:Format with mimetype = application/atom+xml & application/opensearchdescription+xml

  outputs:
    results: # parameter id [WPS] map to wps:Output/ows:identifier
      label: Outputs blah blah
      outputSource:
      - step1/results
      type:
        items: Directory
        type: array

  steps:
    step1:
      in:
        arg1: base_dir
        arg2: input_file
      out:
      - results
      run: '#metadata_extractor'
```

The parameter file ``argo.json``:

```json
{
  "inputs": [
    {
      "id": "input_file",
      "input": {
        "format": {
          "mimeType": "application/json"
        },
        "value": {
          "inlineValue": "https://catalog.terradue.com/sentinel3/search?uid=S3B_SL_1_RBT____20200520T050759_20200520T051059_20200520T060015_0179_039_105_0360_LN2_O_NR_004"
        }
      }
    }
  ],
  "outputs": [
    {
      "format": {
        "mimeType": "string",
        "schema": "string",
        "encoding": "string"
      },
      "id": "results",
      "transmissionMode": "value"
    }
  ],
  "mode": "async",
  "response": "raw"
} 
```

Run:

```shell script
curl -v -L -X POST "http://localhost/wps3/processes/eo_metadata_generation_1_0/jobs" -H  \
  "accept: application/json" -H  "Prefer: respond-async" -H  "Content-Type: application/json" -d@argo.json
```

Get Argo Jobs:

```shell script
curl  -v  -s -L "http://localhost/wps3/processes/eo_metadata_generation_1_0/jobs" -H "accept: application/json" 
```

```text
*   Trying 127.0.0.1...
* TCP_NODELAY set
* Connected to localhost (127.0.0.1) port 80 (#0)
> GET /wps3/processes/eo_metadata_generation_1_0/jobs HTTP/1.1
> Host: localhost
> User-Agent: curl/7.58.0
> accept: application/json
> 
< HTTP/1.1 200 OK 
< Date: Mon, 25 May 2020 15:53:53 GMT
< Server: Apache/2.4.6 (CentOS)
< X-Powered-By: ZOO@ZOO-Project
< Transfer-Encoding: chunked
< Content-Type: application/json;charset=UTF-8
< 
{ [421 bytes data]
* Connection #0 to host localhost left intact
[
  {
    "id": "06223bbe-9e9e-11ea-8f64-a0c5899f98fe",
    "infos": {
      "status": "successful",
      "message": "ZOO-Kernel successfully run your service!",
      "links": [
        {
          "Title": "Status location",
          "href": "/watchjob/processes/eo_metadata_generation_1_0/jobs/06223bbe-9e9e-11ea-8f64-a0c5899f98fe"
        },
        {
          "Title": "Result location",
          "href": "/watchjob/processes/eo_metadata_generation_1_0/jobs/06223bbe-9e9e-11ea-8f64-a0c5899f98fe/result"
        }
      ]
    }
  }
]

```

and Get Result

```shell script
curl  -v  -s -L "http://localhost/watchjob/processes/eo_metadata_generation_1_0/jobs/06223bbe-9e9e-11ea-8f64-a0c5899f98fe/result" -H "accept: application/json"
```

```text
*   Trying 127.0.0.1...
* TCP_NODELAY set
* Connected to localhost (127.0.0.1) port 80 (#0)
> GET /watchjob/processes/eo_metadata_generation_1_0/jobs/06223bbe-9e9e-11ea-8f64-a0c5899f98fe/result HTTP/1.1
> Host: localhost
> User-Agent: curl/7.58.0
> accept: application/json
> 
< HTTP/1.1 200 OK
< Date: Mon, 25 May 2020 15:46:09 GMT
< Server: Apache/2.4.6 (CentOS)
< Transfer-Encoding: chunked
< Content-Type: application/json;charset=UTF-8
< 
{ [178 bytes data]
* Connection #0 to host localhost left intact
{
  "outputs": [
    {
      "id": "results",
      "value": {
        "inlineValue": "/tmp/eoepca/S3B_SL_1_RBT____20200520T050759_20200520T051059_20200520T060015_0179_039_105_0360_LN2_O_NR_004.atom"
      }
    }
  ]
}

```

To browse the result we will mount the persistent volume on a pod and access it.
Write the following pod specifications in a file named **shell-demo.yaml** :
```
apiVersion: v1
kind: Pod
metadata:
  name: shell-demo
spec:
  volumes:
  - name: workdir
    persistentVolumeClaim:
       claimName: eoepca-pvc
  containers:
  - name: nginx
    image: nginx
    volumeMounts:
    - name: workdir
      mountPath: /tmp/eoepca
  hostNetwork: true
  dnsPolicy: Default
```
Create the pod with the following command
```
kubectl apply -f shell-demo.yam
```
Access the pod and navigate to the result path
```
kubectl exec -it shell-demo -- /bin/bash
root@minikube:/# ls /tmp/eoepca/S3B_SL_1_RBT____20200520T050759_20200520T051059_20200520T060015_0179_039_105_0360_LN2_O_NR_004.atom
```

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->

## License

Distributed under the Apache-2.0 License. See `LICENSE` for more information.

## Contact

<!-- ACKNOWLEDGEMENTS -->

## Acknowledgements

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/EOEPCA/template-svce.svg?style=flat-square
[contributors-url]: https://github.com/EOEPCA/template-svce/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/EOEPCA/template-svce.svg?style=flat-square
[forks-url]: https://github.com/EOEPCA/template-svce/network/members
[stars-shield]: https://img.shields.io/github/stars/EOEPCA/template-svce.svg?style=flat-square
[stars-url]: https://github.com/EOEPCA/template-svce/stargazers
[issues-shield]: https://img.shields.io/github/issues/EOEPCA/template-svce.svg?style=flat-square
[issues-url]: https://github.com/EOEPCA/template-svce/issues
[license-shield]: https://img.shields.io/github/license/EOEPCA/template-svce.svg?style=flat-square
[license-url]: https://github.com/EOEPCA/template-svce/blob/master/LICENSE
[build-shield]: https://www.travis-ci.com/EOEPCA/template-svce.svg?branch=master
[product-screenshot]: images/screenshot.png
[zoo-project-link]: http://www.zoo-project.org/
[eoepca-zoo]: https://hub.docker.com/r/eoepca/ades-core-engine-api-framework/tags