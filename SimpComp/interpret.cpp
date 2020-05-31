#ifdef MSWINDOWS
#    pragma warning(disable: 4996)
#endif


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "interpret.h"
#include "icode.h"

void ICodeInterpretator::initialize(const IProgram* icode) {
    assert(icode != 0);
    program = icode;
    currentCommand = icode->begin();
    stack.initialize();
}

void ICodeInterpretator::execute() throw (
   StackException, InterpretatorException, OutOfRangeException
) {
    while (currentCommand != program->end()) {
        executeCommand();
    }
}

void ICodeInterpretator::executeCommand() throw (
   StackException, InterpretatorException, OutOfRangeException
) {
    assert(currentCommand != program->end());
    int commandType = currentCommand->type;
    NameDef* name;

    switch (commandType) {

        case ICommand::assign: {
            Value value0, value1;
            stack.pop(value1);
            stack.pop(value0);
            if (
                (value0.value_type & 
                (VALUE_TYPE_VARIABLE | VALUE_TYPE_ARRAY)) == 0
            ) {
                throw InterpretatorException(
                    "Left side of assigment is not an l-value"
                );
            }
            name = value0.name_ptr;
            assert(name != 0);
            Value res;
            if (name->baseType == TYPE_INT) {
                value1.convertToInt(res);
                if (value0.value_type == VALUE_TYPE_VARIABLE) {
                    name->value = res;
                } else {
                    assert(value0.value_type == VALUE_TYPE_ARRAY);
                    int idx = value0.int_value;
                    if (idx < 0 || idx >= name->dimension)
                        throw OutOfRangeException("Array index out of bounds");
                    ((int*) name->array)[idx] = res.int_value;
                }
            } else if (name->baseType == TYPE_DOUBLE) {
                value1.convertToDouble(res);
                if (value0.value_type == VALUE_TYPE_VARIABLE) {
                    name->value = res;
                } else {
                    assert(value0.value_type == VALUE_TYPE_ARRAY);
                    int idx = value0.int_value;
                    if (idx < 0 || idx >= name->dimension)
                        throw OutOfRangeException("Array index out of bounds");
                    ((double*) name->array)[idx] = res.double_value;
                }
            } else if (name->baseType == TYPE_STRING) {
                value1.convertToString(res);
                if (value0.value_type == VALUE_TYPE_VARIABLE) {
                    name->value = res;
                } else {
                    assert(value0.value_type == VALUE_TYPE_ARRAY);
                    int idx = value0.int_value;
                    if (idx < 0 || idx >= name->dimension)
                        throw OutOfRangeException("Array index out of bounds");
                    ((string*) name->array)[idx] = res.string_value;
                }
            }
            break;
        }

        case ICommand::int_const: {
            Value value;
            value.value_type = VALUE_TYPE_INT;
            value.int_value = currentCommand->int_value;
            stack.push(value);
            break;
        }

        case ICommand::double_const: {
            Value value;
            value.value_type = VALUE_TYPE_DOUBLE;
            value.double_value = currentCommand->double_value;
            stack.push(value);
            break;
        }

        case ICommand::string_const: {
            Value value;
            value.value_type = VALUE_TYPE_STRING;
            value.string_value = currentCommand->string_value;
            stack.push(value);
            break;
        }

        case ICommand::name: {  // Value of name
            if (currentCommand->name_ptr->value.value_type == 0) {
                char line[128];
                sprintf(
                    line,
                    "Value of variable %s was not defined",
                    currentCommand->name_ptr->name.c_str()
                );
                throw InterpretatorException(line);
            }
            stack.push(currentCommand->name_ptr->value);
            break;
        }

        case ICommand::name_lvalue: {  // L-Value of name
            name = currentCommand->name_ptr;
            Value value;
            value.name_ptr = name;
            value.value_type = VALUE_TYPE_VARIABLE;
            if (name->modifiers == NameDef::NAME_ARRAY)
                value.value_type = VALUE_TYPE_ARRAY;
            stack.push(value);
            break;
        }

        case ICommand::def_variable: {
            // Nothing to do
            break;
        }

        case ICommand::def_array: {
            name = currentCommand->name_ptr;
            Value dim, s;
            stack.pop(dim);
            dim.convertToInt(s);
            int n = s.int_value;
            name->allocateArray(n);
            break;
        }

        case ICommand::array_element: {
            Value a, idx;
            stack.pop(idx);
            stack.pop(a);
            if (a.value_type != VALUE_TYPE_ARRAY)
                throw InterpretatorException("Illegal array expression");
            Value index;
            idx.convertToInt(index);
            int n = index.int_value;
            if (n < 0 || n >= a.name_ptr->dimension)
                throw OutOfRangeException("Array index out of bounds");
            void* array = a.name_ptr->array;
            Value res;
            if (a.name_ptr->baseType == TYPE_INT) {
                res.value_type = VALUE_TYPE_INT;
                res.int_value = ((int*) array)[n];
            } else if (a.name_ptr->baseType == TYPE_DOUBLE) {
                res.value_type = VALUE_TYPE_DOUBLE;
                res.double_value = ((double*) array)[n];
            } else if (a.name_ptr->baseType == TYPE_STRING) {
                res.value_type = VALUE_TYPE_STRING;
                res.string_value = ((string*) array)[n];
            }
            stack.push(res);
            break;
        }

        case ICommand::array_lvalue: {
            Value a, idx;
            stack.pop(idx);
            stack.pop(a);
            if (a.value_type != VALUE_TYPE_ARRAY)
                throw InterpretatorException("Illegal array expression");
            Value index;
            idx.convertToInt(index);
            int n = index.int_value;
            if (n < 0 || n >= a.name_ptr->dimension)
                throw OutOfRangeException("Array index out of bounds");
            Value res;
            res.value_type = VALUE_TYPE_ARRAY;
            res.name_ptr = a.name_ptr;
            res.int_value = n;
            stack.push(res);
            break;
        }

        case ICommand::plus: {
            Value v0, v1, res;
            stack.pop(v1);
            stack.pop(v0);
            Value::add(v0, v1, res);
            stack.push(res);
            break;
        }

        case ICommand::minus: {
            Value v0, v1, res;
            stack.pop(v1);
            stack.pop(v0);
            Value::sub(v0, v1, res);
            stack.push(res);
            break;
        }

        case ICommand::mul: {
            Value v0, v1, res;
            stack.pop(v1);
            stack.pop(v0);
            Value::mul(v0, v1, res);
            stack.push(res);
            break;
        }

        case ICommand::div: {
            Value v0, v1, res;
            stack.pop(v1);
            stack.pop(v0);
            Value::div(v0, v1, res);
            stack.push(res);
            break;
        }

        case ICommand::mod: {
            Value v0, v1, res;
            stack.pop(v1);
            stack.pop(v0);
            Value::mod(v0, v1, res);
            stack.push(res);
            break;
        }

        case ICommand::uminus: {
            Value v0, res;
            stack.pop(v0);
            Value::negate(v0, res);
            stack.push(res);
            break;
        }

        case ICommand::cmp: {
            Value v0, v1, res;
            stack.pop(v1);
            stack.pop(v0);
            Value::compare(v0, v1, res);
            stack.push(res);
            break;
        }

        case ICommand::output: {
            Value v;
            stack.pop(v);
            v.print();
            break;
        }

        case ICommand::input: {
            Value v;
            stack.pop(v);
            v.scanf();
            break;
        }

        case ICommand::go_to: {
            const Label* label = currentCommand->goto_label_ptr;
            assert(label->number != 0);
            //... if (label->location == 0)
            //...     throw InterpretatorException("Undefined label");
            currentCommand = label->location;
            return;
        }

        case ICommand::if_goto: {
            Value v;
            stack.pop(v);
            assert(v.value_type == VALUE_TYPE_INT);
            int res = v.int_value;
            int cond = currentCommand->ext;
            if (
                (cond == ICommand::eq && res == 0) ||
                (cond == ICommand::ne && res != 0) ||
                (cond == ICommand::gt && res > 0) ||
                (cond == ICommand::lt && res < 0) ||
                (cond == ICommand::ge && res >= 0) ||
                (cond == ICommand::le && res <= 0)
            ) {
                const Label* label = currentCommand->goto_label_ptr;
                assert(label->number != 0);
                //... if (label->location == 0)
                //...     throw InterpretatorException("Undefined label");
                currentCommand = label->location;
                return;
            }
            break;
        }
    }
    ++currentCommand;
}

void ICodeInterpretator::printStackTop() const {
    if (stack.size() <= 0) {
        printf("Stack empty"); 
        return;
    }
    stack.top().print();
}
