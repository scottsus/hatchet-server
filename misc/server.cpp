// The server version of test.cpp.
// Currently WIP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
    boost::asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v4(), 0));
    udp::endpoint receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345);

    std::srand(std::time(nullptr));

    while (true)
    {
        double lat = (std::rand() % 1800) / 10.0 - 90.0;
        double lon = (std::rand() % 3600) / 10.0 - 180.0;

        std::string message = std::to_string(lat) + "," + std::to_string(lon);
        socket.send_to(boost::asio::buffer(message), receiver_endpoint);

        std::cout << "Sent: " << message << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}