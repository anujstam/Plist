# Plist

Pythonic Lists in C


Plist is an implementation of a pythonic integer list in C. Plist structures are able to change size dynamically, and work as a substitute to integer arrays of unknown length, providing convenient functions to make working with them easy.
Plist was made as a project for self use and for educational purposes.

## Structure 
Plist structures have the following components 

  - An integer array (list)
  - The number of elements in the array (size)
  - The minimal value in the array (min)
  - The maximal value in the array (max)
  - An integer, 0 or 1, indicating if the Plist is sorted (sorted) 

## Functions

Plists can be initialized using the init_plist() function to set up default values.
Maximal and Minimal elements can be accessed directly using Plist.max and Piist.min
To access the actual integer array use Plist.list, and use Plist.size to determine the number of elements in it

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

The TimSort implementation is not a 100% implementation of the Timsort in python. It uses a similar concept, IE divides the array into arrays of size 32, performs insertion sort on them and merges the sequential arrays. The run-off arrays that are produced in the process are merged while this happens before they are finally merged with the total array

## Features

You do not need to worry about input sizes. The Plist is able to resize itself to take up exactly as much space as it requires. Nothing more and nothing less.

Min and Max is O(1) because it is updated as and when values are inserted into the list. There is a slight decrease in deletion efficiency in cases where the minimum or maximum value is deleted.

Sorting uses the TimSort algorithm for best real world performance.

The structure keeps track of whether it is sorted or not as and when inputs come in, which allows repetitive sorting to be skipped. It also allows for an easy way to determine the best search algorithm to use

A convenient display function display(plist p) allows for easy viewing of the plist


Almost every main python list function has been implemented.



### Todos

 - Iter, Filter, Map
 - (maybe) allow other data types

License
----

Apache


___
Developed by Anuj Sanjay Tambwekar
