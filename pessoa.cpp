#include "iostream"
#include "QString"
#include "QDebug"
#include "pessoa.h"
using namespace std;

Pessoa::Pessoa(){
    //cout << "Object is being created" << endl;
}

void Pessoa::setIdade(int idade){
    //cout << "setIdade Recebeu: " << idade << endl;
    this->_idade = idade;
}

int Pessoa::getIdade(void){
    return this->_idade;
}

void Pessoa::setNome(QString nome){
    //_nome = "";
    //cout << "setNome Recebeu: " << nome << endl;
    //qDebug() << nome;
    //qDebug() << "setNome Recebeu: " << nome;
    this->_nome = nome;
    //_nome = "Sergio";
    //qDebug() << "_nome na setnome tem: " << _nome;
    //getNome();
}

QString Pessoa::getNome(void){
    //int g  = 10;
    //cout << g;
    //qDebug() << g;
   //qDebug() << "_nome na getnome tem: " << _nome;
   return this->_nome;
}
