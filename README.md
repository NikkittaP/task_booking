# Task_booking

Welcome to the Task_booking application! This application provides a backend service for booking movie tickets for various theaters and movies.

## Features

- Add new movies with titles.
- Add new theaters with customizable seating arrangements.
- Link movies to theaters.
- View available movies and theaters.
- Book seats for movies at specific theaters.
- Unit tests for robustness.

## Prerequisites

Before running the application, make sure you have the following installed:

- CMake

(Optional) Docker (if you prefer running the application in a Docker container)

## Getting Started

Follow these steps to run the application:

1. Clone this repository to your local machine.
2. Navigate to the project directory.
3. **(Local Build)** Build the application using CMake:

    ```bash
    cmake .
    make
    ```

4. **(Local Build)** Run the tests:

    ```bash
    ./test_task_booking
    ```

5. **(Local Build)** After successful testing, you can run the application:

    ```bash
    ./task_booking
    ```

6. **(Optional: Docker)** Alternatively, you can use Docker for running the application:
   
    - Build the Docker image using the provided `build_docker_image.sh` script:

        ```bash
        ./build_docker_image.sh
        ```

    - Run the Docker container using the `run_docker_image.sh` script:

        ```bash
        ./run_docker_image.sh
        ```

## Documentation

Documentation for the codebase can be generated using Doxygen. To generate documentation:

1. Ensure Doxygen is installed on your system.
2. Run the Doxygen command:

    ```bash
    doxygen Doxyfile
    ```

## Authors

- Nikita Petrov

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
