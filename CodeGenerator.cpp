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
    cout<<"enum "<<enumStatement->name.lexeme<<"{";
    int fieldsSize = enumStatement->fields.size();
    for(int i = 0 ; i < fieldsSize ; i++) {
        Token token = enumStatement->fields[i];
        cout<<token.lexeme;
        if(i != fieldsSize - 1) {
            cout<<",";
        }
    }
    cout<<"};\n"<<endl;
}

void CodeGenerator::visit(VarStatement *varStatement) {
    if(varStatement->isPointer) {
        cout<<varStatement->type.lexeme<<"* "<<varStatement->name.lexeme;
    }else{
        cout<<varStatement->type.lexeme<<" "<<varStatement->name.lexeme;
    }

    if(varStatement->isInitialized) {
        cout<<"=";
        varStatement->value->accept(this);
    }
    cout<<";\n";
}

void CodeGenerator::visit(StructStatement *structStatement) {
    cout<<"struct "<< structStatement->name.lexeme<<"{\n";
    for(auto field : structStatement->fields) {
        field->accept(this);
    }
    cout<<"};\n";
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

void CodeGenerator::visit(ExpressionStatement *expressionStatement) {
    expressionStatement->expression->accept(this);
}

void CodeGenerator::visit(AssignExpression *assign) {
    ExpressionVisitor::visit(assign);
}

void CodeGenerator::visit(LiteralExpression *literal) {
    cout<<literal->value;
}

