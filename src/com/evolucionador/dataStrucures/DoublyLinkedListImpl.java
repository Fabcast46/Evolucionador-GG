package com.evolucionador.dataStrucures;

import java.util.NoSuchElementException;

 
public class DoublyLinkedListImpl<E> {
    private Node<E> head; 
    private Node<E> tail;
    private int size;
    
     
    public DoublyLinkedListImpl() {
        size = 0;
    }
    
    /**
     * returns the size of the linked list
     * @return
     */
    public int size() { 
        
        return size;
    }
     
    /**
     * return whether the list is empty or not
     * @return
     */
    public boolean isEmpty() { return size == 0; }
     
    /**
     * adds element at the starting of the linked list
     * @param element
     */
    public void addFirst(E element) {
        Node<E> tmp = new Node<E>(element);
        if(head==null){
            head=tmp;
            tail=tmp;
            tmp.setNextNode(null);
            tmp.setPrevNode(null);
        }else{
             tmp.setNextNode(head);
             head.setPrevNode(tmp);
             head=tmp;
        }
        size++;
        //System.out.println("adding: "+data);
    }
     
    /**
     * adds element at the end of the linked list
     * @param element
     */
    public void addLast(E element) {
         
        Node<E> tmp = new Node<E>(element);
        if(tail==null){
            head=tmp;
            tail=tmp;
            tmp.setNextNode(null);
            tmp.setPrevNode(null);
        }
        else{
            tmp.setPrevNode(tail);
            tail.setNextNode(tmp);
            tail=tmp;
        }            
        size++;
        //System.out.println("adding: "+data);
    }
     
    /**
     * this method walks forward through the linked list
     */
    public void iterateForward(){
         
        System.out.println("iterating forward..");
        Node<E> tmp = head;
        while(tmp != null){
            System.out.println(tmp.getData());
            tmp = tmp.getNextNode();
        }
    }
     
    /**
     * this method walks backward through the linked list
     */
    public void iterateBackward(){
         
        System.out.println("iterating backword..");
        Node<E> tmp = tail;
        while(tmp != null){
            System.out.println(tmp.getData());
            tmp = tmp.getPrevNode();
        }
    }
     
    /**
     * this method removes element from the start of the linked list
     * @return
     */
    public E removeFirst() {
        if (size == 0) throw new NoSuchElementException();
        Node<E> tmp = head;
        head = head.getNextNode();
        head.setPrevNode(null);
        size--;
        //System.out.println("deleted: "+tmp.data);
        return tmp.getData();
    }
     
    /**
     * this method removes element from the end of the linked list
     * @return
     */
    public E removeLast() {
        if (size == 0) throw new NoSuchElementException();
        Node<E> tmp = tail;
        tail = tail.getPrevNode();
        tail.setNextNode(null);       
        size--;
        //System.out.println("deleted: "+tmp.data);
        return tmp.getData();
    }
    
    public void clear(){
    	Node<E> tmp = head;
    	for (int i = 0; i < size; i++){
    		tmp.setData(null);
    		tmp = tmp.getNextNode();
    	}           
        size = 0;
    }
    
    public Node<E> getHead(){
    	return head;
    }       
}
