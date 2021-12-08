#!/bin/bash
docker run -it -v $(pwd):/home -p "3000:3000" slr $@