import numpy as np

def sigmoid(x):
    """Funkcja sigmoidalna"""
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    """Pochodna funkcji sigmoidalnej"""
    return x * (1 - x)

def neural_network(input_data, weights_hidden, weights_output):
    """Dwuwarstwowa sieć neuronowa"""
    # Przekształć wejście do macierzy kolumnowej
    X = np.array(input_data, ndmin=2).T
    
    # Oblicz wartości w warstwie ukrytej
    hidden_input = np.dot(weights_hidden, X)
    hidden_output = sigmoid(hidden_input)
    
    # Oblicz wartość w warstwie wyjściowej
    output_input = np.dot(weights_output, hidden_output)
    output = sigmoid(output_input)
    
    return output

def backpropagation(input_data, target, weights_hidden, weights_output, learning_rate, epochs):
    """Algorytm propagacji wstecznej"""
    X = np.array(input_data, ndmin=2).T
    y = np.array(target, ndmin=2).T

    print("+" + "=" * 10 + "+" + "=" * 10 + "+")
    print(f"|{'Epoch':^10}|{'Accuracy':^10}|")
    print("+" + "=" * 10 + "+" + "=" * 10 + "+")
    
    for epoch in range(epochs):
        # Przekształć dane przez sieć neuronową
        hidden_input = np.dot(weights_hidden, X)
        hidden_output = sigmoid(hidden_input)
        output_input = np.dot(weights_output, hidden_output)
        output = sigmoid(output_input)
        
        # Oblicz błąd dla warstwy wyjściowej
        output_error = y - output
        output_delta = output_error * sigmoid_derivative(output)
        
        # Oblicz błąd dla warstwy ukrytej
        hidden_error = np.dot(weights_output.T, output_delta)
        hidden_delta = hidden_error * sigmoid_derivative(hidden_output)
        
        # Zaktualizuj wagi dla warstwy wyjściowej
        weights_output += learning_rate * np.dot(output_delta, hidden_output.T)
        
        # Zaktualizuj wagi dla warstwy ukrytej
        weights_hidden += learning_rate * np.dot(hidden_delta, X.T)

        accuracy = 0
        for i in range(len(target)):
            if target[i] == int(output.flatten()[i]):
                accuracy += 1
        accuracy /= 1000

        print(f"|{epoch + 1:^10}|{accuracy:^10.2f}|")
        print("+" + "-" * 10 + "+" + "-" * 10 + "+")
    
    return weights_hidden, weights_output

# Dane wejściowe
input_data = (2 * np.random.random_sample((1000, 2)) - 1)
input_data[input_data == 0] = 1
input_data_l1 = input_data / np.linalg.norm(input_data, ord=1)
input_data_l2 = input_data / np.linalg.norm(input_data, ord=2)

target = np.zeros((1000, 1), dtype=int)
for i in range((1000)):
    if input_data[i][0] * input_data[i][1] > 0:
        target[i] = 1
input_data[input_data == 0] = 1

# Inicjalizacja wag
weights_hidden = 2 * np.random.random((4, 2)) - 1
weights_output = 2 * np.random.random((1, 4)) - 1

# Parametry uczenia
learning_rate = 0.2
epochs = 100

# Uczenie sieci neuronowej
weights_hidden, weights_output = backpropagation(input_data, target, weights_hidden, weights_output, learning_rate, epochs)

# Testowanie sieci neuronowej
output = neural_network(input_data, weights_hidden, weights_output)
output = np.round(output)
print("Wynik:", output.flatten())
print(target.reshape(-1))

accuracy = 0
for i in range(len(target)):
    if target[i] == int(output.flatten()[i]):
        accuracy += 1
accuracy /= 1000

print(accuracy)
