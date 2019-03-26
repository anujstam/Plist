# Plist

Pythonic Lists in C


Plist is an implementation of a pythonic integer list in C. Plist structures are able to change size dynamically, and work as a substitute to integer arrays of unknown length, providing convenient functions to make working with them easy.
Plist was made as a project for self use and for educational purposes.

## Structure 
Plist structures have the following components 

  - An integer array (pyl)
  - The number of elements in the array (size)
  - The minimal value in the array (min)
  - The maximal value in the array (max)
  - An integer, 0 or 1, indicating if the Plist is sorted (sorted) 

## Functions

Plists can be initialized using the init_plist() function to set up default values.
Maximal and Minimal elements can be accessed directly using Plist.max and Piist.min
To access the actual integer array use Plist.pyl, and use Plist.size to determine the number of elements in it

Plist works by reallocating the list when the capacity changes. In the event of a reallocation error, an error message is displayed

The standard pythonic list functions have been implemented for the same. These include but are not limited to - 
  - append (plist* p, int val) appends val at the end of the list
  - insert (plist* p, int val, int index) will insert val at index. If index is invalid it will default to 0 or the end of the array depending on which is closer
  - del (plist* p, int index) will delete value at index. If the index is not present nothing will happen
  - remove (plist*p, int val) will remove value val if it exists. Nothing happens if val is not present in the list 
  - push (plist* p, int val) pushes val onto the Plist array, just like append
  - pop (plist* p) removes and returns the last value in the plist. If the Plist's array is empty it returns -1
  - sort (plist* p) sorts the Plist's array using TimSort algorithm
  - search (plist* p, int val) will return the index of val if it is present in the Plist's array. If not it returns -1
 
Other functions such as extend, intersection, union, difference are also included

## Features

You do not need to worry about input sizes. The Plist is able to resize itself to take up exactly as much space as it requires. Nothing more and nothing less.

Min and Max is O(1) because it is updated as and when values are inserted into the list. There is a slight decrease in deletion efficiency in cases where the minimum or maximum value is deleted.

Sorting uses the TimSort algorithm for best real world performance. Other major sorting algorithms are also provided for comparison.
The structure keeps track of whether it is sorted or not as and when inputs come in, which allows repetitive sorting to be skipped. It also allows for an easy way to determine the best search algorithm to use


Almost every main python list function has been implemented.



### Todos

 - Set operation
 - Efficiency checking
 - Multiple sort algo implementations
 - (maybe) allow other data types

License
----

MIT


___
Developed by Anuj Sanjay Tambwekar
