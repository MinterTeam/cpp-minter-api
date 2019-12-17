#!/usr/bin/env bash

set -e

mkdir -p _build && cd _build
cmake .. -DCMAKE_BUILD_TYPE=Debug -Dminter_api_TEST=On
cmake --build . --target minter_api-test
./bin/minter_api-test