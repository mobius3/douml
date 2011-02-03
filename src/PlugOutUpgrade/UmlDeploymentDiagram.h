#ifndef UMLDEPLOYMENTDIAGRAM_H
#define UMLDEPLOYMENTDIAGRAM_H

#include "UmlBaseDeploymentDiagram.h"
//Added by qt3to4:
#include <Q3CString>

// This class manages 'deployment diagrams', notes that the class 'UmlDiagram'
// is a mother class of all the diagrams, allowing to generalize their
// management
// You can modify it as you want (except the constructor)

class UmlDeploymentDiagram : public UmlBaseDeploymentDiagram {
  public:
    UmlDeploymentDiagram(void * id, const Q3CString & n) 
      : UmlBaseDeploymentDiagram(id, n) {};
};

#endif
