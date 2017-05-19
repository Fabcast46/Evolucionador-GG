package com.evolucionador.genetic;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class sock {
	
	final int PORT = 7001;
	Socket connection;
	ServerSocket service;
	
	public sock(){
		
	}
	
	public void con(String msg){
		try
	    {
	        service= new ServerSocket(PORT);
	        System.out.println("Esperando conexion");
	        connection = service.accept();
	        System.out.println("Conexion aceptada");
	        
	        
	        
	        BufferedWriter wr = new BufferedWriter(new OutputStreamWriter(connection.getOutputStream())); 
	        wr.write(msg);
	        wr.flush(); // flushes the stream
	        
	        //String inputLine; 
	        //BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream())); 
	        //while((inputLine = in.readLine()) != null){
	        //    System.out.println(inputLine);
	        //}
	        service.close();
	    } catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
    
}