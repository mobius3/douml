#ifndef LABELEDFUNCTIONS_H
#define LABELEDFUNCTIONS_H
#include <QMultiHash>
#include <QHash>
#include <QHashIterator>
// id 1 user 1
#define PROJECT_ID (1*128 + 1)

// id 2 user 0
#define FIRST_BASE_ID (2*128)

// id 2 user 1
#define FIRST_USER_ID (2*128 + 1)

// first 1000 items reserved for builtins
#define FIRST_ID 128000


template <class X> class Labeled;
template <class X> class IdIterator;
extern int user_id();

struct IntList {
  int * pint;
  const char * file;
  IntList * next;
};

// initialized to 0 before any execution associated
// to the initializations before 'main'
IntList * FirstCell;


static bool NeedRenumber;
static bool ImportLib;

void set_in_import(bool y, bool as_lib)
{
  NeedRenumber = y;
  ImportLib = as_lib;
}

bool in_import()
{
  return NeedRenumber;
}

bool in_lib_import()
{
  return ImportLib;
}

void memo_idmax_loc(int & idmaxref, const char * who)
{
  if (who != 0) {
    IntList * cell = new IntList;

    cell->pint = &idmaxref;
    cell->next = FirstCell;
    cell->file = who;
    FirstCell = cell;
  }
}
template <class X>
class IdDict {
#if 0
  // not managed by some C++ compiler
  template <class> friend class Labeled;
  template <class> friend class IdIterator;
  friend int place(IdDict & d, int id,Labeled*);
  friend int new_place(IdDict & d, int user_id, Labeled*);

  private:
#else
  public:
#endif
    QHash<int, Labeled<X>*> dict[2];
    QHash<int, char*> dictlib;
    //Q3IntDict<char> dictlib;
    int idmax;
    bool old_diagram;

  public:
    IdDict(const char * who)
    {
        idmax = 0; memo_idmax_loc(idmax, who);
    }
    IdDict(int sz, const char * who)
    {
        idmax = 0;  memo_idmax_loc(idmax, who);
    }

    Labeled<X>* operator[](int k) {
      int dictionaryVersion = (old_diagram || in_import()) ? 1 : 0;
        return dict[dictionaryVersion][k];
    }

    void remove(int id);

    void clear(bool olds);

    void update_idmax_for_root();

    void read_old_diagram(bool y);

    void memo_id_oid(int id, int oid);
};



template <class X>
int place(IdDict<X> & d, int id, Labeled<X>* x)
{
  const int uid = user_id();

  if (id != -1) {
    // id is relevant
    bool check = TRUE;

    if (id == 0) {
      // compute a new id
      if ((d.idmax < FIRST_ID) && (uid != 0))
    d.idmax = FIRST_ID - 128;
      id = (d.idmax += 128) | uid;
    }
    else if (d.old_diagram) {
      // place id unchanged among the old ones
      //d.dict[1].replace(id, x);
      if(d.dict[1].contains(id))
      {
          d.dict[1][id] = x;
      }
      else
      {
        d.dict[1].insert(1,x);
      }

      // id doesn't contains a user_id field
      // create new one for the current user_id
      if ((d.idmax < FIRST_ID) && (uid != 0))
    d.idmax = FIRST_ID - 128;
      id = (d.idmax += 128) | uid;
    }
    else if (NeedRenumber) {
      // place id unchanged among the old ones
        if(d.dict[1].contains(id))
        {
            d.dict[1][id] = x;
        }
        else
        {
          d.dict[1].insert(1,x);
        }

      int nid;

	  if (ImportLib && ((nid = (int) ((long) d.dictlib[id])) != 0)) {
	// an id was already attributed for it
	id = nid;

	if ((d.idmax < FIRST_ID) && (uid != 0))
	  d.idmax = FIRST_ID - 128;

	if ((((unsigned) (id & ~127)) > ((unsigned) d.idmax)) &&
		((id & 127) == uid))
	  d.idmax = id & ~127;
	  }
	  else if ((d.dict[0][id] != 0) || ((id & 127) != uid)) {
	// already used or for an other user, change id to a new one
	if ((id & 127) < 2) {
	  // import a plug out in a plug out !!!!!
	  // user_id part is unchanged
	  id = (id & 127) + FIRST_ID;

	  while (d.dict[0][id] != 0)
		id += 128;

	  check = FALSE;
	}
	else {
	  // create new id for the current user_id
	  if ((d.idmax < FIRST_ID) && (uid != 0))
		d.idmax = FIRST_ID - 128;
	  id = (d.idmax += 128) | uid;
	}
	  }
	  else
	// id unchanged for the current user
	check = FALSE;
	if ((((unsigned) (id & ~127)) > ((unsigned) d.idmax)) &&
		((id & 127) == uid))
	  d.idmax = id & ~127;
	}
	else {
	  // no renum, id unchanged
	  check = FALSE;
	  if ((((unsigned) (id & ~127)) > ((unsigned) d.idmax)) &&
	  ((id & 127) == uid))
	d.idmax = id & ~127;
	}

    if (check) {
      // useless except bug or project broken by user probably on merge
      while (d.dict[0][id] != 0)
    id = (d.idmax += 128) | uid;
    }
    d.dict[0].insert(id, x);

  }

  return id;
}
template <class X>
int new_place(IdDict<X> & d, int user_id, Labeled<X>* x)
{
  if (d.idmax == FIRST_ID)
    d.idmax = FIRST_BASE_ID;
  else
    d.idmax += 128;

  while (d.dict[0][d.idmax | user_id] != 0)
    // not possible except bug
    d.idmax += 128;

  d.dict[0].insert(d.idmax | user_id, x);
  return d.idmax | user_id;
}
template <class X>
struct NeedChange {
  IdDict<X> & dict;
  int & ident;
  Labeled<X>* elt;

  NeedChange(IdDict<X> & d, int & id, Labeled<X>* e) : dict(d), ident(id), elt(e) {}
};

#include <QList>
static QList<NeedChange*> MustBeRenumered;
template <class X>
void will_change_id(IdDict<X> & d, int & id, Labeled<X>* x)
{
  MustBeRenumered.append(new NeedChange<X>(d, id, x));
}

template <class X>
void IdDict<X>::remove(int id)
{
    QHash<int, Labeled<X>* >::iterator it = dict[0].find(id);
    dict[0].erase(it);
}
template <class X>
void IdDict<X>::clear(bool olds) {
  if (olds) {
dict[1].clear();
dictlib.clear();
  }
  else {
idmax = FIRST_ID;
dict[0].clear();
  }
}
template <class X>
void IdDict<X>::update_idmax_for_root()
{
  QHash<int, Labeled<X>*>::iterator it(dict);

  while (it != dict[0].end()) {
int id = it.key();

if ((((unsigned) (id & ~127)) > ((unsigned) idmax)) &&
    ((id & 127) == 0))
  idmax = id & ~127;

++it;
  }
}
template <class X>
void IdDict<X>::read_old_diagram(bool y)
{
    old_diagram = y;
}
template <class X>
void IdDict<X>::memo_id_oid(int id, int oid) {
  QHash<int, Labeled<X>*>::iterator it = dict[0].find(id);
  dict[0].erase(it);
  if(dictlib.contains(oid))
  {
    dictlib[oid] = (char *) id;
  }
  else
  {
    dictlib.insert(oid, (char *) id);
  }
}


#endif // LABELEDFUNCTIONS_H
