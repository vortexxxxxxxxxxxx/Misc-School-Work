#!/usr/bin/env python

import sys

from tokenizer import tokenize
from parser import parse
from evaluator import evaluate

def main():
    environment = {}
    
    watched_identifier = None
    executable_file = None
    
    # Parse command line arguments for 'watch=' and the filename
    for arg in sys.argv[1:]:
        if arg.startswith('watch='):
            # identifier is everything after 'watch='
            watched_identifier = arg[len('watch='):]
            if not watched_identifier:
                print("Error: 'watch' argument requires an identifier")
                sys.exit(1)
        elif not executable_file:
            # The first non-watch argument executable filename
            executable_file = arg
    
    # Check for script execution mode (filename provided)
    if executable_file:
        # Filename provided, read and execute it
        with open(executable_file, 'r') as f:
            source_code = f.read()
        try:
            tokens = tokenize(source_code)
            ast = parse(tokens)
            
            #Passing the watched_identifier to evaluate
            final_value, exit_status = evaluate(ast, environment, watched_identifier)
            
            if exit_status == "exit":
                sys.exit(final_value if isinstance(final_value, int) else 0)
        except Exception as e:
            print(f"Error: {e}")
            sys.exit(1)

    # Check for REPL mode (no script file provided, or only 'watch' was provided)
    elif len(sys.argv) == 1 or (len(sys.argv) > 1 and watched_identifier is not None and executable_file is None):
        # REPL loop
        print("Starting REPL...")
        while True:
            try:
                # Read input
                source_code = input('>> ')

                # Exit condition for the REPL loop
                if source_code.strip() in ['exit', 'quit']:
                    break

                # Tokenize, parse, and execute the code
                tokens = tokenize(source_code)
                ast = parse(tokens)
                
                final_value, exit_status = evaluate(ast, environment, watched_identifier)
                
                if exit_status == "exit":
                    print(f"Exiting with code: {final_value}") # REPL can print this
                    sys.exit(final_value if isinstance(final_value, int) else 0)
                elif final_value is not None: # Print result in REPL if not None
                    print(final_value)
            except Exception as e:
                print(f"Error: {e}")
                
    else:
        print("Usage: python runner.py [watch=<identifier>] [filename.mylang]")

if __name__ == "__main__":
    main()