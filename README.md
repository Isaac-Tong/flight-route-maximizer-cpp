# CS225 Final Project | Isaac, Irfaan, Pranshu, Eric

![Flight Path Map](/src/readme_img.png)

## About The Final Project
For our CS225 Final Project, we chose the OpenFlights Dataset to create a graph. Our objective was to calculate the sequence of routes to take in order to minimize the physical traveling distance between two airports. We completed this by implementing Dijkstra's algorithm.Another algorithm used is Breadth-First Search which allows us to figure out if we are able to travel between the two airports given.

## Final Project Presentation
Link: https://youtu.be/F1Ar8MY7jUU

## Dataset
https://openflights.org/data.html
1. Airports Dataset: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports-extended.dat
2. Routes Dataset: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports-extended.dat


## Build and Run 

1. Compile the code
```
$ /make
```
2. You have two options to run the executable
```
# OPTION 1: Run ./flightsOpt with arguments: [starting Airport IATA Code] [destination Airport IATA Code] [path to routes file] [path to airports file]

Example:
$ ./flightsOpt ORD AKL ./tests/sets_to_test/./dataset/routes_subset.txt ./dataset/airports_extended_formatted.txt
```
```
# OPTION 2: Run ./flightsOpt with arguments: [starting Airport IATA Code] [destination Airport IATA Code] default default

Example:
$ ./flightsOpt ORD AKL default default
```
*__Note 1:__ Running the executable with option 1 allows you to specify the airport and routes dataset while running the executable with option 2 will use our default airport and routes dataset.*\
\
*__Note 2:__ In both options, you MUST specify the starting airport and ending airport for the first two arguments using the IATA codes for the airport. Eg. ORD = Chicago O'Hare*


## Build and Run Test Cases
1. Compile the code
```
$ /make test
```

2. Run the test cases
```
$ ./test
```

## Formatting / Using Your Own Dataset






### Contact
* Isaac Tong - isaact2@illinois.edu
* Eric Jin - ericjin2@illinois.edu
* Pranshu Chaturvedi - pranshu3@illinois.edu
* Irfaan Attarwala - iia2@illinois.edu




