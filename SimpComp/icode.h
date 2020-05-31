//
// Promezhutochnyy kod, ispol'zuyemyy dlya interpretatsii
//
#ifndef ICODE_H
#define ICODE_H

#include <list>
#include <string>
//... #include "nt.h"         // Name table
//... #include "lt.h"         // Label table

using std::list;
using std::string;

class Label;
class NameDef;

class ICommand {
public:
    enum {
        int_const = 0,
        double_const,
        string_const,
        assign,
        name,           // Znacheniye imeni
        name_lvalue,    // Ssylka na imya
        def_variable,   // Opredeleniye peremennoy
        def_array,      // Opredeleniye massiva
        array_element,  // Znacheniye elementa massiva
        array_lvalue,   // l-znacheniye elementa massiva
        plus,
        minus,
        mul,
        div,
        mod,
        uminus,
        cmp,
        go_to,
        if_goto,        // Uslovnyy perehod
        eq, ne, gt, ge, lt, le, // usloviya (condishini)
        input,
        output,
        nop             // Net operatsii
    };

    int label;          // Metka etoy komandy
    const Label* label_ptr; // Ukazatel' na tablitsu metok
    int type;           // Tip komandy
    int ext;            // Dopolnitel'naya informatsiya (bazovyy tip, usloviye dlya if_goto i t. D.

    NameDef* name_ptr;  // Ukazatel' na imya tablitsy
    int goto_label;     // label dlya goto
    const Label* goto_label_ptr; // Ukazatel' na tablitsu metok
    int int_value;      // Ispol'zuyetsya dlya konstant, no mozhet soderzhat'
                        //     Dopolnitlel'nuy infu
    double double_value;
    string string_value;

    ICommand():
        label(0),
        label_ptr(0),
        type(0),
        ext(0),
        name_ptr(0),
        goto_label(0),
        goto_label_ptr(0),
        int_value(0),
        double_value(0),
        string_value()
    {}

    void print() const;
};


class IProgram: public list<ICommand> {
public:
    IProgram::iterator addNewCommand();
    void print() const;
};

#endif
