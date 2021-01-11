# Flight Route Maximizer | Isaac, Irfaan, Pranshu, Eric

![Flight Path Map](/src/readme_img.png)

## About The Project
Our objective was to calculate the sequence of routes to take in order to minimize the physical traveling distance between two airports. We completed this by implementing Dijkstra's algorithm.Another algorithm used is Breadth-First Search which allows us to figure out if we are able to travel between the two airports given.

## Dataset
https://openflights.org/data.html
1. Airports Dataset: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports-extended.dat
2. Routes Dataset: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports-extended.dat

#
## Build and Run 

__NOTE: The program might take a significant amount of time if the dataset is large__

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

### World Map Projection Image
```
"outputProjection.png" projects all the routes in the dataset onto the world map.

"outputShortest.png" projects the minimum weighted path given the starting airport and ending airport onto the world map.

```

### Output Files
Whenever BFS or Djikstra's algorithm is run, "DijksrtaOutput.txt" and "bfs_airports_visited.txt" will be generated.

__DijksrtaOutput.txt__
```
Example Output:

SHORTEST DISTANCE: 12345
SHORTEST PATH: XXX-YYY-ZZZ

DIJKSTRA OUTPUT
Airport: YXU Distance: 1345 Previous Airport: START
Airport: OPF Distance: 1908 Previous Airport: OPF
Airport: GOP Distance: 14068 Previous Airport: DEL

** To get the shortest weighted path of an airport to the starting airport, keep going back to the previous airport until START has been reached. A distance of 2147483647 or some other ridiculously large number means that that there is no connection from that airport to the starting airport.
```
__bfs_airports_visited.txt__
```
Example Output:

Start of BFS between XXX and ZZZ
YVR
EWR
HND
NRT
ORD
```

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
In order for our program to understand your own airport and routes dataset text files, they must be formatted in a very specific way. The following description will tell you how to format your airport and routes text file. 

### Airports File
*Each piece of data must be separated by a comma*
```
Format:
[Airport IATA Code],[Lattitude],[Longitude],airport

Example:
YVR,49.19390106,-123.1839981,airport
```

### Routes File
*Each piece of data must be separated by a comma*\
__*Although not all pieces of information of the routes are neccesary for our program, it is neccesary that you include them as our data parsing function will require their existance__
```
Format:
[IATA Airline ID],[Openflights Airline ID],[Starting Airport IATA Code],[Starting Airport Openflights ID],[Destination Airport IATA Code],[Destination Airport Openflights ID],[Codeshare],[Stops],[Equipment]

Example:
2B,410,DME,4029,KZN,2990,,0,CR2
```

## Contact
* Isaac Tong - isaact2@illinois.edu
* Eric Jin - ericjin2@illinois.edu
* Pranshu Chaturvedi - pranshu3@illinois.edu
* Irfaan Attarwala - iia2@illinois.edu
