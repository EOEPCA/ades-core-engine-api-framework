<!--
*** To avoid retyping too much info. Do a search and replace for the following:
*** dev-env-cpp, twitter_handle, email
-->

<!-- PROJECT SHIELDS -->
<!--
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
![Build][build-shield]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/EOEPCA/proc_comm_lib_argo">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">proc-comm-lib-cwl</h3>

  <p align="center">
    CWL parser library for C++. 
    <br />
    <a href="https://github.com/EOEPCA/proc-comm-lib-cwl"><strong>Explore the docs »</strong></a>
    <br />
    <a href="https://github.com/EOEPCA/proc-comm-lib-cwl">View Demo</a>
    ·
    <a href="https://github.com/EOEPCA/proc-comm-lib-cwl/issues">Report Bug</a>
    ·
    <a href="https://github.com/EOEPCA/proc-comm-lib-cwl/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->

## Table of Contents

- [Table of Contents](#table-of-contents)
- [About The Project](#about-the-project)
  - [Built With](#built-with)
  - [Travis Build](#travis-build)
  - [Manual Build](#manual-build)
  - [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites-1)
  - [Installation](#installation)
  - [Testing](#testing)
- [How to use it](#how-to-use-it)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)

<!-- ABOUT THE PROJECT -->

## About The Project

 *proc-comm-lib-cwl* is a shared library to provides the means to parse a Common Workflow Language Specification document. It is based on the CWL schema which you can find [here](https://www.commonwl.org/v1.0/CommandLineTool.html).

### Built With

- [CMAKE](https://cmake.org/)
- [googletest](https://github.com/google/googletest)

### Travis Build

The library can be compiled using Travis. All necessary scripts are provided in the `travis` folder

To speed up the build phase of Travis we can use a compiler prepared by the EOEPCA team

You need to add an environment variable with reference to the docker image

```ini
BUILDER_ENV_IMAGE=eoepca/eoepca-build-cpp:1.0
```

### Manual Build

### Prerequisites

Before you start, you should already have the following softwares installed:

- [Docker](https://www.docker.com/)
- [Linux bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell))


To compile the library, a compiler that supports C++[14](https://en.cppreference.com/w/cpp/14)/[17](https://en.cppreference.com/w/cpp/17) is required.

EOEPCA team provides a ready-made Docker Image

```shel
docker pull eoepca/eoepca-build-cpp:1.0
```

If you want to create the Docker image yourself, the repository provides a Docker file to satisfy all requests (Dockerfile_builder)

```bash
docker build -t eoepca-build-cpp:1.0 -f Dockerfile_builder
```


## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

- [Docker](https://www.docker.com/)
- [Linux bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell))

### Installation

1. Clone the repo

```sh
git clone https://github.com/EOEPCA/proc-comm-lib-cwl.git
```

2. Change local directory

```sh
cd proc-comm-lib-cwl
```

For this example we'll use the ready-made Docker Image `eoepca/eoepca-build-cpp:1.0`

3. Build application

Let's prepare the environment variables

```shell
export LOCAL_DOCKERIMAGE='eoepca/eoepca-build-cpp:1.0'
export CMAKERELEASE='Release'
```

Prepare the makefile

```shel
docker run --rm -ti  -v $PWD:/project/ -w /project/build/  ${LOCAL_DOCKERIMAGE} cmake -DCMAKE_BUILD_TYPE=${CMAKERELEASE} -G "CodeBlocks - Unix Makefiles" ..
```

... and make

```shel
docker run --rm -ti  -v $PWD:/project/ -w /project/build/  ${LOCAL_DOCKERIMAGE} make
```

list directory

```shell
ls -ltr build/
```

expected results:

```shell
[qbert@mycase proc-comm-lib-cwl]$ ls -ltr build/
drwxrwxr-x  7 root root    4096 mag  7 07:04 ./
drwxrwxr-x 12 root root    4096 mag  7 07:26 ../
drwxrwxr-x  3 root root    4096 mag  6 17:00 3ty/
drwxrwxr-x  2 root root    4096 mag  6 17:01 bin/
-rw-rw-r--  1 root root   52666 mag  6 18:02 CMakeCache.txt
drwxrwxr-x  9 root root    4096 mag  7 07:10 CMakeFiles/
-rw-rw-r--  1 root root    1872 mag  6 17:01 cmake_install.cmake
drwxrwxr-x  2 root root    4096 mag  6 17:18 lib/
-rw-rw-r--  1 root root 5865576 mag  7 07:04 libsources.a
-rw-rw-r--  1 root root   15822 mag  6 18:02 Makefile
-rwxrwxr-x  1 root root 4490968 mag  7 06:39 proc_comm_lib_cwl*
-rw-rw-r--  1 root root   60637 mag  6 18:02 proc_comm_lib_cwl.cbp
drwxrwxr-x  6 root root    4096 mag  7 07:10 tests/
-rw-rw-r--  1 root root     236 mag  6 17:00 yaml-cpp.pc

```

The library has been created `libeoepcaargo.so`

### Testing

from the root of the repository

```shell
 ./build/tests/libtest-test --gtest_break_on_failure
```

runs only the unit tests


## How to use it

Here is a quick sample of how to use the proc-comm-lib-cwl library:

```cpp

#include <iostream>
#include <converter/model.hpp>
#include <model/graph.hpp>
#include <cwlconverter.cpp>


int main() {

    Graph graph;
    graph.loadCwlFile("./workflow.yaml");

    std::cout<< graph.getCommandLineTool().getBaseCommand() << std::endl;
    std::cout<< graph.getCommandLineTool().getInputs().front().getInputBinding().getPosition() << std::endl;
    std::cout<< graph.getCommandLineTool().getInputs().front().getInputBinding().getPrefix() << std::endl;


    std::cout<< graph.getWorkflow().getDoc() << std::endl;
    std::cout<< graph.getWorkflow().getInputs().front().getInputBinding().getPosition() << std::endl;
    std::cout<< graph.getWorkflow().getInputs().front().getInputBinding().getPrefix() << std::endl;


    return 0;
}

```
The output will look like this:
```
echo
1
--input
Hello World Test Workflow
32766


```


## Roadmap

See the [open issues](https://github.com/EOEPCA/proc-comm-lib-cwl/issues) for a list of proposed features (and known issues).

<!-- CONTRIBUTING -->

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

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/EOEPCA/template-svce.svg?style=flat-square
[contributors-url]: https://github.com/EOEPCA/proc-comm-lib-cwl/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/EOEPCA/template-svce.svg?style=flat-square
[forks-url]: https://github.com/EOEPCA/proc-comm-lib-cwl/network/members
[stars-shield]: https://img.shields.io/github/stars/EOEPCA/template-svce.svg?style=flat-square
[stars-url]: https://github.com/EOEPCA/proc-comm-lib-cwl/stargazers
[issues-shield]: https://img.shields.io/github/issues/EOEPCA/template-svce.svg?style=flat-square
[issues-url]: https://github.com/EOEPCA/proc-comm-lib-cwl/issues
[license-shield]: https://img.shields.io/github/license/EOEPCA/template-svce.svg?style=flat-square
[license-url]: https://github.com/EOEPCA/proc-comm-lib-cwl/blob/master/LICENSE
[build-shield]: https://www.travis-ci.com/EOEPCA/template-svce.svg?branch=master
[product-screenshot]: images/screenshot.png
