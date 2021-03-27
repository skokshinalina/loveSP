# Get the GCC preinstalled image from Docker Hub
FROM gcc:4.9

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /home/an1/3/12

# Specify the working directory
WORKDIR /home/an1/3/12

# Use GCC to compile the Test.cpp source file
RUN g++ -o 12 12.cpp

# Run the program output from the previous step
CMD ["./12"]