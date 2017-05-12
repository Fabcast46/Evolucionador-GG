/*
 * xCliente.cpp
 *
 *  Created on: 21 de mar. de 2016
 *      Author: wilson
 */

#include "xCliente.h"

	 struct addrinfo host_info;
 	 struct addrinfo *host_info_list;

xCliente::xCliente() {
	// TODO Auto-generated constructor stub
}

xCliente::~xCliente() {
	// TODO Auto-generated destructor stub
}
/*El metodo run() es el metodo principal que se encarga de hacer las llamadas de los demas metodos que pertenecen a nuestra clase socket cliente*/
void xCliente::run(const char* menj){
		crearSocket();
		ligarKernel();
		
		getMensaje();
                sendMensaje(menj);
}
/*Metodo que se encarga de crear el cliente define la IP,Puerto y protocolo de envio*/
void xCliente::crearSocket(){
	 	 	memset(&host_info, 0, sizeof host_info);
		    host_info.ai_family = AF_UNSPEC;
		    host_info.ai_socktype = SOCK_STREAM;
		    status = getaddrinfo("localhost", "7001", &host_info, &host_info_list);
		    if (status != 0)  cout << "getaddrinfo error" << gai_strerror(status) ;
}
/*Este metodo liga la liga el kernel , asignando los datos q definimos en el metodo anterior en status*/
void xCliente::ligarKernel(){
	 	 	cout << "Creando socket..."  << endl;
		    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,host_info_list->ai_protocol);
                    cout<<"Familia"<<host_info_list->ai_family<<endl;
                    cout<<"Tipo"<<host_info_list->ai_socktype<<endl;
                    cout<<"Protocolo"<<host_info_list->ai_protocol<<endl;
		    if (socketfd == -1) cout << "socket error " ;
		    cout << "Conectando"  << endl;
		    status = connect(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
		    if (status == -1)  cout << "connect error" ;
}
void xCliente::sendMensaje(const char* msj){
			cout << "Enviando mensaje..."  << endl;
			len = strlen(msj);
			bytes_sent = send(socketfd, msj, len, 0);
}
void xCliente::getMensaje(){
    		cout << "Esperando recibir datos..."<< endl;
    		ssize_t bytes_recieved;
    		char incomming_data_buffer[1000];
    		bytes_recieved = recv(socketfd, incomming_data_buffer2,1000, 0);
    		// If no data arrives, the program will just wait here until some data arrives.
    		if (bytes_recieved == 0) cout << "host shut down." << endl ;
    		if (bytes_recieved == -1)cout << "recieve error!" << endl ;
    		cout << bytes_recieved << " bytes recibidos :" << endl ;
    		incomming_data_buffer2[bytes_recieved] = '\0' ;
    		cout << incomming_data_buffer2 << endl;
    		cout << "Recibido Completo. Cerrando socket..." << endl;
    		freeaddrinfo(host_info_list);

	        //close(socketfd);

}