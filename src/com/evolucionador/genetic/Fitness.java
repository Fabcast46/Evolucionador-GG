package com.evolucionador.genetic;

import com.evolucionador.dataStrucures.*;
import com.evolucionador.entities.*;

public class Fitness {		
	private float _IniHandDam;
	private float _IniFootDam;
	private float _IniBodyDam;
	private float _IniTotalDef;

	// constructor
	public Fitness(){
		_IniHandDam = 0;
		_IniFootDam = 0;
		_IniBodyDam = 0;
		_IniTotalDef = 0;
	}
	
	// suma todos los datos que van a ser utilizados para el calculo del fitness
	public float getSumOfAll(){
		return _IniHandDam + _IniFootDam + _IniBodyDam + _IniTotalDef;
	}
	
	// restablece los datos
	public void restarData(){
		_IniHandDam = 0;
		_IniFootDam = 0;
		_IniBodyDam = 0;
		_IniTotalDef = 0;
	}
	
	// establece los valores bases de acuerdo a los datos de los individuos de la poblacion
	public void setBase(DoublyLinkedListImpl<Entity> pListEntities){
		this.restarData();
		Node<Entity> tmp = pListEntities.getHead();
		for(int j = 0 ; j < pListEntities.size(); j++){
			_IniHandDam = _IniHandDam + tmp.getData().getGenome().getCromosome(0);
			_IniFootDam = _IniFootDam + tmp.getData().getGenome().getCromosome(1);
			_IniBodyDam = _IniBodyDam + tmp.getData().getGenome().getCromosome(2);
			_IniTotalDef = _IniTotalDef + tmp.getData().getGenome().getCromosome(6);
			
			tmp = tmp.getNextNode();
		}

		return;
	}
	
	// calcular el fitness de un individuo en especifico, utilizando los valores establecidos
	public float caculateFitness(Entity pEntity){
		Genome pGen = pEntity.getGenome();	
				
		float Thefitness = (pGen.getHandDam()/_IniHandDam) + (pGen.getFootDam()/_IniFootDam) + (pGen.getBodyDam()/_IniBodyDam) +
				(pGen.getTotalDef()/_IniTotalDef);				
		
		return Thefitness;
	}		
}
