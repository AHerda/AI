import tensorflow as tf
import tensorflow_decision_forests as tfdf
import numpy as np

mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()

x_train, x_test = x_train / 255.0, x_test / 255.0
x_train = np.array([x_train[i].flatten() for i in range(len(x_train))])
x_test = np.array([x_test[i].flatten() for i in range(len(x_test))])


model = tfdf.keras.RandomForestModel()
model.fit(x_train, y_train)

model.summary()

pred = model.predict(x_test)

confusion_matrix = np.zeros((10, 10), dtype=int)
accuracy = 0

results = np.zeros(10000, dtype=int)
for i in range(10000):
    max = 0 
    for j in range(10):
        if pred[i][j] > max:
            max = pred[i][j]
            results[i] = j

for i in range(len(results)):
    if y_test[i] == results[i]:
        accuracy += 1
    confusion_matrix[y_test[i]][results[i]] += 1
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
    print(f"{float(confusion_matrix[i][i]) / sum(confusion_matrix[:][i]) * 100:^4.1f}%|", end="")
print(f"{accuracy * 100:^4.1f}%|")
print("\n" + ("+" + "-" * 5) * 11 + "+")