# LibraryManagementSystem

# Running the Program

- Download the file library_management_system.cpp.
- Compile and run using g++:  
  g++ library_management_system.cpp -o library  
  ./library  
  
# What main() Does

The main function demonstrates how the system works in sequential steps:  

1. Create Library  

Initializes a library named "Central Library".  

3. Add Librarians  

Creates two librarians (Alice and Luna) and adds them to the library.  

3. Create Books  

Creates three books: Harry Potter, Five Survive, Six of Crows

4. Librarians Add Books  

- Alice adds Harry Potter and Five Survive.  

- Luna adds Six of Crows.  

4. Register Members  

Two members (Monica and Pip) register with the library.  

5. Member Actions

- Monica logs in, borrows Harry Potter and Five Survive.  

- Pip logs in and tries to borrow Harry Potter (fails because it’s borrowed).  

- Monica returns Harry Potter, and then Pip borrows it.  

- Monica returns Five Survive.  

6. Librarian Removes a Book  

Luna removes Six of Crows from the library.  

7. Remove Librarian  

The library removes Luna from its list of librarians.  
