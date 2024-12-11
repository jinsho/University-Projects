import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures, StandardScaler
from sklearn.linear_model import Ridge

# Função para ajustar a curva com polinômio e regularização (Ridge)
def ajuste_curva_polynomial_regularizado(file_path):
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
    x = df[coluna_x].values.reshape(-1, 1)  # A variável X precisa ser 2D para o modelo
    y = df[coluna_y].values
    
    # Normalizar os dados (isso ajuda a melhorar o condicionamento numérico)
    scaler = StandardScaler()
    x_normalizado = scaler.fit_transform(x)
    
    # Testar diferentes graus de polinômio (de 1 a 10)
    graus = list(range(1, 11))
    melhor_erro = float('inf')
    melhor_grau = 1
    coeficientes_ideais = None
    melhor_modelo = None
    melhor_poly = None
    
    # Ajuste com polinômio e regularização Ridge
    for grau in graus:
        poly = PolynomialFeatures(degree=grau)
        x_poly = poly.fit_transform(x_normalizado)  # Transformar X em suas potências
        
        # Ajuste Ridge (regularizado), tentando diferentes valores de alpha
        modelo = Ridge(alpha=10)  # Ajuste para alpha maior
        modelo.fit(x_poly, y)
        
        # Calcular o erro
        y_ajustado = modelo.predict(x_poly)
        erro = np.sum((y - y_ajustado)**2)  # Erro quadrático total
        if erro < melhor_erro:
            melhor_erro = erro
            melhor_grau = grau
            coeficientes_ideais = modelo.coef_
            melhor_modelo = modelo
            melhor_poly = poly
    
    print(f"Melhor grau de ajuste: {melhor_grau}")
    
    # Gerar a curva ajustada com o melhor modelo
    x_valores = np.linspace(min(x), max(x), 100).reshape(-1, 1)
    x_poly_valores = melhor_poly.transform(scaler.transform(x_valores))  # Transformar e normalizar
    y_valores_ajustados = melhor_modelo.predict(x_poly_valores)
    
    # Plotar o gráfico
    plt.figure(figsize=(10, 6))
    
    #plt.scatter(x, y, color='blue', label='Dados Reais', zorder=5)
    # Plotar a curva ajustada
    plt.plot(x_valores, y_valores_ajustados, color='red', label=f'Ajuste Polinomial Regularizado (grau {melhor_grau})')
    
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
ajuste_curva_polynomial_regularizado(file_path)
