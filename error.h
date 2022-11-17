    /**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Definition of error codes and return values
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

///internal error codes
#define TOKEN_OK 0
#define SYNTAX_OK 0
#define SEMANTIC_OK 0
#define GENERATING_OK 0
 ///error codes given in the task description (see project requirements)
#define ERR_LEX 1              /// error in the program within the lexical analysis (incorrect structure of the current lexeme).
#define ERR_SYNTAX 2           /// an error in the program within the syntactic analysis (incorrect program syntax, missing header, etc.).
#define ERR_SEMANTIC_DEF_FCE 3 /// semantic error in the program - undefined function, attempt to redefine the function.
#define ERR_SEMANTIC_ARG_FCE 4 /// semantic/runtime error in the program – wrong number/type of parameters when calling the function or type of return value from the function.
#define ERR_SEMANTIC_DEF_VAR 5 /// semantic error in the program - use of an undefined variable.
#define ERR_SEMANTIC_RETURN 6  /// semantic/runtime error in program - missing/left over expression in return statement from function.
#define ERR_SEMANTIC_TYPE 7    /// semantic/runtime type compatibility bug in arithmetic, string, and relational expressions.
#define ERR_SEMANTIC_OTHER 8   /// other semantic errors.
#define ERR_INTERNAL 99        /// an internal compiler error, i.e. not affected by the input program (e.g. memory allocation error, etc.).

