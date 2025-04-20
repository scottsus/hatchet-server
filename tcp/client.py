import socket
import time


def send_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Server address and port
    server_address = ("localhost", 8080)

    try:
        print(f"Connecting to {server_address[0]}:{server_address[1]}...")
        client_socket.connect(server_address)

        time.sleep(2)

        # Clear
        # command = "ClearAll"
        # print(f"Sending command: {command}")
        # client_socket.sendall(command.encode())
        # time.sleep(5)

        # Send a command without waiting for a response
        command = "Init 104"
        print(f"Sending command: {command}")
        client_socket.sendall(command.encode())
        time.sleep(5)
        response = client_socket.recv(8192).decode()
        print(f"Received response: {response}")

        command = "SetParameters 104,2.5,-3.7,0.034906585039886591,0.1,0,4,41.87892716196967,12.508081927663124"
        print(f"Sending command: {command}")
        client_socket.sendall(command.encode())
        time.sleep(5)

        command = "Set #68000C00000091000000000000000000000000FFE80000000000000000002CA7000009A7"
        print(f"Sending command: {command}")
        client_socket.sendall(command.encode())
        time.sleep(5)

        command = "Get 104"
        print(f"Sending command: {command}")
        client_socket.sendall(command.encode())
        time.sleep(1)
        # response = client_socket.recv(1024).decode()
        # print(f"Received response: {response}")
        # time.sleep(5)

    except ConnectionRefusedError:
        print("Connection failed. Is the server running?")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        print("Closing connection")
        time.sleep(2)
        client_socket.close()


if __name__ == "__main__":
    send_client()
