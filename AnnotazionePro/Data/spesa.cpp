#include "spesa.h"

spesa::spesa() : elenco(), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione) : annotazione(titolo),elenco(titolo,descrizione), _spesa()
{

}

spesa::spesa(QString titolo, QString descrizione, const lista<type_spesa*> &spesa) : annotazione(titolo),elenco(titolo,descrizione),_spesa(spesa)
{

}

spesa::spesa(QDomElement spesa):
    annotazione(spesa.childNodes().at(0).toElement().childNodes().at(0).toElement()),
    elenco(spesa.childNodes().at(0).toElement())
{
    int count=1;
    type_spesa *ts;
    while(spesa.childNodes().at(count).isElement())
    {
        ts=new type_spesa();
        ts->setValue(spesa.childNodes().at(count).toElement().attribute("Value"));
        ts->setIsDone(spesa.childNodes().at(count).toElement().attribute("IsDone")=="0" ? 0:1);
        ts->setCost(spesa.childNodes().at(count).toElement().attribute("Cost").toDouble());
        _spesa.insertBack(ts);
        count++;
    }
}

spesa::spesa(const spesa &spes):annotazione(spes.getTitolo()),elenco(spes.getTitolo(),spes.getDescrizione()),_spesa(spes.getSpesa())
{

}

spesa::~spesa()
{
    _spesa.clear();
}

bool spesa::operator==(const spesa &s) const {
    return s.getSpesa()==_spesa && s.getDescrizione()==getDescrizione()&&annotazione::operator==(s);
}

bool spesa::operator!=(const spesa &s) const
{
    return !(this==&s);
}

spesa &spesa::operator=(const spesa &s) {
    if(this!=&s)
    {
        _spesa=s.getSpesa();
        setDescrizione(s.getDescrizione());
        annotazione::operator=(s);
    }
    return *this;
}

QDomElement spesa::XmlSerialize(QDomDocument doc) const
{
    QDomElement spesa = doc.createElement("Spesa");
    spesa.appendChild(elenco::XmlSerialize(doc));
    for( lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        QDomElement elemento= doc.createElement("Elemento");
        elemento.setAttribute("Value",(*ci)->getValue());
        elemento.setAttribute("IsDone",(*ci)->getIsDone());
        elemento.setAttribute("Cost",(*ci)->getCost());
        spesa.appendChild(elemento);
    }
    return spesa;
}

QString spesa::ToString() const
{
    QString testo;
    testo+=annotazione::ToString();
    testo+="Descrizione: "+getDescrizione()+"; ";
    testo+="Spesa :";
    for( lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        testo+="\n- Valore: "+(*ci)->getValue()+"; Costo: "+QString::number((*ci)->getCost())+"; Stato: "+((*ci)->getIsDone() ? "Non Completato" : "Completato" )+";";
    }
    return testo;
}

double spesa::CostoComplessivo() const
{

    double total=0;
    for(lista<type_spesa*>::constiterator ci = _spesa.begin(); ci!=_spesa.end();ci++)
    {
        total+= (*ci)->getCost();
    }
    return total;
}

lista<type_spesa *> spesa::getSpesa() const
{
    return _spesa;
}

void spesa::setSpesa(const lista<type_spesa *> _newSpesa)
{
    _spesa.clear();
    for( lista<type_spesa*>::constiterator ci = _newSpesa.begin(); ci!=_newSpesa.end();ci++)
    {
        _spesa.insertBack(*ci);
    }
}




