#ifndef PESSOA_H
#define PESSOA_H

class Pessoa
{
public:
    Pessoa();
    int _idade;
    QString _nome;

    //Methods
    void setIdade(int idade);
    int getIdade(void);
    void setNome(QString nome);
    QString getNome(void);
};

#endif // PESSOA_H
