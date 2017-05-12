package com.evolucionador.enemies;

import com.evolucionador.dataStrucures.*;
import com.evolucionador.entities.*;
import com.evolucionador.genetic.*;
import java.util.Random;
import java.io.*;

public class Poblacion {
	
	//private static final String FILENAME = "E:\\test\\filename.txt";
	
	protected Fitness _Fitness;
	protected DoublyLinkedListImpl<Entity> _Individuos;
	protected DoublyLinkedListImpl<Entity> _Padres;
	protected int _CantPadres;
	protected Random _Random;
	protected Reproduction _Reproduction;
	protected short CurrentGeneration;
	public int _Mutaciones;
	public int _Inversiones;
	
	
	
	
	// constructor
	public Poblacion(){
		this._CantPadres = 0;
		this._Random = new Random();
		this._Reproduction = new Reproduction();
		this._Individuos = new DoublyLinkedListImpl<Entity>();
		this._Fitness = new Fitness();
		this._Padres = new DoublyLinkedListImpl<Entity>();
	}
	
	public String getRandomName(){
		// The name of the file to open.
        String fileName = "/home/fabricio/workspace/evo/src/names";

        // This will reference one line at a time
        String line = null;

        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            int random = _Random.nextInt(4945)+1;
            for(int i = 0;i < random; i++){
            	line = bufferedReader.readLine();
            }
              

            // Always close files.
            bufferedReader.close();         
        }
        catch(FileNotFoundException ex) {
            System.out.println(
                "Unable to open file '" + 
                fileName + "'");                
        }
        catch(IOException ex) {
            System.out.println(
                "Error reading file '" 
                + fileName + "'");                  
            // Or we could just do this: 
            // ex.printStackTrace();
        }
		
		
		return line;
	}
	
	public Entity selectTheFittest(){
		int escogible = 0;
		int cantidadElementos = this._Individuos.size();
		Node<Entity> tmpNode = this._Individuos.getHead();
		Node<Entity> tmpFittest = this._Individuos.getHead();
		float tmpFitness = _Fitness.caculateFitness(tmpNode.getData());
		
		for(int i = 0; i < cantidadElementos; i++){
			if(_Fitness.caculateFitness(tmpNode.getData()) <= tmpFitness){
				tmpNode = tmpNode.getNextNode();
			}
			else{
				if(this._CantPadres != 0){
					Node<Entity> tmpFather = this._Padres.getHead();
					for(int j = 0; j < _Padres.size(); j++){
						if(tmpNode.getData() != tmpFather.getData()){
							if(_Padres.size() == 1){
								escogible = 0;
							}
							//tmpFittest = tmpNode;
							//tmpFitness = _Fitness.caculateFitness(tmpNode.getData());
							//tmpNode = tmpNode.getNextNode();
							//break;
							
						}
						else{
							escogible = 1;
							tmpFather = tmpFather.getNextNode();
						}
					}
					if(escogible == 0){
						tmpFittest = tmpNode;
						tmpFitness = _Fitness.caculateFitness(tmpNode.getData());
						tmpNode = tmpNode.getNextNode();
					}
					else{
						tmpNode = tmpNode.getNextNode();
						escogible = 0;
					}					
				}
				else{
					tmpFittest = tmpNode;
					tmpFitness = _Fitness.caculateFitness(tmpNode.getData());
					tmpNode = tmpNode.getNextNode();
				}
			}
		}
		if(this._CantPadres == 0){
			_Padres.addFirst(tmpFittest.getData());
			//this._CantPadres++;
		}
		else{
			_Padres.addLast(tmpFittest.getData());
			//this._CantPadres++;
		}
		return tmpFittest.getData();
	}
	
	// selecciona de manera aleatoria un fitness
	public Entity randomSelectTheFittest(){
		//obtener un numero aleatorio, desde 0 hasta la suma de todos los fitnes multiplicado por la cantidad de genes
		int randomObtained = _Random.nextInt((int) (_Fitness.getSumOfAll()*4));

		int cantidadElementos = this._Individuos.size();
		Node<Entity> tmpNode = this._Individuos.getHead();


		for(int i = 0; i<cantidadElementos; i++){
			if(  (_Fitness.caculateFitness(tmpNode.getData()) *_Fitness.getSumOfAll()) > randomObtained ){				
				break;
			}
			randomObtained = (int) (randomObtained - (_Fitness.caculateFitness(tmpNode.getData())*_Fitness.getSumOfAll()));
			tmpNode = tmpNode.getNextNode();
		}
		return tmpNode.getData();		
	}
	
	/**
	 * Utiliza el metodo "randomSelectTheFittest"
	 * para retornar una entidad
	 */
	public Entity randomSelectTheFittestFather(){
		Entity pResp = this.randomSelectTheFittest();
		this._CantPadres++;
		return pResp;
	}
			
	// calcula el fitness de una entidad
	public float calculateFitnessTo(Entity pEntity){
		return _Fitness.caculateFitness(pEntity);
	}
	
	// metodo para llavar a cabo una generacion
	public void DoGeneration(){
		//_Padres.addFirst(null);
		//this._Mutaciones = 0;
		//this._Inversiones = 0;
		_Padres.clear();	
		int newBorns = 10;
		
		for(int k=0; k < newBorns;k++){
			int select = 0;
			//La seleccion natural ocurre en las dos siguiente lineas.
			Entity NewFather = selectTheFittest();
			this._CantPadres++;
			Entity NewMother = selectTheFittest();
			while(NewFather == NewMother){
				if(select==5){
					while(NewFather == NewMother)
					NewMother = randomSelectTheFittestFather();
				}
				else{					
					NewMother = selectTheFittest();
				}
				select++;
			}
			this._CantPadres++;
			Entity NewSon = _Reproduction.reproducir(NewFather, NewMother);
			NewSon.getGenome()._Name = getRandomName();
			_Individuos.addLast(NewSon); 
		}		
		CurrentGeneration++;
		this._Mutaciones = _Reproduction.mutaciones;
		this._Inversiones = _Reproduction.inversiones;

		return;
	}	
	
	// regresa una lista de individuos
	public DoublyLinkedListImpl<Entity> getIndividuals(){		
		return _Individuos;
	}	
	
	public short getCurrentGeneration(){
		return CurrentGeneration;
	}
	
	public int getCantidadDeIndividuos(){
		return _Individuos.size();
	}	
}
