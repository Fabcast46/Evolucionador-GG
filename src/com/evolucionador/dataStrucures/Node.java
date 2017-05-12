package com.evolucionador.dataStrucures;


public class Node<E> {

        public E data;
        private Node<E> next;
        private Node<E> prev;
        
        public Node(){
        	next=null;
            prev=null;
            data=null;
        }
        public Node(E data) {
            this(data, null, null);
        }
        public Node(E element, Node<E> next, Node<E> prev) {
            this.data = element;
            this.next = next;
            this.prev = prev;
        }
        public E getData() {
            return data;
        }
        public void setNextNode(Node<E> next) {
            this.next = next;
        }
        public Node<E> getPrevNode() {
            return prev;
        }
        public void setPrevNode(Node<E> prev) {
            this.prev = prev;
        }
        public void setData(E data) {
            this.data = data;
        }
        public Node<E> getNextNode() {
            return next;
        }
}
