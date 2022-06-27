pub enum Expr {
    Literal(Value),
    Identifier(String),
    BinaryOperator {
        operator: Token,
        right_side: Expr,
        left_side: Expr,
    },
    UnaryOperator {
        operator: Token,
        left_side: Expr,
    },
    ProcCall {
        identifier: String,
        arguments: Vec<String>,
    },
}

pub enum Value {
    Float(f64),
    String(String),
}
