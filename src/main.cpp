// #include "server_ws.hpp"

// typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;

// using namespace std;
        #include "LineFollow.h"
    // #include "support/SensorDebug.h"
    //     #include "ev3dev.h"
    //     using namespace ev3dev;	
    #include "Claw.h"
int main(){
    // Claw x;
    // x.lower();
	
	// motor m_right(OUTPUT_A);
	// motor m_left(OUTPUT_D);	

	// light_sensor line_sensor (INPUT_2);
	// line_sensor.set_mode(light_sensor::mode_reflect);

    robot r;
    r.read_recepie();
    //r.test();
    //r.get_stones();
    //r.follow_line_until_stone(200,m_right,m_left,line_sensor);
    // // SensorDebug s;
    // s.detect_stone_ir();

    	// //Open websocket
	// WsServer server;
	// server.config.port=8080;
	// auto& echo_all=server.endpoint["^/echo_all/?$"];
    // echo_all.on_message=[&server](shared_ptr<WsServer::Connection> /*connection*/,
    // shared_ptr<WsServer::Message> message) {
    //     auto message_str=message->string();
        
    //     //echo_all.get_connections() can also be used to solely receive connections on this endpoint
    //     for(auto &a_connection: server.get_connections()) {
    //         auto send_stream=make_shared<WsServer::SendStream>();
    //         *send_stream << message_str;
            
    //         //server.send is an asynchronous function
    //         server.send(a_connection, send_stream);
    //     }
    // };
    
    // thread server_thread([&server](){
    //     //Start WS-server
    //     server.start();
    // });
    
    // //Wait for server to start so that the client can connect
	// this_thread::sleep_for(chrono::seconds(1));




	return 0;
}	
