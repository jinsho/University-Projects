import pandas as pd
from datetime import datetime

# Função para processar os dados do CSV
def process_csv(file_path):
    # Carregar o CSV, pulando a primeira linha de dados (considerada cabeçalho)
    df = pd.read_csv(file_path, header=0)  # 'header=0' garante que a primeira linha seja usada como cabeçalho
    
    # Assumindo que a coluna 'Hora' está no formato hh:mm:ss e é a coluna que precisa ser convertida para datetime
    df['Hora'] = pd.to_datetime(df['Hora'], format='%H:%M:%S')
    
    # Filtrando as linhas que atendem ao critério de tempo (1 minuto de intervalo)
    result = []
    last_time = None
    
    for i, row in df.iterrows():
        current_time = row['Hora']
        if last_time is None or (current_time - last_time).seconds >= 60:
            result.append(row)
            last_time = current_time
    
    # Criando um DataFrame com as linhas filtradas
    df_filtered = pd.DataFrame(result)
    
    # Adicionando a coluna de "minutos passados"
    start_time = df_filtered['Hora'].iloc[0]
    df_filtered['Minutos Passados'] = df_filtered['Hora'].apply(lambda x: (x - start_time).total_seconds() / 60)
    
    # Substituindo a coluna 'Hora' pelos valores de 'Minutos Passados'
    df_filtered['Hora'] = df_filtered['Minutos Passados']
    
    # Renomeando a coluna 'Hora' para 'Minutos'
    df_filtered.rename(columns={'Hora': 'Minutos'}, inplace=True)
    
    # Remover a coluna 'Minutos Passados' já que agora temos essa informação na coluna 'Minutos'
    df_filtered.drop('Minutos Passados', axis=1, inplace=True)
    
    # Corrigindo a conversão de dados: Convertendo apenas valores numéricos e mantendo os decimais
    for column in df_filtered.columns:
        # Convertendo apenas se a coluna for numérica, para não perder valores decimais
        if df_filtered[column].dtype == 'object':
            try:
                df_filtered[column] = pd.to_numeric(df_filtered[column], errors='coerce')
            except Exception:
                # Se não for possível converter para numérico, mantemos a coluna como string
                df_filtered[column] = df_filtered[column].astype(str)
    
    # Salve o DataFrame final como CSV
    df_filtered.to_csv('processed_file.csv', index=False)
    
    print("Arquivo processado e salvo como 'processed_file.csv'")
    return df_filtered

# 1. Solicitar o nome do arquivo CSV
file_path = input("Digite o caminho para o arquivo CSV (ex: 'data_battery10-12-24.csv'): ")

# Processar o CSV
processed_data = process_csv(file_path)

# Exibir as primeiras linhas do arquivo processado
print("\nPrimeiras linhas do arquivo processado:")
print(processed_data.head())
