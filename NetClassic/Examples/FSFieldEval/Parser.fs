// Implementation file for parser generated by fsyacc
module Parser
#nowarn "64";; // turn off warnings that type variables used in production annotations are instantiated to concrete type
open Ast
open Microsoft.FSharp.Text.Lexing
open Microsoft.FSharp.Text.Parsing.ParseHelpers
# 1 "Parser.fsy"

# 9 "Parser.fs"
// This type is the type of tokens accepted by the parser
type token = 
  | EOF
  | LPAREN
  | RPAREN
  | LBRACKET
  | RBRACKET
  | COMMA
  | DOT
  | PI
  | E
  | SIN
  | COS
  | TAN
  | ASIN
  | ACOS
  | ATAN
  | LOG
  | LN
  | EXP
  | SQR
  | SQRT
  | R2D
  | D2R
  | ABS
  | ROUND
  | TRUNC
  | DIST
  | ILL
  | NOR
  | VEC
  | VEC1
  | COLON
  | ASTERISK
  | SLASH
  | CARET
  | PLUS
  | DASH
  | TABLE of (int64)
  | LITERAL of (string)
  | FLOAT of (float)
// This type is used to give symbolic names to token indexes, useful for error messages
type tokenId = 
    | TOKEN_EOF
    | TOKEN_LPAREN
    | TOKEN_RPAREN
    | TOKEN_LBRACKET
    | TOKEN_RBRACKET
    | TOKEN_COMMA
    | TOKEN_DOT
    | TOKEN_PI
    | TOKEN_E
    | TOKEN_SIN
    | TOKEN_COS
    | TOKEN_TAN
    | TOKEN_ASIN
    | TOKEN_ACOS
    | TOKEN_ATAN
    | TOKEN_LOG
    | TOKEN_LN
    | TOKEN_EXP
    | TOKEN_SQR
    | TOKEN_SQRT
    | TOKEN_R2D
    | TOKEN_D2R
    | TOKEN_ABS
    | TOKEN_ROUND
    | TOKEN_TRUNC
    | TOKEN_DIST
    | TOKEN_ILL
    | TOKEN_NOR
    | TOKEN_VEC
    | TOKEN_VEC1
    | TOKEN_COLON
    | TOKEN_ASTERISK
    | TOKEN_SLASH
    | TOKEN_CARET
    | TOKEN_PLUS
    | TOKEN_DASH
    | TOKEN_TABLE
    | TOKEN_LITERAL
    | TOKEN_FLOAT
    | TOKEN_end_of_input
    | TOKEN_error
// This type is used to give symbolic names to token indexes, useful for error messages
type nonTerminalId = 
    | NONTERM__startMain
    | NONTERM_Main
    | NONTERM_Expr

// This function maps tokens to integers indexes
let tagOfToken (t:token) = 
  match t with
  | EOF  -> 0 
  | LPAREN  -> 1 
  | RPAREN  -> 2 
  | LBRACKET  -> 3 
  | RBRACKET  -> 4 
  | COMMA  -> 5 
  | DOT  -> 6 
  | PI  -> 7 
  | E  -> 8 
  | SIN  -> 9 
  | COS  -> 10 
  | TAN  -> 11 
  | ASIN  -> 12 
  | ACOS  -> 13 
  | ATAN  -> 14 
  | LOG  -> 15 
  | LN  -> 16 
  | EXP  -> 17 
  | SQR  -> 18 
  | SQRT  -> 19 
  | R2D  -> 20 
  | D2R  -> 21 
  | ABS  -> 22 
  | ROUND  -> 23 
  | TRUNC  -> 24 
  | DIST  -> 25 
  | ILL  -> 26 
  | NOR  -> 27 
  | VEC  -> 28 
  | VEC1  -> 29 
  | COLON  -> 30 
  | ASTERISK  -> 31 
  | SLASH  -> 32 
  | CARET  -> 33 
  | PLUS  -> 34 
  | DASH  -> 35 
  | TABLE _ -> 36 
  | LITERAL _ -> 37 
  | FLOAT _ -> 38 

