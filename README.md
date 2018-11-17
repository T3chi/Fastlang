# Fastlang
## A simple interpreter for a generic C-style programming language.

Was made to solidify principles behind interpreters and compilers.
Test files were added to compare performance against C++ and Python equivalents.
(Note: The language's name was chosen for irony.)
Currently all tokenizing is done by splitting tokens based on whitespace.

#### example.fast:

```javascript
println "hello world" ;

var i = 0 ;

while ( i < 100 ) { 

 i = i + 1 ;
 
}

println i ;
```
