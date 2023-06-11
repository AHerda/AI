import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
from sklearn.tree import plot_tree
from sklearn.ensemble import RandomForestClassifier

mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()

x_train = x_train.reshape(-1, 28 * 28) / 255.0
x_test = x_test.reshape(-1, 28 * 28) / 255.0

model = RandomForestClassifier(n_estimators=300, 
                            max_depth=3,
                            max_features='auto', 
                            min_samples_leaf=4,
                            bootstrap=True, 
                            n_jobs=-1, 
                            random_state=0)

model.fit(x_train, y_train)

pred = model.predict(x_test)

confusion_matrix = np.zeros((10, 10), dtype=int)
accuracy = 0

for i in range(len(pred)):
    if y_test[i] == pred[i]:
        accuracy += 1
    confusion_matrix[y_test[i]][pred[i]] += 1
accuracy /= len(y_test)


for i in range(10):
    print(("+" + "-" * 5) * 11 + "+")
    print("|", end="")
    for j in range(10):
        print(f"{confusion_matrix[i][j]:^5}|", end="")
    print(f"{float(confusion_matrix[i][i]) / sum(confusion_matrix[i]) * 100:^4.1f}%|")
print(("+" + "-" * 5) * 11 + "+")
print("|", end="")
for i in range(10):
    print(f"{float(confusion_matrix[i][i]) / sum([confusion_matrix[n][i] for n in range(10)]) * 100:^4.1f}%|", end="")
print(f"{accuracy * 100:^4.1f}%|")
print(("+" + "-" * 5) * 11 + "+")

fig = plt.figure(figsize=(15, 10))
plot_tree(model.estimators_[0],
          filled=True, impurity=True, 
          rounded=True)

fig.savefig('zad1.png', dpi=500)