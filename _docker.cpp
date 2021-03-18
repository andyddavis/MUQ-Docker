#include <iostream>

#include <ctime>
#include <string>
#include <boost/asio.hpp>
//#include "spdlog/spdlog.h"

#include "include/comm.h"

int main(int argc, char **argv) {
  const int dim = 5;
  Eigen::VectorXd dummyoutput = Eigen::VectorXd::Ones(dim);
  dummyoutput(4) = 42;

  const int port = 4242;

  try {
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 4242));
    tcp::socket socket(io_service);
    acceptor.accept(socket);

    while (true) {
      std::cout << "TOP OF WHILE" << std::endl;
      std::string command = read_string(socket);
      std::cout << std::endl << std::endl << "COMMAND: " << command << std::endl;
      if (command == "dimIn") {
        std::cout << "HERE IN DOCKER" << std::endl;
        Eigen::VectorXi dimIn = Eigen::VectorXi::Constant(1,4);
        std::cout << "SENDING DIM IN" << std::endl;
        send_vector_i(socket, dimIn);
        std::cout << "HERE" << std::endl;
      } else if (command == "dimOut") {
        Eigen::VectorXi dimOut = Eigen::VectorXi::Constant(2,5);
        send_vector_i(socket, dimOut);
      } else if (command == "sample") {
        //spdlog::info("Received sample request");
        Eigen::VectorXd input = read_vector(socket);
        std::cout << "Got input:" << std::endl << input << std::endl;
        send_vector(socket, dummyoutput);
        send_vector(socket, dummyoutput);
        //spdlog::info("Sent sample");
      } else if (command == "shutdown") {
        break;
      } else {
        //spdlog::error("Received unknown command!");
      }
      std::cout << "AFTER IF" << std::endl;
    }

  } catch( std::exception& e ) {
    std::cerr << e.what() << std::endl;
  }

  std::cout << "done" << std::endl;
}
