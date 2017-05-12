package com.evolucionador.enemies;

import java.util.Random;

import com.evolucionador.entities.*;
import com.evolucionador.genetic.*;

public class Gladiator extends Poblacion {
	private Random _Random;
	
	public Gladiator(){
		_Random = new Random();  
		Genome newGenome;
		for(int i = 0; i < 90; i++){
			Entity father = new Entity();
			Entity mother = new Entity();
			newGenome = new Genome(_Random.nextInt(33)+1, _Random.nextInt(33)+1,
					_Random.nextInt(33)+1, _Random.nextInt(33)+1, _Random.nextInt(33)+1,
					_Random.nextInt(33)+1, _Random.nextInt(33)+1);			
			Entity newGladiator = new Entity(father,mother,newGenome);
			newGladiator.getGenome().setTotalDef();
			newGladiator.getGenome().setName(this.getRandomName());
			this._Individuos.addLast(newGladiator);
			
		}
		_Fitness.setBase(this._Individuos);
	}
}