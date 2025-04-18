import socket


def tcp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Server address and port
    server_address = ("localhost", 8080)

    try:
        print(f"Connecting to {server_address[0]}:{server_address[1]}...")
        client_socket.connect(server_address)

        message = "Hello, server!"
        print(f"Sending: {message}")
        client_socket.sendall(message.encode())

        data = client_socket.recv(1024)
        print(f"Received: {data.decode()}")

    except ConnectionRefusedError:
        print("Connection failed. Is the server running?")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        print("Closing connection")
        client_socket.close()


if __name__ == "__main__":
    tcp_client()
