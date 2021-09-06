#include "model_annotazione.h"

model_annotazione::model_annotazione() : _needToSave(false),_annotazioni()
{

}

model_annotazione::~model_annotazione()
{
    _annotazioni.clear();
}

void model_annotazione::readFromFile(const QDomDocument &doc)
{
    reset();
    QDomElement root = doc.firstChildElement();
    if(root.nodeName()!= "Annotazioni")
        throw new std::invalid_argument("La root non ha nome \"Annotazioni\"");
    for (int i=0;i<root.childNodes().size();++i)
    {
        if(root.childNodes().at(i).nodeName()=="Nota")
        {
            QDomElement no=root.childNodes().at(i).toElement();
           aggiungiAnnotazione(new nota(no));
        }
        else if(root.childNodes().at(i).nodeName()=="Promemoria")
        {
            QDomElement prom=root.childNodes().at(i).toElement();
            aggiungiAnnotazione(new promemoria(prom));
        }
        else if(root.childNodes().at(i).nodeName()=="Ricorrenza")
        {
            QDomElement ricorr=root.childNodes().at(i).toElement();
            aggiungiAnnotazione(new ricorrenza(ricorr));
        }
        else if(root.childNodes().at(i).nodeName()=="Elenco")
        {
            QDomElement elenc=root.childNodes().at(i).toElement();
            aggiungiAnnotazione(new elenco(elenc));
        }
        else if(root.childNodes().at(i).nodeName()=="Spesa")
        {
            QDomElement spes=root.childNodes().at(i).toElement();
            aggiungiAnnotazione(new spesa(spes));
        }
        else
        {
            throw new std::runtime_error("Impossibile processare il contenuto");
        }

    }
    _needToSave = false;

}

QDomDocument model_annotazione::saveFile() const
{
    QDomDocument doc("Annotazioni");
    QDomElement root = doc.createElement("Annotazioni");

    for (lista<annotazione*>::constiterator cit = _annotazioni.begin(); cit != _annotazioni.end(); ++cit)
    {
        root.appendChild((*cit)->XmlSerialize(doc));
    }
    doc.appendChild(root);
    return doc;
}

void model_annotazione::aggiungiAnnotazione(annotazione  *annotazione)
{
    _annotazioni.insertBack(annotazione);
    _needToSave=true;
}

lista<annotazione *> model_annotazione::getAnnotazioni() const
{
    return _annotazioni;
}

annotazione *model_annotazione::getAnnotazione(const unsigned int i) const
{
    if( _annotazioni.getSize()<i)
    {
        return nullptr;
    }
    else
    {
        unsigned int _counter = 0;
        for(lista<annotazione*>::constiterator ci=_annotazioni.begin();ci!=_annotazioni.end();ci++)
        {
            if(_counter == i)
                return *ci;
            _counter++;
        }
    }
    return nullptr;
}

void model_annotazione::reset()
{
    _annotazioni.clear();
    _needToSave=true;
}

void model_annotazione::rimouviElemento(const annotazione *annot)
{
    lista<annotazione *>::constiterator ci = _annotazioni.begin();
    bool _eliminato = false;
    while( ci != _annotazioni.end() && _eliminato == false)
    {
        if(*ci == annot)
        {
            _annotazioni.erase(ci);
            _eliminato=true;
        }
        ci++;
    }
    _needToSave=true;
}

bool model_annotazione::modificaElemento(int _index,annotazione *annot)
{
    int i=0;
    for(lista<annotazione*>::constiterator ci=_annotazioni.begin();
        ci!=_annotazioni.end();ci++)
    {

        if(i==_index)
        {

            if(dynamic_cast<promemoria*>(*ci))
            {

                promemoria* P1= dynamic_cast<promemoria*>(*ci);
                promemoria* P2= dynamic_cast<promemoria*>(annot);

                if( (*P1)==(*P2))
                    return false;
                else{
                    _needToSave=true;
                    *P1=*P2;
                    return true;
                }
            }
            else if(dynamic_cast<ricorrenza*>(*ci))
            {
                ricorrenza* R1= dynamic_cast<ricorrenza*>(*ci);
                ricorrenza* R2= dynamic_cast<ricorrenza*>(annot);

                if( (*R1)==(*R2))
                    return false;
                else{
                    _needToSave=true;
                    *R1=*R2;
                    return true;
                }
            }
            else if(dynamic_cast<spesa*>(*ci))
            {
                spesa* S1= dynamic_cast<spesa*>(*ci);
                spesa* S2= dynamic_cast<spesa*>(annot);

                if(*S1==(*S2))
                    return false;
                else
                {
                    _needToSave=true;
                    *S1=*S2;
                    return true;
                }
            }
            else if(dynamic_cast<elenco*>(*ci) )
            {
                elenco* E1= dynamic_cast<elenco*>(*ci);
                elenco* E2= dynamic_cast<elenco*>(annot);

                if(*E1==(*E2))
                    return false;
                else
                {
                    _needToSave=true;
                    *E1=*E2;
                    return true;
                }

            }
            if(dynamic_cast<nota*>(*ci))
            {
                nota* N1= dynamic_cast<nota*>(*ci);
                nota* N2= dynamic_cast<nota*>(annot);

                if( *N1==(*N2) )
                    return false;
                else{
                    _needToSave=true;
                    *N1=*N2;
                    return true;
                }
            }
        }
        i++;
    }
    return false;
};

bool model_annotazione::muoviElementoDx(const lista<annotazione*>::constiterator ci)
{
    int i = _annotazioni.indexOfInt(_annotazioni.index(ci));
    bool trovato=false;
    if(i!=int(_annotazioni.getSize()-1))
    {
        int count=0;
        lista<annotazione*> temp;
        for(lista<annotazione*>::constiterator cit=_annotazioni.begin();cit!=_annotazioni.end();cit++)
        {
            if(count==i)
            {
                temp.insertBack(*(++cit));
                temp.insertBack(*(--cit));
                cit++;
                trovato=true;
            }
            else
            {
                temp.insertBack(*cit);
            }
            count++;
        }
        _annotazioni.clear();
        _annotazioni=temp;
        return trovato;
    }
    return trovato;
}

bool model_annotazione::muoviElementoSx(const lista<annotazione*>::constiterator ci)
{
    int i = _annotazioni.indexOfInt(_annotazioni.index(ci));
    bool trovato=false;
    if(i!=0)
    {
        int count=0;
        lista<annotazione*> temp;
        for(lista<annotazione*>::constiterator cit=_annotazioni.begin();cit!=_annotazioni.end();cit++)
        {
            if((count+1)==i)
            {
                temp.insertBack(*(++cit));
                temp.insertBack(*(--cit));
                cit++;
                trovato=true;
            }
            else
            {
                temp.insertBack(*cit);
            }
            count++;
        }
        _annotazioni.clear();
        _annotazioni=temp;
        return trovato;
    }
    return trovato;
}

bool model_annotazione::deviSalvare() const
{
    return _needToSave;
}

void model_annotazione::salvato()
{
    _needToSave = false;
}

QStringList model_annotazione::categorie()
{
    QStringList tipologieItems;
    tipologieItems.push_back("Nota");
    tipologieItems.push_back("Promemoria");
    tipologieItems.push_back("Ricorrenza");
    tipologieItems.push_back("Elenco");
    tipologieItems.push_back("Spesa");
    return tipologieItems;
}

