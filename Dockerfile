FROM ubuntu
RUN apt-get update && apt-get install -y gcc g++ gdb gcc-multilib nano
WORKDIR /home/
COPY text /home/
COPY lab5.cpp /home/
RUN gcc lab5.cpp -lstdc++ -lpthread -o lab5
