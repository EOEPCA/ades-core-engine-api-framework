
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
      <ows:Identifier>argo</ows:Identifier>
      <ows:Title>Eoepca Deploy Process</ows:Title>
      <ows:Abstract>argo test 1.0</ows:Abstract>
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
      "id": "argo",
      "title": "Eoepca Deploy Process",
      "abstract": "argo test 1.0",
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
          "href": "/watchjob/processes/argo/"
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
    }
  ]
}
```

## Usage


### Prerequisites

- [dev-env-argo](https://github.com/EOEPCA/dev-env-argo)
- [curl](https://en.wikipedia.org/wiki/CURL)


### Start

Our tutorial will start in the dev-env-argo environment

1) Start "eoepca-ades-core"

```shell script
docker run --rm  -d --name zoo -p 7777:80   eoepca-ades-core:1.0
```

2) run a getProcess to test the installation:

```shell script
curl -s -L "http://localhost:7777/wps3/processes" -H "accept: application/json"
```

3) Looking for the our service argo:
 
```shell script
curl -s -L "http://localhost:7777/wps3/processes/argo" -H "accept: application/json"
```

```json
{
  "process": {
    "id": "argo",
    "title": "Eoepca Deploy Process",
    "abstract": "argo test 1.0",
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
        "title": "Execute End Point",
        "href": "/watchjob/processes/argo/jobs/"
      }
    ],
    "inputs": [
      {
        "id": "input_string",
        "title": "The input1",
        "abstract": "the input_string",
        "minOccurs": "1",
        "maxOccurs": "1",
        "input": {
          "formats": [
            {
              "default": true,
              "mimeType": "application/atom+xml"
            },
            {
              "default": false,
              "mimeType": "application/atom+xml"
            }
          ]
        }
      }
    ],
    "outputs": [
      {
        "id": "result_osd",
        "title": "OpenSearch Description to the Results",
        "abstract": "OpenSearch Description to the Results",
        "output": {
          "formats": [
            {
              "default": true,
              "mimeType": "application/opensearchdescription+xml"
            },
            {
              "default": false,
              "mimeType": "application/opensearchdescription+xml"
            }
          ]
        }
      }
    ]
  }
}
```

For this release "Argo" is only a simple 







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