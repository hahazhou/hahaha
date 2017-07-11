#include <array>
#include <iostream>
#include <string>
#include"Fix.h"
#include <boost/asio.hpp>
#include<fstream>
#include<vector>
//server服务器的编写

using boost::asio::ip::tcp;

int main()
{ 
	ifstream stocklist("Stocks.txt");
	string stock_num1, stock_quan1,stock_pri1,stock_num2,stock_quan2,stock_pri2,stock_num3,stock_quan3,stock_pri3;
	stocklist >> stock_num1 >> stock_quan1 >> stock_pri1 >> stock_num2 >> stock_pri2 >> stock_quan2>> stock_num3 >> stock_pri3 >> stock_quan3;
	vector<string>stock1;
	stock1.push_back(stock_num1);
	stock1.push_back(stock_quan1);
	stock1.push_back(stock_pri1);
	vector<string>stock2;
	stock1.push_back(stock_num2);
	stock1.push_back(stock_quan2);
	stock1.push_back(stock_pri2);
	vector<string>stock3;
	stock1.push_back(stock_num3);
	stock1.push_back(stock_quan3);
	stock1.push_back(stock_pri3);
	//将股票的代码，价格，数量放入vector中，假设有3只股票

	boost::asio::io_service io_service;
	tcp::acceptor acc(io_service, tcp::endpoint(tcp::v6(), 9876));

	while (1) {
		boost::system::error_code ignored;

		tcp::socket socket(io_service);
		acc.accept(socket);

		std::array<char, 256> input_buffer;
		std::size_t input_size = socket.read_some(
			boost::asio::buffer(input_buffer),
			ignored);
		std::string visitor(input_buffer.data(),
			input_buffer.data() + input_size);

		std::cout << "Visited from " +
			socket.remote_endpoint().address().to_string() +
			" by visitor " << visitor << std::endl;

		std::string message = "Hello, you are " + visitor +".Please input your require." +"\n";
		boost::asio::write(socket, boost::asio::buffer(message), ignored);
		//获得访问者的id

		std::array<char, 256> input_buffer2;
		std::size_t input_size = socket.read_some(
			boost::asio::buffer(input_buffer2),
			ignored);
		std::string visitor(input_buffer2.data(),
			input_buffer2.data() + input_size);
		fix FIX_message = socket.remote_endpoint().address().to_string();
		//获得来自client的FIX信息

		string ack = FIX_message.Get_35();//获取订单状态
		if (ack == "D") {
			string ticker_symbol = FIX_message.Get_55();
			if (ticker_symbol == stock1[0]) {//假设订单是对第一只股票的操作（后面的程序在stock2和stock3同理）
				string side1 = FIX_message.Get_54();
				if (side1 == "Buy ") {//来自买方
					int price1 = FIX_message.Get_44();
					if (price1 == stoi(stock1[2])) {
						int quantity1 = FIX_message.Get_38();
						if (quantity1 > stoi(stock1[1])) {
							int un_shared_order = quantity1 - stoi(stock1[1]);//计算出没有被fill的股票数目
							stock1[1] = "0";
							ofstream Orderbook;
							Orderbook.open("Buyer Order Book.txt");
							Orderbook << FIX_message.Get_11() + "  " + to_string(un_shared_order) + "  " + to_string(price1);
							//写入orderbook
							string sendback = "35=D 39=2 150=2";
							boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
							//反馈给client
						}
						else {
							int l_quantity = stoi(stock1[1]) - quantity1;
							stock1[1] = to_string(l_quantity);
							if (quantity1 == 0) {
								string sendback = "35=D 39=0 150=0";
								boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
								//订单已被full-fill
							}
							else {
								string sendback = "35=D 39=1 150=1";
								boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
								//订单被Partial-fill
							}
						}
					}
				}
				else {
					//来自卖方
					ofstream Orderbook_sell;
					Orderbook_sell.open("Seller Order Book.txt");
					int new_quantity = stoi(stock1[1]) + FIX_message.Get_38();
					Orderbook_sell << FIX_message.Get_11() + "  " + to_string(new_quantity) + "  " + to_string(FIX_message.Get_44());
					//将卖方信息写入orderbook
				}
			}
				else if (ticker_symbol == stock2[0]) {
					string side1 = FIX_message.Get_54();
					if (side1 == "Buy ") {
						int price1 = FIX_message.Get_44();
						if (price1 == stoi(stock2[2])) {
							int quantity1 = FIX_message.Get_38();
							if (quantity1 > stoi(stock2[1])) {
								int un_shared_order = quantity1 - stoi(stock2[1]);
								stock2[1] = "0";
								ofstream Orderbook;
								Orderbook.open("Buyer Order Book.txt");
								Orderbook << FIX_message.Get_11() + "  " + to_string(un_shared_order) + "  " + to_string(price1);
								string sendback = "35=D 39=2 150=2";
								boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
							}
							else {
								int l_quantity = stoi(stock2[1]) - quantity1;
								stock2[1] = to_string(l_quantity);
								if (quantity1 == 0) {
									string sendback = "35=D 39=0 150=0";
									boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
								}
								else {
									string sendback = "35=D 39=1 150=1";
									boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
								}
							}
						}
					}
					else {
						ofstream Orderbook_sell;
						Orderbook_sell.open("Seller Order Book.txt");
						int new_quantity = stoi(stock2[1]) + FIX_message.Get_38();
						Orderbook_sell << FIX_message.Get_11() + "  " + to_string(new_quantity) + "  " + to_string(FIX_message.Get_44());
					}
			}
				else if (ticker_symbol == stock3[0]) {
					string side1 = FIX_message.Get_54();
					if (side1 == "Buy ") {
						int price1 = FIX_message.Get_44();
						if (price1 == stoi(stock3[2])) {
							int quantity1 = FIX_message.Get_38();
							if (quantity1 > stoi(stock3[1])) {
								int un_shared_order = quantity1 - stoi(stock3[1]);
								stock3[1] = "0";
								ofstream Orderbook;
								Orderbook.open("Buyer Order Book.txt");
								Orderbook << FIX_message.Get_11() + "  " + to_string(un_shared_order) + "  " + to_string(price1);
								string sendback = "35=D 39=2 150=2";
								boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
							}
							else {
								int l_quantity = stoi(stock3[1]) - quantity1;
								stock3[1] = to_string(l_quantity);
								if (quantity1 == 0) {
									string sendback = "35=D 39=0 150=0";
									boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
								}
								else {
									string sendback = "35=D 39=1 150=1";
									boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
								}
							}
						}
					}
					else {
						ofstream Orderbook_sell;
						Orderbook_sell.open("Seller Order Book.txt");
						int new_quantity = stoi(stock3[1]) + FIX_message.Get_38();
						Orderbook_sell << FIX_message.Get_11() + "  " + to_string(new_quantity) + "  " + to_string(FIX_message.Get_44());
					}
				}
				else {
					string sendback = "Stock Not Found.";
					boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
				}//没有找到对应的股票
		}
		else if (ack == "F") {
			if (FIX_message.Get_54() == "Buy ") {
				ifstream orderbook_buyer("Buyer Order Book");
				string order;
				orderbook_buyer >> order;
				if (FIX_message.Get_11() == order) {
					string sendback = "35=8 39=4";
					boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
					//成功取消订单
				}
				else {
					string sendback = "35=9 39=4";
					boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
					//订单已被处理，取消失败
				}
			}
		}
		else {
			string sendback = "Invalid FIX Message.";
			boost::asio::write(socket, boost::asio::buffer(sendback), ignored);
		}//错误FIX信息的处理

		socket.shutdown(tcp::socket::shutdown_both, ignored);
		socket.close();
	}
	return 0;
}
