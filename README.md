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

# Notes:
- getvect() was over 600 lines, split into 
- internal command handlers
- Version 1.0 was working, however, getvect()
- But getvect() and psuedo code needed revisions 

# Progress status
- Currently working on final code audit for Version 2.0 [debugging and finishing error catching functions] 
