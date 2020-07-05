#include "include/CodeGenerator.h"

using namespace std;

CodeGenerator::CodeGenerator(ErrorHandler &errorHandler)
        : errorHandler(errorHandler){
}

void CodeGenerator::generateCode(const std::vector<Statement*>& statements) {
    for(auto statement : statements) {
        statement->accept(this);
    }
}

void CodeGenerator::visit(EnumStatement* enumStatement) {
    cout<<"typedef enum {";
    int fieldsSize = enumStatement->fields.size();
    for(int i = 0 ; i < fieldsSize ; i++) {
        Token token = enumStatement->fields[i];
        cout<<token.lexeme;
        if(i != fieldsSize - 1) {
            cout<<",";
        }
    }
    cout<<"}"<<enumStatement->name.lexeme<<";"<<endl;
}

void CodeGenerator::visit(VarStatement *varStatement) {
    cout<<varStatement->type.lexeme<<" ";
    MemoryType type = varStatement->memoryType;
    generateMemoryType(type);
    cout<<varStatement->name.lexeme;
    if(varStatement->isInitialized) {
        cout<<"=";
        varStatement->value->accept(this);
    }
    cout<<";\n";
}

void CodeGenerator::visit(StructStatement *structStatement) {
    cout<<"typedef struct{\n";
    for(Parameter field : structStatement->fields) {
        cout<<field.type.lexeme;
        if(field.isPointer) {
            cout << "*";
        }
        cout<<" "<<field.name.lexeme<<";\n";
    }
    cout<<"}"<<structStatement->name.lexeme<<";\n";
    //TODO: Generate Struct new function
    //TODO: Generate Struct Free Function
}

void CodeGenerator::visit(BlockStatement *blockStatement) {
    for(auto statement : blockStatement->statements) {
        statement->accept(this);
    }
}

void CodeGenerator::visit(FunctionStatement *functionStatement) {
    cout<<functionStatement->returnType.lexeme<<" " <<functionStatement->name.lexeme<<" (";
    int paramSize = functionStatement->parameters.size();
    int paramCounter = 0;
    for(auto param : functionStatement->parameters) {
        paramCounter++;
        if(param.isPointer) {
            cout<<param.type.lexeme<<" *"<<param.name.lexeme;
        }else {
            cout<<param.type.lexeme<<" "<<param.name.lexeme;
        }
        if(paramSize != paramCounter) {
            cout<<", ";
        }
    }
    cout<<") {\n";

    for(auto statement : functionStatement->body) {
        statement->accept(this);
    }

    if(functionStatement->returnType.lexeme != "void") {
        cout<<"return ";
        functionStatement->returnValue->accept(this);
        cout<<";\n";
    }
    cout<<"}\n";
}

void CodeGenerator::visit(IfStatement *ifStatement) {
    cout<<"if(";
    ifStatement->condition->accept(this);
    cout<<"){\n";
    for(auto statement : ifStatement->body) {
        statement->accept(this);
    }
    cout<<"}\n";
}

void CodeGenerator::visit(WhileStatement *whileStatement) {
    cout<<"while(";
    whileStatement->condition->accept(this);
    cout<<"){\n";
    for(auto statement : whileStatement->body) {
        statement->accept(this);
    }
    cout<<"}\n";
}

void CodeGenerator::visit(ArrayStatement *arrayStatement) {
    cout<<arrayStatement->type.lexeme<<" ";
    MemoryType type = arrayStatement->memoryType;
    generateMemoryType(type);
    cout<<arrayStatement->name.lexeme;
    cout<<"[";
    arrayStatement->size->accept(this);
    cout<<"]";
    if(arrayStatement->isInitialized) {
        cout<<"=";
        arrayStatement->value->accept(this);
    }
    cout<<";\n";
}

void CodeGenerator::visit(AssignExpression *assign) {
    generateMemoryType(assign->type);
    assign->name->accept(this);
    cout<<"=";
    assign->value->accept(this);
    cout<<";\n";
}

