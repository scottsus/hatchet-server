# basic scripts

default:
    @just --list

# Start Docker container and run the server
start:
    docker-compose up -d
    docker-compose exec arianna bash -c 'make run'

# Build project
build:
    docker-compose up -d
    docker-compose exec arianna bash -c 'make'

# Run test client
test:
    docker-compose up -d
    docker-compose exec arianna bash -c 'make test_client'

# Clean build artifacts
clean:
    docker-compose exec arianna bash -c 'make clean'

# Stop Docker container
stop:
    docker-compose down

# Rebuild project from scratch
rebuild: clean build
