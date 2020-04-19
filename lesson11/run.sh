#!/usr/bin/env bash
container_home=$(pwd)/container-home
bash x11docker --home=$container_home --hostdisplay --clipboard tarsioonofrio/cheddar cheddar