void CodeGenerator::visit(ExpressionStatement *expressionStatement) {
    expressionStatement->expression->accept(this);
}

void CodeGenerator::visit(LiteralExpression *literal) {
    cout<<literal->value;
}

void CodeGenerator::visit(CallExpression *callExpression) {
    callExpression->callee->accept(this);
    cout<<"(";
    int argsSize = callExpression->arguments.size();
    int argsCounter = 1;
    for(auto arg : callExpression->arguments) {
        arg->accept(this);
        if(argsCounter != argsSize) {
            cout<<",";
        }
        argsCounter++;
    }
    cout<<");\n";
}

void CodeGenerator::visit(VariableExpression *varExpression) {
    cout<<varExpression->name.lexeme;
}

void CodeGenerator::visit(GroupExpression *groupExpression) {
    cout<<"(";
    groupExpression->expression->accept(this);
    cout<<")";
}

void CodeGenerator::visit(LogicalExpression *groupExpression) {
    groupExpression->left->accept(this);
    Token opt = groupExpression->opt;
    switch(opt.tokenType) {
        case OR : {
            cout<<" || ";
            break;
        }
        case XOR: {
            cout<<" ^ ";
            break;
        }
        case AND : {
            cout<<" && ";
            break;
        }
    }
    groupExpression->right->accept(this);
}

void CodeGenerator::visit(GetExpression *getExpression) {
    getExpression->object->accept(this);
    cout<<"."<<getExpression->name.lexeme;
}

void CodeGenerator::visit(TernaryExpression *ternaryExpression) {
    ternaryExpression->condition->accept(this);
    cout<<"?";
    ternaryExpression->truthExpr->accept(this);
    cout<<":";
    ternaryExpression->falseExpr->accept(this);
}

void CodeGenerator::visit(BinaryExpression *binaryExpression) {
    TokenType optType = binaryExpression->opt.tokenType;
    binaryExpression->left->accept(this);
    switch (optType) {
        case EQUAL_EQUAL: {
            cout<<"==";
            break;
        }
        case BANG_EQUAL: {
            cout<<"!=";
            break;
        }
        case GREATER: {
            cout<<">";
            break;
        }
        case GREATER_EQUAL: {
            cout<<">=";
            break;
        }
        case LESS: {
            cout<<"<";
            break;
        }
        case LESS_EQUAL: {
            cout<<"<=";
            break;
        }
        case PLUS: {
            cout<<"+";
            break;
        }
        case MINUS: {
            cout<<"-";
            break;
        }
        case STAR: {
            cout<<"*";
            break;
        }
        case SLASH: {
            cout<<"/";
            break;
        }
    }
    binaryExpression->right->accept(this);
}

void CodeGenerator::visit(UnaryExpression *unaryExpression) {
    TokenType optType = unaryExpression->opt.tokenType;
    switch(optType) {
        case BANG : {
            cout<<"!";
            break;
        }
        case MINUS : {
            cout<<"-";
            break;
        }
        case PLUS_PLUS : {
            cout<<"++";
            break;
        }
        case MINUS_MINUS: {
            cout<<"--";
            break;
        }
    }
    unaryExpression->expression->accept(this);
}

void CodeGenerator::visit(ArrayExpression *arrayExpression) {
    arrayExpression->variable->accept(this);
    cout<<"[";
    arrayExpression->index->accept(this);
    cout<<"]";
}


void CodeGenerator::visit(ArrayValuesExpression *arrayExpression) {
    cout<<"{";
    int valuesSize = arrayExpression->values.size();
    int valuesCounter = 1;
    for(auto val : arrayExpression->values) {
        val->accept(this);
        if(valuesCounter != valuesSize) {
            cout<<",";
        }
        valuesCounter++;
    }
    cout<<"}";
}

void CodeGenerator::generateMemoryType(MemoryType type) {
    if(type == SINGLE_POINTER) {
        cout<<"*";
    }
    else if(type == DOUBLE_POINTER) {
        cout<<"**";
    }
    else if(type == ADDRESS_POINTER) {
        cout<<"&";
    }
}





