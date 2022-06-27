#[allow(non_camel_case_types)]
#[derive(Debug, Copy, Clone)]

enum TokenType {
    OPEN_CURLY,
    CLOSE_CURLY,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_BRACE,
    CLOSE_BRACE,
    ASSIGN,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MOD,
    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_EQUAL,
    LESS_THAN_EQUAL,
    NOT,
    AND,
    OR,
    IF,
    ELSE,
    REPEAT,
    TIMES,
    UNTIL,
    FOR,
    IN,
    PROCEDURE,
    RETURN,
    STRING,
    NUMBER,
    IDENTIFIER,
    EOF,
}

#[allow(dead_code)]
#[derive(Debug)]
pub struct Token {
    token_type: TokenType,
    literal: String,
    line: i32,
}
pub struct Lexer {
    src: String,
    tokens: Vec<Token>,
    start: i32,
    line: i32,
    current: i32,
}

impl Lexer {
    pub fn new(src: String) -> Self {
        Self {
            src,
            tokens: Vec::<Token>::new(),
            start: 1,
            line: 0,
            current: 0,
        }
    }

    pub fn lex(&mut self) -> &Vec<Token> {
        while !&self.is_at_end() {
            self.start = self.current;
            let current_char = self.consume();

            match current_char {
                '(' => self.add_token(TokenType::OPEN_PAREN),
                ')' => self.add_token(TokenType::CLOSE_PAREN),
                '{' => self.add_token(TokenType::OPEN_CURLY),
                '}' => self.add_token(TokenType::CLOSE_CURLY),
                '[' => self.add_token(TokenType::OPEN_BRACE),
                ']' => self.add_token(TokenType::CLOSE_BRACE),
                '+' => self.add_token(TokenType::ADD),
                '-' => self.add_token(TokenType::SUBTRACT),
                '*' => self.add_token(TokenType::MULTIPLY),
                '/' => {
                    if self.is_match_with_next('/') {
                        while self.peek() != '\n' && !self.is_at_end() {
                            self.consume();
                        }
                    } else {
                        self.add_token(TokenType::DIVIDE)
                    }
                }
                '>' => {
                    if self.is_match_with_next('=') {
                        self.add_token(TokenType::GREATER_THAN_EQUAL)
                    } else {
                        self.add_token(TokenType::GREATER_THAN)
                    }
                }
                '<' => {
                    if self.is_match_with_next('=') {
                        self.add_token(TokenType::LESS_THAN_EQUAL)
                    } else if self.is_match_with_next('-') {
                        self.add_token(TokenType::ASSIGN)
                    } else {
                        self.add_token(TokenType::LESS_THAN);
                    }
                }
                '!' => {
                    if self.is_match_with_next('=') {
                        self.add_token(TokenType::NOT_EQUAL)
                    } else {
                        self.add_token(TokenType::NOT)
                    }
                }
                '=' => self.add_token(TokenType::EQUAL),
                '\n' => self.line += 1,
                '\t' | '\r' | ' ' => {}
                '"' => self.lex_string(),
                _ if current_char.is_numeric() => self.lex_number(),
                _ if current_char.is_alphabetic() => self.lex_identifier(),
                _ => panic!("Unrecognized symbol at line: {}", self.line),
            }
        }

        self.tokens.push(Token {
            token_type: TokenType::EOF,
            literal: "".to_string(),
            line: self.line,
        });

        &self.tokens
    }

    fn is_at_end(&self) -> bool {
        self.current >= (self.src.len()) as i32
    }

    fn consume(&mut self) -> char {
        self.current += 1;
        self.src.chars().nth((self.current - 1) as usize).unwrap()
    }

    fn add_token(&mut self, token_type: TokenType) {
        self.tokens.push(Token {
            token_type,
            literal: self.src.as_str()[(self.start as usize)..(self.current as usize)].to_string(),
            line: self.line,
        });
    }

    fn is_match_with_next(&mut self, expected: char) -> bool {
        return if self.src.chars().nth(self.current as usize).unwrap() == expected {
            self.current += 1;
            true
        } else {
            false
        };
    }

    fn peek(&self) -> char {
        return if self.is_at_end() {
            '\0'
        } else {
            self.src.chars().nth(self.current as usize).unwrap()
        };
    }

    fn lex_string(&mut self) {
        while !self.is_at_end() && self.consume() != '"' {}

        if self.is_at_end() {
            panic!("Expected closing \"");
        }

        self.add_token(TokenType::STRING)
    }

    fn lex_number(&mut self) {
        while !self.is_at_end() && self.consume().is_numeric() {}

        self.add_token(TokenType::NUMBER)
    }

    fn lex_identifier(&mut self) {
        while !self.is_at_end() && self.consume().is_alphanumeric() {}

        self.current -= 1;

        let identifier = self
            .src
            .get((self.start as usize)..(self.current as usize))
            .unwrap();

        match identifier {
            "PROCEDURE" => self.add_token(TokenType::PROCEDURE),
            "IF" => self.add_token(TokenType::IF),
            "ELSE" => self.add_token(TokenType::ELSE),
            "REPEAT" => self.add_token(TokenType::REPEAT),
            "TIMES" => self.add_token(TokenType::TIMES),
            "NOT" => self.add_token(TokenType::NOT),
            "AND" => self.add_token(TokenType::AND),
            "OR" => self.add_token(TokenType::OR),
            "UNTIL" => self.add_token(TokenType::UNTIL),
            "RETURN" => self.add_token(TokenType::RETURN),
            "MOD" => self.add_token(TokenType::MOD),
            "FOR" => self.add_token(TokenType::FOR),
            "FOR" => self.add_token(TokenType::IN),
            _ => self.add_token(TokenType::IDENTIFIER),
        }
    }
}
