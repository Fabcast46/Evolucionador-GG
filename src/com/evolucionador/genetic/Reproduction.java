package com.evolucionador.genetic;
import com.evolucionador.entities.*;
import com.evolucionador.dataStrucures.*;
import java.util.Random;

public class Reproduction{
	private Random _Random;
	public int mutaciones;
	public int inversiones;
	
	// analiza y realiza la mutacion del material genetico 
	private Genome mutate(Genome pGenoma){
		for(int i=0; i<7; i++){
			int valordemut = _Random.nextInt(10000);//porcentaje de mutacion y inversion
			//esta parte se encarga de hacer la mutacion
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
				//System.out.println("Valor de hijo despues" + resultado);
			}								
			//esta parte se encarga de hacer la inversion
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
				//cout<<"valor hijo despues "<<resultado2<<endl;
			}				
		}
		return pGenoma;		
	}
	
	// constructor
	public Reproduction(){
		this._Random = new Random();
	}
	
	// metodo para realizar un cruce entre dos individuos
	public Entity reproducir(Entity pFather, Entity pMother){		
		Genome pFatherGenome = pFather.getGenome();
		Genome pMotherGenome = pMother.getGenome();
		Genome newGenome = new Genome(0,0,0,0,0,0,0);
		int pGenFather = 0;
		int pGenMother = 0;
		int pNewGen1 = 0;
		int temporal=0;
		int primerval=0;
		BitVector usobitv =new BitVector();

		for(int i = 0; i<7;i++){
			pGenFather = pFatherGenome.getCromosome(i);
			pGenMother = pMotherGenome.getCromosome(i);
			temporal = _Random.nextInt(7)+1;
			//cout<<"porcentaje padre "<<temporal<<endl;
			pNewGen1 = 0;
			//cout<<"valor padre "<<pGenFather<<endl<<"valor madre "<<pGenMother<<endl;
			for (int l=1;l<=8;l++){
				if(l<=temporal){
					primerval=usobitv.tomar(pGenFather,l);
				//	cout<<"valor del padre "<<primerval<<endl;
					pNewGen1=usobitv.cambiar(pNewGen1,l,primerval);
				//	cout<<"valor hijo antes "<<pNewGen1<<endl;
				}
				else{
					primerval=usobitv.tomar(pGenMother,l);
				//	cout<<"valor de la madre "<<primerval<<endl;
					pNewGen1=usobitv.cambiar(pNewGen1,l,primerval);
				//	cout<<"valor hijo antes "<<pNewGen1<<endl;
				}
			}
			
			newGenome.setCromosome(i,pNewGen1);
			//cout<<"nuevo Gen Id "<<i<<". Es: "<<pNewGen1<<" equivale: "<<pNewGen1<<endl;
//			cout<<"valor hijo antes2 "<<pNewGen1<<endl;
			//cout<<"nuevo Gen Id "<<i<<". Es: "<<bitset<16>(pNewGen1).to_string()<<" equivale: "<<pNewGen1<<endl;
		}
		//La mutacion ocurre dentro de la reproduccion
		newGenome = mutate(newGenome);
		Entity newEntity = new Entity(pFather,pMother,newGenome);
		//cout<<"New Entity: "<< newEntity->getID() << endl;
		return newEntity;
	}
}
