#ifndef _UMLUSECASE_H
#define _UMLUSECASE_H


#include "UmlBaseUseCase.h"

#include "Vector.h"

// This class manages 'use case'
//
// You can modify it as you want (except the constructor)
class UmlUseCase : public UmlBaseUseCase
{
public:
    UmlUseCase(void * id, const QByteArray & n) : UmlBaseUseCase(id, n) {};

    //returns a string indicating the king of the element
    virtual QByteArray sKind();

    //entry to produce the html code receiving chapter number
    //path, rank in the mother and level in the browser tree
    virtual void html(QByteArray pfix, unsigned int rank, unsigned int level);

    //set the html ref
    //set the use case list
    virtual void memo_ref();

    static void ref_index();

    static void generate_index();

    virtual bool chapterp();


protected:
    static Vector usecases;

};

#endif
