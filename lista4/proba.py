import tensorflow as tf
from sklearn.metrics import accuracy_score, confusion_matrix
import matplotlib.pyplot as plt

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

x_train = x_train.reshape(-1, 28 * 28) / 255.0
x_test = x_test.reshape(-1, 28 * 28) / 255.0

#feature scaling
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
x_train = scaler.fit_transform(x_train)
x_test = scaler.fit_transform(x_test)

#PCA
from sklearn.decomposition import PCA
pca = PCA(n_components=2, random_state=0)
train_pca = pca.fit_transform(x_train, y_train)
test_pca = pca.fit_transform(x_test, y_test)

#PCA -> DBSCAN
from sklearn.cluster import DBSCAN
eps = 0.5
min_samples = 20
print(f"eps = {eps}, min_samples = {min_samples}")
db = DBSCAN(eps=eps, min_samples=min_samples)
db = db.fit(train_pca)
labels_db = db.labels_
clusters_db = db.fit_predict(test_pca)
n_clusters_ = len(set(clusters_db)) - (1 if -1 in clusters_db else 0)
print ("number of clusters in pca-DBSCAN: ", n_clusters_)
noise_percentage = (clusters_db == -1).sum() / len(clusters_db) * 100
print("Procent szumu:", noise_percentage)


### Evaluation Metrics
# ARI(adjusted rand index)
from sklearn.metrics.cluster import adjusted_rand_score
# y_test / clusters_km compare
print ("ARI of training set: {:.2f}".format(adjusted_rand_score(y_test, clusters_db)))


colors = ["#476A2A","#7851B8",'#BD3430','#4A2D4E','#875525',
          '#A83683','#4E655E','#853541','#3A3120','#535D8E', 'black']

fig = plt.figure(figsize=(10,10))
plt.xlim(test_pca[:,0].min(), test_pca[:,0].max())
plt.ylim(test_pca[:,1].min(), test_pca[:,1].max())
for i in range(len(y_test)):
    plt.text(test_pca[i,0], test_pca[i,1], str(y_test[i]),
             color = colors[clusters_db[i]],
             fontdict={'weight':'bold', 'size':9})
plt.title('PCA -> k-MEANS')
plt.xlabel("first PC")
plt.ylabel("second PC")
#plt.text(15, 25, str("k-MEANS time: {}".format(time()-t)),
         #bbox = dict(boxstyle='round', facecolor='wheat', alpha=0.5),
         #fontsize=9)
fig.savefig('zad2.png', dpi=500)