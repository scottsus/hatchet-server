# Arianna Library

This is a containerized version of `libarianna` as a TCP server that listens on port 8080.

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

- `just start` - Start the server
- `just test` - Run the test client
- `just stop` - Stop the Docker container
- `just clean` - Clean build artifacts

Run `just` without arguments to see all available commands with descriptions.

### Sanity Check

To sanity check the setup, do

```bash
just start
just test
```

The server should successfully make a connection to the client 🚀
