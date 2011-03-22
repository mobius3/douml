
#include "UmlUseCaseView.h"
#include "UmlItem.h"
#include "File.h"

#include "UmlCom.h"
UmlItem * UmlUseCaseView::item() {
  return this;
}

void UmlUseCaseView::readObject(File & f, QCString) {
  f.skipNextForm();
}

void UmlUseCaseView::import(UmlItem * parent, File & f)
{
  QCString s;

  if (f.read(s) != STRING)
    f.syntaxError(s, " use case view's name expected");

  QCString a;
  QCString id;
  QCString ste;
  QCString doc;
  QDict<QCString> prop;
  
  for (;;) {
    int k = f.readDefinitionBeginning(a, id, ste, doc, prop);

    if (k != ATOM)
      f.syntaxError(a);
    
    if (a == "file_name") {
      if (f.read(a) != STRING)
	f.syntaxError(a, "a filename");
      
      File f2(a, f.name());
      
      if (! f2.open(IO_ReadOnly))
	UmlCom::trace("<br>cannot open '" + a + "' referenced in "
		      + QCString(f.name()));
      else {     
        f2.read("(");
        f2.read("object");
        f2.read("Petal");
        f2.skipBlock();
      
        f2.read("(");
        f2.read("object");
        f2.read("Class_Category");
        import(parent, f2);
      }

      f.skipBlock();
      return;
    }
    else if (!id.isEmpty()) {
      f.unread(k, a);
      
      UmlUseCaseView * ucv;
      
      if (scanning) {
	ucv = UmlBaseUseCaseView::create(parent, s);
	
	if (ucv != 0)
	  newItem(ucv, id);
	
	if (!ste.isEmpty())
	  ucv->set_Stereotype(ste);
	
	if (!doc.isEmpty())
	  ucv->set_Description(doc);
	
	ucv->setProperties(prop);
      }
      else
	ucv = (UmlUseCaseView *) findItem(id, anUseCaseView);
      
      if (ucv == 0) {
	UmlCom::trace("<br>cannot create use case view named '" +
		      s + "' in '" + parent->fullName() + "'");
	throw 0;
      }
      
      ucv->Uc::import(f);
      return;
    }
    else
      f.skipNextForm();
  }

}

UmlUseCaseView::~UmlUseCaseView() {
}

