# Arianna Library

This is a containerized version of `libarianna` meant to be machine-agnostic. It now includes a library version that can be used by other applications.

## Development Workflow

### Using Just Task Runner (Recommended)

The project includes a `justfile` that simplifies common development tasks. First, install Just:

```bash
# macOS
brew install just

# Ubuntu/Debian
sudo apt-get install just

# Windows
choco install just
```

Then you can use these commands:

- `just build` - Build the project
- `just start` - Start the server
- `just test` - Run the test client
- `just stop` - Stop the Docker container
- `just shell` - Get a shell inside the container
- `just clean` - Clean build artifacts
- `just rebuild` - Clean and rebuild the project
- `just sync` - Copy source files to the container (if volume mounts aren't working)

Run `just` without arguments to see all available commands with descriptions.

### Manual Workflow

For development with live code editing (changes to source files on your host machine are immediately reflected in the container):

1. Use Docker Compose to build and run the container with volume mappings:

   ```
   docker-compose build
   docker-compose up -d
   ```

   This will start a container that keeps running in the background with volumes mapped for the src, data, and dist directories.

2. Enter the running container:

   ```
   docker-compose exec arianna bash
   ```

3. Inside the container, you can build and run the project:

   ```
   make
   ```

   This will build:

   - `dist/processor.o` - The processor library
   - `dist/data_loader.o` - The data loader library
   - `dist/buffer.o` - The buffer library
   - `dist/server.o` - The server library
   - `dist/main` - The main program that uses the libraries
   - `dist/test_client` - A simple client to test the server

4. Run the main program:

   ```
   make run
   ```

5. Edit files in the `src/`, `data/`, or any other directory on your host machine, and the changes will be immediately available inside the container.

6. When you're done, stop the container:
   ```
   docker-compose down
   ```

This extracts the 74 bit strings, then runs them through `libarianna`. ⚠️ The starting coordinate will still be Bellevue.

## TCP Server

The main program now includes a TCP server that serves coordinates from the buffer. When a client connects to the server, it receives a single coordinate from the buffer.

### Running the Server

Using Just (recommended):

```bash
just start
```

Or manually:

```bash
LD_LIBRARY_PATH=./dist ./dist/main
```

The server listens on port 8080 and serves coordinates from the buffer.

### Testing the Server

Using Just (recommended):

```bash
just test
```

Or manually with the test client:

```bash
./dist/test_client
```

Or using the make target:

```bash
make test_client
```

The test client connects to `127.0.0.1:8080` and receives a single coordinate from the buffer.
