import numpy as np
import sys
import symnmfsp as nmf
import symnmf
import kmeans
from sklearn.metrics import silhouette_score

GENERAL_ERROR = "An Error Has Occurred"

def main():
    """
    Program Entry. Performs an analysis on datapoint vectors using kmeans and symNMF models
    """
    args = sys.argv
    if len(args) != 2:
        error_and_exit
    try:
        k = int(args[1])
    except ValueError as ve:
        error_and_exit
    file_name = args[2]
    datapoints = symnmf.get_datapoints(file_name)    
    np.random.seed(1234)

    # call symnmf, get optimized decomposition matrix, find the best vector array and produce a silhouette score
    nmf = symnmf.symnmf(datapoints, k)
    nmf_vectors = np.array(nmf).argmax(axis=1).tolist()
    nmf_score = silhouette_score(datapoints, nmf_vectors)
    
    # call kmeans, get centroids, find the closest centroid for each vector and produce a silhouette score
    kmeans_centroids = kmeans.calculate_centroids(datapoints, k)
    kmeans_vectors = [kmeans.find_min_centroid(vector, kmeans_centroids) for vector in datapoints]
    kmeans_score = silhouette_score(datapoints, kmeans_vectors)

    print("nmf: %.4f" % nmf_score)
    print("kmeans: %.4f" % kmeans_score)

def error_and_exit():
    print (GENERAL_ERROR)
    exit()   

if (__name__ == "__main__"):
    main()