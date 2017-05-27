#include "server_ws.hpp"

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;

using namespace std;

int main(){
	//Open websocket
	WsServer server;
	server.config.port=8080;
	auto& echo_all=server.endpoint["^/echo_all/?$"];
    echo_all.on_message=[&server](shared_ptr<WsServer::Connection> /*connection*/,
    shared_ptr<WsServer::Message> message) {
        auto message_str=message->string();
        
        //echo_all.get_connections() can also be used to solely receive connections on this endpoint
        for(auto &a_connection: server.get_connections()) {
            auto send_stream=make_shared<WsServer::SendStream>();
            *send_stream << message_str;
            
            //server.send is an asynchronous function
            server.send(a_connection, send_stream);
        }
    };
    
    thread server_thread([&server](){
        //Start WS-server
        server.start();
    });
    
    //Wait for server to start so that the client can connect
	this_thread::sleep_for(chrono::seconds(1));


	return 0;
}	
