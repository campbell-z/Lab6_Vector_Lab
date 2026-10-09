# Lab6_Vector_Lab_Campbell_Z

# Pseudo Code:
- vectop.c reads commands from user
- get_command() identifies top-level commands 
- if input is vector comand, getvect() tokenizes the input and dispatches it to internal handlers
- store named vectors in permnanent vectors array
- findvect() to locate a vector by name
- add_vector() to insert new vector or replace existing vector with same name
- get_vector() copies stored vector into caller's result variable
- clear() marks all stored vectors as unused
- addvect(), subvect(), scalmult(), dotprod(), and crossprod() for individual math operations
- resopvect() for selecting and executing operation
- vector-valued immediate results stored in new_vect working array
- new_vect_index++ when working result is used and =0 when >= MAX_VECTORS
- getvect() tokenizes the input and checks the token count
- one token = display named vectors
- three tokens = unassigned operation and print result ans =
- four tokens = 2-d vector
- five tokens = 3-d vector or assigned operation && print
- vector valued assigned operations name result with destination variable and save in perm storage
- print scalar result and don't store dot products
- if malformed command, report error and return
- vectors[] retains named vectors until replaced or cleared
- new_vect[] holds temporary results and is reused 

# Version History
- Version 1.5
  WIP version that was used for breaking up getvect() from 600 lines to multiple internal handler function
  for easier debugging and readibility.
  
- Version 2.0
  Updated version that saw significant changes in vector.c
  Vector processing function getvect() split into:
  
    1. display_vector_command()
    2. handle_opeeration()
    3. handle_assignment()
    4. handle_assignment_operation()
    5. valid_vector_name

  As well as improved error catching and debugging using errno library.

  Some notable changes in vectop.c this update were:

  1. is_blank_line() used to check for whitespaces for cleaner UI when user wants an empty line
  2. Significant error catching added for overlong inputs
 
- Version 2.1
  Added Makefile and slightly tweaked vector.c header. Currently auditing style for final version 2.2.

  