// This function maps integers indexes to symbolic token ids
let tokenTagToTokenId (tokenIdx:int) = 
  match tokenIdx with
  | 0 -> TOKEN_EOF 
  | 1 -> TOKEN_LPAREN 
  | 2 -> TOKEN_RPAREN 
  | 3 -> TOKEN_LBRACKET 
  | 4 -> TOKEN_RBRACKET 
  | 5 -> TOKEN_COMMA 
  | 6 -> TOKEN_DOT 
  | 7 -> TOKEN_PI 
  | 8 -> TOKEN_E 
  | 9 -> TOKEN_SIN 
  | 10 -> TOKEN_COS 
  | 11 -> TOKEN_TAN 
  | 12 -> TOKEN_ASIN 
  | 13 -> TOKEN_ACOS 
  | 14 -> TOKEN_ATAN 
  | 15 -> TOKEN_LOG 
  | 16 -> TOKEN_LN 
  | 17 -> TOKEN_EXP 
  | 18 -> TOKEN_SQR 
  | 19 -> TOKEN_SQRT 
  | 20 -> TOKEN_R2D 
  | 21 -> TOKEN_D2R 
  | 22 -> TOKEN_ABS 
  | 23 -> TOKEN_ROUND 
  | 24 -> TOKEN_TRUNC 
  | 25 -> TOKEN_DIST 
  | 26 -> TOKEN_ILL 
  | 27 -> TOKEN_NOR 
  | 28 -> TOKEN_VEC 
  | 29 -> TOKEN_VEC1 
  | 30 -> TOKEN_COLON 
  | 31 -> TOKEN_ASTERISK 
  | 32 -> TOKEN_SLASH 
  | 33 -> TOKEN_CARET 
  | 34 -> TOKEN_PLUS 
  | 35 -> TOKEN_DASH 
  | 36 -> TOKEN_TABLE 
  | 37 -> TOKEN_LITERAL 
  | 38 -> TOKEN_FLOAT 
  | 41 -> TOKEN_end_of_input
  | 39 -> TOKEN_error
  | _ -> failwith "tokenTagToTokenId: bad token"

/// This function maps production indexes returned in syntax errors to strings representing the non terminal that would be produced by that production
let prodIdxToNonTerminal (prodIdx:int) = 
  match prodIdx with
    | 0 -> NONTERM__startMain 
    | 1 -> NONTERM_Main 
    | 2 -> NONTERM_Expr 
    | 3 -> NONTERM_Expr 
    | 4 -> NONTERM_Expr 
    | 5 -> NONTERM_Expr 
    | 6 -> NONTERM_Expr 
    | 7 -> NONTERM_Expr 
    | 8 -> NONTERM_Expr 
    | 9 -> NONTERM_Expr 
    | 10 -> NONTERM_Expr 
    | 11 -> NONTERM_Expr 
    | 12 -> NONTERM_Expr 
    | 13 -> NONTERM_Expr 
    | 14 -> NONTERM_Expr 
    | 15 -> NONTERM_Expr 
    | 16 -> NONTERM_Expr 
    | _ -> failwith "prodIdxToNonTerminal: bad production index"

let _fsyacc_endOfInputTag = 41 
let _fsyacc_tagOfErrorTerminal = 39

// This function gets the name of a token as a string
let token_to_string (t:token) = 
  match t with 
  | EOF  -> "EOF" 
  | LPAREN  -> "LPAREN" 
  | RPAREN  -> "RPAREN" 
  | LBRACKET  -> "LBRACKET" 
  | RBRACKET  -> "RBRACKET" 
  | COMMA  -> "COMMA" 
  | DOT  -> "DOT" 
  | PI  -> "PI" 
  | E  -> "E" 
  | SIN  -> "SIN" 
  | COS  -> "COS" 
  | TAN  -> "TAN" 
  | ASIN  -> "ASIN" 
  | ACOS  -> "ACOS" 
  | ATAN  -> "ATAN" 
  | LOG  -> "LOG" 
  | LN  -> "LN" 
  | EXP  -> "EXP" 
  | SQR  -> "SQR" 
  | SQRT  -> "SQRT" 
  | R2D  -> "R2D" 
  | D2R  -> "D2R" 
  | ABS  -> "ABS" 
  | ROUND  -> "ROUND" 
  | TRUNC  -> "TRUNC" 
  | DIST  -> "DIST" 
  | ILL  -> "ILL" 
  | NOR  -> "NOR" 
  | VEC  -> "VEC" 
  | VEC1  -> "VEC1" 
  | COLON  -> "COLON" 
  | ASTERISK  -> "ASTERISK" 
  | SLASH  -> "SLASH" 
  | CARET  -> "CARET" 
  | PLUS  -> "PLUS" 
  | DASH  -> "DASH" 
  | TABLE _ -> "TABLE" 
  | LITERAL _ -> "LITERAL" 
  | FLOAT _ -> "FLOAT" 

