import numpy as np
from PIL import Image
import tensorflow as tf

mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()

x_train, x_test = x_train / 255.0, x_test / 255.0

model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape = (28, 28)),
    tf.keras.layers.Dense(64, activation = "relu"),
    tf.keras.layers.Dense(32, activation  ="relu"),
    tf.keras.layers.Dense(10, activation = "softmax")
])

model.compile(optimizer = "adam", loss = "sparse_categorical_crossentropy", metrics = ["accuracy"])

model.fit(x_train, y_train, epochs = 2)



images = np.empty((40, 28, 28), dtype=np.dtype(float, 3))
labels = np.zeros(40)
for i in range(10):
    for j in range(1, 5):
        image = Image.open(f"cyferki/{i}{j}.png")
        arr = np.array([[color[0] for color in row] for row in np.asarray(image)])
        arr = abs(255 - arr) / 255.0
        images[4 * i + j - 1] = arr
        labels[4 * i + j - 1] = i

test_loss, test_accuracy = model.evaluate(images, labels)

print("+" + "-" * 17 + "+" + "-" * 17 + "+")
print(f"|{'Test loss':^17}|{'Test Accuracy':^17}|")
print("+" + "-" * 17 + "+" + "-" * 17 + "+")
print(f"|{f'{test_loss:.2f}':^17}|{f'{test_accuracy * 100:.2f} %':^17}|")
print("+" + "-" * 17 + "+" + "-" * 17 + "+")