#include "Gladiator.h"

Gladiator::Gladiator() {
}

void Gladiator::setBodyDam(int dato){
    bodyDam = dato;
}

void Gladiator::setFootDam(int dato) {
    footDam = dato;
}

void Gladiator::setHandDam(int dato) {
    handDam = dato;
}

void Gladiator::setBodyDef(int dato) {
    bodyDef = dato;
}

void Gladiator::setFootDef(int dato) {
    footDef = dato;
}

void Gladiator::setHandDef(int dato) {
    handDef = dato;
}

void Gladiator::setTotalDef(int dato) {
    totalDef = dato;
}

int Gladiator::getBodyDam() {
    return bodyDam;
}

int Gladiator::getBodyDef() {
    return bodyDef;
}

int Gladiator::getFootDam() {
    return footDam;
}

int Gladiator::getFootDef() {
    return footDef;
}

int Gladiator::getHandDam() {
    return handDam;
}

int Gladiator::getHandDef() {
    return handDef;
}

int Gladiator::getTotalDef() {
    return totalDef;
}

Gladiator::~Gladiator() {
}