// This function gets the data carried by a token as an object
let _fsyacc_dataOfToken (t:token) = 
  match t with 
  | EOF  -> (null : System.Object) 
  | LPAREN  -> (null : System.Object) 
  | RPAREN  -> (null : System.Object) 
  | LBRACKET  -> (null : System.Object) 
  | RBRACKET  -> (null : System.Object) 
  | COMMA  -> (null : System.Object) 
  | DOT  -> (null : System.Object) 
  | PI  -> (null : System.Object) 
  | E  -> (null : System.Object) 
  | SIN  -> (null : System.Object) 
  | COS  -> (null : System.Object) 
  | TAN  -> (null : System.Object) 
  | ASIN  -> (null : System.Object) 
  | ACOS  -> (null : System.Object) 
  | ATAN  -> (null : System.Object) 
  | LOG  -> (null : System.Object) 
  | LN  -> (null : System.Object) 
  | EXP  -> (null : System.Object) 
  | SQR  -> (null : System.Object) 
  | SQRT  -> (null : System.Object) 
  | R2D  -> (null : System.Object) 
  | D2R  -> (null : System.Object) 
  | ABS  -> (null : System.Object) 
  | ROUND  -> (null : System.Object) 
  | TRUNC  -> (null : System.Object) 
  | DIST  -> (null : System.Object) 
  | ILL  -> (null : System.Object) 
  | NOR  -> (null : System.Object) 
  | VEC  -> (null : System.Object) 
  | VEC1  -> (null : System.Object) 
  | COLON  -> (null : System.Object) 
  | ASTERISK  -> (null : System.Object) 
  | SLASH  -> (null : System.Object) 
  | CARET  -> (null : System.Object) 
  | PLUS  -> (null : System.Object) 
  | DASH  -> (null : System.Object) 
  | TABLE _fsyacc_x -> Microsoft.FSharp.Core.Operators.box _fsyacc_x 
  | LITERAL _fsyacc_x -> Microsoft.FSharp.Core.Operators.box _fsyacc_x 
  | FLOAT _fsyacc_x -> Microsoft.FSharp.Core.Operators.box _fsyacc_x 
