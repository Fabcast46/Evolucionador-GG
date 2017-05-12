/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Gladiator.h
 * Author: fabricio
 *
 * Created on 11 de mayo de 2017, 12:26 PM
 */

#ifndef GLADIATOR_H
#define GLADIATOR_H

class Gladiator {
public:
    Gladiator();
    void setHandDam(int dato);
    void setFootDam(int dato);
    void setBodyDam(int dato);
    void setHandDef(int dato);
    void setFootDef(int dato);
    void setBodyDef(int dato);
    void setTotalDef(int dato);
    int getHandDam();
    int getFootDam();
    int getBodyDam();
    int getHandDef();
    int getFootDef();
    int getBodyDef();
    int getTotalDef();
    virtual ~Gladiator();
private:
    int handDam;
    int footDam;
    int bodyDam;
    int handDef;
    int footDef;
    int bodyDef;
    int totalDef;

};

#endif /* GLADIATOR_H */

