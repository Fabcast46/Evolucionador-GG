package com.evolucionador.dataStrucures;

import com.evolucionador.genetic.*;

public class BitVector {
	//metodo que se encarga de obtener un bit de una posicion especifica
    public int tomar(int numero,int posicion){
    	int bit=0;
    	int mascara=1;
    	mascara=mascara<<(posicion-1); //mascara para aplicar el or
    	if ((numero|mascara)==numero){ //si el numero no cambia con el or con la mascara es que en esa posicion habia un uno
    		bit=1;
    		return bit;
    	}
    	return bit; //como el numero cambio es que habia un 0 en la posicion
    }

    //metodo encargado de poner un valor a un bit en una posicion especifica del numero
    public int cambiar(int numero,int posicion,int valor){
    	int resultado=0;
    	if (valor==1){
    		int mascara=1<<(posicion-1);// se crea una mascara de puros 0s con un 1 en la posicion que se quiere cambiar
    		resultado= numero|mascara;
    	}
    	if (valor==0){
    		Largo tamanotot = new Largo();
    		int tamadenum=tamanotot.tamano(numero);
    		int mascaraand=(int) ((Math.pow(2,tamadenum)-1)-Math.pow(2,posicion-1));// formula que da una mascar de 1s con un 0 en la posicion que se quiere cambiar
    		if (mascaraand<=0){
    			resultado=numero;
    		}
    		else{
    			resultado=numero&mascaraand;
    		}
    	}
    	return resultado;
    }
}