let _fsyacc_gotos = [| 0us; 65535us; 1us; 65535us; 0us; 1us; 9us; 65535us; 0us; 2us; 10us; 11us; 13us; 14us; 15us; 16us; 17us; 18us; 25us; 21us; 26us; 22us; 27us; 23us; 28us; 24us; |]
let _fsyacc_sparseGotoTableRowOffsets = [|0us; 1us; 3us; |]
let _fsyacc_stateToProdIdxsTableElements = [| 1us; 0us; 1us; 0us; 5us; 1us; 10us; 11us; 12us; 13us; 1us; 1us; 2us; 2us; 16us; 1us; 3us; 1us; 4us; 1us; 5us; 1us; 6us; 1us; 6us; 1us; 7us; 5us; 7us; 10us; 11us; 12us; 13us; 1us; 7us; 2us; 8us; 9us; 6us; 8us; 9us; 10us; 11us; 12us; 13us; 2us; 8us; 9us; 6us; 8us; 9us; 10us; 11us; 12us; 13us; 1us; 8us; 5us; 8us; 10us; 11us; 12us; 13us; 1us; 8us; 1us; 9us; 5us; 10us; 10us; 11us; 12us; 13us; 5us; 10us; 11us; 11us; 12us; 13us; 5us; 10us; 11us; 12us; 12us; 13us; 5us; 10us; 11us; 12us; 13us; 13us; 1us; 10us; 1us; 11us; 1us; 12us; 1us; 13us; 2us; 14us; 15us; 2us; 14us; 15us; 2us; 14us; 15us; 1us; 14us; 1us; 14us; 1us; 14us; 1us; 14us; 1us; 14us; 1us; 14us; 1us; 14us; 1us; 14us; 1us; 16us; 1us; 16us; 1us; 16us; 1us; 16us; 1us; 16us; |]
let _fsyacc_stateToProdIdxsTableRowOffsets = [|0us; 2us; 4us; 10us; 12us; 15us; 17us; 19us; 21us; 23us; 25us; 27us; 33us; 35us; 38us; 45us; 48us; 55us; 57us; 63us; 65us; 67us; 73us; 79us; 85us; 91us; 93us; 95us; 97us; 99us; 102us; 105us; 108us; 110us; 112us; 114us; 116us; 118us; 120us; 122us; 124us; 126us; 128us; 130us; 132us; |]
let _fsyacc_action_rows = 45
let _fsyacc_actionTableElements = [|8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 0us; 49152us; 5us; 32768us; 0us; 3us; 31us; 25us; 32us; 26us; 34us; 27us; 35us; 28us; 0us; 16385us; 1us; 16386us; 1us; 40us; 0us; 16387us; 0us; 16388us; 0us; 16389us; 1us; 32768us; 38us; 9us; 0us; 16390us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 5us; 32768us; 2us; 12us; 31us; 25us; 32us; 26us; 34us; 27us; 35us; 28us; 0us; 16391us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 5us; 32768us; 5us; 15us; 31us; 25us; 32us; 26us; 34us; 27us; 35us; 28us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 6us; 32768us; 4us; 20us; 5us; 17us; 31us; 25us; 32us; 26us; 34us; 27us; 35us; 28us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 5us; 32768us; 4us; 19us; 31us; 25us; 32us; 26us; 34us; 27us; 35us; 28us; 0us; 16392us; 0us; 16393us; 0us; 16394us; 0us; 16395us; 2us; 16396us; 31us; 25us; 32us; 26us; 2us; 16397us; 31us; 25us; 32us; 26us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 8us; 32768us; 1us; 10us; 3us; 13us; 7us; 5us; 8us; 6us; 35us; 8us; 36us; 29us; 37us; 4us; 38us; 7us; 1us; 32768us; 6us; 30us; 1us; 32768us; 37us; 31us; 1us; 16399us; 1us; 32us; 1us; 32768us; 37us; 33us; 1us; 32768us; 1us; 34us; 1us; 32768us; 37us; 35us; 1us; 32768us; 30us; 36us; 1us; 32768us; 37us; 37us; 1us; 32768us; 2us; 38us; 1us; 32768us; 2us; 39us; 0us; 16398us; 1us; 32768us; 37us; 41us; 1us; 32768us; 30us; 42us; 1us; 32768us; 37us; 43us; 1us; 32768us; 2us; 44us; 0us; 16400us; |]
let _fsyacc_actionTableRowOffsets = [|0us; 9us; 10us; 16us; 17us; 19us; 20us; 21us; 22us; 24us; 25us; 34us; 40us; 41us; 50us; 56us; 65us; 72us; 81us; 87us; 88us; 89us; 90us; 91us; 94us; 97us; 106us; 115us; 124us; 133us; 135us; 137us; 139us; 141us; 143us; 145us; 147us; 149us; 151us; 153us; 154us; 156us; 158us; 160us; 162us; |]
let _fsyacc_reductionSymbolCounts = [|1us; 2us; 1us; 1us; 1us; 1us; 2us; 3us; 7us; 5us; 3us; 3us; 3us; 3us; 11us; 3us; 6us; |]
let _fsyacc_productionToNonTerminalTable = [|0us; 1us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; 2us; |]
let _fsyacc_immediateActions = [|65535us; 49152us; 65535us; 16385us; 65535us; 16387us; 16388us; 16389us; 65535us; 16390us; 65535us; 65535us; 16391us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 16392us; 16393us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 65535us; 16398us; 65535us; 65535us; 65535us; 65535us; 16400us; |]
let _fsyacc_reductions ()  =    [| 
# 310 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
                      raise (Microsoft.FSharp.Text.Parsing.Accept(Microsoft.FSharp.Core.Operators.box _1))
                   )
                 : '_startMain));
# 319 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 22 "Parser.fsy"
                                 _1 
                   )
# 22 "Parser.fsy"
                 : expr));
# 330 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 25 "Parser.fsy"
                                 Literal _1 
                   )
# 25 "Parser.fsy"
                 : 'Expr));
# 341 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 26 "Parser.fsy"
                              Float System.Math.PI 
                   )
# 26 "Parser.fsy"
                 : 'Expr));
# 351 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 27 "Parser.fsy"
                             Float 0.0 
                   )
# 27 "Parser.fsy"
                 : 'Expr));
# 361 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : float)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 28 "Parser.fsy"
                                 Float _1 
                   )
# 28 "Parser.fsy"
                 : 'Expr));
# 372 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _2 = (let data = parseState.GetInput(2) in (Microsoft.FSharp.Core.Operators.unbox data : float)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 29 "Parser.fsy"
                                      Float (- _2) 
                   )
