package com.evolucionador.genetic;


import javax.ws.rs.*;
import javax.ws.rs.core.*;
import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
 
import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.evolucionador.enemies.*;
import com.evolucionador.entities.*;
import com.evolucionador.dataStrucures.*;


@Path("/evolucionador/generacion/")
public class Evolucionador {
	static sock _Socket = new sock();
	static Gladiator _Gladiadores1;
	static Gladiator _Gladiadores2;
	private static int contador = 0;
	private static int _ID = 0;
	private static int cantidadMuta1 = 0;
	private static int cantidadInver1 = 0;
	private static int cantidadMuta2 = 0;
	private static int cantidadInver2 = 0;
	private static double _fitnessProm1 = 0;
	private static double _fitnessProm2 = 0;
	private static String msg1;
	private static String msg2;

	// escribe las caracteristicas necesarias de los individuos en el xml
	//
	// en esta parte es donde tenemos que cambiar las caracteristicas que se van a escribir
	// en el archivo xml
	public void escribir(Document doc, Element rootElement, Poblacion Population){
		Node<Entity> tmpO = Population.getIndividuals().getHead();
		for(int i = 0; i < Population.getCantidadDeIndividuos(); i++){
			// individuo
    		Element individuo = doc.createElement("Gladiador"+String.valueOf(_ID));
    		rootElement.appendChild(individuo);
    		_ID++;
    		
    		//nombre
    		Element nombre = doc.createElement("Nombre");
    		nombre.appendChild(doc.createTextNode(tmpO.getData().getGenome()._Name));
    		individuo.appendChild(nombre);
    		
    		//daño mano
    		Element danoM = doc.createElement("DanoMano");
    		int handDam = tmpO.getData().getGenome().getCromosome(0);        		
    		danoM.appendChild(doc.createTextNode(String.valueOf(handDam)));
    		individuo.appendChild(danoM);
    		
    		//daño pie
    		Element danoP = doc.createElement("DanoPie");
    		int footDam = tmpO.getData().getGenome().getCromosome(1);        		
    		danoP.appendChild(doc.createTextNode(String.valueOf(footDam)));
    		individuo.appendChild(danoP);
    		
    		//daño cuerpo
    		Element danoC = doc.createElement("DanoCuerpo");
    		int bodyDam = tmpO.getData().getGenome().getCromosome(2);        		
    		danoC.appendChild(doc.createTextNode(String.valueOf(bodyDam)));
    		individuo.appendChild(danoC);
    		
    		//defensa mano
    		Element defMano = doc.createElement("ResistenciaMano");
    		int handDef = tmpO.getData().getGenome().getCromosome(3);        		
    		defMano.appendChild(doc.createTextNode(String.valueOf(handDef)));
    		individuo.appendChild(defMano);
    		    		
    		//defensa pie
    		Element defPie = doc.createElement("ResistenciaPie");
    		int footDef = tmpO.getData().getGenome().getCromosome(4);        		
    		defPie.appendChild(doc.createTextNode(String.valueOf(footDef)));
    		individuo.appendChild(defPie);
    		
    		//defensa cuerpo
    		Element defCuerpo = doc.createElement("ResistenciaCuerpo");
    		int bodyDef = tmpO.getData().getGenome().getCromosome(5);        		
    		defCuerpo.appendChild(doc.createTextNode(String.valueOf(bodyDef)));
    		individuo.appendChild(defCuerpo);
    		
    		//defensa total
    		Element defTotal = doc.createElement("ResistenciaTotal");
    		int totalDef = tmpO.getData().getGenome().getCromosome(6);        		
    		defTotal.appendChild(doc.createTextNode(String.valueOf(totalDef)));
    		individuo.appendChild(defTotal);
    		    		
    		tmpO = tmpO.getNextNode();
        }
	}
	
	// Muestra la cantidad de individuos
	public void showIndividuos(){		
		System.out.println("Cantidad de gladiadores 1...   " + _Gladiadores1.getCantidadDeIndividuos());
		System.out.println("Cantidad de gladiadores 2...   " + _Gladiadores2.getCantidadDeIndividuos());
	}
	
