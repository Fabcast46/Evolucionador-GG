package com.evolucionador.genetic;



public class Largo {
	// constructor
	public Largo(){}
	
	// devuelve el tamaño
	public int tamano(int num){
		int n = 0;
		for(int i = 0; i <= 16; i++){
			if (num > Math.pow(2,n)){
				n = n+1;
			}
		}
		return n;
	}
}