# 29 "Parser.fsy"
                 : 'Expr));
# 383 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _2 = (let data = parseState.GetInput(2) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 30 "Parser.fsy"
                                              _2 
                   )
# 30 "Parser.fsy"
                 : 'Expr));
# 394 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _2 = (let data = parseState.GetInput(2) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            let _4 = (let data = parseState.GetInput(4) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            let _6 = (let data = parseState.GetInput(6) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 31 "Parser.fsy"
                                                                        Vector(_2, _4, _6) 
                   )
# 31 "Parser.fsy"
                 : 'Expr));
# 407 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _2 = (let data = parseState.GetInput(2) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            let _4 = (let data = parseState.GetInput(4) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 32 "Parser.fsy"
                                                             Vector(_2, _4, Float(0.0)) 
                   )
# 32 "Parser.fsy"
                 : 'Expr));
# 419 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 33 "Parser.fsy"
                                              Mul(_1, _3) 
                   )
# 33 "Parser.fsy"
                 : 'Expr));
# 431 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 34 "Parser.fsy"
                                           Div(_1, _3) 
                   )
# 34 "Parser.fsy"
                 : 'Expr));
# 443 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 35 "Parser.fsy"
                                          Plus(_1, _3) 
                   )
# 35 "Parser.fsy"
                 : 'Expr));
# 455 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : 'Expr)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 36 "Parser.fsy"
                                          Minus(_1, _3) 
                   )
# 36 "Parser.fsy"
                 : 'Expr));
# 467 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : int64)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            let _5 = (let data = parseState.GetInput(5) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            let _7 = (let data = parseState.GetInput(7) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            let _9 = (let data = parseState.GetInput(9) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 38 "Parser.fsy"
                           match _3 with 
                           | "evaluate" -> TableEval(_1, _5, _7, _9) 
                           | _ -> failwith "unexpected table function"
                   )
# 38 "Parser.fsy"
                 : 'Expr));
# 484 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : int64)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 41 "Parser.fsy"
                                             Table(_1,_3)
                   )
# 41 "Parser.fsy"
                 : 'Expr));
# 496 "Parser.fs"
        (fun (parseState : Microsoft.FSharp.Text.Parsing.IParseState) ->
            let _1 = (let data = parseState.GetInput(1) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            let _3 = (let data = parseState.GetInput(3) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            let _5 = (let data = parseState.GetInput(5) in (Microsoft.FSharp.Core.Operators.unbox data : string)) in
            Microsoft.FSharp.Core.Operators.box
                (
                   (
# 42 "Parser.fsy"
                                                                       ImplicitTableEval(_1, _3, _5) 
                   )
# 42 "Parser.fsy"
                 : 'Expr));
|]
# 510 "Parser.fs"
let tables () : Microsoft.FSharp.Text.Parsing.Tables<_> = 
  { reductions= _fsyacc_reductions ();
    endOfInputTag = _fsyacc_endOfInputTag;
    tagOfToken = tagOfToken;
    dataOfToken = _fsyacc_dataOfToken; 
    actionTableElements = _fsyacc_actionTableElements;
    actionTableRowOffsets = _fsyacc_actionTableRowOffsets;
    stateToProdIdxsTableElements = _fsyacc_stateToProdIdxsTableElements;
    stateToProdIdxsTableRowOffsets = _fsyacc_stateToProdIdxsTableRowOffsets;
    reductionSymbolCounts = _fsyacc_reductionSymbolCounts;
    immediateActions = _fsyacc_immediateActions;
    gotos = _fsyacc_gotos;
    sparseGotoTableRowOffsets = _fsyacc_sparseGotoTableRowOffsets;
    tagOfErrorTerminal = _fsyacc_tagOfErrorTerminal;
    parseError = (fun (ctxt:Microsoft.FSharp.Text.Parsing.ParseErrorContext<_>) -> 
                              match parse_error_rich with 
                              | Some f -> f ctxt
                              | None -> parse_error ctxt.Message);
    numTerminals = 42;
    productionToNonTerminalTable = _fsyacc_productionToNonTerminalTable  }
let engine lexer lexbuf startState = (tables ()).Interpret(lexer, lexbuf, startState)
let Main lexer lexbuf : expr =
    Microsoft.FSharp.Core.Operators.unbox ((tables ()).Interpret(lexer, lexbuf, 0))