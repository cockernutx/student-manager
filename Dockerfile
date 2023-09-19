FROM debian:latest

RUN apt update
# Install firefox cause i cant be bothered to install all the other deps
RUN apt install -y gcc gdb

RUN apt install -y build-essential git
    
