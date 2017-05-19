package com.evolucionador.genetic;
import com.evolucionador.entities.*;
import com.evolucionador.dataStrucures.*;
import java.util.Random;

public class Reproduction{
	private Random _Random;
	public int mutaciones;
	public int inversiones;
	
	// analiza y realiza la mutacion y la inversion del material genetico 
	private Genome mutate(Genome pGenoma){
		mutaciones = 0;
		inversiones= 0;
		for(int i=0; i<7; i++){
			int valordemut = _Random.nextInt(10000);//porcentaje de mutacion y inversion

			//esta seccion se encarga de realizar la mutacion de un cromosoma especifico 
			if(valordemut <= 120){
				int cromosoma = pGenoma.getCromosome(i);//cromosoma original
				Largo tamanoto = new Largo();
				int cantidad = tamanoto.tamano(cromosoma);
				int posicion= _Random.nextInt(cantidad+2)+1;//posicion random donde se realiza mutacion
				BitVector usobitv = new BitVector();
				int resultado = usobitv.cambiar(cromosoma,posicion,1);
				if(cromosoma==resultado){
					resultado=usobitv.cambiar(cromosoma,posicion,0);
				}
				pGenoma.setCromosome(i,resultado);
				mutaciones++;
			}				
			
			//esta seccion se encarga de realizar la inversion de un cromosoma especifico
			if(valordemut<=20){
				int cromosoma=pGenoma.getCromosome(i);
				int resultado2=cromosoma;
				int primerrango=_Random.nextInt(3)+1;//posicion inicial desde donde empieza la inversion
				int segundorango=_Random.nextInt(3)+5;//posicion final donde termina la inversion
				BitVector usobitv = new BitVector();
				int posicion=segundorango;
				for(int j=primerrango;j<=segundorango;j++){//se encarga de ir cambiando los bits
					int primervalor= usobitv.tomar(cromosoma,j);
					resultado2=usobitv.cambiar(resultado2,posicion,primervalor);
					posicion=posicion-1;
				}
				pGenoma.setCromosome(i,resultado2);
				inversiones++;
			}				
		}
		return pGenoma;		
	}
	
	// constructor
	public Reproduction(){
		this._Random = new Random();
	}
	
	// metodo para realizar un cruce entre dos individuos, 
	// toma la mitad de bits del padre y la otra mitad de la madre
	// realiza un cruce entre la mitad derecha del padre y la izquierda de la madre
	// realiza otro cruce entre la mitad izquierda del padre y la derecha de la madre
	// analiza cual de los dos cruces es el mejor y establece ese cromosoma al nuevo individuo
	// retorna el individuo resultante
	public Entity reproducir(Entity pFather, Entity pMother){		
		Genome pFatherGenome = pFather.getGenome();
		Genome pMotherGenome = pMother.getGenome();
		Genome newGenome = new Genome(0,0,0,0,0,0,0);
		int pGenFather = 0;
		int pGenMother = 0;
		int pNewGen1 = 0;
		int pNewGen2 = 0;
		int temporal=0;
		int primerval=0;
		BitVector usobitv =new BitVector();

		for(int i = 0; i<7;i++){
			pGenFather = pFatherGenome.getCromosome(i);
			pGenMother = pMotherGenome.getCromosome(i);
			temporal = 4;
			pNewGen1 = 0;
			pNewGen2 = 0;
			for (int l=1;l<=8;l++){
				if(l<=temporal){
					primerval=usobitv.tomar(pGenFather,l);
					pNewGen1=usobitv.cambiar(pNewGen1,l,primerval);
				}
				else{
					primerval=usobitv.tomar(pGenMother,l);
					pNewGen1=usobitv.cambiar(pNewGen1,l,primerval);
				}
			}
			
			for (int l=1;l<=8;l++){
				if(l<=temporal){
					primerval=usobitv.tomar(pGenMother,l);
					pNewGen2=usobitv.cambiar(pNewGen2,l,primerval);
				}
				else{
					primerval=usobitv.tomar(pGenFather,l);
					pNewGen2=usobitv.cambiar(pNewGen2,l,primerval);
				}
			}
			if(pNewGen1 >= pNewGen2){
				newGenome.setCromosome(i, pNewGen1);
			}
			else if(pNewGen1 < pNewGen2){
				newGenome.setCromosome(i, pNewGen2);
			}
		}
		//La mutacion ocurre dentro de la reproduccion
		newGenome = mutate(newGenome);
		Entity newEntity = new Entity(pFather,pMother,newGenome);
		return newEntity;
	}
}
