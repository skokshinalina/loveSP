FROM ubuntu
RUN apt update
RUN apt install gcc g++ gdb gcc-multilib nano -y
WORKDIR /home/test/
COPY first.cpp /home/test/
COPY second.cpp /home/test/
RUN gcc first.cpp -lstdc++ -o first | gcc second.cpp -lstdc++ -o second