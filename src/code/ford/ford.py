import sys

class reader:
    # Get the number of vertex and number of pipes from input
    def readDimensions(input):
        vertex = int(input.readline())
        pipes = int(input.readline())
        return vertex,pipes

    # Get the cost vector from input
    def readCost(input):
        cost = input.readline().split()
        cost = [float(index) for index in cost] # Converts each string into a float value
        return cost

    # Get the graph from input
    def readGraph(input):
        graph = [line.split() for line in input]
        i = 0
        for line in graph:
            j = 0
            for index in line:
                graph[i][j] = float(index) # Converts each string into a float value
                j+=1
            i+=1
        return graph

    def readInput(input):
        vertex, pipes = reader.readDimensions(input)
        cost = reader.readCost(input)
        graph = reader.readGraph(input)
        return vertex, pipes, cost, graph

class Ford:
    def __init__(self, graph):
        self.graph = graph # Store the graph into the object
        self.dimx = len(graph) # Number of rows in graph
        self.dimy = len(graph[0]) # Number of columns in graph
        self.source = 0 # The source will be always the first vertice
        self.sink = self.dimx-1 # The sink will be always the last vertice
        self.path = [0] * self.dimx # Stores the actual path (auxiliar to BFS)

    def breadthFirstSearch(self): # Do a BFS search in the actual flow graph
        visited = [False] * self.dimx # All vertices is not visited
        bfsQueue = [] # Create a queue for BFS

        visited[self.source] = True # Mark the source as visited
        bfsQueue.append(self.source) # Insert the source into the bfsQueue

        while bfsQueue: # While the bfsQueue isn't empty
            actualVertice = bfsQueue.pop(0) # Pop a vertice from bfsQueue

            # Get all adjacent vertices of the actualVertice
            for index, value in enumerate(self.graph[actualVertice]):
                if visited[index] == False and value > 0: # If an adjacent vertice has not been visited yet, mark it visited and append it to the bfsQueue. Then, add the actualVertice to the path list
                    visited[index] = True
                    bfsQueue.append(index)
                    self.path[index] = actualVertice

        # If we got to the sink vertice, starting from the source
        if visited[self.sink]:
            return True # Path is valid
        else:
            return False # Path is not valid

    def FordFulkerson(self): # Returns the maximum flow from self.source to self.sink
        pass



input = open(sys.argv[1], "r")
output = open(sys.argv[2], "w")

vertex, pipes, cost, graph = reader.readInput(input)

fordFulkerson = Ford(graph)
