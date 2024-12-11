import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Função para ajustar a curva com polinômio de grau variável
def ajuste_curva_polynomial(file_path):
    # Carregar o CSV
    df = pd.read_csv(file_path)
    
    # Exibir as colunas disponíveis para o usuário
    print("Colunas disponíveis no CSV:")
    print(df.columns)
    
    # Solicitar ao usuário que escolha as colunas X e Y
    coluna_x = input("Digite o nome da coluna X: ")
    coluna_y = input("Digite o nome da coluna Y: ")
    
    # Verificar se as colunas existem
    if coluna_x not in df.columns or coluna_y not in df.columns:
        print("Uma das colunas não existe no arquivo. Por favor, verifique os nomes.")
        return
    
    # Selecionar as colunas X e Y
    x = df[coluna_x].values
    y = df[coluna_y].values
    
    # Tentativa de ajuste de polinômio para o grau ideal
    graus = list(range(1, 11))  # Testar polinômios de grau 1 a 10
    melhor_erro = float('inf')
    melhor_grau = 1
    coeficientes_ideais = None
    
    # Loop para encontrar o melhor grau para o polinômio
    for grau in graus:
        coeficientes = np.polyfit(x, y, grau)
        p = np.poly1d(coeficientes)
        y_ajustado = p(x)
        erro = np.sum((y - y_ajustado)**2)  # Erro quadrático total
        if erro < melhor_erro:
            melhor_erro = erro
            melhor_grau = grau
            coeficientes_ideais = coeficientes
    
    print(f"Melhor grau de ajuste: {melhor_grau}")
    
    # Criar a função do polinômio ajustado
    p = np.poly1d(coeficientes_ideais)
    
    # Gerar valores de Y ajustados
    y_ajustado = p(x)
    
    # Plotar o gráfico
    plt.figure(figsize=(10, 6))
    
    # Plotar os pontos reais
    #plt.scatter(x, y, color='blue', label='Dados Reais', zorder=5)
    
    # Plotar a curva ajustada
    x_valores = np.linspace(min(x), max(x), 100)
    y_valores_ajustados = p(x_valores)
    plt.plot(x_valores, y_valores_ajustados, color='red', label=f'Ajuste Polinomial (grau {melhor_grau})', zorder=4)
    
    # Títulos e labels
    plt.title(f'Ajuste de Curva entre {coluna_x} e {coluna_y}')
    plt.xlabel(coluna_x)
    plt.ylabel(coluna_y)
    plt.legend()
    plt.grid(True)
    
    # Exibir o gráfico
    plt.show()

# 1. Solicitar o caminho do arquivo CSV
file_path = input("Digite o caminho para o arquivo CSV (ex: 'data_battery10-12-24.csv'): ")

# Ajuste a curva e plote
ajuste_curva_polynomial(file_path)
