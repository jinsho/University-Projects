import pandas as pd
import matplotlib.pyplot as plt

# Função para plotar a curva de dados
def plotar_curva(file_path, coluna_x, coluna_y):
    # Carregar os dados do CSV processado
    df = pd.read_csv(file_path)
    
    # Exibir as colunas disponíveis
    print("\nColunas disponíveis para plotagem:")
    print(df.columns.tolist())
    
    # Solicitar as colunas para o gráfico
    x = df[coluna_x]
    y = df[coluna_y]
    
    # Criando o gráfico
    plt.figure(figsize=(10, 6))
    
    # Plotando os dados como uma linha (curva vermelha)
    plt.plot(x, y, label=f'{coluna_x} vs {coluna_y}', color='red', linewidth=2)
    
    # Configurações do gráfico
    plt.title(f'Curva de {coluna_x} vs {coluna_y}')
    plt.xlabel(coluna_x)
    plt.ylabel(coluna_y)
    plt.grid(True)
    plt.legend()
    
    # Exibindo o gráfico
    plt.show()

# 2. Solicitar as colunas para plotagem
coluna_x = input("Digite o nome da coluna para o eixo X: ")
coluna_y = input("Digite o nome da coluna para o eixo Y: ")

# 3. Plotar o gráfico com as colunas especificadas
plotar_curva('processed_file.csv', coluna_x, coluna_y)