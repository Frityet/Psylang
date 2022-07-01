mod lexer;
mod parser;
use std::env;

fn main() {
    let argument = env::args().nth(1);

    let file = if let Some(f) = argument {
        f
    } else {
        panic!("Expected File Path Recieved: {:?}", argument);
    };

    if file == "repl" {
        println!("Running repl");
        loop {
            print!(">>");

            let mut line = String::new();

            std::io::stdin().read_line(&mut line).unwrap();

            let mut lexer = lexer::Lexer::new(line);

            lexer.lex().iter().for_each(|token| println!("{:?}", token))
        }
    }

    //Read the file
    let maybe_file_contends = std::fs::read_to_string(&file);

    let file_contents = if maybe_file_contends.is_ok() {
        maybe_file_contends.unwrap()
    } else {
        panic!("Unable to read file: {:?}", file);
    };

    let mut lexer = lexer::Lexer::new(file_contents);

    lexer.lex();
}
