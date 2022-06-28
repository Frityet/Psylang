pub enum Expression {
    Literal(Value),
    Identifier(String),
    BinaryOperator {
        operator: Token,
        right_expression: Expression,
        left_expression: Expression,
    },
    UnaryOperator {
        operator: Token,
        left_expression: Expression,
    },
    ProcCall {
        identifier: String,
        arguments: Vec<String>,
    },
}

pub enum Value {
    Number(f64),
    String(String),
}
