import sys

class reader:
    # Get the number of vertex and number of edges from input
    def readDimensions(input):
        vertex = int(input.readline())
        edges = int(input.readline())
        return vertex,edges

    # Get the capacity vector from input
    def readCapacity(input):
        capacity = input.readline().split()
        capacity = [int(index) for index in capacity] # Converts each string into a int value
        return capacity

    # Get the graph from input
    def readIncidenceMatrix(input):
        graph = [line.split() for line in input]
        i = 0
        for line in graph:
            j = 0
            for index in line:
                graph[i][j] = int(index) # Converts each string into a int value
                j+=1
            i+=1
        return graph

    def readInput(input):
        vertex, edges = reader.readDimensions(input)
        capacity = reader.readCapacity(input)
        graph = reader.readIncidenceMatrix(input)
        return vertex, edges, capacity, graph

class Ford:
    def __init__(self, capacity, incidenceMatrix):
        self.capacity = capacity # Stores the original capacity
        self.incidenceMatrix = incidenceMatrix # Stores the incidence matrix
        self.graph = self.incidenceMatrixToGraph() # Stores the graph into the object
        self.dimx = len(self.graph) # Number of rows in graph
        self.dimy = len(self.graph[0]) # Number of columns in graph
        self.source = 0 # The source will be always the first vertice
        self.sink = self.dimx-1 # The sink will be always the last vertice
        self.parent = [0] * self.dimx # Stores the parents of the actual vertice (auxiliar to DFS)
        self.visited = [False] * len(self.incidenceMatrix[0]) # Stores the visited vertex (auxiliar to DFS)
        self.actualFlow = [0] * len(self.incidenceMatrix[0]) # Stores the actual flow of the edges
        self.stCut = [0] * len(self.incidenceMatrix[0]) # Stores the minimum st-cut

    def incidenceMatrixToGraph(self):
        graph = [[0 for i in range(len(self.incidenceMatrix))]for j in range(len(self.incidenceMatrix))] # Creates a adjacency matrix numVertex X numVertex

        # If we detect a directed edge going from i to k, we find which vertice is k and add the capacity of the edge to the adjacency matrix
        for i in range(len(self.incidenceMatrix)):
            for j in range(len(self.incidenceMatrix[0])):
                if self.incidenceMatrix[i][j] == -1:
                    for k in range(len(self.incidenceMatrix)):
                        if self.incidenceMatrix[k][j] == 1:
                            graph[i][k] = capacity[j]

        return graph

    def addActualFlow(self, s, t, pathFlow, path):
        for column in range(len(self.incidenceMatrix[0])):
            if abs(self.incidenceMatrix[s][column]) == 1 and abs(self.incidenceMatrix[t][column] == 1): # If it is -1 or 1
                self.actualFlow[column] += pathFlow
                path[column] = 1
        return path

    def depthFirstSearch(self): # Do a DFS search in the actual flow graph
        self.visited = [False] * self.dimx # All vertices is not visited
        dfsStack = [] # Create a stack for DFS

        self.visited[self.source] = True # Mark the source as visited
        dfsStack.append(self.source) # Insert the source into the dfsStack

        while dfsStack: # While the dfsStack isn't empty
            actualVertice = dfsStack.pop(-1) # Pop a vertice from dfsStack

            # Get all adjacent vertices of the actualVertice
            for index, value in enumerate(self.graph[actualVertice]):
                if self.visited[index] == False and value > 0: # If an adjacent vertice has not been visited yet, mark it visited and append it to the dfsStack. Then, add the adjacent vertex to the parent list
                    self.visited[index] = True
                    dfsStack.append(index)
                    self.parent[index] = actualVertice

        # If we got to the sink vertice, starting from the source
        if self.visited[self.sink]:
            return True # Path is valid
        else:
            return False # Path is not valid

    def FordFulkerson(self, output): # Returns the maximum flow from self.source to self.sink
        maxFlow = 0 # Initially, no flow on the graph

        # Increments the maxFlow while there is a valid path from self.source to self.sink
        while self.depthFirstSearch():
            pathFlow = float('Inf') # Make the path flow equals to infinite
            path = [0] * len(self.incidenceMatrix[0]) # Stores the actual valid path

            actual = self.sink # Initialize the actual vertice in the sink
            # path[actual] = 1 # The sink will be always in a valid path
            while(actual != self.source):
                pathFlow = min(pathFlow, self.graph[self.parent[actual]][actual]) # Get the minimum flow between the actual path flow and the flow of the actual edge
                actual = self.parent[actual] # Make the actual vertice equal to the previous vertice on the DFS actual path
                # path[actual] = 1 # Stores the actual path

            # Adds the path flow to the total flow
            maxFlow += pathFlow

            # Residual graph building -> Update the graph residual capacities in each edge and reverse edges along the valid path
            t = self.sink
            while(t != self.source):
                s = self.parent[t] # s gets the previous vertice of the actual path
                self.graph[s][t] -= pathFlow # Reduce the pathFlow of the edge
                self.graph[t][s] += pathFlow # Add the pathFlow to the inverse edge
                path = self.addActualFlow(s, t, pathFlow, path) # Adds the actual flow to the self.actualFlow vector and gets the actual path
                t = self.parent[t] # t gets the previous vertice of the actual path (same as actual s)

            self.printsOutput(output, path)

        output.write("%d\n\n" %maxFlow)
        self.findSTCut(output)

    def printsOutput(self, output, path):
        for item in path:
            output.write("%d "%item)
        output.write("\n\n")

        for item in self.capacity:
            output.write("%d "%item)
        output.write("\n\n")

        for item in self.actualFlow:
            output.write("%d "%item)
        output.write("\n\n\n")

    def addSTCut(self, actual, vertice):
        for column in range(len(self.incidenceMatrix[0])): # Search the edge in the incidenceMatrix
            if abs(self.incidenceMatrix[actual][column]) == 1 and abs(self.incidenceMatrix[vertice][column] == 1): # If it is -1 or 1
                self.stCut[column] = 1 # Set the stCut vector to be 1 in that edge

    def printsSTCut(self, output):
        originalGraph = self.incidenceMatrixToGraph() # Gets original graph
        actual = self.source # Starts searching in the source vertice
        minCutStack = [] # Stack for the DFS minCut search
        minCutStack.append(self.source) # Starts the search with the source vertice
        vertice = 0 # Vertice counter
        while minCutStack: # While the DFS minCutStack is not empty
            if vertice == len(originalGraph[actual]) - 1: # If the vertice has reached the end of the graph checking of the actual vertice
                actual = minCutStack.pop(-1) # The actual vertice is the
                self.graph[actual][vertice] = -1 # Marks the edge, so it won't be visited again
                vertice = -1 # Resets the vertice counter
            elif originalGraph[actual][vertice] > 0: # If the original capacity is > 0
                if self.graph[actual][vertice] == 0: # And the final residual capacity is 0
                    self.addSTCut(actual, vertice) # Adds the edge to the self.stCut vector
                    self.graph[actual][vertice] = -1 # Marks the edge, so it won't be visited again
                elif self.graph[actual][vertice] > 0: # If the final residual capacity is > 0
                    self.graph[actual][vertice] = -1 # Marks the edge, so it won't be visited again
                    minCutStack.append(vertice) # Appends the vertice to the stack
                    actual = vertice # The actual vertice gets the vertice it goes
                    vertice = -1 # Resets the vertice counter
            vertice+=1 # Go to the next possible vertice

        for item in self.stCut:
            output.write("%d "%item)

    def findSourceAndTargetVertex(self, column):
        for line in range(len(self.incidenceMatrix)):
            if abs(self.incidenceMatrix[line][column]) == 1:
                sourceVertice = line
                self.incidenceMatrix[line][column] = 0
                break

        for line in range(len(self.incidenceMatrix)):
            if abs(self.incidenceMatrix[line][column]) == 1:
                targetVertice = line
                self.incidenceMatrix[line][column] = 0
                break

        return sourceVertice, targetVertice

    def findSTCut(self, output):
        for column in range(len(self.incidenceMatrix[0])): # Search the edge in the incidenceMatrix
            source, target = self.findSourceAndTargetVertex(column)
            if self.visited[source] == True and self.visited[target] == False:
                self.stCut[column] = 1

        for item in self.stCut:
            output.write("%d "%item)


input = open(sys.argv[1], "r")
output = open(sys.argv[2], "w")

vertex, edges, capacity, incidenceMatrix = reader.readInput(input)

fordFulkerson = Ford(capacity, incidenceMatrix)

fordFulkerson.FordFulkerson(output)

input.close()
output.close()
