#14.WAP a program to implement any DM concept on complex data type (image, audio, video, time series, spatial, multidimensional data)
import cv2
import numpy as np
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

image = cv2.imread('harry.jpg')
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

pixels = image.reshape(-1, 3)

k = 3

kmeans = KMeans(n_clusters=k)
kmeans.fit(pixels)
labels = kmeans.labels_
centers = kmeans.cluster_centers_

# Reshape the clustered data back to image dimensions
segmented_image = centers[labels].reshape(image.shape)

plt.subplot(121), plt.imshow(image)
plt.title('Original Image'), plt.axis('off')
plt.subplot(122), plt.imshow(segmented_image.astype(np.uint8))
plt.title('Segmented Image'), plt.axis('off')
plt.show()