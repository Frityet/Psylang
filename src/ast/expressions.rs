mod operator;

pub enum Expression {
    Literal(Type),
    Identifier(String),
    BinaryOperator {
        operator: Operator,
        right_expression: Expression,
        left_expression: Expression,
    },
    UnaryOperator {
        operator: Operator,
        left_expression: Expression,
    },
    ProcCall {
        identifier: Identifier,
        arguments: Option<Vec<Expression>>,
    },
}
