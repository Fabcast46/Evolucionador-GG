/*
 * xCliente.h
 *
 *  Created on: 21 de mar. de 2016
 *      Author: wilson
 */

#ifndef XCLIENTE_H_
#define XCLIENTE_H_
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>

using namespace std;

class xCliente {
public:
	xCliente();
	virtual ~xCliente();
	void crearSocket();
	void ligarKernel();
	void getMensaje();
	void sendMensaje(const char* menj);
	void run(const char* msj);
	void run2(const char* msj);
	void run1();
    ssize_t bytes_sent;
	int status;
	int len;
	int socketfd ;
        char incomming_data_buffer2[1000];
};


#endif /* XCLIENTE_H_ */
