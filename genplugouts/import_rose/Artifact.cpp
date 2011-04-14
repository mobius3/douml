
#include <qdir.h>
#include <qfileinfo.h>
#include "CppSettings.h"
#include "JavaSettings.h"
#include "IdlSettings.h"
#include "UmlCom.h"
#include "UmlClass.h"
#include "UmlDeploymentView.h"
#include "UmlArtifact.h"
#include "Artifact.h"
#include "File.h"
#include "UmlPackage.h"

QAsciiDict<Artifact> Artifact::all;

Artifact * Artifact::find(const QCString & uid)
{
  return all[uid];
}

void Artifact::import_component_view(File & f)
{
  QCString s;
  
  f.read(s);
  
  for (;;) {
    switch (f.read(s)) {
    case ATOM:
      break;
    case ')':
      return;
    case -1:
      f.eof();
      throw 0;
    default:
      f.syntaxError(s, "an atom");
    }
    
    if (s == "visible_modules") {
      // module dependency
      f.skipNextForm();
      /*f.read("(");
      f.read("list");
      f.read("dependency_list");
      ...*/
    }
    else if (s == "physical_models") {
      f.read("(");
      f.read("list");
      f.read("unit_reference_list");
      import_components(f);
    }
    else if (s == "physical_presentations") {
      // diagrams
      f.skipNextForm();
    }
    else if (s == "file_name") {
      if (f.read(s) != STRING)
	f.syntaxError(s, "a filename");
      
      File f2(s, f.name());
      
      if (! f2.open(IO_ReadOnly))
	UmlCom::trace("<br>cannot open '" + s + "' referenced in "
		      + QCString(f.name()));
      else {     
        f2.read("(");
        f2.read("object");
        f2.read("Petal");
        f2.skipBlock();
      
        f2.read("(");
        f2.read("object");
        f2.read("SubSystem");
        import_component_view(f2);
      }

      f.skipBlock();
      return;
    }
    else
      f.skipNextForm();
  }
}

void Artifact::import_components(File & f)
{
  for (;;) {
    QCString s;
  
    switch (f.read(s)) {
    case '(':
      break;
    case ')':
      return;
    case -1:
      f.eof();
      throw 0;
    default:
      f.syntaxError(s);
    }

    f.read("object");
    
    switch (f.read(s)) {
    case ATOM:
      break;
    case -1:
      f.eof();
      throw 0;
    default:
      f.syntaxError(s, "an atom");
    }

    if (s == "module")
      import(f);
    else if (s == "SubSystem")
      import_component_view(f);
    else {
#ifdef DEBUGROSE
      UmlCom::trace("<br>import does not manage '" + s + "'");
#endif
      f.skipBlock();
    }
  }
}

void Artifact::import(File & f)
{
  QCString name;
  
  if (f.read(name) != STRING)
    f.syntaxError(name, "artifact's name");
  
  QCString s;
  
  f.read(s);
  f.read(s);
    
  QCString id;
  QCString ste;
  QCString doc;
  QDict<QCString> prop;
  Language lang = None;
  
  while (f.readDefinitionBeginning(s, id, ste, doc, prop) != ')') {
    // atom
    if (s == "language")
      lang = f.readLanguage();
  }

  // may already exist because of "visible_modules"
  Artifact * art = all[id];
  
  if (art == 0) {
    art = new Artifact;
    all.insert(strdup(id), art);
  }

  art->name = name;
  art->stereotype = ste;
  art->description = doc;
  art->language = lang;
  
  QCString * v;
  
  switch (lang) {
  case Cplusplus:
    if ((v = prop.find("Traversal/CodeFile")) != 0)
      art->cpp_path = *v;
    break;
  case AnsiCplusplus:
    if ((v = prop.find("Cplusplus/RevEngRootDirectory")) != 0)
      art->cpp_path = *v;
    break;
  case VCplusplus:
    break;
  case Java:
    if ((v = prop.find("Java/FileName")) != 0)
      art->java_path = *v;
    break;
  default:
    break;
  }
}

