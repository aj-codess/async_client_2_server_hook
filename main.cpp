#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>

using namespace std;


std::vector<char> virtual_buffer(20*1024); // pool of memory where read data from a source is kept

void data_2_grab(boost::asio::ip::tcp::socket& socket){

    socket.async_read_some(boost::asio::buffer(virtual_buffer.data(),virtual_buffer.size()),[&](boost::system::error_code error_pool,std::size_t length){
        if(!error_pool){
            for(int i=0;i<length;i++){
                cout<<virtual_buffer[i]<<endl;
            };
            data_2_grab(socket);
        };
    });

};
//above is a function which reads data async from a socket connection. and this operation is run on the context io_context



int main(){
    
boost::system::error_code error_pool;

boost::asio::io_context context;
boost::asio::io_context::work idleWork(context);
std::thread io_context_thread=std::thread([&](){context.run();});

boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("127.0.0.1",error_pool),8080);
boost::asio::ip::tcp::socket socket(context);

socket.connect(endpoint,error_pool);

if(!error_pool){
    cout<<"connected...."<<endl;
} else{
    cout<<"there was an error connecting to the address- \n "<<error_pool.message()<<endl;  
};


if(socket.is_open()){

    data_2_grab(socket);

    std::string request="GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
    socket.write_some(boost::asio::buffer(request.data(),request.size()),error_pool);


     std::this_thread::sleep_for(std::chrono::seconds(5));

     context.stop();

     if(io_context_thread.joinable()){
        io_context_thread.join();
     };

};

    return 0;
}
