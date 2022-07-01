mod expressions;

pub enum Statement {
    Expression(Expression),
    Block(Option<Vec<Statement>>),
    If {
        condition: Expression,
        body: Block,
    },
    Else {
        body: Block,
    },
    DetirminantRepeat {
        body: Block,
        number_of_repeats: Expression,
    },
    IndetirminantRepeat {
        body: Block,
        condition: Expression,
    },
    FunctionDef {
        name: Identifier,
        arguments: Option<Vec<Identifier>>,
    },
    VariableDeclaration {
        name: Identifier,
    },
    VariableDefinition {
        name: Identifier,
    },
}
