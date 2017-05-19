package com.evolucionador.genetic;

import com.evolucionador.dataStrucures.*;

public class Genome extends DoublyLinkedListImpl<Integer>{
	
	public String _Name;
	public int _HandDamage;
	public int _FootDamage;
	public int _BodyDamage;
	public int _HandDef;
	public int _FootDef;
	public int _BodyDef;
	public int _TotalDef;
	
	
	
	// constructor en el que se establecen los valores a cada individuo
	public Genome(int HandDam, int FootDam, int BodyDam, int HandDef, int FootDef, int BodyDef, int TotalDef){
		this._HandDamage = HandDam;
		this._FootDamage = FootDam;
		this._BodyDamage = BodyDam;
		this._HandDef = HandDef;
		this._FootDef = FootDef;
		this._BodyDef = BodyDef;
		this._TotalDef = TotalDef;
		addLast(HandDam);
		addLast(FootDam);
		addLast(BodyDam);
		addLast(HandDef);
		addLast(FootDef);
		addLast(BodyDef);
		addLast(TotalDef);
		
	}
	
	// regresa el cromosoma especificado por el parametro de entrada
	public int getCromosome(int pCromID){
		Node<Integer> tmp = getHead();
		for(int i = 0; i < pCromID; i++){
			tmp = tmp.getNextNode();
		}
		return tmp.getData();
	}
	
	// establece un cromosoma especifico con el valor dado, en la posicion del parametro de entrada
	public void setCromosome(int pCromID, int pData){
		Node<Integer> tmp = getHead();
		for(int i = 0; i != pCromID; i++){
			tmp = tmp.getNextNode();
		}
		tmp.setData(pData);		
	}
	
	// Establece el nombre del individuo de acuerdo al dado de entrada
	public void setName(String name){
		_Name = name;
	}
	
	// establece la resistencia total de acuerdo a las otras 3 resistencias
	public void setTotalDef(){
		int tmp = (this.getHandDef() + this.getFootDef() + this.getBodyDef());
		setCromosome(6, tmp);
	}
	
	// retorna el daño de ataque de mano
	public int getHandDam(){
		return getCromosome(0);
	}
	
	// retorna el daño de ataque de pie
	public int getFootDam(){
		return getCromosome(1);
	}
	
	// retorna el daño de ataque de cuerpo
	public int getBodyDam(){
		return getCromosome(2);
	}
	
	// retorna la defensa de mano
	public int getHandDef(){
		return getCromosome(3);
	}
	
	// retorna la defensa de pie
	public int getFootDef(){
		return getCromosome(4);
	}
	
	// retorna la defensa de cuerpo
	public int getBodyDef(){
		return getCromosome(5);
	}
	
	// retorna la defensa de total
	public int getTotalDef(){
		return getCromosome(6);
	}
		
}
