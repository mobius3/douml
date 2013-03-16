#include "operationfuncs.h"
#include "BrowserOperation.h"
#include "BrowserClass.h"
#include "OperationData.h"
#include "DialogUtil.h"
#include "GenerationSettings.h"
namespace OperationFuncs
{
void add_param(BrowserOperation* oper, QString & form, int rank, QString s)
{
    int index = param_begin(form, rank);

    if (index == -1)
        return;

    if (rank == 0) {
        // first param, index point to '}' ending ${(}
        OperationData* data = static_cast<OperationData*>(oper->get_data());
        if (data->get_n_params() != 1)
            s += ", ";

        index += 1;
    }
    else
        // index point to ',' or '$' starting ${)}
        s = ", " + s;

    form.insert(index, s);
}


void replace_param( QString & form, int rank, QString s)
{
    int index_start = param_begin(form, rank);

    if (index_start == -1)
        return;

    const char * p = form;

    switch (p[index_start]) {
    case '$':
        // '$' starting ${)}, param not yet present, not first one,
        // not possible except if user remove it in language form
        form.insert(index_start, ", " + s);
        return;

    case ',':
        index_start += (p[index_start + 1] == ' ') ? 2 : 1;
        break;

    default:
        // first param, index point to '}' ending ${(}
        index_start += 1;
    }

    int index_sup = supOf(p, index_start);

    switch (p[index_sup]) {
    case ',':
    case '$': // ${)}
        break;

    default:
        // error
        return;
    }

    form.replace(index_start, index_sup - index_start, s);
}

void recompute_param(BrowserOperation* oper, int rank, bool recompute)
{
    char t[16];
    char p[16];
    char v[16];


    sprintf(t, "${t%d}", rank);
    sprintf(p, "${p%d}", rank);
    sprintf(v, "${v%d}", rank);

    QStringList list;
    BrowserNodeList nodes;

    nodes.clear();
    list.clear();
    BrowserClass::instances(nodes);
    nodes.full_names(list);

    OperationData* data = static_cast<OperationData*>(oper->get_data());
    AType theType = data->get_param_type(rank);
    UmlParamDirection dir = data->get_param_dir(rank);

        QString theo =
            GenerationSettings::cpp(theType, dir, rank);

        QString cppDecl = data->get_cppdecl();

        if ((cppDecl.find(t) == -1) && (cppDecl.find(p) == -1))
            add_param(oper, cppDecl, rank, theo + QString(v));
        else if (recompute)
            replace_param(cppDecl, rank, theo + QString(v));
        data->set_cppdecl(cppDecl);

        QString cppDef =  data->get_cppdef();

        if ((cppDef.find(t) == -1) && (cppDef.find(p) == -1))
            add_param(oper, cppDef, rank, theo);
        else if (recompute)
            replace_param(cppDef, rank, theo);
        data->set_cppdef(cppDef);


        QString javaDef =  data->get_javadef();
        if ((javaDef.find(t) == -1) && (javaDef.find(p) == -1))
        {
            add_param(oper, javaDef, rank, QString(t) + QString(" ") + QString(p));
            data->set_javadef(javaDef);
        }
        QString phpDef =  data->get_phpdef();

        if (phpDef.find(p) == -1)
        {
            add_param(oper, phpDef, rank, QString(p) + QString(v));
            data->set_phpdef(phpDef);
        }
        QString pythonDef =  data->get_pythondef();

        if (pythonDef.find(p) == -1) {
            add_param(oper, pythonDef, rank, QString(p) + QString(v));
            data->set_pythondef(pythonDef);
        }
        QString idlDecl =  data->get_idldecl();
        if ((idlDecl.find(t) == -1) && (idlDecl.find(p) == -1)) {
            char d[16];

            sprintf(d, "${d%d}", rank);
            add_param(oper, idlDecl, rank, QString(d) + QString(" ") + QString(t) + QString(" ") + QString(p));
            data->set_idldecl(idlDecl);
        }
}


// automatic add / remove param when only one language is set

int bypass_string(const char * s, int index)
{
    // index is just after the "
    for (;;) {
        switch (s[index]) {
        case '"':
            return index + 1;

        case '\\':
            if (s[index + 1] == 0)
                return index + 1;

            index += 2;
            break;

        case 0:
            return index;

        default:
            index += 1;
        }
    }
}

int bypass_char(const char * s, int index)
{
    // index is just after the '
    for (;;) {
        switch (s[index]) {
        case '\'':
            return index + 1;

        case '\\':
            if (s[index + 1] == 0)
                return index + 1;

            index += 2;
            break;

        case 0:
            return index;

        default:
            index += 1;
        }
    }
}

int bypass_cpp_comment(const char * s, int index)
{
    // index is just after the //
    const char * p = strchr(s, '\n');

    return (p == 0)
           ? index + strlen(s + index)
           : p - s;
}

int bypass_c_comment(const char * s, int index)
{
    // index is just after the /*
    for (;;) {
        switch (s[index]) {
        case '*':
            if (s[index + 1] == '/')
                return index + 2;

            break;

        case 0:
            return index;
        }

        index += 1;
    }
}

int supOf(const char * s, int index)
{
    // return the index after of the parameter form
    // s at least contains ${)}
    int ouvr = 0;

    for (;;) {
        switch (s[index]) {
        case '$':
            if (strncmp(s + index, "${)}", 4) == 0)
                return index;

            index += 1;
            break;

        case '(':
        case '[':
        case '{':
            ouvr += 1;
            index += 1;
            break;

        case ')':
        case ']':
        case '}':
            ouvr -= 1;
            index += 1;
            break;

        case '"':
            index = bypass_string(s, index + 1);
            break;

        case '\'':
            index = bypass_char(s, index + 1);
            break;

        case '/':
            switch (s[index + 1]) {
            case '/':
                index = bypass_cpp_comment(s, index + 2);
                break;

            case '*':
                index = bypass_c_comment(s, index + 2);
                break;

            default:
                index += 1;
            }

            break;

        case 0:
            // in case ${)} is in a comment etc ...
            return index;

        case ',':
            if (ouvr == 0)
                return index;

            // no break
        default:
            index += 1;
        }
    }
}

int param_begin(QString s, int rank)
{
    // return position of ',' or '}' (inside ${(}),
    // or '$' (inside ${)}) or -1 on error
    const char * p = s;
    const char * b = strstr(p, "${(}");

    if ((b == 0) || (strstr(b + 4, "${)}") == 0))
        return -1;

    int index  = (b - p) + 3;	// '}'

    while (rank != 0) {
        int end = supOf(p, index + 1);

        switch (p[end]) {
        case ',':
            index = end;
            break;

        case '$': // ${)}
            return (rank == 1) ? end : -1;

        default:
            return -1;
        }

        rank -= 1;
    }

    return index;
}

void renumber(QString & form, int rank,
                     int delta, bool equal )
{
    int index = form.find("${(}");

    if (index == -1)
        return;

    index += 4;

    int index_sup = form.find("${)}", index);

    while (index < index_sup) {
        index = form.find("${", index);

        if (index == -1)
            break;

        int index2 = form.find('}', index + 3);
        QString n = form.mid(index + 3, index2 - index - 3);
        bool ok = FALSE;
        int r = n.toInt(&ok);

        if (!ok || ((equal) ? (r != rank) : (r < rank)))
            index = index2 + 1;
        else {
            char nn[16];

            sprintf(nn, "%d", r + delta);
            form.replace(index + 3, n.length(), nn);
            index = form.find('}', index + 3) + 1;
        }
    }
}



void delete_param(int rank, OperationData* data)
{
    // remove and renumber
    data->set_cppdecl(delete_param(rank, data->get_cppdecl()));
    data->set_cppdef(delete_param(rank, data->get_cppdef()));
    data->set_javadef(delete_param(rank, data->get_javadef()));
    data->set_phpdef(delete_param(rank, data->get_phpdef()));
    data->set_pythondef(delete_param(rank, data->get_pythondef()));
    data->set_idldecl(delete_param(rank, data->get_idldecl()));
}

QString delete_param(int rank, QString text)
{
    // remove
    QString form = text;
    int index = param_begin(form, rank);

    if (index == -1)
        return "";

    const char * p = form;
    int index_sup;

    switch (p[index]) {
    case '$':
        // '$' starting ${)}, param not yet present, not first one,
        // not possible except if user remove it in language form
        return "";

    case ',':
        index_sup = supOf(p, index + 1);
        break;

    default: // first param, index point to '}' ending ${(}
        index += 1;
        index_sup = supOf(p, index);
        break;
    }

    QString result;

    switch (p[index_sup]) {
    case ',':
        if (p[index] == ',') {
            if (p[index + 1] == ' ')
                result = form.mid(index + 2, index_sup - index - 2);
            else
                result = form.mid(index + 1, index_sup - index - 1);
        }
        else {
            // first param
            result = form.mid(index, index_sup - index);
            index_sup += (p[index_sup + 1] == ' ') ? 2 : 1;
        }

        break;

    case '$': // ${)}
        if (p[index] == ',') {
            if (p[index + 1] == ' ')
                result = form.mid(index + 2, index_sup - index - 2);
            else
                result = form.mid(index + 1, index_sup - index - 1);
        }
        else {
            // alone param
            result = form.mid(index, index_sup - index);
        }

        break;

    default:
        // error
        return "";
    }

    form.remove(index, index_sup - index);

    // renumber
    renumber(form, rank, -1);
    return form;
}


QString extract_specifier(int position,  QString s)
{
    // s at least contains ${)}
    QRegExp rxStart(QRegExp::escape("${(}"));
    QRegExp rxPrev(QRegExp::escape("${v" + QString::number(position - 1) +  "}"));
    int startIndex;
    if(position == 0)
        startIndex = rxStart.indexIn(s) + 4 ;
    else
        startIndex = rxPrev.indexIn(s) + 4 + QString::number(position).length();
    if(s.at(startIndex) == ",")
        startIndex++;

    QRegExp rxType(QRegExp::escape("${t" + QString::number(position)));
    int tIndex = rxType.indexIn(s);
    int length = tIndex -(startIndex);
    QString specifier;
    if(length > 0)
        specifier = s.mid(startIndex, length);
    return specifier;
}

QString extract_pointer(int position,  QString s)
{
    // s at least contains ${)}
    QRegExp rxStart(QRegExp::escape("${t" + QString::number(position) +  "}"));
    int startIndex;
    startIndex = rxStart.indexIn(s) + 4 + QString::number(position).length();

    QRegExp rxEnd(QRegExp::escape("${p" + QString::number(position)+  "}"));
    int tIndex = rxEnd.indexIn(s);
    int length = tIndex -(startIndex);
    QString ptrType;
    if(length > 0)
        ptrType = s.mid(startIndex, length);
    return ptrType;
}

QString set_specifier(int position,  QString s, QString newValue)
{
    // s at least contains ${)}
    QRegExp rxStart(QRegExp::escape("${(}"));
    QRegExp rxPrev(QRegExp::escape("${v" + QString::number(position - 1) +  "}"));
    int startIndex;
    if(position == 0)
        startIndex = rxStart.indexIn(s) + 4 ;
    else
        startIndex = rxPrev.indexIn(s) + 4 + QString::number(position).length();

    QRegExp rxType(QRegExp::escape("${t" + QString::number(position)));
    int tIndex = rxType.indexIn(s);
    int length = tIndex -(startIndex + 1);
    if(length < 0)
        length = 0;
    //s = s.replace(startIndex,length,newValue);
    s = s.left(startIndex) + newValue + s.right(s.length() - tIndex);
    return s;
}

QString set_pointer(int position,  QString s, QString newValue)
{
    // s at least contains ${)}
    QRegExp rxStart(QRegExp::escape("${t" + QString::number(position) +  "}"));
    int startIndex;
    startIndex = rxStart.indexIn(s) + 4 + QString::number(position).length();

    QRegExp rxEnd(QRegExp::escape("${p" + QString::number(position)+  "}"));
    int tIndex = rxEnd.indexIn(s);
    int length = tIndex -(startIndex + 1);
    if(length < 0)
        length = 0;
    //s = s.replace(startIndex,length,newValue);
    s = s.left(startIndex) + newValue + s.right(s.length() - tIndex);
    return s;
}


//void move_param(int old_rank, int new_rank)
//{
//    switch (unique) {
//    case CppView:
//        move_param(old_rank, new_rank, cppTab->ui->edCppDeclProto);
//        move_param(old_rank, new_rank, cppTab->ui->edCppDefProto);
//        break;

//    case JavaView:
//        move_param(old_rank, new_rank, edjavadef);
//        break;

//    case PhpView:
//        move_param(old_rank, new_rank, edphpdef);
//        break;

//    case PythonView:
//        move_param(old_rank, new_rank, edpythondef);
//        break;

//    case IdlView:
//        move_param(old_rank, new_rank, edidldecl);
//        break;

//    default:
//        break;
//    }
//}

//void move_param(int old_rank, int new_rank,
//                                 QString proto)
//{
//    QString s = delete_param(old_rank, ed);

//    if (s.isEmpty())
//        return;

//    s = "${(}" + s + "${)}";
//    renumber(s, old_rank, new_rank - old_rank, TRUE);

//    QString form = ed->text();

//    renumber(form, new_rank, 1);
//    add_param(form, new_rank, s.mid(4, s.length() - 8));

//    ed->setText(form);
//}

}
