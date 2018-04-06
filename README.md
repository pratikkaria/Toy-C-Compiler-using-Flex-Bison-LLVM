## Lab3 COL728 Compilers
Submitted By: Sandeep Kumar
2017ANZ8353

### How to run
A test file opt.c is included in the the code.
Run
*make check*
to see the IR code, and
*make test*
to run the generated IR code using lli.

To run the code

### Things supported
* This is for int type variable only.
* Algebraic: Constant additon, multiplication and subtraction.
* Dead code: Not called function will be removed
* Dead code for while: While loop with false enter condition will be removed
* Dead code if: If statment with constant condition will be removed and replaced with either true block or false block.
* Constant folding: Constants will be folded  and unsed variable will be removed

These are usually done in the IR level, but for the assignment we will do this as the AST level.
