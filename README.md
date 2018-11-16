# Fastlang
A simple interpreter for a generic C-style programming language.
Was made to solidify principles behind interpreters and compilers.
Test files were added to compare performance against C++ and Python equivalents.
Currently all tokenizing is done by splitting tokens based on whitespace.
example.fast:
println "hello world" ;
var i = 0 ;
while ( i < 100 ) { 
      i = i + 1 ;
}
println i ;
