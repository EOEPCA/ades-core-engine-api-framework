#!/usr/bin/env bash

curl -v -L -X POST "http://localhost:7777/wps3/processes/argo/jobs" -H  \
  "accept: application/json" -H  "Prefer: respond-async" -H  "Content-Type: application/json" -d@argo.json