void Artifact::add(UmlPackage * pack, UmlClass * cl, QCString & art_path) {
  //pack, cl

  switch (language) {
  case Cplusplus:
    // cpp_path is the header pathname
    {
      int index = cpp_path.findRev('.');
      
      if (index != -1) {
	QCString s = cpp_path.left(index + 1);
	
	add_cpp(pack, cl,
		s + CppSettings::headerExtension(),
		s + CppSettings::sourceExtension());
      }
    }
    break;
  case AnsiCplusplus:
    // cl's header and body files may contains a path part
    {
      QDir d(cpp_path);
      QCString h = cl->file();
      QCString body = cl->bodyFile();
      
      add_cpp(pack, cl,
	      (h.isEmpty()) ? h : QCString(QDir::cleanDirPath(d.filePath(cl->file()))),
	      (body.isEmpty()) ? body : QCString(QDir::cleanDirPath(d.filePath(cl->bodyFile()))));
    }
    break;
  case Corba:
    // no info
    add_corba(pack, cl, name + "." + IdlSettings::sourceExtension());
    break;
  case Java:
    // java_path is the pathname
    {
      int index = java_path.findRev('.');
      
      if (index != -1)
	add_java(pack, cl, art_path,
		 java_path.left(index + 1) + JavaSettings::sourceExtension());
    }
    break;
  default:
    break;
  }
}

void Artifact::add_cpp(UmlPackage * pack, UmlClass * cl, QCString h, QCString src) {
  QCString basename;
  QCString hpath;
  QCString srcpath;
  
  if (! h.isEmpty()) {
    h = normalize(h, CppSettings::rootDir());
    
    QFileInfo fi(h);
    
    basename = fi.baseName();
    hpath = fi.dirPath();
  }

  if (! src.isEmpty()) {
    src = normalize(src, CppSettings::rootDir());
    
    QFileInfo fi(src);
    
    if (basename.isEmpty())
      basename = fi.baseName();
    srcpath = fi.dirPath();
  }

  if (basename.isEmpty())
    return;

  QList<UmlArtifact> artifacts;
  UmlArtifact * art;
  UmlPackage * p = 0;	// to avoid compiler warning
  
  pack->subArtifacts(artifacts, basename, name);
  
  // search for an existing artifact
  for (art = artifacts.first(); art != 0; art = artifacts.next()) {
    p = (UmlPackage *) art->parent()->parent();
    if ((hpath.isEmpty() || p->cppHDir().isEmpty() || (hpath == p->cppHDir())) &&
	(srcpath.isEmpty() || p->cppSrcDir().isEmpty() || (srcpath == p->cppSrcDir()))) {
      // p & art compatible
      break;
    }
  }

  if (art == 0) {
    // no compatible artifact
    QList<UmlDeploymentView> deplviews;
    UmlDeploymentView * deplview;
    UmlPackage * compatible = 0;
    
    pack->subDeplViews(deplviews, name);

    if (deplviews.isEmpty()) {
      if ((hpath.isEmpty() || pack->cppHDir().isEmpty() || (hpath == pack->cppHDir())) &&
	  (srcpath.isEmpty() || pack->cppSrcDir().isEmpty() || (srcpath == pack->cppSrcDir())))
	// pack compatible
	compatible = pack;
    }
    else {
      for (deplview = deplviews.first(); deplview != 0; deplview = deplviews.next()) {
	p = (UmlPackage *) deplview->parent();
	
	if ((hpath.isEmpty() || p->cppHDir().isEmpty() || (hpath == p->cppHDir())) &&
	    (srcpath.isEmpty() || p->cppSrcDir().isEmpty() || (srcpath == p->cppSrcDir()))) {
	  // p is compatible
	  compatible = p;
	  art = UmlArtifact::create(deplview, basename);
	  
	  if (art != 0) {
	    art->set_Stereotype("source");
	    break;
	  }
	}
      }
    }
    
    if (art == 0) {
      if (compatible == 0) {
	// must create a package to have the right paths
	p = pack->addPackage(pack->name());
	p->set_CppNamespace(pack->cppNamespace());
      }
      else
	p = compatible;
      
      // must create a artifact view
      deplview = pack->addDeplView(name, p);
      art = UmlArtifact::create(deplview, basename);
      art->set_Stereotype("source");
    }
  }

  // art is the artifact, p its associated package
    
  if (!hpath.isEmpty()) {
    if (p->cppHDir().isEmpty())
      p->set_CppHDir(hpath);
    if (art->cppHeader().isEmpty())
      art->set_CppHeader(CppSettings::headerContent());
  }

  if (!srcpath.isEmpty()) {
    if (p->cppSrcDir().isEmpty())
      p->set_CppSrcDir(srcpath);
    if (art->cppSource().isEmpty())
      art->set_CppSource(CppSettings::sourceContent());
  }
    
  art->addAssociatedClass(cl);
}

