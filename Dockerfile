# Use a base image with the necessary dependencies for C++ development
FROM ubuntu:latest

# Install required tools and dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libgtest-dev

# Set the working directory in the container
WORKDIR /app

# Copy the CMake project files into the container
COPY . .

# Build the project using CMake
RUN cmake .

# Compile the project
RUN make

# Define the command to run the compiled program
CMD ["./task_booking"]