	// Realiza la generacion inicial de enemigos
	public void inicio(){		
		_Gladiadores1 = new Gladiator();
		_Gladiadores2 = new Gladiator();
	}
	
	// Realiza cruces para generar nuevos individuos 
	public void generation(){		
		_Gladiadores1.DoGeneration();
		cantidadMuta1 = _Gladiadores1._Mutaciones;
		cantidadInver1 = _Gladiadores1._Inversiones;
		_Gladiadores2.DoGeneration();
		cantidadMuta2 = _Gladiadores2._Mutaciones;
		cantidadInver2 = _Gladiadores2._Inversiones;
	}
	
	// Metodo inicial del evolucionador, se encarga de revisar si es la primer generacion
	@GET
	@Produces(MediaType.TEXT_HTML)
	public String returnTitle() {
		if(contador == 0){
			inicio();			
		}
		else{
			generation();
		}
		
		Node<Entity> individuo1;
		individuo1 = _Gladiadores1.getIndividuals().getHead();
		for(int i = 0; i < _Gladiadores1.getCantidadDeIndividuos(); i++){
			_fitnessProm1 += _Gladiadores1.calculateFitnessTo(individuo1.getData());
			individuo1.getNextNode();
		}
		_fitnessProm1 = _fitnessProm1 / _Gladiadores1.getCantidadDeIndividuos();
		Node<Entity> individuo2;
		individuo2 = _Gladiadores2.getIndividuals().getHead();
		for(int i = 0; i < _Gladiadores2.getCantidadDeIndividuos(); i++){
			_fitnessProm2 += _Gladiadores2.calculateFitnessTo(individuo2.getData());
			individuo2.getNextNode();
		}
		_fitnessProm2 = _fitnessProm2 / _Gladiadores2.getCantidadDeIndividuos();
		
		showIndividuos();             
        _ID = 1;   
        //String msg;        
        msg1 = String.valueOf(_Gladiadores1.selectTheFittest().getGenome().getHandDam())+"/"+String.valueOf(_Gladiadores1.selectTheFittest().getGenome().getFootDam())+"/"+
        		String.valueOf(_Gladiadores1.selectTheFittest().getGenome().getBodyDam())+"/"+String.valueOf(_Gladiadores1.selectTheFittest().getGenome().getHandDef())+"/"+
        		String.valueOf(_Gladiadores1.selectTheFittest().getGenome().getFootDef())+"/"+String.valueOf(_Gladiadores1.selectTheFittest().getGenome().getBodyDef())+"/"+
        		String.valueOf(_Gladiadores1.selectTheFittest().getGenome().getTotalDef())+"/"+_Gladiadores1.calculateFitnessTo(_Gladiadores1.selectTheFittest())+"/"+
        		String.valueOf(_fitnessProm1)+"/"+String.valueOf(cantidadMuta1)+"/";
        msg2 = String.valueOf(_Gladiadores2.selectTheFittest().getGenome().getHandDam())+"/"+String.valueOf(_Gladiadores2.selectTheFittest().getGenome().getFootDam())+"/"+
        		String.valueOf(_Gladiadores2.selectTheFittest().getGenome().getBodyDam())+"/"+String.valueOf(_Gladiadores2.selectTheFittest().getGenome().getHandDef())+"/"+
        		String.valueOf(_Gladiadores2.selectTheFittest().getGenome().getFootDef())+"/"+String.valueOf(_Gladiadores2.selectTheFittest().getGenome().getBodyDef())+"/"+
        		String.valueOf(_Gladiadores2.selectTheFittest().getGenome().getTotalDef())+"/"+_Gladiadores2.calculateFitnessTo(_Gladiadores2.selectTheFittest())+"/"+
        		String.valueOf(_fitnessProm2)+"/"+String.valueOf(cantidadMuta2)+"/";
        //_Socket.con(msg);
        try {        	
    		DocumentBuilderFactory docFactory = DocumentBuilderFactory.newInstance();
    		DocumentBuilder docBuilder = docFactory.newDocumentBuilder();
     
    		// elemento raiz
    		Document doc = docBuilder.newDocument();
    		Element rootElement = doc.createElement("Gladiadores");
    		doc.appendChild(rootElement);
    		
    		
    		Element numero = doc.createElement("Cantidad");
    		rootElement.appendChild(numero);

    		Element valor = doc.createElement("Valor");
    		valor.appendChild(doc.createTextNode(String.valueOf(_Gladiadores1.getCantidadDeIndividuos())));
    		numero.appendChild(valor);
    		
    		Element mutaciones = doc.createElement("Mutaciones");
    		rootElement.appendChild(mutaciones);
    		Element valorMuta = doc.createElement("Valor");
    		valorMuta.appendChild(doc.createTextNode(String.valueOf(cantidadMuta1)));
    		mutaciones.appendChild(valorMuta); 
    		
    		Element inversiones = doc.createElement("Inversiones");
    		rootElement.appendChild(inversiones);
    		Element valorInver = doc.createElement("Valor");
    		valorInver.appendChild(doc.createTextNode(String.valueOf(cantidadInver1)));
    		inversiones.appendChild(valorInver); 
    		
    		escribir(doc, rootElement, _Gladiadores1);
    		
    
    		// escribimos el contenido en un archivo .xml
    		TransformerFactory transformerFactory = TransformerFactory.newInstance();
    		Transformer transformer = transformerFactory.newTransformer();
    		DOMSource source = new DOMSource(doc);
    		
    		StreamResult result = new StreamResult(new File("/home/fabricio/workspace/EvolucionadorGenetico/Poblacion1/generacion_" + String.valueOf(contador) + ".xml"));
         
    		transformer.transform(source, result);
     
    		System.out.println("File saved!");
    		
    		
    		// elemento raiz
    		Document doc2 = docBuilder.newDocument();
    		Element rootElement2 = doc2.createElement("Gladiadores");
    		doc2.appendChild(rootElement2);
    		
    		
    		Element numero2 = doc2.createElement("Cantidad");
    		rootElement2.appendChild(numero2);

    		Element valor2 = doc2.createElement("Valor");
    		valor2.appendChild(doc2.createTextNode(String.valueOf(_Gladiadores2.getCantidadDeIndividuos())));
    		numero2.appendChild(valor2);
    		
    		Element mutaciones2 = doc2.createElement("Mutaciones");
    		rootElement2.appendChild(mutaciones2);
    		Element valorMuta2 = doc2.createElement("Valor");
    		valorMuta2.appendChild(doc2.createTextNode(String.valueOf(cantidadMuta2)));
    		mutaciones2.appendChild(valorMuta2); 
    		
    		Element inversiones2 = doc2.createElement("Inversiones");
    		rootElement2.appendChild(inversiones2);
    		Element valorInver2 = doc2.createElement("Valor");
    		valorInver2.appendChild(doc2.createTextNode(String.valueOf(cantidadInver2)));
    		inversiones2.appendChild(valorInver2);  
    		
    		escribir(doc2, rootElement2, _Gladiadores2);
    		
    
    		// escribimos el contenido en un archivo .xml
    		TransformerFactory transformerFactory2 = TransformerFactory.newInstance();
    		Transformer transformer2 = transformerFactory2.newTransformer();
    		DOMSource source2 = new DOMSource(doc2);
    		
    		StreamResult result2 = new StreamResult(new File("/home/fabricio/workspace/EvolucionadorGenetico/Poblacion2/generacion_" + String.valueOf(contador) + ".xml"));
         
    		transformer2.transform(source2, result2);
     
    		System.out.println("File saved!");
     
    		} catch (ParserConfigurationException pce) {
    			pce.printStackTrace();
    		} catch (TransformerException tfe) {
    			tfe.printStackTrace();
    		}
		
        System.out.println(contador);
        
		contador++;
        
		return (msg1+msg2);
	}	
	
}