void Artifact::add_corba(UmlPackage * pack, UmlClass * cl, QCString src) {
  // src if the filename without path
  QFileInfo fi(src);
  QCString basename;
  
  basename = fi.baseName();
  
  QList<UmlArtifact> artifacts;
  UmlArtifact * art;
  UmlPackage * p;
  
  // search for an existing artifact
  pack->subArtifacts(artifacts, basename, name);
  if (! artifacts.isEmpty()) {
    p = pack;
    art = artifacts.first();
  }
  else {
    QList<UmlDeploymentView> deplviews;
    UmlDeploymentView * deplview;
    
    pack->subDeplViews(deplviews, name);
    art = 0;
    
    for (deplview = deplviews.first(); deplview != 0; deplview = deplviews.next()) {
      if ((art = UmlArtifact::create(deplview, basename)) != 0) {
	art->set_Stereotype("source");
	p = (UmlPackage *) deplview->parent();
	break;
      }
    }
      
    if (art == 0) {
      // must create a deployment view
      deplview = pack->addDeplView(name, pack);
      art = UmlArtifact::create(deplview, basename);
      art->set_Stereotype("source");
      p = pack;
    }
  }

  // art is the artifact, p its associated package
    
  if (art->idlSource().isEmpty())
      art->set_IdlSource(IdlSettings::sourceContent());
    
  art->addAssociatedClass(cl);
}

void Artifact::add_java(UmlPackage * pack, UmlClass * cl, QCString art_path, QCString src) {
  QCString basename;
  QCString srcpath;
  
  src = normalize(src, JavaSettings::rootDir());
    
  QFileInfo fi(src);
    
  basename = fi.baseName();
  srcpath = fi.dirPath();
  
  // manage java package using the artifact path
  int index;
  
  if ((index = art_path.find("::")) != -1) {
    // mandatory : Component View::
    art_path = art_path.mid(index + 2);
    
    if ((index = art_path.findRev("::")) != -1) {
      // pack::...::file, remove ::file
      art_path = art_path.left(index);
      
      while ((index = art_path.findRev("::")) != -1)
	// :: -> .
	art_path = art_path.left(index) + "." + art_path.mid(index + 2);
    }
  }

  QList<UmlArtifact> artifacts;
  UmlArtifact * art;
  UmlPackage * p = 0;	// to avoid compiler warning
  
  pack->subArtifacts(artifacts, basename, "java deployment view");
  
  // search for an existing artifact
  for (art = artifacts.first(); art != 0; art = artifacts.next()) {
    p = (UmlPackage *) art->parent()->parent();
    if ((srcpath.isEmpty() || p->javaDir().isEmpty() || (srcpath == p->javaDir())) &&
	(p->javaPackage() == art_path)) {
      // p & art compatible
      break;
    }
  }

  if (art == 0) {
    // no compatible artifact
    QList<UmlDeploymentView> deplviews;
    UmlDeploymentView * deplview;
    UmlPackage * compatible = 0;
    
    pack->subDeplViews(deplviews, "java deployment view");

    if (deplviews.isEmpty()) {
      if (srcpath.isEmpty() || pack->javaDir().isEmpty() || (srcpath == pack->javaDir()))
	// pack compatible
	compatible = pack;
    }
    else {
      for (deplview = deplviews.first(); deplview != 0; deplview = deplviews.next()) {
	p = (UmlPackage *) deplview->parent();
	
	if ((srcpath.isEmpty() || p->javaDir().isEmpty() || (srcpath == p->javaDir())) &&
	    (p->javaPackage() == art_path)) {
	  // p is compatible
	  compatible = p;
	  art = UmlArtifact::create(deplview, basename);
	  
	  if (art != 0) {
	    art->set_Stereotype("source");
	    break;
	  }
	}
      }
    }
    
    if (art == 0) {
      if (compatible == 0) {
	// must create a package to have the right paths
	p = pack->addPackage("java package");
      }
      else
	p = compatible;
      
      // must create a artifact view
      deplview = pack->addDeplView("java deployment view", p);
      art = UmlArtifact::create(deplview, basename);
      art->set_Stereotype("source");
    }
  }

  // art is the artifact, p its associated package

  if (!srcpath.isEmpty()) {
    if (p->javaDir().isEmpty())
      p->set_JavaDir(srcpath);
    if (art->javaSource().isEmpty())
      art->set_JavaSource(IdlSettings::sourceContent());
  }
  if (p->javaPackage() != art_path)
    p->set_JavaPackage(art_path);
    
  art->addAssociatedClass(cl);
}

QCString Artifact::normalize(QCString path, QCString root) {
  File f(path, "");	// normalize, replace $var
  
  path = QCString(f.name());
  
  int rl = root.length();
  
  if (rl != 0) {
    if (root[rl-1] != '/') {
      root += '/';
      rl += 1;
    }
    
    if (path.left(rl) == root)
      return path.mid(rl);
  }

  return path;
}

