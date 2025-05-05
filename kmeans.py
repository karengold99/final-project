import sys

ITER_DEFAULT = 300
epsilon = 0.0001
K_ERROR_MESSAGE = "Invalid number of clusters!"
ITER_ERROR_MESSAGE = "Invalid maximum iteration!"
GENERAL_ERROR = "An Error Has Occurred"

def main():
    args = sys.argv
    if len(args) < 2:
        print (GENERAL_ERROR)
        exit()
    try:
        k = int(args[1])
    except ValueError as ve:
        print (GENERAL_ERROR)
        exit()   
    iter = ITER_DEFAULT
    if (len(args) > 3):
        try:
            iter = int(args[2])
        except ValueError as ve:
            print (GENERAL_ERROR)     
            exit()
        if iter <= 1 or iter > 1000:
            print (ITER_ERROR_MESSAGE)
            exit()
        file_to_read = args[3]
    else:
        file_to_read = args[2]
    print (k, iter, file_to_read)
    vectors=get_vectors(file_to_read)
    if k<1 or k>=len(vectors):
        print (K_ERROR_MESSAGE)
        exit()
    centroids = calculate_centroids(vectors, k, iter)
    print_centroids(centroids)
    
def get_vectors(file_to_read):
    vectors=[]
    try:
        with open(file_to_read) as file:
            for line in file:
                new_vector=[]
                strings=line.rstrip().split(',')
                for s in strings:
                    new_vector.append(float(s))
                vectors.append(new_vector)
    except FileNotFoundError as err:
        print (GENERAL_ERROR)
        exit()
    return vectors

def calculate_centroids(vectors, k, iter = ITER_DEFAULT):
    centroids = set_initial_values(vectors, k)
    iter_counter=0
    while iter_counter < iter:
        vector_cluster = assign_vectors_to_clusters(vectors, centroids)
        new_centroids = calculate_new_centroids(vectors, vector_cluster, k)
        iter_counter += 1
        if calc_max_distance(centroids, new_centroids) <= epsilon:
            break
        centroids = new_centroids
    return centroids

def set_initial_values(vectors, k):
    centroids=[]
    for vector in vectors[:k]:
        cluster=[]
        for elements in vector:
            cluster.append(elements)
        centroids.append(cluster)
    return centroids

def assign_vectors_to_clusters(vectors, centroids):
    vector_cluster=[]
    for vector in vectors:
        cluster = 0
        min_dist = calc_distance(vector, centroids[0])
        for c in range(len(centroids)):
            dist = calc_distance(vector, centroids[c])
            if dist < min_dist:
                min_dist = dist
                cluster = c
        vector_cluster.append(cluster)
    return vector_cluster

def calculate_new_centroids(vectors, vector_cluster, k):
    vector_length = len(vectors[0])
    new_centroids = [[0 for i in range(vector_length)] for j in range(k)]
    cluster_counters = [0 for i in range(k)]
    for v in range(len(vectors)):
        cluster = vector_cluster[v]
        cluster_counters[cluster] += 1
        for i in range(len(vectors[v])):
            new_centroids[cluster][i] += vectors[v][i]
    for c in range(k):
        for i in range(vector_length):
            new_centroids[c][i] /= cluster_counters[c]
    return new_centroids

def print_centroids(centroids):
    for c in centroids:
        line=""
        for element in c:
            line += ("{e:.4f},").format(e=element)
        print (line[:-1])

def calc_max_distance(centroids, new_centroids):
    max_distance = 0
    for i in range(len(centroids)):
        dist = calc_distance(centroids[i], new_centroids[i])
        if dist > max_distance:
            max_distance = dist;
    return max_distance;

def calc_distance(vector1, vector2):
    sum = 0.0
    for i in range(len(vector1)):
        sum = sum + (vector1[i]-vector2[i])**2.0
    return sum**0.5

def find_min_centroid(vector, centroids):
    min_distance = sys.float_info.max
    min_centroid = -1
    for i in range(0, len(centroids)):
        distance = calc_distance(vector, centroids[i])
        if distance < min_distance:
            min_distance = distance
            min_centroid = i
    return min_centroid

if (__name__ == "__main__"):
    main()