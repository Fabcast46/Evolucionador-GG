package com.evolucionador.entities;
import com.evolucionador.genetic.*;

public class Entity {
	
	public Genome _Genome;
	public Entity _Father;
	public Entity _Mother;
	
	public int _HandDamage;
	public int _FootDamage;
	public int _BodyDamage;
	public int _HandDef;
	public int _FootDef;
	public int _BodyDef;
	public int _TotalDef;
		
	public int _ID;
	
	// constructor
	public Entity(){
		_Genome = null;
		_HandDamage = 0;
		_FootDamage = 0;
		_BodyDamage = 0;
		_HandDef = 0;
		_FootDef = 0;
		_BodyDef = 0;
		_TotalDef = 0;
	}
	
	// constructor para establecer caracteristicas especiales
	public Entity(Entity pFather, Entity pMother, Genome pGenome){
		this._Genome = pGenome;		
		this._Father = pFather;
		this._Mother = pMother;
	}
	
	// retorna el genoma del individuo, el cual posee los cromosomas del individuo
	public Genome getGenome(){
		return _Genome;
	}
	
	// asigna un ID al individuo
	public void setID(int pID){
		_ID = pID;
	}
	
	// retorna el ID del individuo
	public int getID(){
		return _ID;
	}
	
}
