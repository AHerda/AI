import tensorflow as tf

mnist = tf.keras.datasets.mnist
(x_train, y_train), (x_test, y_test) = mnist.load_data()

x_train, x_test = x_train / 255.0, x_test / 255.0

model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(input_shape = (28, 28)),
    tf.keras.layers.Dense(16, activation = "relu"),
    tf.keras.layers.Dense(16, activation  ="relu"),
    tf.keras.layers.Dense(10, activation = "softmax")
])

model.compile(optimizer = "adam", loss = "sparse_categorical_crossentropy", metrics = ["accuracy"])

model.fit(x_train, y_train, epochs = 1)
test_loss, test_accuracy = model.evaluate(x_test, y_test)

print("+" + "-" * 17 + "+" + "-" * 17 + "+")
print(f"|{'Test loss':^17}|{'Test Accuracy':^17}|")
print("+" + "-" * 17 + "+" + "-" * 17 + "+")
print(f"|{f'{test_loss * 100:.3f}':^17}|{f'{test_accuracy * 100:.2f} %':^17}|")
print("+" + "-" * 17 + "+" + "-" * 17 + "+")