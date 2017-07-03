#include <array>
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include<sstream>
//客户端程序的编写

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	std::string f35;
	std::string f11;
	std::string f41;
	std::string f150;
	std::string f38;
	std::string f39;
	std::string f40;
	std::string f44;
	std::string f151;
	std::string f31;
	std::string f32;
	std::string f6;
	std::string f14;
	std::string f54;
	std::string f55;
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query("169.254.82.41", "9876");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);
	boost::system::error_code error;
	std::string id = " ";
	boost::asio::write(socket, boost::asio::buffer(id), error);//与服务器的连接，将自己的id传给server
	while (true) {
		std::cout << std::string("FIX 35=") << std::endl;
		std::cin >> f35;
		std::string m35 = "35=" + f35 + " ";
		std::cout << std::string("FIX 11=") << std::endl;
		std::cin >> f11;
		std::string m11 = "11=" + f11 + " ";
		std::cout << std::string("FIX 41=") << std::endl;
		std::cin >> f41;
		std::string m41 = "41=" + f41 + " ";
		std::cout << std::string("FIX 150=") << std::endl;
		std::cin >> f150;
		std::string m150 = "150=" + f150 + " ";
		std::cout << std::string("FIX 38=") << std::endl;
		std::cin >> f38;
		std::string m38 = "38=" + f38 + " ";
		std::cout << std::string("FIX 39=") << std::endl;
		std::cin >> f39;
		std::string m39 = "39=" + f39 + " ";
		std::cout << std::string("FIX 40=") << std::endl;
		std::cin >> f40;
		std::string m40 = "40=" + f40 + " ";
		std::cout << std::string("FIX 44=") << std::endl;
		std::cin >> f44;
		std::string m44 = "44=" + f44 + " ";
		std::cout << std::string("FIX 151=") << std::endl;
		std::cin >> f151;
		std::string m151 = "151=" + f151 + " ";
		std::cout << std::string("FIX 31=") << std::endl;
		std::cin >> f31;
		std::string m31 = "31=" + f31 + " ";
		std::cout << std::string("FIX 32=") << std::endl;
		std::cin >> f32;
		std::string m32 = "32=" + f32 + " ";
		std::cout << std::string("FIX 14=") << std::endl;
		std::cin >> f14;
		std::string m14 = "14=" + f14 + " ";
		std::cout << std::string("FIX 6=") << std::endl;
		std::cin >> f6;
		std::string m6 = "6=" + f6 + " ";
		std::cout << std::string("FIX 54=") << std::endl;
		std::cin >> f54;
		std::string m54 = "54=" + f54 + " ";
		std::cout << std::string("FIX 55=") << std::endl;
		std::cin >> f55;
		std::string m55 = "55=" + f55 + " ";//用户输入自己的订单信息
		std::string fix_message = m35 + m11 + m41 + m150 + m38 + m39 + m40 + m44 + m151 + m31 + m32 + m14 + m6 + m54 + m55;
		boost::asio::write(socket, boost::asio::buffer(fix_message), error);
		std::array<char, 256> input_buffer;
		std::size_t rsize = socket.read_some(
			boost::asio::buffer(input_buffer), error);
		std::cout << std::string(input_buffer.data(), input_buffer.data() + rsize) << std::endl;
		//将用户的订单信息传给server
	}
	return 0;
}
